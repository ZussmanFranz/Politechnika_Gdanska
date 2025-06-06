import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from pathlib import Path

# --- CONFIGURATION ---
DATA_DIR = Path("./2018_paths")
PLOTS_DIR = Path("./plots")
PLOTS_DIR.mkdir(exist_ok=True)
SHOW_PLOTS = True

# Hyperparameters
DENSE_POINTS = 400
NODE_COUNTS_BASIC = [5, 10, 20, 40, 80, 160]
NODE_COUNTS_CHEBYSHEV = [5, 10, 20, 40]

# Datasets
DATASETS = {
    "GdanskPromenade": DATA_DIR / "SpacerniakGdansk.csv",
    "MountEverest": DATA_DIR / "MountEverest.csv",
    "VariousHills": DATA_DIR / "rozne_wniesienia.txt",
    "Chelm": DATA_DIR / "chelm.txt",
    "ChallengerDeep": DATA_DIR / "GlebiaChallengera.csv",
}
BASIC_ROUTES = ["GdanskPromenade", "MountEverest"]
CHEBYSHEV_ROUTE = "VariousHills"

# --- DATA LOADING ---
def load_profile(filepath):
    """Load distance/elevation profile from file."""
    filepath = Path(filepath)
    try:
        if filepath.suffix == ".csv":
            try:
                df = pd.read_csv(filepath, header="infer")
            except pd.errors.ParserError:
                df = pd.read_csv(filepath, header=None)
        elif filepath.suffix in [".txt", ".data"]:
            try:
                df = pd.read_csv(filepath, header=None, delimiter=",")
            except pd.errors.ParserError:
                df = pd.read_csv(filepath, header=None, delimiter=r"\s+")
        else:
            print(f"Unsupported file type: {filepath.suffix}")
            return None, None
        df = df.iloc[:, :2]
        df.columns = ["distance", "elevation"]
        df = df.dropna()
        df["distance"] = pd.to_numeric(df["distance"], errors="coerce")
        df["elevation"] = pd.to_numeric(df["elevation"], errors="coerce")
        df = df.dropna().sort_values(by="distance").reset_index(drop=True)
        return df["distance"].values, df["elevation"].values
    except Exception as e:
        print(f"Error loading {filepath}: {e}")
        return None, None

# --- SCALING HELPERS ---
def scale_to_unit(x):
    xmin, xmax = np.min(x), np.max(x)
    if xmax == xmin:
        return np.zeros_like(x), xmin, xmax
    return (x - xmin) / (xmax - xmin), xmin, xmax

def scale_from_unit(x_scaled, xmin, xmax):
    if xmax == xmin:
        return np.full_like(x_scaled, xmin)
    return x_scaled * (xmax - xmin) + xmin

# --- LAGRANGE INTERPOLATION ---
def lagrange_eval(x_nodes, y_nodes, x):
    k = len(x_nodes)
    if k == 0:
        return np.nan
    if k == 1:
        return y_nodes[0]
    result = 0.0
    for j in range(k):
        num = 1.0
        denom = 1.0
        for m in range(k):
            if m == j:
                continue
            num *= x - x_nodes[m]
            denom *= x_nodes[j] - x_nodes[m]
        if denom == 0:
            return np.nan
        result += y_nodes[j] * (num / denom)
    return result

def lagrange_interpolate(x_nodes, y_nodes, x_dense):
    unique_x, unique_idx = np.unique(x_nodes, return_index=True)
    x_nodes, y_nodes = unique_x, y_nodes[unique_idx]
    if len(x_nodes) < 1:
        return np.full_like(x_dense, np.nan, dtype=float)
    if len(x_nodes) == 1:
        return np.full_like(x_dense, y_nodes[0], dtype=float)
    x_nodes_scaled, xmin, xmax = scale_to_unit(x_nodes)
    x_dense_scaled = (x_dense - xmin) / (xmax - xmin) if xmax != xmin else np.zeros_like(x_dense)
    return np.array([lagrange_eval(x_nodes_scaled, y_nodes, x) for x in x_dense_scaled])

# --- CUBIC SPLINE INTERPOLATION ---
def natural_cubic_spline(x_nodes, y_nodes, x_eval):
    k = len(x_nodes)
    if k < 2:
        return np.full_like(x_eval, y_nodes[0] if k == 1 else np.nan, dtype=float)
    h = np.diff(x_nodes)
    if np.any(h <= 0):
        return np.full_like(x_eval, np.nan, dtype=float)
    # Build system
    if k == 3:
        rhs = 6 * ((y_nodes[2] - y_nodes[1]) / h[1] - (y_nodes[1] - y_nodes[0]) / h[0])
        diag = 2 * (h[0] + h[1])
        M_internal = np.array([rhs / diag]) if diag != 0 else np.array([0.0])
    elif k > 3:
        n = k - 2
        A = np.zeros((n, n))
        b = np.zeros(n)
        for i in range(n):
            A[i, i] = 2 * (h[i] + h[i + 1])
            b[i] = 6 * ((y_nodes[i + 2] - y_nodes[i + 1]) / h[i + 1] - (y_nodes[i + 1] - y_nodes[i]) / h[i])
            if i > 0:
                A[i, i - 1] = h[i]
            if i < n - 1:
                A[i, i + 1] = h[i + 1]
        try:
            M_internal = np.linalg.solve(A, b)
        except np.linalg.LinAlgError:
            M_internal = np.linalg.pinv(A) @ b
    else:
        M_internal = np.array([])
    M = np.zeros(k)
    if k > 2:
        M[1:k-1] = M_internal
    a, b_coef, c, d = (np.zeros(k - 1) for _ in range(4))
    for i in range(k - 1):
        a[i] = y_nodes[i]
        c[i] = M[i] / 2.0
        d[i] = (M[i + 1] - M[i]) / (6 * h[i])
        b_coef[i] = (y_nodes[i + 1] - y_nodes[i]) / h[i] - (h[i] / 6.0) * (2 * M[i] + M[i + 1])
    y_interp = np.zeros_like(x_eval, dtype=float)
    for idx, x in enumerate(x_eval):
        if x < x_nodes[0]:
            y_interp[idx] = y_nodes[0] + b_coef[0] * (x - x_nodes[0])
            continue
        if x > x_nodes[-1]:
            slope = b_coef[-1] + 2 * c[-1] * h[-1] + 3 * d[-1] * h[-1] ** 2
            y_interp[idx] = y_nodes[-1] + slope * (x - x_nodes[-1])
            continue
        seg = np.searchsorted(x_nodes, x, side="right") - 1
        seg = np.clip(seg, 0, k - 2)
        dx = x - x_nodes[seg]
        y_interp[idx] = a[seg] + b_coef[seg] * dx + c[seg] * dx ** 2 + d[seg] * dx ** 3
    return y_interp

def cubic_spline_interpolate(x_nodes, y_nodes, x_dense):
    if len(x_nodes) < 2:
        return np.full_like(x_dense, y_nodes[0] if len(x_nodes) == 1 else np.nan, dtype=float)
    idx = np.argsort(x_nodes)
    x_nodes, y_nodes = x_nodes[idx], y_nodes[idx]
    unique_x, unique_idx = np.unique(x_nodes, return_index=True)
    x_nodes, y_nodes = unique_x, y_nodes[unique_idx]
    if len(x_nodes) < 2:
        return np.full_like(x_dense, y_nodes[0] if len(x_nodes) == 1 else np.nan, dtype=float)
    return natural_cubic_spline(x_nodes, y_nodes, x_dense)

# --- CHEBYSHEV NODES ---
def chebyshev_nodes(n, a, b):
    if n <= 0:
        return np.array([])
    if n == 1:
        return np.array([(a + b) / 2])
    i = np.arange(1, n + 1)
    x_cheb = np.cos((2 * i - 1) * np.pi / (2 * n))
    return np.sort((b - a) / 2 * x_cheb + (a + b) / 2)

def chebyshev_indices(x, n):
    if n <= 0:
        return np.array([], dtype=int)
    if n >= len(x):
        return np.arange(len(x))
    a, b = np.min(x), np.max(x)
    cheb_x = chebyshev_nodes(n, a, b)
    idx = [np.argmin(np.abs(x - cx)) for cx in cheb_x]
    return np.unique(idx)

# --- PLOTTING ---
def plot_interpolations(plot_data, title, filename, cols=2):
    n_plots = len(plot_data)
    if n_plots == 0:
        print(f"No data to plot for {title}")
        return
    rows = (n_plots + cols - 1) // cols
    fig, axes = plt.subplots(rows, cols, figsize=(8 * cols, 5.5 * rows), squeeze=False)
    axes = axes.flatten()
    for i, data in enumerate(plot_data):
        ax = axes[i]
        ax.plot(data["x_orig"], data["y_orig"], "k-", alpha=0.3, label="Original")
        if data["y_interp"] is not None and not np.all(np.isnan(data["y_interp"])):
            ax.plot(data["x_dense"], data["y_interp"], "b-", label="Interpolation")
        ax.plot(data["x_nodes"], data["y_nodes"], "ro", markersize=5, label=f"Nodes ({len(data['x_nodes'])})")
        ax.set_xlabel("Distance")
        ax.set_ylabel("Elevation")
        ax.set_title(data["subplot_title"])
        ax.legend(fontsize="small")
        ax.grid(True)
    for j in range(i + 1, len(axes)):
        fig.delaxes(axes[j])
    fig.suptitle(title, fontsize=16)
    plt.tight_layout(rect=(0, 0, 1, 0.96))
    plt.savefig(filename)
    print(f"Saved plot: {filename}")
    if SHOW_PLOTS:
        plt.show()
    plt.close(fig)

# --- MAIN ANALYSIS ---
def main():
    print("--- ANALYSIS STARTED (custom implementations, subplots) ---")
    print("\n--- BASIC ANALYSIS ---")
    for route in BASIC_ROUTES:
        if route not in DATASETS:
            print(f"Dataset for '{route}' not found. Skipping.")
            continue
        print(f"\nProcessing route: {route}")
        x, y = load_profile(DATASETS[route])
        if x is None or len(x) < 2:
            print(f"No data or not enough data for {route}. Skipping.")
            continue
        x = np.asarray(x)
        x_dense = np.linspace(np.min(x), np.max(x), DENSE_POINTS)
        # Lagrange
        lagrange_plots = []
        for n_nodes in NODE_COUNTS_BASIC:
            if n_nodes > len(x) or n_nodes < 1:
                continue
            node_idx = np.linspace(0, len(x) - 1, n_nodes, dtype=int)
            x_nodes, y_nodes = x[node_idx], y[node_idx]
            y_interp = lagrange_interpolate(x_nodes, y_nodes, x_dense)
            lagrange_plots.append({
                "x_orig": x,
                "y_orig": y,
                "x_nodes": x_nodes,
                "y_nodes": y_nodes,
                "x_dense": x_dense,
                "y_interp": y_interp,
                "subplot_title": f"Nodes: {len(x_nodes)}",
            })
        if lagrange_plots:
            plot_interpolations(
                lagrange_plots,
                f"Lagrange Interpolation (custom) for: {route}",
                PLOTS_DIR / f"{route}_Lagrange_basic.png"
            )
        # Spline
        spline_plots = []
        for n_nodes in NODE_COUNTS_BASIC:
            if n_nodes > len(x) or n_nodes < 2:
                continue
            node_idx = np.linspace(0, len(x) - 1, n_nodes, dtype=int)
            x_nodes, y_nodes = x[node_idx], y[node_idx]
            y_interp = cubic_spline_interpolate(x_nodes, y_nodes, x_dense)
            spline_plots.append({
                "x_orig": x,
                "y_orig": y,
                "x_nodes": x_nodes,
                "y_nodes": y_nodes,
                "x_dense": x_dense,
                "y_interp": y_interp,
                "subplot_title": f"Nodes: {len(x_nodes)}",
            })
        if spline_plots:
            plot_interpolations(
                spline_plots,
                f"Natural Spline Interpolation (custom) for: {route}",
                PLOTS_DIR / f"{route}_Spline_basic.png"
            )
    print("\n--- CHEBYSHEV NODE ANALYSIS ---")
    print(f"Chebyshev node placement for: {CHEBYSHEV_ROUTE} - Lagrange Interpolation (2x2)")
    if CHEBYSHEV_ROUTE not in DATASETS:
        print(f"Dataset for '{CHEBYSHEV_ROUTE}' not found. Skipping.")
        return
    x, y = load_profile(DATASETS[CHEBYSHEV_ROUTE])
    if x is None or y is None or len(x) < 2:
        print(f"No data or not enough data for {CHEBYSHEV_ROUTE}. Skipping.")
        return
    x = np.asarray(x)
    x_dense = np.linspace(np.min(x), np.max(x), DENSE_POINTS)
    cheb_plots = []
    for n_nodes in NODE_COUNTS_CHEBYSHEV:
        if n_nodes > len(x):
            print(f"Requested nodes ({n_nodes}) exceed available points ({len(x)}). Skipping.")
            continue
        if n_nodes < 1:
            print(f"Requested nodes ({n_nodes}) too small. Skipping.")
            continue
        idx = chebyshev_indices(x, n_nodes)
        if len(idx) < 1:
            print(f"Could not select enough unique Chebyshev nodes ({len(idx)} for requested {n_nodes}). Skipping.")
            continue
        x_nodes, y_nodes = x[idx], y[idx]
        y_interp = lagrange_interpolate(x_nodes, y_nodes, x_dense)
        cheb_plots.append({
            "x_orig": x,
            "y_orig": y,
            "x_nodes": x_nodes,
            "y_nodes": y_nodes,
            "x_dense": x_dense,
            "y_interp": y_interp,
            "subplot_title": f"Chebyshev nodes: {len(x_nodes)} (requested {n_nodes})",
        })
    if cheb_plots:
        plot_interpolations(
            cheb_plots,
            f"Lagrange Interpolation (Chebyshev nodes) for: {CHEBYSHEV_ROUTE} (2x2)",
            PLOTS_DIR / f"{CHEBYSHEV_ROUTE}_Lagrange_Chebyshev_2x2.png",
            cols=2
        )
        if len(cheb_plots) < len(NODE_COUNTS_CHEBYSHEV):
            print(f"Warning: Only {len(cheb_plots)} of {len(NODE_COUNTS_CHEBYSHEV)} expected plots generated for {CHEBYSHEV_ROUTE} (Lagrange-Chebyshev).")
    else:
        print(f"No data to generate Lagrange-Chebyshev plot for {CHEBYSHEV_ROUTE}.")
    print("\n--- ANALYSIS COMPLETE ---")
    print(f"Plots saved in: {PLOTS_DIR.resolve()}")
    if SHOW_PLOTS:
        print("Interactive plots displayed. Close the plot window to continue.")

if __name__ == "__main__":
    main()

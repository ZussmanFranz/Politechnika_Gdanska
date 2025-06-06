import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from pathlib import Path


BASE_DATA_PATH = Path("./2018_paths")
OUTPUT_PLOT_DIR = Path("./plots_zad3")
OUTPUT_PLOT_DIR.mkdir(exist_ok=True)
INTERACTIVE_PLOTS = True


def load_profile_data(filepath):
    filepath = Path(filepath)
    try:
        if filepath.suffix == ".csv":
            try:
                df = pd.read_csv(filepath, header="infer")
            except pd.errors.ParserError:
                try:
                    df = pd.read_csv(filepath, header=None)
                except pd.errors.ParserError:
                    df = pd.read_csv(filepath, header=None, delimiter=r"\s+")
        elif filepath.suffix == ".txt" or filepath.suffix == ".data":
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
        df = df.dropna()
        df = df.sort_values(by="distance").reset_index(drop=True)
        return df["distance"].values, df["elevation"].values
    except Exception as e:
        print(f"Error loading {filepath}: {e}")
        return None, None


def scale_to_01(x):
    xmin, xmax = np.min(x), np.max(x)
    if xmax == xmin:
        return np.zeros_like(x), xmin, xmax
    return (x - xmin) / (xmax - xmin), xmin, xmax


def scale_from_01(x_scaled, xmin, xmax):
    if xmax == xmin:
        return np.full_like(x_scaled, xmin)
    return x_scaled * (xmax - xmin) + xmin


def custom_lagrange_interpolation_eval(x_nodes, y_nodes, x_eval_point):
    k = len(x_nodes)
    if k == 0:
        return np.nan
    if k == 1:
        return y_nodes[0]
    total_sum = 0.0
    for j in range(k):
        numerator = 1.0
        denominator = 1.0
        for m in range(k):
            if m == j:
                continue
            numerator *= x_eval_point - x_nodes[m]
            denominator *= x_nodes[j] - x_nodes[m]
        if denominator == 0:
            return np.nan
        total_sum += y_nodes[j] * (numerator / denominator)
    return total_sum


def lagrange_interpolation_scaled_custom(x_nodes, y_nodes, x_dense):
    unique_x, unique_indices = np.unique(x_nodes, return_index=True)
    x_nodes_proc, y_nodes_proc = unique_x, y_nodes[unique_indices]
    if len(x_nodes_proc) < 1:
        return np.full_like(x_dense, np.nan, dtype=float)
    if len(x_nodes_proc) == 1:
        return np.full_like(x_dense, y_nodes_proc[0], dtype=float)

    x_nodes_scaled, x_min_orig, x_max_orig = scale_to_01(x_nodes_proc)
    if x_max_orig == x_min_orig:
        return np.full_like(x_dense, np.mean(y_nodes_proc), dtype=float)
    x_dense_scaled = (x_dense - x_min_orig) / (x_max_orig - x_min_orig)

    y_interp_values = np.array(
        [
            custom_lagrange_interpolation_eval(x_nodes_scaled, y_nodes_proc, x_d_s)
            for x_d_s in x_dense_scaled
        ]
    )
    return y_interp_values


def custom_natural_cubic_spline(x_nodes, y_nodes, x_eval_points):
    k = len(x_nodes)
    if k < 2:
        if k == 1:
            return np.full_like(x_eval_points, y_nodes[0], dtype=float)
        return np.full_like(x_eval_points, np.nan, dtype=float)
    if k == 2:
        h0 = x_nodes[1] - x_nodes[0]
        if h0 == 0:
            return np.full_like(x_eval_points, y_nodes[0], dtype=float)
        slope = (y_nodes[1] - y_nodes[0]) / h0
        return y_nodes[0] + slope * (x_eval_points - x_nodes[0])

    h = np.diff(x_nodes)
    if np.any(h <= 0):
        return np.full_like(x_eval_points, np.nan, dtype=float)

    if k == 3:
        rhs_val = 6 * (
            (y_nodes[2] - y_nodes[1]) / h[1] - (y_nodes[1] - y_nodes[0]) / h[0]
        )
        diag_val = 2 * (h[0] + h[1])
        M_internal = (
            np.array([rhs_val / diag_val]) if diag_val != 0 else np.array([0.0])
        )
    elif k > 3:
        num_unknowns = k - 2
        A_matrix = np.zeros((num_unknowns, num_unknowns))
        b_system_rhs = np.zeros(num_unknowns)
        for i in range(num_unknowns):
            A_matrix[i, i] = 2 * (h[i] + h[i + 1])
            term1 = (y_nodes[i + 2] - y_nodes[i + 1]) / h[i + 1]
            term2 = (y_nodes[i + 1] - y_nodes[i]) / h[i]
            b_system_rhs[i] = 6 * (term1 - term2)
            if i > 0:
                A_matrix[i, i - 1] = h[i]
            if i < num_unknowns - 1:
                A_matrix[i, i + 1] = h[i + 1]
        try:
            M_internal = np.linalg.solve(A_matrix, b_system_rhs)
        except np.linalg.LinAlgError:
            try:
                M_internal = np.linalg.pinv(A_matrix) @ b_system_rhs
            except np.linalg.LinAlgError:
                return np.full_like(x_eval_points, np.nan, dtype=float)
    else:
        M_internal = np.array([])

    M_coeffs = np.zeros(k)
    if k > 2:
        M_coeffs[1 : k - 1] = M_internal

    a, b, c, d = (np.zeros(k - 1) for _ in range(4))
    for i in range(k - 1):
        a[i] = y_nodes[i]
        c[i] = M_coeffs[i] / 2.0
        d[i] = (M_coeffs[i + 1] - M_coeffs[i]) / (6 * h[i])
        b[i] = (y_nodes[i + 1] - y_nodes[i]) / h[i] - (h[i] / 6.0) * (
            2 * M_coeffs[i] + M_coeffs[i + 1]
        )

    y_interp = np.zeros_like(x_eval_points, dtype=float)
    for eval_idx, x_e in enumerate(x_eval_points):
        if x_e < x_nodes[0]:
            slope_at_start = b[0]
            y_interp[eval_idx] = y_nodes[0] + slope_at_start * (x_e - x_nodes[0])
            continue
        elif x_e > x_nodes[k - 1]:
            slope_at_end = (
                b[k - 2] + 2 * c[k - 2] * h[k - 2] + 3 * d[k - 2] * h[k - 2] ** 2
            )
            y_interp[eval_idx] = y_nodes[k - 1] + slope_at_end * (x_e - x_nodes[k - 1])
            continue
        seg_idx = np.searchsorted(x_nodes, x_e, side="right") - 1
        seg_idx = np.clip(seg_idx, 0, k - 2)
        dx = x_e - x_nodes[seg_idx]
        y_interp[eval_idx] = (
            a[seg_idx] + b[seg_idx] * dx + c[seg_idx] * dx**2 + d[seg_idx] * dx**3
        )
    return y_interp


def cubic_spline_interpolation_custom(x_nodes, y_nodes, x_dense):
    if len(x_nodes) < 2:
        if len(x_nodes) == 1:
            return np.full_like(x_dense, y_nodes[0], dtype=float)
        return np.full_like(x_dense, np.nan, dtype=float)
    sorted_indices = np.argsort(x_nodes)
    x_nodes_sorted, y_nodes_sorted = x_nodes[sorted_indices], y_nodes[sorted_indices]
    unique_x, unique_indices = np.unique(x_nodes_sorted, return_index=True)
    x_nodes_proc, y_nodes_proc = unique_x, y_nodes_sorted[unique_indices]
    if len(x_nodes_proc) < 2:
        if len(x_nodes_proc) == 1:
            return np.full_like(x_dense, y_nodes_proc[0], dtype=float)
        return np.full_like(x_dense, np.nan, dtype=float)
    return custom_natural_cubic_spline(x_nodes_proc, y_nodes_proc, x_dense)


def plot_interpolations_subplots(
    all_plot_data, main_title, figure_filename, num_cols=2
):
    num_plots = len(all_plot_data)
    if num_plots == 0:
        print(f"No data to plot for {main_title}")
        return

    num_rows = (num_plots + num_cols - 1) // num_cols
    fig, axes = plt.subplots(
        num_rows, num_cols, figsize=(8 * num_cols, 6 * num_rows), squeeze=False
    )
    axes_flat = axes.flatten()

    i = -1  # Ensure 'i' is always defined
    for i, data in enumerate(all_plot_data):
        ax = axes_flat[i]
        ax.plot(
            data["x_orig"], data["y_orig"], "k-", alpha=0.3, label="Oryginalne dane"
        )
        if data["y_interp"] is not None and not np.all(np.isnan(data["y_interp"])):
            ax.plot(data["x_dense"], data["y_interp"], "b-", label="Interpolacja")
        ax.plot(
            data["x_nodes"],
            data["y_nodes"],
            "ro",
            markersize=5,
            label=f"Węzły ({len(data['x_nodes'])})",
        )

        ax.set_xlabel("Odległość")
        ax.set_ylabel("Wysokość")
        ax.set_title(data["subplot_title"])
        ax.legend(fontsize="small")
        ax.grid(True)

    for j in range(i + 1, len(axes_flat)):
        fig.delaxes(axes_flat[j])

    fig.suptitle(main_title, fontsize=16)
    plt.tight_layout(rect=(0, 0, 1, 0.96))

    plt.savefig(figure_filename)
    print(f"Saved consolidated plot: {figure_filename}")
    if INTERACTIVE_PLOTS:
        plt.show()
    plt.close(fig)


def generate_chebyshev_nodes(n, a, b):
    """
    Generate n Chebyshev nodes in the interval [a, b].
    Chebyshev nodes are the roots of the Chebyshev polynomial of the first kind.
    They minimize interpolation error for polynomial interpolation.

    Args:
        n: Number of nodes to generate
        a: Left endpoint of interval
        b: Right endpoint of interval

    Returns:
        Array of n Chebyshev nodes in [a, b]
    """
    if n <= 0:
        return np.array([])
    if n == 1:
        return np.array([(a + b) / 2])

    i = np.arange(1, n + 1)
    x_cheb = np.cos((2 * i - 1) * np.pi / (2 * n))

    x_cheb_transformed = (b - a) / 2 * x_cheb + (a + b) / 2

    return np.sort(x_cheb_transformed)


def select_chebyshev_indices(x_original, n_nodes):
    """
    Select indices from x_original that correspond to Chebyshev node positions.

    Args:
        x_original: Original x data points
        n_nodes: Number of nodes to select

    Returns:
        Array of indices corresponding to Chebyshev-like distribution
    """
    if n_nodes <= 0:
        return np.array([], dtype=int)
    if n_nodes >= len(x_original):
        return np.arange(len(x_original))

    x_min, x_max = np.min(x_original), np.max(x_original)
    cheb_nodes = generate_chebyshev_nodes(n_nodes, x_min, x_max)

    indices = []
    for cheb_x in cheb_nodes:
        closest_idx = np.argmin(np.abs(x_original - cheb_x))
        indices.append(closest_idx)

    indices = np.unique(np.array(indices))
    return indices


datasets = {
    "SpacerniakGdansk": BASE_DATA_PATH / "SpacerniakGdansk.csv",
    "MountEverest": BASE_DATA_PATH / "MountEverest.csv",
    "rozne_wzniesienia": BASE_DATA_PATH / "rozne_wniesienia.txt",
    "Chelm": BASE_DATA_PATH / "chelm.txt",
    "GlebiaChallengera": BASE_DATA_PATH / "GlebiaChallengera.csv",
}
routes_for_basic_analysis = ["SpacerniakGdansk", "MountEverest"]
route_for_additional_analysis = "rozne_wzniesienia"


node_counts_basic = [4, 8, 16, 32, 64, 128]


NUM_DENSE_POINTS = 300

print("--- ROZPOCZĘCIE ANALIZY (implementacje własne, subplots) ---")


print("\n--- ANALIZA PODSTAWOWA ---")
for route_name in routes_for_basic_analysis:
    if route_name not in datasets:
        print(f"Dataset for '{route_name}' not found. Skipping.")
        continue

    print(f"\nProcessing route: {route_name}")
    x_original, y_original = load_profile_data(datasets[route_name])

    if x_original is None or len(x_original) < 2:
        print(
            f"No data/not enough data for {route_name}. Skipping basic analysis for this route."
        )
        continue

    x_original_np = np.asarray(x_original)
    x_dense = np.linspace(
        np.min(x_original_np), np.max(x_original_np), NUM_DENSE_POINTS
    )

    lagrange_plot_data_for_route = []
    for n_nodes in node_counts_basic:
        if n_nodes > len(x_original) or n_nodes < 1:
            continue

        node_indices = np.linspace(0, len(x_original) - 1, n_nodes, dtype=int)
        x_nodes = x_original[node_indices]
        if y_original is None:
            continue
        y_nodes = y_original[node_indices]

        y_interp_lagrange = lagrange_interpolation_scaled_custom(
            x_nodes, y_nodes, x_dense
        )

        lagrange_plot_data_for_route.append(
            {
                "x_orig": x_original,
                "y_orig": y_original,
                "x_nodes": x_nodes,
                "y_nodes": y_nodes,
                "x_dense": x_dense,
                "y_interp": y_interp_lagrange,
                "subplot_title": f"Węzły: {len(x_nodes)}",
            }
        )

    if lagrange_plot_data_for_route:
        main_title_lagrange = f"Interpolacja Lagrange'a (własna) dla: {route_name}"
        filename_lagrange = (
            OUTPUT_PLOT_DIR / f"{route_name}_Lagrange_basic_subplots.png"
        )
        plot_interpolations_subplots(
            lagrange_plot_data_for_route, main_title_lagrange, filename_lagrange
        )

    spline_plot_data_for_route = []
    for n_nodes in node_counts_basic:
        if n_nodes > len(x_original) or n_nodes < 2:
            continue

        node_indices = np.linspace(0, len(x_original) - 1, n_nodes, dtype=int)
        x_nodes = x_original[node_indices]
        if y_original is None:
            continue
        y_nodes = y_original[node_indices]

        y_interp_spline = cubic_spline_interpolation_custom(x_nodes, y_nodes, x_dense)

        spline_plot_data_for_route.append(
            {
                "x_orig": x_original,
                "y_orig": y_original,
                "x_nodes": x_nodes,
                "y_nodes": y_nodes,
                "x_dense": x_dense,
                "y_interp": y_interp_spline,
                "subplot_title": f"Węzły: {len(x_nodes)}",
            }
        )

    if spline_plot_data_for_route:
        main_title_spline = f"Interpolacja Spline (własna, nat.) dla: {route_name}"
        filename_spline = OUTPUT_PLOT_DIR / f"{route_name}_Spline_basic_subplots.png"
        plot_interpolations_subplots(
            spline_plot_data_for_route, main_title_spline, filename_spline
        )


print("\\n--- ANALIZA DODATKOWA ---")
print(
    f"Analiza wpływu rozmieszczenia węzłów (Chebyshev) dla trasy: {route_for_additional_analysis} - Interpolacja Lagrange'a (2x2)"
)


node_counts_chebyshev_lagrange = [4, 8, 16, 32]

if route_for_additional_analysis not in datasets:
    print(
        f"Dataset for '{route_for_additional_analysis}' not found. Skipping dodatkową analizę."
    )
else:
    x_original_add, y_original_add = load_profile_data(
        datasets[route_for_additional_analysis]
    )

    if x_original_add is None or y_original_add is None or len(x_original_add) < 2:
        print(
            f"Brak danych/niewystarczająca ilość danych (potrzebne co najmniej 2 punkty) dla {route_for_additional_analysis}. Pomijanie dodatkowej analizy."
        )
    else:
        x_original_add_np = np.asarray(x_original_add)
        x_dense_add = np.linspace(
            np.min(x_original_add_np), np.max(x_original_add_np), NUM_DENSE_POINTS
        )

        lagrange_chebyshev_plot_data = []
        for n_nodes_requested in node_counts_chebyshev_lagrange:
            if n_nodes_requested > len(x_original_add):
                print(
                    f"Żądana liczba węzłów ({n_nodes_requested}) przekracza liczbę dostępnych punktów ({len(x_original_add)}) dla {route_for_additional_analysis} (Chebyshev). Pomijanie."
                )
                continue
            if n_nodes_requested < 1:
                print(
                    f"Żądana liczba węzłów ({n_nodes_requested}) jest zbyt mała. Pomijanie."
                )
                continue

            chebyshev_node_indices = select_chebyshev_indices(
                x_original_add, n_nodes_requested
            )

            if len(chebyshev_node_indices) < 1:
                print(
                    f"Nie udało się wybrać wystarczającej liczby unikalnych węzłów Chebyshev ({len(chebyshev_node_indices)} wybranych dla żądanych {n_nodes_requested}) dla {route_for_additional_analysis}. Pomijanie."
                )
                continue

            x_nodes_cheb = x_original_add[chebyshev_node_indices]
            y_nodes_cheb = y_original_add[chebyshev_node_indices]

            y_interp_lagrange_cheb = lagrange_interpolation_scaled_custom(
                x_nodes_cheb, y_nodes_cheb, x_dense_add
            )

            lagrange_chebyshev_plot_data.append(
                {
                    "x_orig": x_original_add,
                    "y_orig": y_original_add,
                    "x_nodes": x_nodes_cheb,
                    "y_nodes": y_nodes_cheb,
                    "x_dense": x_dense_add,
                    "y_interp": y_interp_lagrange_cheb,
                    "subplot_title": f"Węzły Chebyshev: {len(x_nodes_cheb)} (żądano {n_nodes_requested})",
                }
            )

        if lagrange_chebyshev_plot_data:
            main_title_lagrange_cheb = f"Interpolacja Lagrange'a (węzły Chebyshev) dla: {route_for_additional_analysis} (Układ docelowy 2x2)"
            filename_lagrange_cheb = (
                OUTPUT_PLOT_DIR
                / f"{route_for_additional_analysis}_Lagrange_Chebyshev_2x2_subplots.png"
            )
            plot_interpolations_subplots(
                lagrange_chebyshev_plot_data,
                main_title_lagrange_cheb,
                filename_lagrange_cheb,
                num_cols=2,
            )
            if len(lagrange_chebyshev_plot_data) < len(node_counts_chebyshev_lagrange):
                print(
                    f"Uwaga: Wygenerowano tylko {len(lagrange_chebyshev_plot_data)} z {len(node_counts_chebyshev_lagrange)} oczekiwanych wykresów dla {route_for_additional_analysis} (Lagrange-Chebyshev)."
                )
        else:
            print(
                f"Brak danych do wygenerowania wykresu Lagrange-Chebyshev dla {route_for_additional_analysis}."
            )

print("\\n--- ANALIZA ZAKOŃCZONA ---")
print(f"Wykresy zostały zapisane w katalogu: {OUTPUT_PLOT_DIR.resolve()}")
if INTERACTIVE_PLOTS:
    print(
        "Wyświetlanie interaktywnych wykresów. Zamknij okno wykresu, aby kontynuować."
    )

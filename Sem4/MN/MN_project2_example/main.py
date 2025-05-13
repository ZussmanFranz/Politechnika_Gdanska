import numpy as np
import time
import matplotlib.pyplot as plt

# --- Configuration ---
STUDENT_INDEX = 201627
TOLERANCE = 1e-9
MAX_ITERATIONS = 2000

# --- Derived Parameters ---
index_str = str(STUDENT_INDEX)
c = int(index_str[-2])
d = int(index_str[-1])
e = int(index_str[3])
f = int(index_str[2])

# --- Helper Functions (Keep as they are) ---


def calculate_N(c_val, d_val):
    return 1200 + 10 * c_val + d_val


def create_banded_matrix(N, a1, a2, a3):
    A = np.zeros((N, N))
    for i in range(N):
        A[i, i] = a1
        if i > 0:
            A[i, i - 1] = a2
        if i < N - 1:
            A[i, i + 1] = a2
        if i > 1:
            A[i, i - 2] = a3
        if i < N - 2:
            A[i, i + 2] = a3
    return A


def create_b_vector(N, f_val):
    b = np.zeros(N)
    for n in range(1, N + 1):
        b[n - 1] = np.sin(n * (f_val + 1))
    return b


def calculate_residual_norm(A, x, b):
    if x is None:
        return float("inf")
    x = np.asarray(x).flatten()
    b = np.asarray(b).flatten()
    A = np.asarray(A)
    if A.shape[1] != x.shape[0]:
        raise ValueError(f"Shape mismatch: A ({A.shape}) and x ({x.shape})")
    if A.shape[0] != b.shape[0]:
        raise ValueError(f"Shape mismatch: A ({A.shape}) and b ({b.shape})")

    residual = A @ x - b
    return np.linalg.norm(residual)


# --- Iterative Methods (Sparse Manual - Keep from previous version) ---


def jacobi_sparse_manual(A_orig, b_orig, max_iter=MAX_ITERATIONS, tolerance=TOLERANCE):
    N = len(b_orig)
    A = A_orig
    b = b_orig.copy().flatten()
    x = np.zeros(N)
    x_new = np.zeros(N)
    residuals = []
    iterations = 0

    a1 = A[0, 0]
    a2 = A[0, 1] if N > 1 else 0
    a3 = A[0, 2] if N > 2 else 0
    if abs(a1) < 1e-15:
        print(f"Error: Jacobi diagonal element a1 is near zero.")
        return None, [], 0, 0.0

    start_time = time.perf_counter()

    for k in range(max_iter):
        iterations = k + 1
        for i in range(N):
            s = 0.0
            if i > 1:
                s += a3 * x[i - 2]
            if i > 0:
                s += a2 * x[i - 1]
            if i < N - 1:
                s += a2 * x[i + 1]
            if i < N - 2:
                s += a3 * x[i + 2]
            x_new[i] = (b[i] - s) / a1

        x = x_new.copy()

        norm_res = calculate_residual_norm(A_orig, x, b_orig)
        residuals.append(norm_res)

        if norm_res < tolerance:
            break

    end_time = time.perf_counter()

    if not residuals or (residuals[-1] >= tolerance and iterations == max_iter):
        print(
            f"Jacobi method (Sparse Manual) did not converge within {max_iter} iterations."
        )
        return x, residuals, iterations, end_time - start_time
    else:
        return x, residuals, iterations, end_time - start_time


def gauss_seidel_sparse_manual(
    A_orig, b_orig, max_iter=MAX_ITERATIONS, tolerance=TOLERANCE
):
    N = len(b_orig)
    A = A_orig
    b = b_orig.copy().flatten()
    x = np.zeros(N)
    residuals = []
    iterations = 0

    a1 = A[0, 0]
    a2 = A[0, 1] if N > 1 else 0
    a3 = A[0, 2] if N > 2 else 0
    if abs(a1) < 1e-15:
        print(f"Error: Gauss-Seidel diagonal element a1 is near zero.")
        return None, [], 0, 0.0

    start_time = time.perf_counter()

    for k in range(max_iter):
        iterations = k + 1
        x_old_iteration = x.copy()

        for i in range(N):
            s1 = 0.0
            s2 = 0.0

            if i > 1:
                s1 += a3 * x[i - 2]
            if i > 0:
                s1 += a2 * x[i - 1]

            s_gs = 0.0
            if i > 1:
                s_gs += a3 * x[i - 2]
            if i > 0:
                s_gs += a2 * x[i - 1]
            if i < N - 1:
                s_gs += a2 * x[i + 1]
            if i < N - 2:
                s_gs += a3 * x[i + 2]

            x[i] = (b[i] - s_gs) / a1

        norm_res = calculate_residual_norm(A_orig, x, b_orig)
        residuals.append(norm_res)

        if norm_res < tolerance:
            break

    end_time = time.perf_counter()

    if not residuals or (residuals[-1] >= tolerance and iterations == max_iter):
        print(
            f"Gauss-Seidel method (Sparse Manual) did not converge within {max_iter} iterations."
        )
        return x, residuals, iterations, end_time - start_time
    else:
        return x, residuals, iterations, end_time - start_time


# --- Direct Methods ---


def gaussian_elimination_solve(A_orig, b_orig):
    N = A_orig.shape[0]
    A = A_orig.copy().astype(float)
    b = b_orig.copy().astype(float).flatten()
    x = np.zeros(N, dtype=float)
    start_time = time.perf_counter()

    for k in range(N - 1):
        max_row_index = k + np.argmax(np.abs(A[k:, k]))
        if max_row_index != k:
            A[[k, max_row_index]] = A[[max_row_index, k]]
            b[[k, max_row_index]] = b[[max_row_index, k]]

        if abs(A[k, k]) < 1e-15:
            print("Error: Matrix is singular or near-singular (Gaussian Elimination).")
            return None, time.perf_counter() - start_time

        for i in range(k + 1, N):
            factor = A[i, k] / A[k, k]
            A[i, k:] -= factor * A[k, k:]
            b[i] -= factor * b[k]

    if abs(A[N - 1, N - 1]) < 1e-15:
        print("Error: Matrix is singular or near-singular (Gaussian Elimination).")
        return None, time.perf_counter() - start_time

    for i in range(N - 1, -1, -1):
        sum_ax = np.dot(A[i, i + 1 :], x[i + 1 :])
        x[i] = (b[i] - sum_ax) / A[i, i]

    end_time = time.perf_counter()
    return x, end_time - start_time


def lu_decomposition_doolittle(A_orig):
    N = A_orig.shape[0]
    A = A_orig.copy().astype(float)
    L = np.eye(N, dtype=float)
    U = np.zeros((N, N), dtype=float)

    for k in range(N):
        for j in range(k, N):
            sum_lu = np.dot(L[k, :k], U[:k, j])
            U[k, j] = A[k, j] - sum_lu

        if abs(U[k, k]) < 1e-15:
            print(
                f"Error: Zero pivot encountered in U at ({k},{k}). LU decomposition failed."
            )
            return None, None

        for i in range(k + 1, N):
            sum_lu = np.dot(L[i, :k], U[:k, k])
            L[i, k] = (A[i, k] - sum_lu) / U[k, k]

    return L, U


def forward_substitution(L, b):
    N = L.shape[0]
    y = np.zeros(N, dtype=float)
    b = b.flatten()

    for i in range(N):
        sum_ly = np.dot(L[i, :i], y[:i])
        y[i] = b[i] - sum_ly
    return y


def backward_substitution(U, y):
    N = U.shape[0]
    x = np.zeros(N, dtype=float)
    y = y.flatten()

    for i in range(N - 1, -1, -1):
        if abs(U[i, i]) < 1e-15:
            print(
                f"Error: Zero diagonal element in U at ({i},{i}) during back substitution."
            )
            return None
        sum_ux = np.dot(U[i, i + 1 :], x[i + 1 :])
        x[i] = (y[i] - sum_ux) / U[i, i]
    return x


def lu_solve_doolittle(A_orig, b_orig):
    start_time = time.perf_counter()
    L, U = lu_decomposition_doolittle(A_orig)

    if L is None or U is None:
        return None, time.perf_counter() - start_time

    y = forward_substitution(L, b_orig)
    if y is None:
        return None, time.perf_counter() - start_time

    x = backward_substitution(U, y)
    if x is None:
        return None, time.perf_counter() - start_time

    end_time = time.perf_counter()
    return x, end_time - start_time


# --- Main Execution ---
if __name__ == "__main__":
    print(f"Student Index: {STUDENT_INDEX}")
    a1_taskA = 5 + e
    print(f"Derived parameters: c={c}, d={d}, e={e} -> a1={a1_taskA}, f={f}")

    # === Task A: System Setup ===
    print("\n--- Task A: System Setup ---")
    N_taskA = calculate_N(c, d)
    a2_taskA = -1.0
    a3_taskA = -1.0
    print(f"Matrix size N = {N_taskA}")
    print(f"Matrix parameters: a1 = {a1_taskA}, a2 = {a2_taskA}, a3 = {a3_taskA}")

    A_taskA = create_banded_matrix(N_taskA, a1_taskA, a2_taskA, a3_taskA)
    b_taskA = create_b_vector(N_taskA, f)

    print(f"Matrix A (first 5x5):\n{A_taskA[:5, :5]}")
    print(f"Vector b (first 5 elements): {b_taskA.flatten()[:5]}")
    print("Solving equation Ax = b with these parameters.")

    # === Task B: Jacobi and Gauss-Seidel (Sparse Manual) ===
    print("\n--- Task B: Jacobi and Gauss-Seidel Methods (Sparse Manual) ---")

    # Jacobi (Sparse Manual)
    x_jacobi, residuals_jacobi, iter_jacobi, time_jacobi = jacobi_sparse_manual(
        A_taskA, b_taskA, MAX_ITERATIONS, TOLERANCE
    )
    print(f"\nJacobi Method (Sparse Manual):")
    if x_jacobi is not None:
        final_resid_jacobi = calculate_residual_norm(A_taskA, x_jacobi, b_taskA)
        print(
            f"  Iterations: {iter_jacobi} (Converged: {final_resid_jacobi < TOLERANCE})"
        )
        print(f"  Execution Time: {time_jacobi:.4f} seconds")
        print(f"  Final Residual Norm: {final_resid_jacobi:e}")
    else:
        print(f"  Failed to compute.")
        print(f"  Execution Time: {time_jacobi:.4f} seconds")

    # Gauss-Seidel (Sparse Manual)
    x_gs, residuals_gs, iter_gs, time_gs = gauss_seidel_sparse_manual(
        A_taskA, b_taskA, MAX_ITERATIONS, TOLERANCE
    )
    print(f"\nGauss-Seidel Method (Sparse Manual):")
    if x_gs is not None:
        final_resid_gs = calculate_residual_norm(A_taskA, x_gs, b_taskA)
        print(f"  Iterations: {iter_gs} (Converged: {final_resid_gs < TOLERANCE})")
        print(f"  Execution Time: {time_gs:.4f} seconds")
        print(f"  Final Residual Norm: {final_resid_gs:e}")
    else:
        print(f"  Failed to compute.")
        print(f"  Execution Time: {time_gs:.4f} seconds")

    # Plotting
    plt.figure(figsize=(10, 6))
    if residuals_jacobi:
        plt.plot(
            range(1, len(residuals_jacobi) + 1),
            residuals_jacobi,
            marker=".",
            linestyle="-",
            label=f"Jacobi ({iter_jacobi} iter)",
        )
    if residuals_gs:
        plt.plot(
            range(1, len(residuals_gs) + 1),
            residuals_gs,
            marker=".",
            linestyle="-",
            label=f"Gauss-Seidel ({iter_gs} iter)",
        )
    plt.axhline(
        TOLERANCE, color="r", linestyle="--", label=f"Tolerance ({TOLERANCE:e})"
    )
    plt.yscale("log")
    plt.xlabel("Iteration Number")
    plt.ylabel("Residual Norm (||Ax - b||)")
    plt.title(f"Task B: Convergence (Sparse Manual) (N={N_taskA}, a1={a1_taskA})")
    plt.legend()
    plt.grid(True, which="both", ls="--")
    plt.savefig("task_b_convergence_sparse.png")
    plt.show()

    # === Task C: Iterative Methods with a1=3 (Sparse Manual) ===
    print("\n--- Task C: Iterative Methods with a1=3 (Sparse Manual) ---")
    N_taskC = N_taskA
    a1_taskC = 3.0
    a2_taskC = -1.0
    a3_taskC = -1.0
    print(f"Matrix size N = {N_taskC}")
    print(f"Matrix parameters: a1 = {a1_taskC}, a2 = {a2_taskC}, a3 = {a3_taskC}")

    A_taskC = create_banded_matrix(N_taskC, a1_taskC, a2_taskC, a3_taskC)
    b_taskC = b_taskA

    # Jacobi (Sparse Manual)
    x_jacobi_C, residuals_jacobi_C, iter_jacobi_C, time_jacobi_C = jacobi_sparse_manual(
        A_taskC, b_taskC, MAX_ITERATIONS, TOLERANCE
    )
    print(f"\nJacobi Method (Task C - Sparse Manual):")
    if x_jacobi_C is not None:
        final_resid_jacobi_C = calculate_residual_norm(A_taskC, x_jacobi_C, b_taskC)
        print(
            f"  Iterations: {iter_jacobi_C} (Converged: {final_resid_jacobi_C < TOLERANCE})"
        )
        print(f"  Execution Time: {time_jacobi_C:.4f} seconds")
        print(f"  Final Residual Norm: {final_resid_jacobi_C:e}")
    else:
        print(f"  Failed to compute.")
        print(f"  Execution Time: {time_jacobi_C:.4f} seconds")

    # Gauss-Seidel (Sparse Manual)
    x_gs_C, residuals_gs_C, iter_gs_C, time_gs_C = gauss_seidel_sparse_manual(
        A_taskC, b_taskC, MAX_ITERATIONS, TOLERANCE
    )
    print(f"\nGauss-Seidel Method (Task C - Sparse Manual):")
    if x_gs_C is not None:
        final_resid_gs_C = calculate_residual_norm(A_taskC, x_gs_C, b_taskC)
        print(f"  Iterations: {iter_gs_C} (Converged: {final_resid_gs_C < TOLERANCE})")
        print(f"  Execution Time: {time_gs_C:.4f} seconds")
        print(f"  Final Residual Norm: {final_resid_gs_C:e}")
    else:
        print(f"  Failed to compute.")
        print(f"  Execution Time: {time_gs_C:.4f} seconds")

    # Plotting for Task C
    plt.figure(figsize=(10, 6))
    plot_limit = 1e10
    if residuals_jacobi_C:
        resid_jacobi_plot = np.array(residuals_jacobi_C)
        plt.plot(
            range(1, len(resid_jacobi_plot) + 1),
            resid_jacobi_plot,
            marker=".",
            linestyle="-",
            label=f"Jacobi ({iter_jacobi_C} iter)",
        )
    if residuals_gs_C:
        resid_gs_plot = np.array(residuals_gs_C)
        plt.plot(
            range(1, len(resid_gs_plot) + 1),
            resid_gs_plot,
            marker=".",
            linestyle="-",
            label=f"Gauss-Seidel ({iter_gs_C} iter)",
        )
    plt.axhline(
        TOLERANCE, color="r", linestyle="--", label=f"Tolerance ({TOLERANCE:e})"
    )
    plt.yscale("log")
    plt.xlabel("Iteration Number")
    plt.ylabel("Residual Norm (||Ax - b||)")
    plt.title(f"Task C: Convergence Check (Sparse Manual) (N={N_taskC}, a1={a1_taskC})")
    plt.legend()
    plt.grid(True, which="both", ls="--")
    plt.savefig("task_c_convergence_sparse.png")
    plt.show()

    # === Task D: Direct Methods for Task C Matrix ===
    print("\n--- Task D: Direct Methods for Task C Matrix ---")
    print(f"Using system from Task C (a1={a1_taskC})")

    # LU Decomposition (Doolittle)
    x_lu, time_lu = lu_solve_doolittle(A_taskC, b_taskC)
    print(f"\nLU Decomposition Method (Doolittle):")
    if x_lu is not None:
        final_resid_lu = calculate_residual_norm(A_taskC, x_lu, b_taskC)
        print(f"  Solution found.")
        print(f"  Execution Time: {time_lu:.4f} seconds")
        print(f"  Final Residual Norm: {final_resid_lu:e}")
    else:
        print(f"  LU decomposition or solver failed.")
        print(f"  Execution Time: {time_lu:.4f} seconds")

    # Gaussian Elimination
    x_gauss, time_gauss = gaussian_elimination_solve(A_taskC, b_taskC)
    print(f"\nGaussian Elimination Method:")
    if x_gauss is not None:
        final_resid_gauss = calculate_residual_norm(A_taskC, x_gauss, b_taskC)
        print(f"  Solution found.")
        print(f"  Execution Time: {time_gauss:.4f} seconds")
        print(f"  Final Residual Norm: {final_resid_gauss:e}")
    else:
        print(f"  Gaussian elimination failed (matrix likely singular).")
        print(f"  Execution Time: {time_gauss:.4f} seconds")

    # === Task E: Performance Analysis vs N ===
    print("\n--- Task E: Performance vs N (All Methods) ---")
    a1_taskE = a1_taskA
    a2_taskE = a2_taskA
    a3_taskE = a3_taskA
    f_taskE = f

    # N_values = [100, 500, 1000, 1500, 2000, 2500, 3000]
    N_values = [100, 300, 500, 700, 1000]
    times_jacobi_sparse = []
    times_gs_sparse = []
    times_lu = []
    times_gauss = []

    print("Running simulations for different N values...")
    for N_test in N_values:
        print(f"  N = {N_test}")
        A_test = create_banded_matrix(N_test, a1_taskE, a2_taskE, a3_taskE)
        b_test = create_b_vector(N_test, f_taskE)

        # Jacobi (Sparse Manual)
        _, _, _, time_j = jacobi_sparse_manual(
            A_test, b_test, MAX_ITERATIONS, TOLERANCE
        )
        times_jacobi_sparse.append(time_j)

        # Gauss-Seidel (Sparse Manual)
        _, _, _, time_g = gauss_seidel_sparse_manual(
            A_test, b_test, MAX_ITERATIONS, TOLERANCE
        )
        times_gs_sparse.append(time_g)

        # LU Decomposition (Doolittle)
        _, time_l = lu_solve_doolittle(A_test, b_test)
        times_lu.append(time_l)

        # Gaussian Elimination
        _, time_ga = gaussian_elimination_solve(A_test, b_test)
        times_gauss.append(time_ga)

    print("Finished simulations.")
    print("N values:", N_values)
    print("Jacobi Times (Sparse):", times_jacobi_sparse)
    print("Gauss-Seidel Times (Sparse):", times_gs_sparse)
    print("LU Times:", times_lu)
    print("Gaussian Elim Times:", times_gauss)

    # Plotting Task E - Linear Scale
    plt.figure(figsize=(10, 6))
    plt.plot(
        N_values,
        times_jacobi_sparse,
        marker="o",
        linestyle="-",
        label="Jacobi (Sparse)",
    )
    plt.plot(
        N_values,
        times_gs_sparse,
        marker="s",
        linestyle="-",
        label="Gauss-Seidel (Sparse)",
    )
    plt.plot(N_values, times_lu, marker="^", linestyle="-", label="LU (Doolittle)")
    plt.plot(N_values, times_gauss, marker="d", linestyle="-", label="Gaussian Elim.")
    plt.xlabel("Matrix Size (N)")
    plt.ylabel("Execution Time (seconds)")
    plt.title("Task E: Performance vs N (All Methods, Linear Scale)")
    plt.legend()
    plt.grid(True)
    plt.savefig("task_e_performance_all_linear.png")
    plt.show()

    # Plotting Task E - Logarithmic Scale (Y-axis)
    plt.figure(figsize=(10, 6))
    plt.plot(
        N_values,
        times_jacobi_sparse,
        marker="o",
        linestyle="-",
        label="Jacobi (Sparse)",
    )
    plt.plot(
        N_values,
        times_gs_sparse,
        marker="s",
        linestyle="-",
        label="Gauss-Seidel (Sparse)",
    )
    plt.plot(N_values, times_lu, marker="^", linestyle="-", label="LU (Doolittle)")
    plt.plot(N_values, times_gauss, marker="d", linestyle="-", label="Gaussian Elim.")
    plt.yscale("log")
    plt.xlabel("Matrix Size (N)")
    plt.ylabel("Execution Time (seconds)")
    plt.title("Task E: Performance vs N (All Methods, Log Scale)")
    plt.legend()
    plt.grid(True, which="both", ls="--")
    plt.savefig("task_e_performance_all_log.png")
    plt.show()

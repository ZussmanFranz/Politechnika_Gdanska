import numpy as np
import matplotlib.pyplot as plt
import time

# --- Configuration ---
STUDENT_INDEX = "201253"
c = int(STUDENT_INDEX[-2])  # Przedostatnia cyfra
d = int(STUDENT_INDEX[-1])  # Ostatnia cyfra
e = int(STUDENT_INDEX[3])   # Czwarta cyfra
f = int(STUDENT_INDEX[2])   # Trzecia cyfra

MAX_ITERATIONS = 2000
TOLERANCE = 1e-9

def calculate_N(c_val, d_val):
    return 1200 + 10 * c_val + d_val

def generate_A(N, a1, a2, a3):
    A = np.zeros((N, N))
    for i in range(N):
        A[i, i] = a1  # Main diagonal
        if i > 0:
            A[i, i - 1] = a2  # Lower adjacent
        if i < N - 1:
            A[i, i + 1] = a2  # Upper adjacent
        if i > 1:
            A[i, i - 2] = a3  # Lower outer
        if i < N - 2:
            A[i, i + 2] = a3  # Upper outer
    return A

def generate_b(N, f):
    b = np.zeros(N)
    for n in range(1, N + 1):
        b[n - 1] = np.sin(n * (f + 1))
    return b

def calculate_residual_norm(A, x, b):
    if x is None: # If a method failed to converge / produce x
        return float('inf')
    r = np.dot(A, x) - b
    return np.linalg.norm(r)

# --- Iterative Methods ---

def jacobi_method(A, b, tol=TOLERANCE, max_iter=MAX_ITERATIONS, x0=None):
    """
    Solves Ax = b using the Jacobi method (optimized with NumPy vectorization).
    Returns solution x, number of iterations, and history of residual norms.
    """
    N = len(b)
    if x0 is None:
        x = np.zeros(N)
    else:
        x = np.copy(x0)
    
    residuals_history = []
    D = np.diag(A)
    R = A - np.diagflat(D)

    for k in range(max_iter):
        x_new = (b - np.dot(R, x)) / D
        current_residual_norm = calculate_residual_norm(A, x_new, b)
        residuals_history.append(current_residual_norm)
        if current_residual_norm < tol:
            return x_new, k + 1, residuals_history
        x = x_new
    print(f"Jacobi: Nie zbiegła w ramach {max_iter} iteracji. Norma residuum: {current_residual_norm}")
    return x, max_iter, residuals_history


def gauss_seidel_method(A, b, tol=TOLERANCE, max_iter=MAX_ITERATIONS, x0=None):
    """
    Solves Ax = b using the Gauss-Seidel method (optimized for pentadiagonal matrix).
    Returns solution x, number of iterations, and history of residual norms.
    """
    N = len(b)
    if x0 is None:
        x = np.zeros(N)
    else:
        x = np.copy(x0)
    residuals_history = []
    for k in range(max_iter):
        for i in range(N):
            s = 0.0
            if i > 1:
                s += A[i, i-2] * x[i-2]
            if i > 0:
                s += A[i, i-1] * x[i-1]
            if i < N-1:
                s += A[i, i+1] * x[i+1]
            if i < N-2:
                s += A[i, i+2] * x[i+2]
            x[i] = (b[i] - s) / A[i, i]
        current_residual_norm = calculate_residual_norm(A, x, b)
        residuals_history.append(current_residual_norm)
        if current_residual_norm < tol:
            return x, k + 1, residuals_history
    print(f"Gauss-Seidel: Nie zbiegła w ramach {max_iter} iteracji. Norma residuum: {current_residual_norm}")
    return x, max_iter, residuals_history

# --- Direct Method (LU Factorization) ---

def lu_decomposition(A):
    N = A.shape[0]
    L = np.eye(N)  # Lower triangular matrix with 1s on diagonal
    U = np.zeros((N, N)) # Upper triangular matrix

    for k in range(N):
        U[k, k:] = A[k, k:] - L[k, :k] @ U[:k, k:]
        if k + 1 < N:
            L[k+1:, k] = (A[k+1:, k] - L[k+1:, :k] @ U[:k, k]) / U[k, k]
    return L, U

def lu_solve(L, U, b):
    """
    Solves Ax = b using pre-computed L and U matrices.
    1. Solves Ly = b (forward substitution)
    2. Solves Ux = y (backward substitution)
    """
    N = L.shape[0]
    y = np.zeros(N)
    x = np.zeros(N)

    # Forward substitution: Ly = b
    for i in range(N):
        y[i] = b[i] - np.dot(L[i, :i], y[:i])

    # Backward substitution: Ux = y
    for i in range(N - 1, -1, -1):
        x[i] = (y[i] - np.dot(U[i, i+1:], x[i+1:])) / U[i, i]
        
    return x

# --- Plotting Function ---
def plot_residuals(residuals_jacobi, residuals_gs, title_suffix="", filename_prefix="residuals_plot"): 
    plt.figure(figsize=(10, 6))
    plt.plot(residuals_jacobi, label="Jacobi Residual Norm", marker='o', linestyle='-', markersize=4)
    plt.plot(residuals_gs, label="Gauss-Seidel Residual Norm", marker='x', linestyle='--', markersize=4)
    plt.yscale('log')
    plt.xlabel("Iteration")
    plt.ylabel("Norm of Residuum (log scale)")
    plt.title(f"Convergence of Iterative Methods {title_suffix}")
    plt.legend()
    plt.grid(True, which="both", ls="-")
    
    filename = f'{filename_prefix}.png'
    plt.savefig(filename)
    print(f"Zapisano wykres residuów jako: {filename}")
    plt.show()

def plot_performance(N_values, times_jacobi, times_gs, times_lu, y_scale='linear', filename_prefix="performance_plot"): 
    plt.figure(figsize=(10, 6))
    plt.plot(N_values, times_jacobi, label="Jacobi Time", marker='o')
    plt.plot(N_values, times_gs, label="Gauss-Seidel Time", marker='x')
    plt.plot(N_values, times_lu, label="LU Factorization + Solve Time", marker='s')
    
    plt.xlabel("Matrix Size N")
    plt.ylabel(f"Execution Time (seconds) - {y_scale} scale")
    plt.title(f"Performance Comparison (Y-axis: {y_scale})")
    if y_scale == 'log':
        plt.yscale('log')
    plt.legend()
    plt.grid(True, which="both", ls="-")
    
    filename = f"{filename_prefix}_{y_scale}_scale.png"
    plt.savefig(filename)
    print(f"Zapisano wykres wydajności jako: {filename}")
    plt.show()

def check_diag_dominance(A, N, matrix_name, task_name):
    # Sprawdzenie warunku zbieżności (dominacja diagonalna) dla macierzy z zadania A
    # Wystarczający, ale nie konieczny warunek. |a_ii| > sum_j!=i |a_ij|
    diag_dominant_A = True
    for i in range(N):
        row_sum_off_diag = np.sum(np.abs(A[i, :])) - np.abs(A[i,i])
        if np.abs(A[i,i]) <= row_sum_off_diag: # Using <= for strict dominance check
            diag_dominant_A = False
            print(f"{matrix_name} (Zad. {task_name}) nie jest ściśle diagonalnie dominująca w wierszu {i}.")
            break
    if diag_dominant_A:
        print(f"{matrix_name} (Zad. {task_name}) jest ściśle diagonalnie dominująca wierszowo - metody iteracyjne powinny się zbiegać.")
    else:
        print(f"{matrix_name} (Zad. {task_name}) NIE jest ściśle diagonalnie dominująca wierszowo - zbieżność metod iteracyjnych nie jest zagwarantowana przez ten warunek.")

# --- Main Execution ---
if __name__ == "__main__":
    print(f"Student Index: {STUDENT_INDEX}")

    N_main = calculate_N(c, d)

    print("\n--- Zadanie A: Stwórz układ równań ---")
    a1_A = 5 + e
    a2_A = -1
    a3_A = -1
    print(f"Parametry macierzy A dla Zadania A: a1 = {a1_A}, a2 = {a2_A}, a3 = {a3_A}")
    
    A_task_A = generate_A(N_main, a1_A, a2_A, a3_A)
    b_task_A = generate_b(N_main, f)
    
    print(f"Macierz A (kształt): {A_task_A.shape}")
    print(f"Wektor b (kształt): {b_task_A.shape}")

    # Opis równania macierzowego:
    print("Rozwiązywane równanie macierzowe: Ax = b, gdzie A jest macierzą pasmową (pentadiagonalną)")
    print(f"o wymiarach {N_main}x{N_main} z elementami na diagonalach a1={a1_A}, a2={a2_A}, a3={a3_A}.")
    print(f"Wektor b ma długość {N_main}, a jego n-ty element (1-indeksowany) to sin(n * ({f}+1)).")
    print("Szukamy wektora x.")

    check_diag_dominance(A_task_A, N_main, "Macierz A", "A")

    print("\n--- Zadanie B: Metody iteracyjne (Jacobi, Gauss-Seidl) dla układu z Zadania A ---")
    tol_B = TOLERANCE
    max_iter_B = MAX_ITERATIONS

    print(f"Warunek stopu: norma residuum < {tol_B}")

    start_time_jacobi_B = time.perf_counter()
    x_jacobi_B, iters_jacobi_B, residuals_jacobi_B = jacobi_method(A_task_A, b_task_A, tol=tol_B, max_iter=max_iter_B)
    end_time_jacobi_B = time.perf_counter()
    time_jacobi_B = end_time_jacobi_B - start_time_jacobi_B
    print(f"Jacobi (Zad. B): {iters_jacobi_B} iteracji, czas: {time_jacobi_B:.4f} s, końcowa norma residuum: {residuals_jacobi_B[-1] if residuals_jacobi_B else 'N/A'}")

    start_time_gs_B = time.perf_counter()
    x_gs_B, iters_gs_B, residuals_gs_B = gauss_seidel_method(A_task_A, b_task_A, tol=tol_B, max_iter=max_iter_B)
    end_time_gs_B = time.perf_counter()
    time_gs_B = end_time_gs_B - start_time_gs_B
    print(f"Gauss-Seidel (Zad. B): {iters_gs_B} iteracji, czas: {time_gs_B:.4f} s, końcowa norma residuum: {residuals_gs_B[-1] if residuals_gs_B else 'N/A'}")
    
    if residuals_jacobi_B and residuals_gs_B:
        plot_residuals(residuals_jacobi_B, residuals_gs_B, 
                       title_suffix="(Zadanie B)",
                       filename_prefix="residuals_plot_B")
    else:
        print("Nie udało się wygenerować historii residuów dla Zadania B.")


    print("\n--- Zadanie C: Metody iteracyjne dla zmodyfikowanego układu ---")
    a1_C = 3
    a2_C = -1
    a3_C = -1
    print(f"Parametry macierzy A dla Zadania C: a1 = {a1_C}, a2 = {a2_C}, a3 = {a3_C}")
    
    A_task_C = generate_A(N_main, a1_C, a2_C, a3_C)
    b_task_C = b_task_A 
    
    check_diag_dominance(A_task_C, N_main, "Macierz A", "C")

    max_iter_C = MAX_ITERATIONS

    start_time_jacobi_C = time.perf_counter()
    x_jacobi_C, iters_jacobi_C, residuals_jacobi_C = jacobi_method(A_task_C, b_task_C, tol=tol_B, max_iter=max_iter_C)
    end_time_jacobi_C = time.perf_counter()
    time_jacobi_C = end_time_jacobi_C - start_time_jacobi_C
    
    print(f'''
            Jacobi (Zad. C): {iters_jacobi_C} iteracji, 
            czas: {time_jacobi_C:.4f} s, 
            końcowa norma residuum: {residuals_jacobi_C[-1] if residuals_jacobi_C else 'N/A'}''')

    start_time_gs_C = time.perf_counter()
    x_gs_C, iters_gs_C, residuals_gs_C = gauss_seidel_method(A_task_C, b_task_C, tol=tol_B, max_iter=max_iter_C)
    end_time_gs_C = time.perf_counter()
    time_gs_C = end_time_gs_C - start_time_gs_C

    print(f'''
            Gauss-Seidel (Zad. C): {iters_gs_C} iteracji, 
            czas: {time_gs_C:.4f} s, 
            końcowa norma residuum: {residuals_gs_C[-1] if residuals_gs_C else 'N/A'}''')

    if residuals_jacobi_C and residuals_gs_C:
        plot_residuals(residuals_jacobi_C, residuals_gs_C, 
                       title_suffix="(Zadanie C)", 
                       filename_prefix="residuals_plot_C")
    else:
        print("Nie udało się wygenerować historii residuów dla Zadania C.")
    
    if (residuals_jacobi_C and residuals_jacobi_C[-1] > tol_B) or \
       (residuals_gs_C and residuals_gs_C[-1] > tol_B):
        print("W Zadaniu C przynajmniej jedna z metod iteracyjnych nie zbiegła do zadanej tolerancji.")
    else:
        print("W Zadaniu C obie metody iteracyjne (potencjalnie) zbiegły.")


    print("\n--- Zadanie D: Metoda bezpośrednia (rozkład LU) dla układu z Zadania C ---")
    start_time_lu_decomp_D = time.perf_counter()
    L_D, U_D = lu_decomposition(np.copy(A_task_C)) # Pass a copy if LU modifies A in place
    end_time_lu_decomp_D = time.perf_counter()
    time_lu_decomp_D = end_time_lu_decomp_D - start_time_lu_decomp_D
    print(f"Czas dekompozycji LU (Zad. D): {time_lu_decomp_D:.4f} s")

    start_time_lu_solve_D = time.perf_counter()
    x_lu_D = lu_solve(L_D, U_D, b_task_C)
    end_time_lu_solve_D = time.perf_counter()
    time_lu_solve_D = end_time_lu_solve_D - start_time_lu_solve_D
    print(f"Czas rozwiązania układu z LU (Zad. D): {time_lu_solve_D:.4f} s")
    
    residual_lu_D = calculate_residual_norm(A_task_C, x_lu_D, b_task_C)
    print(f"Norma residuum dla metody LU (Zad. D): {residual_lu_D:.2e}")


    print("\n--- Zadanie E: Porównanie czasów wykonania dla różnych N ---")
    N_values_E = [100, 300, 900, 1200, 2000]
    max_iter_E = MAX_ITERATIONS

    times_jacobi_E = []
    times_gs_E = []
    times_lu_E = [] 
    
    a1_E = a1_A 
    a2_E = a2_A
    a3_E = a3_A

    print(f'''
            Testowane N: {N_values_E}.
            Parametry macierzy A jak w Zad. A (a1={a1_E}). 
            Max iteracji dla iteracyjnych: {max_iter_E}''')

    for N_curr in N_values_E:
        print(f"  Obliczenia dla N = {N_curr}...")
        A_E = generate_A(N_curr, a1_E, a2_E, a3_E)
        b_E = generate_b(N_curr, f)

        # Jacobi
        start_t = time.perf_counter()
        _, _, res_hist_jac_E = jacobi_method(A_E, b_E, tol=tol_B, max_iter=max_iter_E)
        times_jacobi_E.append(time.perf_counter() - start_t)
        print(f"    Jacobi N={N_curr}: {times_jacobi_E[-1]:.4f}s, resid: {res_hist_jac_E[-1]:.2e} after {len(res_hist_jac_E)} iters")


        # Gauss-Seidel
        start_t = time.perf_counter()
        _, _, res_hist_gs_E = gauss_seidel_method(A_E, b_E, tol=tol_B, max_iter=max_iter_E)
        times_gs_E.append(time.perf_counter() - start_t)
        print(f"    GS N={N_curr}: {times_gs_E[-1]:.4f}s, resid: {res_hist_gs_E[-1]:.2e} after {len(res_hist_gs_E)} iters")


        # LU Decomposition + Solve
        start_t_lu_decomp = time.perf_counter()
        L_E, U_E = lu_decomposition(np.copy(A_E))
        t_lu_decomp = time.perf_counter() - start_t_lu_decomp
        
        start_t_lu_solve = time.perf_counter()
        x_lu_E = lu_solve(L_E, U_E, b_E)
        t_lu_solve = time.perf_counter() - start_t_lu_solve
        times_lu_E.append(t_lu_decomp + t_lu_solve)
        res_lu_E = calculate_residual_norm(A_E, x_lu_E, b_E)
        print(f"    LU N={N_curr}: {times_lu_E[-1]:.4f}s (decomp: {t_lu_decomp:.4f}s, solve: {t_lu_solve:.4f}s), resid: {res_lu_E:.2e}")


    plot_performance(N_values_E, times_jacobi_E, times_gs_E, times_lu_E, 
                        y_scale='linear')
    plot_performance(N_values_E, times_jacobi_E, times_gs_E, times_lu_E, 
                        y_scale='log')
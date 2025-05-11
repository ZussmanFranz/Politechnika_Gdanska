import numpy as np
import matplotlib.pyplot as plt
import time

# --- Student Index Configuration ---
STUDENT_INDEX = "201253"

# --- Helper Functions ---
def parse_index(index_str):
    if len(index_str) < 4:
        raise ValueError("Index string is too short. Must be at least 4 digits.")
    
    c = int(index_str[-2])  # Przedostatnia cyfra
    d = int(index_str[-1])  # Ostatnia cyfra
    e = int(index_str[3])   # Czwarta cyfra
    f = int(index_str[2])   # Trzecia cyfra
    
    N_val = 1200 + 10 * c + d
    
    return N_val, e, f

def generate_A(N, a1, a2, a3):
    """
    Generates the N x N banded matrix A.
    a1: main diagonal
    a2: adjacent diagonals
    a3: outer diagonals (2 positions away)
    """
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

def generate_b(N, f_digit):
    """
    Generates the vector b of length N.
    b_n = sin(n * (f + 1)), where n is 1-indexed for the formula.
    """
    b = np.zeros(N)
    for n_idx in range(N):  # 0-indexed loop for vector b
        n_formula = n_idx + 1  # 1-indexed for the sin formula
        b[n_idx] = np.sin(n_formula * (f_digit + 1))
    return b

def calculate_residual_norm(A, x, b):
    """
    Calculates the Euclidean norm of the residual vector r = Ax - b.
    """
    if x is None: # If a method failed to converge / produce x
        return float('inf')
    r = np.dot(A, x) - b
    return np.linalg.norm(r)

# --- Iterative Methods ---

def jacobi_method(A, b, tol=1e-9, max_iter=2000, x0=None):
    """
    Solves Ax = b using the Jacobi method.
    Returns solution x, number of iterations, and history of residual norms.
    """
    N = len(b)
    if x0 is None:
        x = np.zeros(N)
    else:
        x = np.copy(x0)
    
    x_new = np.zeros(N)
    residuals_history = []
    
    D = np.diag(A)
    if np.any(D == 0):
        print("Jacobi: Zero on diagonal, method might fail.")
        # For this specific problem structure, a1 is likely non-zero.
        # If a1 could be zero, more robust handling would be needed.

    for k in range(max_iter):
        for i in range(N):
            sigma = 0
            for j in range(N):
                if i != j:
                    sigma += A[i, j] * x[j]
            if D[i] == 0: # Should not happen with problem definition if a1 != 0
                 x_new[i] = x[i] # Or handle error appropriately
            else:
                x_new[i] = (b[i] - sigma) / D[i]
        
        x = np.copy(x_new)
        current_residual_norm = calculate_residual_norm(A, x, b)
        residuals_history.append(current_residual_norm)
        
        if current_residual_norm < tol:
            return x, k + 1, residuals_history
            
    print(f"Jacobi: Did not converge within {max_iter} iterations. Residual norm: {current_residual_norm}")
    return x, max_iter, residuals_history # Return current state if not converged

def gauss_seidel_method(A, b, tol=1e-9, max_iter=2000, x0=None):
    """
    Solves Ax = b using the Gauss-Seidel method.
    Returns solution x, number of iterations, and history of residual norms.
    """
    N = len(b)
    if x0 is None:
        x = np.zeros(N)
    else:
        x = np.copy(x0)
        
    residuals_history = []
    
    D_val = np.diag(A) # For checking zero diagonal, not directly used in standard GS formula structure
    if np.any(D_val == 0):
        print("Gauss-Seidel: Zero on diagonal, method might fail.")

    for k in range(max_iter):
        x_old_iter = np.copy(x) # For residual calculation using x from start of iteration
        for i in range(N):
            sigma1 = 0
            for j in range(i): # Elements already updated in this iteration
                sigma1 += A[i, j] * x[j]
            
            sigma2 = 0
            for j in range(i + 1, N): # Elements from previous iteration
                sigma2 += A[i, j] * x_old_iter[j] # Use x_old_iter here for strict GS formula
            
            if A[i,i] == 0: # Should not happen with problem definition if a1 != 0
                x[i] = x[i] # Or handle error
            else:
                x[i] = (b[i] - sigma1 - sigma2) / A[i, i]
        
        current_residual_norm = calculate_residual_norm(A, x, b)
        residuals_history.append(current_residual_norm)
        
        if current_residual_norm < tol:
            return x, k + 1, residuals_history
            
    print(f"Gauss-Seidel: Did not converge within {max_iter} iterations. Residual norm: {current_residual_norm}")
    return x, max_iter, residuals_history # Return current state if not converged

# --- Direct Method (LU Factorization) ---

def lu_decomposition(A):
    """
    Performs LU decomposition of matrix A (Doolittle's method: L has 1s on diagonal).
    Returns L and U matrices.
    Does not use pivoting, as per typical basic implementations unless specified.
    """
    N = A.shape[0]
    L = np.eye(N)  # Lower triangular matrix with 1s on diagonal
    U = np.zeros((N, N)) # Upper triangular matrix

    for k in range(N):
        if A[k,k] == 0 and k < N-1 : # Check required for general matrices, but for our problem a1 should be non-zero
             # Attempt to find a row to swap with if pivoting was implemented.
             # For this project, if A[k,k] (which is a1 or modified a1) becomes 0 due to subtractions
             # and no pivoting, it will fail. The problem matrices are structured to likely avoid this.
             # Or if U[k,k] becomes zero before division.
             pass

        U[k, k:] = A[k, k:] - L[k, :k] @ U[:k, k:]
        if k + 1 < N:
            if U[k, k] == 0:
                print("LU Decomposition: Zero pivot encountered. Decomposition might fail or be inaccurate.")
                # This means the matrix might be singular or require pivoting.
                # For the project's matrices, this might indicate an issue if a1 becomes effectively zero.
                # We'll let it proceed, potential division by zero will raise an error or result in NaNs/infs.
                L[k+1:, k] = (A[k+1:, k] - L[k+1:, :k] @ U[:k, k]) / 1e-18 # Avoid division by zero, but this is a hack
            else:
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
        # L[i,i] is 1 for Doolittle, so no division by L[i,i] needed here

    # Backward substitution: Ux = y
    for i in range(N - 1, -1, -1):
        if U[i,i] == 0:
            print(f"LU Solve: U[{i},{i}] is zero during backward substitution. Solution may be singular or non-unique.")
            # Handle as appropriate - could indicate issues if matrix is singular.
            # For well-posed problems from the project, this should ideally not happen with non-zero a1.
            x[i] = 0 # Or some other placeholder / error flag
            continue
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
    plt.savefig(filename) # Save the plot
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
    plt.savefig(filename) # Save the plot
    print(f"Zapisano wykres wydajności jako: {filename}")
    plt.show()

# --- Main Execution ---
if __name__ == "__main__":
    N_main, e_digit, f_digit = parse_index(STUDENT_INDEX)
    
    print("\n--- Zadanie A: Stwórz układ równań ---")
    a1_A = 5 + e_digit
    a2_A = -1
    a3_A = -1
    print(f"Parametry macierzy A dla Zadania A: a1 = {a1_A}, a2 = {a2_A}, a3 = {a3_A}")
    
    A_task_A = generate_A(N_main, a1_A, a2_A, a3_A)
    b_task_A = generate_b(N_main, f_digit)
    
    print(f"Macierz A (kształt): {A_task_A.shape}")
    print(f"Wektor b (kształt): {b_task_A.shape}")
    # Opis równania macierzowego:
    print("Rozwiązywane równanie macierzowe: Ax = b, gdzie A jest macierzą pasmową (pentadiagonalną)")
    print(f"o wymiarach {N_main}x{N_main} z elementami na diagonalach a1={a1_A}, a2={a2_A}, a3={a3_A}.")
    print(f"Wektor b ma długość {N_main}, a jego n-ty element (1-indeksowany) to sin(n * ({f_digit}+1)).")
    print("Szukamy wektora x.")

    # Sprawdzenie warunku zbieżności (dominacja diagonalna) dla macierzy z zadania A
    # Wystarczający, ale nie konieczny warunek. |a_ii| > sum_j!=i |a_ij|
    diag_dominant_A = True
    for i in range(N_main):
        row_sum_off_diag = np.sum(np.abs(A_task_A[i, :])) - np.abs(A_task_A[i,i])
        if np.abs(A_task_A[i,i]) <= row_sum_off_diag: # Using <= for strict dominance check
            diag_dominant_A = False
            print(f"Macierz A (Zad. A) nie jest ściśle diagonalnie dominująca w wierszu {i}.")
            break
    if diag_dominant_A:
        print("Macierz A (Zad. A) jest ściśle diagonalnie dominująca wierszowo - metody iteracyjne powinny się zbiegać.")
    else:
        print("Macierz A (Zad. A) NIE jest ściśle diagonalnie dominująca wierszowo - zbieżność metod iteracyjnych nie jest zagwarantowana przez ten warunek.")


    print("\n--- Zadanie B: Metody iteracyjne (Jacobi, Gauss-Seidl) dla układu z Zadania A ---")
    tol_B = 1e-9
    max_iter_B = 200 

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
    # Wektor b pozostaje taki sam jak w Zadaniu A (N_main, f_digit)
    b_task_C = b_task_A 
    
    # Sprawdzenie warunku zbieżności dla macierzy z zadania C
    diag_dominant_C = True
    for i in range(N_main):
        row_sum_off_diag = np.sum(np.abs(A_task_C[i, :])) - np.abs(A_task_C[i,i])
        if np.abs(A_task_C[i,i]) <= row_sum_off_diag:
            diag_dominant_C = False
            print(f"Macierz A (Zad. C) nie jest ściśle diagonalnie dominująca w wierszu {i}.")
            print(f"  |A[{i},{i}]| = {np.abs(A_task_C[i,i])}, suma off-diag = {row_sum_off_diag}")
            break
    if diag_dominant_C:
        print("Macierz A (Zad. C) jest ściśle diagonalnie dominująca wierszowo.")
    else:
        print("Macierz A (Zad. C) NIE jest ściśle diagonalnie dominująca wierszowo. Metody iteracyjne MOGĄ SIĘ NIE ZBIEGAĆ.")

    # Użyjmy większej liczby iteracji, bo może się nie zbiegać szybko lub wcale
    max_iter_C = 200 # Start with a moderate number, can increase if it's slow but converging

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
    N_values_E = [100, 200, 300, 400, 500] # Initial small values for quick testing
    # N_values_E = [100, 500, 1000, 1500, 2000] # Larger values for actual analysis
    max_iter_E = 200 # Reduced for performance testing of iterative methods

    times_jacobi_E = []
    times_gs_E = []
    times_lu_E = [] 
    
    # Parameters for A matrix from Zadanie A
    a1_E = 5 + e_digit 
    a2_E = -1
    a3_E = -1

    print(f'''
            Testowane N: {N_values_E}.
            Parametry macierzy A jak w Zad. A (a1={a1_E}). 
            Max iteracji dla iteracyjnych: {max_iter_E}''')

    for N_curr in N_values_E:
        print(f"  Obliczenia dla N = {N_curr}...")
        A_E = generate_A(N_curr, a1_E, a2_E, a3_E)
        b_E = generate_b(N_curr, f_digit)

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
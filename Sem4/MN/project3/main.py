import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from typing import Tuple, List
import os

def load_data(file_path: str) -> Tuple[np.ndarray, np.ndarray, float, float]:
    """
    Load elevation data from various file formats.
    Returns distance and elevation arrays normalized to [0,1] and [-1,1] respectively.
    Also returns original elevation min and max for denormalization.
    """
    ext = os.path.splitext(file_path)[1]
    
    if ext == '.csv':
        df = pd.read_csv(file_path)
        # Assuming CSV has columns for distance and elevation
        # Modify column names based on actual data structure
        distance = df.iloc[:, 0].values
        elevation = df.iloc[:, 1].values
    else:
        # For other file types, assume two columns: distance and elevation
        data = np.loadtxt(file_path)
        distance = data[:, 0]
        elevation = data[:, 1]
    
    # Normalize distance to [0,1]
    distance = (distance - distance.min()) / (distance.max() - distance.min())
    
    # Normalize elevation to [-1,1]
    elevation_min, elevation_max = elevation.min(), elevation.max()
    elevation = 2 * (elevation - elevation_min) / (elevation_max - elevation_min) - 1
    
    return distance, elevation, elevation_min, elevation_max

def lagrange_interpolation(x: np.ndarray, y: np.ndarray, x_new: np.ndarray) -> np.ndarray:
    """
    Implement Lagrange polynomial interpolation from scratch.
    Parameters:
    - x: Array of x coordinates of interpolation points
    - y: Array of y coordinates of interpolation points
    - x_new: Array of x coordinates where to evaluate the polynomial
    Returns:
    - Array of interpolated y values at x_new points
    """
    n = len(x)
    y_new = np.zeros_like(x_new)
    
    for i in range(n):
        # Compute the i-th Lagrange basis polynomial
        basis = np.ones_like(x_new)
        for j in range(n):
            if i != j:
                basis *= (x_new - x[j]) / (x[i] - x[j])
        # Add contribution from this basis polynomial
        y_new += y[i] * basis
    
    return y_new

def cubic_spline_interpolation(x: np.ndarray, y: np.ndarray, x_new: np.ndarray) -> np.ndarray:
    """
    Implement cubic spline interpolation from scratch.
    Parameters:
    - x: Array of x coordinates of interpolation points
    - y: Array of y coordinates of interpolation points
    - x_new: Array of x coordinates where to evaluate the splines
    Returns:
    - Array of interpolated y values at x_new points
    """
    n = len(x)
    
    # Step 1: Calculate the differences and steps
    h = np.diff(x)
    dy = np.diff(y)
    
    # Step 2: Create the tridiagonal system for the second derivatives
    A = np.zeros((n-2, n-2))
    b = np.zeros(n-2)
    
    # Fill the tridiagonal matrix A and the right-hand side b
    for i in range(n-2):
        if i > 0:
            A[i, i-1] = h[i]
        A[i, i] = 2 * (h[i] + h[i+1])
        if i < n-3:
            A[i, i+1] = h[i+1]
        b[i] = 3 * (dy[i+1]/h[i+1] - dy[i]/h[i])
    
    # Step 3: Solve the system for the second derivatives
    m = np.zeros(n)
    if n > 2:
        m[1:-1] = np.linalg.solve(A, b)
    
    # Step 4: Evaluate the spline at the new points
    y_new = np.zeros_like(x_new)
    
    for i in range(len(x_new)):
        # Find the interval that contains x_new[i]
        idx = np.searchsorted(x, x_new[i]) - 1
        idx = np.clip(idx, 0, n-2)
        
        # Local variables for readability
        dx = x_new[i] - x[idx]
        dx1 = x[idx+1] - x[idx]
        
        # Compute the coefficients of the cubic polynomial
        a = m[idx] * (dx1 - dx)**2 * dx / (6 * dx1)
        b = m[idx+1] * dx**2 * (dx - dx1) / (6 * dx1)
        c = (y[idx+1] - y[idx]) / dx1 - (m[idx+1] + 2*m[idx]) * dx1 / 6
        
        # Evaluate the cubic polynomial
        y_new[i] = y[idx] + c * dx + a + b
    
    return y_new

def analyze_route(file_path: str, route_name: str, node_counts: List[int]):
    """
    Analyze a single route using both interpolation methods with different numbers of nodes.
    """
    # Load and normalize data
    x_orig, y_orig, y_min, y_max = load_data(file_path)
    
    # Create dense x points for interpolation
    x_dense = np.linspace(0, 1, 1000)
    
    for n_nodes in node_counts:
        # Select evenly spaced nodes
        indices = np.linspace(0, len(x_orig)-1, n_nodes, dtype=int)
        x_nodes = x_orig[indices]
        y_nodes = y_orig[indices]
        
        # Lagrange interpolation
        y_lagrange = lagrange_interpolation(x_nodes, y_nodes, x_dense)
        
        # Cubic spline interpolation
        y_spline = cubic_spline_interpolation(x_nodes, y_nodes, x_dense)
        
        # Denormalize for plotting
        x_orig_denorm = x_orig * (x_orig.max() - x_orig.min())
        y_orig_denorm = (y_orig + 1) * (y_max - y_min) / 2 + y_min
        x_nodes_denorm = x_nodes * (x_orig.max() - x_orig.min())
        y_nodes_denorm = (y_nodes + 1) * (y_max - y_min) / 2 + y_min
        x_dense_denorm = x_dense * (x_orig.max() - x_orig.min())
        y_lagrange_denorm = (y_lagrange + 1) * (y_max - y_min) / 2 + y_min
        y_spline_denorm = (y_spline + 1) * (y_max - y_min) / 2 + y_min
        
        # Plot Lagrange interpolation
        plt.figure(figsize=(12, 6))
        plt.plot(x_orig_denorm, y_orig_denorm, 'b-', label='Original Data')
        plt.plot(x_nodes_denorm, y_nodes_denorm, 'ro', label='Interpolation Nodes')
        plt.plot(x_dense_denorm, y_lagrange_denorm, 'g-', label='Lagrange Interpolation')
        plt.title(f'{route_name} - Lagrange Interpolation ({n_nodes} nodes)')
        plt.xlabel('Distance (m)')
        plt.ylabel('Elevation (m)')
        plt.legend()
        plt.grid(True)
        plt.savefig(f'plots/{route_name}_lagrange_{n_nodes}_nodes.png')
        plt.close()
        
        # Plot Cubic Spline interpolation
        plt.figure(figsize=(12, 6))
        plt.plot(x_orig_denorm, y_orig_denorm, 'b-', label='Original Data')
        plt.plot(x_nodes_denorm, y_nodes_denorm, 'ro', label='Interpolation Nodes')
        plt.plot(x_dense_denorm, y_spline_denorm, 'g-', label='Cubic Spline')
        plt.title(f'{route_name} - Cubic Spline Interpolation ({n_nodes} nodes)')
        plt.xlabel('Distance (m)')
        plt.ylabel('Elevation (m)')
        plt.legend()
        plt.grid(True)
        plt.savefig(f'plots/{route_name}_spline_{n_nodes}_nodes.png')
        plt.close()

def main():
    # Create plots directory if it doesn't exist
    os.makedirs('plots', exist_ok=True)
    
    # Selected routes with different characteristics
    routes = [
        ('2018_paths/SpacerniakGdansk.csv', 'Flat_Route'),  # Relatively flat route
        ('2018_paths/MountEverest.csv', 'Mountain_Route'),   # Route with significant elevation
        ('2018_paths/WielkiKanionKolorado.csv', 'Canyon_Route')  # Route with varying terrain
    ]
    
    # Different numbers of nodes to analyze
    node_counts = [5, 10, 20, 40]
    
    # Analyze each route
    for file_path, route_name in routes:
        print(f"Analyzing route: {route_name}")
        analyze_route(file_path, route_name, node_counts)

if __name__ == "__main__":
    main()
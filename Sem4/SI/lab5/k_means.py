import numpy as np

def initialize_centroids_forgy(data, k):
    # TODO implement random initialization
    n_samples = data.shape[0]

    # Ensure that the k <= n_samples
    k = min(k, n_samples)
    
    random_indices = np.random.choice(n_samples, k, replace=False)

    centroids = data[random_indices]

    return centroids

def initialize_centroids_kmeans_pp(data, k):
    # TODO implement kmeans++ initizalization
    n_samples, n_features = data.shape

    k = min(k, n_samples)

    centroids = np.zeros((k, n_features))

    # 1. Choose the first centroid randomly from the data points
    # 2. Continue choosing the farest centroid of available 

    return None

def assign_to_cluster(data, centroid):
    # TODO find the closest cluster for each data point
    return None

def update_centroids(data, assignments):
    # TODO find new centroids based on the assignments
    return None

def mean_intra_distance(data, assignments, centroids):
    return np.sqrt(np.sum((data - centroids[assignments, :])**2))

def k_means(data, num_centroids, kmeansplusplus= False):
    # centroids initizalization
    if kmeansplusplus:
        centroids = initialize_centroids_kmeans_pp(data, num_centroids)
    else: 
        centroids = initialize_centroids_forgy(data, num_centroids)

    
    assignments  = assign_to_cluster(data, centroids)
    for i in range(100): # max number of iteration = 100
        print(f"Intra distance after {i} iterations: {mean_intra_distance(data, assignments, centroids)}")
        centroids = update_centroids(data, assignments)
        new_assignments = assign_to_cluster(data, centroids)
        if np.all(new_assignments == assignments): # stop if nothing changed
            break
        else:
            assignments = new_assignments

    return new_assignments, centroids, mean_intra_distance(data, new_assignments, centroids)         


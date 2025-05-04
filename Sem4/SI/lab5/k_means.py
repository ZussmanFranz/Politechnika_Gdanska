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
    n_samples = data.shape[0]
    sample_len = data.shape[1]

    # Ensure that the k <= n_samples
    k = min(k, n_samples)

    # Initialize centroids
    centroids = np.zeros((k, sample_len)).tolist()

    # First centroid is initialized randomly
    centroids[0] = data[np.random.choice(n_samples)]

    # 2: for i in 1...k select centroid, which is farest from all the others

    # Determine the farest location from centroids chosen before
    for i in range(1, k):
        centroids[i] = data[find_farest_point(data, centroids[:i])]

    return centroids

def find_farest_point(data, centroids):
    max_distance = 0
    choosen_index = 0

    for index, element in enumerate(data):
        distance = 0
        
        for centroid in centroids:
            distance += calculate_distance(element, centroid)
        
        if distance > max_distance:
            max_distance = distance
            choosen_index = index

    return choosen_index

def calculate_distance(from_element, to_element):
    return np.sqrt(np.sum((to_element - from_element)**2))

def assign_to_cluster(data, centroid):
    # TODO find the closest cluster for each data point
    return None

def update_centroids(data, assignments):
    # TODO find new centroids based on the assignments
    # HINT: calculate the mean value of every observation, which belongs to your centroid
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


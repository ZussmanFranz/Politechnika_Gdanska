from k_means import k_means, initialize_centroids_kmeans_pp, assign_to_cluster
import pandas as pd
import numpy as np

# Visualization:
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def visualize_initial_kpp(features, kpp_centroids, random_centroids):
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    # Plot all data points (light gray)
    ax.scatter(features[:, 0], features[:, 1], features[:, 2], c='lightgray', label='Data Points')

    # Plot K-Means++ centroids (red)
    ax.scatter(kpp_centroids[:, 0], kpp_centroids[:, 1], kpp_centroids[:, 2],
               c='red', marker='X', s=100, label='K-Means++ Centroids')

    # Plot Random centroids (blue)
    ax.scatter(random_centroids[:, 0], random_centroids[:, 1], random_centroids[:, 2],
               c='blue', marker='D', s=100, label='Random Centroids')

    ax.set_xlabel('Sepal Length')
    ax.set_ylabel('Sepal Width')
    ax.set_zlabel('Petal Length')
    ax.legend()
    ax.set_title("Initial Centroids: K-Means++ vs Random")

    plt.show()

def visualize_assignments(features, assignments, centroids):
    from matplotlib import cm

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    # Define distinct colors for up to 10 clusters using colormap
    colors = cm.get_cmap('tab10', np.max(assignments)+1)

    for cluster_idx in np.unique(assignments):
        cluster_points = features[np.array(assignments) == cluster_idx]
        centroid = centroids[cluster_idx]

        # Plot all points in this cluster
        ax.scatter(cluster_points[:, 0], cluster_points[:, 1], cluster_points[:, 2],
                   color=colors(cluster_idx), label=f"Cluster {cluster_idx}", alpha=0.6)

        # Plot centroid for this cluster
        ax.scatter(centroid[0], centroid[1], centroid[2],
                   color=colors(cluster_idx), marker='X', s=150, edgecolor='black')

    ax.set_xlabel('Sepal Length')
    ax.set_ylabel('Sepal Width')
    ax.set_zlabel('Petal Length')
    ax.set_title("Data Points Clustered and Centroids")
    ax.legend()
    plt.show()

def visualized_test_program():
    data = load_iris()
    features, classes = data
    print(f'Features:\n{features}\n')

    n_samples = features.shape[0]
    random_centroids = features[np.random.choice(n_samples, 3, replace=False)]
    print(f'Random Centroids:\n{random_centroids}')

    centroids = np.array(initialize_centroids_kmeans_pp(features, 3))

    print(f'Centroids k++:\n{centroids}')

    assignments = assign_to_cluster(features, centroids)

    visualize_initial_kpp(features[:, :3], centroids[:, :3], random_centroids[:, :3])
    visualize_assignments(features[:, :3], assignments, centroids[:, :3])

# --- Visualization is over


def load_iris():
    data = pd.read_csv("data/iris.data", names=["sepal_length", "sepal_width", "petal_length", "petal_width", "class"])
    print(data)
    classes = data["class"].to_numpy()
    features = data.drop("class", axis=1).to_numpy()
    return features, classes

def evaluate(clusters, labels):
    for cluster in np.unique(clusters):
        labels_in_cluster = labels[clusters==cluster]
        print(f"Cluster: {cluster}")
        for label_type in np.unique(labels):
            print(f"Num of {label_type}: {np.sum(labels_in_cluster==label_type)}")
    

def clustering(kmeans_pp):
    data = load_iris()
    features, classes = data
    intra_class_variance = []
    for i in range(100):
        assignments, centroids, error = k_means(features, 3, kmeans_pp)
        evaluate(assignments, classes)
        intra_class_variance.append(error)
    print(f"Mean intra-class variance: {np.mean(intra_class_variance)}")

if __name__=="__main__":
    # Demonstarion of clustering and assignment in 3-d plot.
    # visualized_test_program()

    clustering(kmeans_pp = True)
    # clustering(kmeans_pp = False)

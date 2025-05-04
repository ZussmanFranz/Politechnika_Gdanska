from k_means import k_means, initialize_centroids_kmeans_pp
import pandas as pd
import numpy as np

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
    data = load_iris()
    features, classes = data
    print(f'Features:\n{features}\n')

    n_samples = features.shape[0]
    centroids = features[np.random.choice(n_samples, 3, replace=False)]
    print(f'Random Centroids:\n{centroids}')

    # Initialize centroids
    centroids[range(0, 3)] = np.zeros(features.shape[1])

    # centroids[0] = features[np.random.choice(n_samples)]
    centroids[0] = features[np.random.choice(n_samples)]

    example_point = [1.1, 2.2, 3.3, 4.4]

    print(f'K++ Centroids: {centroids}\nExample point: {example_point}')

    distance = np.sqrt(np.sum((example_point - centroids[0])**2))

    print(f'Distance between {example_point} and {centroids[0]}: {distance}')

    centroids = initialize_centroids_kmeans_pp(features, 3)

    print(f'Centroids k++:\n{centroids}')

    # clustering(kmeans_pp = True)
    # clustering(kmeans_pp = False)

import copy

import numpy as np

class Node:
    def __init__(self):
        self.left_child = None
        self.right_child = None
        self.feature_idx = None
        self.feature_value = None
        self.node_prediction = None

    def gini_best_score(self, y, possible_splits):
        best_gini = -np.inf
        best_idx = 0

        total_samples = len(y)

        def gini_impurity(pos, neg):
            total = pos + neg
            if total == 0:
                return 0
            prob_pos = pos / total
            prob_neg = neg / total
            return 1.0 - (prob_pos ** 2 + prob_neg ** 2)

        for split in possible_splits:
            left_y = y[:split+1]
            right_y = y[split+1:]

            left_pos = np.sum(left_y == 1)
            left_neg = np.sum(left_y == 0)
            right_pos = np.sum(right_y == 1)
            right_neg = np.sum(right_y == 0)

            # print(f'\tleft_pos:{left_pos}, left_neg:{left_neg}\n\tright_pos:{right_pos}, right_neg:{right_neg}\n')

            left = left_pos + left_neg
            right = right_pos + right_neg

            gini_left = gini_impurity(left_pos, left_neg)
            gini_right = gini_impurity(right_pos, right_neg)

            weighted_gini = (left / total_samples) * gini_left + (right / total_samples) * gini_right

            gini_gain = 1.0 - weighted_gini

            if gini_gain > best_gini:
                best_gini = gini_gain
                best_idx = split

        return best_idx, best_gini


    def split_data(self, X, y, idx, val):
        left_mask = X[:, idx] < val
        return (X[left_mask], y[left_mask]), (X[~left_mask], y[~left_mask])

    def find_possible_splits(self, data):
        possible_split_points = []
        for idx in range(data.shape[0] - 1):
            if data[idx] != data[idx + 1]:
                possible_split_points.append(idx)
        return possible_split_points

    def find_best_split(self, X, y, feature_subset):
        best_gini = -np.inf
        best_split = None

        # Select features to consider
        if feature_subset and feature_subset < X.shape[1]:
            features_to_consider = np.random.choice(X.shape[1], size=feature_subset, replace=False)
        else:
            features_to_consider = range(X.shape[1])

        for d in features_to_consider:
            order = np.argsort(X[:, d])
            y_sorted = y[order]
            possible_splits = self.find_possible_splits(X[order, d])
            idx, value = self.gini_best_score(y_sorted, possible_splits)
            if value > best_gini:
                best_gini = value
                best_split = (d, order[[idx, idx + 1]])

        if best_split is None:
            return None, None

        best_value = np.mean(X[best_split[1], best_split[0]])

        return best_split[0], best_value

    def predict(self, x):
        if self.feature_idx is None:
            return self.node_prediction
        if x[self.feature_idx] < self.feature_value:
            return self.left_child.predict(x)
        else:
            return self.right_child.predict(x)

    def train(self, X, y, params):

        self.node_prediction = np.mean(y)
        if X.shape[0] == 1 or self.node_prediction == 0 or self.node_prediction == 1:
            return True

        self.feature_idx, self.feature_value = self.find_best_split(X, y, params["feature_subset"])
        if self.feature_idx is None:
            return True

        (X_left, y_left), (X_right, y_right) = self.split_data(X, y, self.feature_idx, self.feature_value)

        if X_left.shape[0] == 0 or X_right.shape[0] == 0:
            self.feature_idx = None
            return True

        # max tree depth
        if params["depth"] is not None:
            params["depth"] -= 1
        if params["depth"] == 0:
            self.feature_idx = None
            return True

        # create new nodes
        self.left_child, self.right_child = Node(), Node()
        self.left_child.train(X_left, y_left, copy.deepcopy(params))
        self.right_child.train(X_right, y_right, copy.deepcopy(params))

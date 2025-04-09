import numpy as np
import pandas as pd


def generate_data():
    TRAIN_SAMPLES = 100
    TEST_SAMPLES = 20
    FEATURE_DIM = 5

    X_train = np.random.rand(TRAIN_SAMPLES, FEATURE_DIM)
    y_train = np.random.binomial(1, 0.5, TRAIN_SAMPLES)
    X_test = np.random.rand(TEST_SAMPLES, FEATURE_DIM)
    y_test = np.random.binomial(1, 0.5, TEST_SAMPLES)
    return (X_train, y_train), (X_test, y_test)


def load_titanic():
    data = pd.read_csv("titanic.csv")
    data = data[["Pclass", "Fare", "Parch", "SibSp", "Age", "Sex", "Survived"]]
    data = data.dropna().reset_index(drop=True)
    data["Sex"] = [1 if sex == "female" else 0 for sex in data["Sex"]]
    test_idx = np.random.choice(range(data.shape[0]), round(0.2*data.shape[0]), replace=False)
    data_test = data.iloc[test_idx, :]
    data_train = data.drop(test_idx, axis=0)
    X_train = data_train.drop("Survived", axis=1).to_numpy()
    y_train = data_train["Survived"].to_numpy()
    X_test = data_test.drop("Survived", axis=1).to_numpy()
    y_test = data_test["Survived"].to_numpy()
    return (X_train, y_train), (X_test, y_test)
    
    
def load_example_data():
    # dane do porowania poprawności liczenia Gini Index ze strony
    # https://blog.quantinsti.com/gini-index/
    data = pd.DataFrame(
        [
            ["Positive", "Low", "High", "Up"],
            ["Negative", "High", "Low", "Down"],
            ["Positive", "Low", "High", "Up"],
            ["Negative", "Low", "High", "Down"],
            ["Negative", "High", "High", "Down"],
            ["Positive", "High", "High", "Up"],
            ["Positive", "Low", "Low", "Down"],
            ["Negative", "Low", "High", "Down"],
            ["Positive", "Low", "Low", "Down"],
            ["Positive", "High", "High", "Up"],
        ],
        columns=["Trend", "Interest", "Volume", "Return"],
    )
    data["Trend"] = [1 if t == "Positive" else 0 for t in data["Trend"]]
    data["Interest"] = [1 if t == "High" else 0 for t in data["Interest"]]
    data["Volume"] = [1 if t == "High" else 0 for t in data["Volume"]]
    data["Return"] = [1 if t == "Up" else 0 for t in data["Return"]]
    X_train = data.drop("Return", axis=1).to_numpy()
    y_train = data["Return"].to_numpy()
    return (X_train, y_train), (X_train.copy(), y_train.copy())

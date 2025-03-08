import numpy as np
import matplotlib.pyplot as plt

from data import get_data, inspect_data, split_data

data = get_data()
inspect_data(data)

train_data, test_data = split_data(data)

# Simple Linear Regression
# predict MPG (y, dependent variable) using Weight (x, independent variable) using closed-form solution
# y = theta_0 + theta_1 * x - we want to find theta_0 and theta_1 parameters that minimize the prediction error

# We can calculate the error using MSE metric:
# MSE = SUM (from i=1 to n) (actual_output - predicted_output) ** 2

# get the columns
y_train = train_data['MPG'].to_numpy()
x_train = train_data['Weight'].to_numpy()

y_test = test_data['MPG'].to_numpy()
x_test = test_data['Weight'].to_numpy()

# TODO: calculate closed-form solution
x_train = x_train.reshape(-1, 1)
X = np.hstack((np.ones((x_train.shape[0], 1)), x_train))
y_train = y_train.reshape(-1, 1)
# theta_best = np.linalg.inv(X.T @ X) @ (X.T @ y_train)
theta_best = np.linalg.solve(X.T @ X, X.T @ y_train)
# theta_best = [0, 0]

y_train_pred = X @ theta_best

x_test = x_test.reshape(-1, 1)
y_test = y_test.reshape(-1, 1)
X_test = np.hstack((np.ones((x_test.shape[0], 1)), x_test))
y_test_pred = X_test @ theta_best

# TODO: calculate error
def mse(y_pred, y):
    return np.mean((y_pred - y)**2)

mse_train = mse(y_train_pred, y_train)
mse_test = mse(y_test_pred, y_test)

print(f"{mse_train=}, {mse_test=}")


# plot the regression line
x = np.linspace(min(x_test), max(x_test), 100)
y = float(theta_best[0]) + float(theta_best[1]) * x
plt.plot(x, y)
plt.scatter(x_test, y_test)
plt.xlabel('Weight')
plt.ylabel('MPG')
plt.show()


xm = np.mean(X[:, 1])
xs = np.std(X[:, 1])

ym = np.mean(y_train)
ys = np.std(y_train)

# TODO: standardization
def standardize(x, m=None, s=None):

    if m is None:
        m = np.mean(x)
    if s is None:
        s = np.std(x)

    return (x-m)/s


X[:, 1] = standardize(X[:, 1])
y_train = standardize(y_train)

# TODO: calculate theta using Full-Batch Gradient Descent

eta = 0.1

theta = np.random.randn(2, 1)
m = X.shape[0]

for epoch in range(1000):
    y_train_pred = X @ theta
    grad = 2/m * X.T @ (y_train_pred - y_train)
    theta -= eta * grad
    if epoch % 20 == 0:
        print(mse(y_train_pred, y_train))





# TODO: calculate error

# plot the regression line
x = np.linspace(min(x_test), max(x_test), 100)
#y = float(theta[0]) + float(theta[1]) * x

x = standardize(x, m=xm, s=xs)
y_pred = float(theta[0]) + float(theta[1]) * x

x_test = standardize(x_test, m=xm, s=xs)
y_test = standardize(y_test, m=ym, s=ys)

plt.plot(x, y_pred)
plt.scatter(x_test, y_test)
plt.xlabel('Weight')
plt.ylabel('MPG')
plt.show()
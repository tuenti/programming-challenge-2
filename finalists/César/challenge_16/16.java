import sys, itertools

from numpy import zeros, e, array, log, ones, dot
from scipy.optimize import fmin_bfgs

def sigmoid(x):
    #print "sigmoid, x = ", x.flatten()
    return 1.0 / (1.0 + e ** (-1.0 * x))

def cost_function_reg(theta, X, y, l):
    #print "J, theta = ", theta
    m, n = X.shape
    theta = array([theta]).T
    h = sigmoid(X.dot(theta))
    thetaR = theta[1:, 0]
    J = (1.0 / m) * ((-y.T.dot(log(h))) - ((1 - y.T).dot(log(1.0 - h)))) \
            + (l / (2.0 * m)) * (thetaR.T.dot(thetaR))
    #print "J = ", J.flatten()
    return J.flatten()

def gradient_reg(theta, X, y, l):
    #print "grad, theta = ", theta
    m, n = X.shape
    theta = array([theta]).T
    h = sigmoid(X.dot(theta))
    delta = h - y
    sumdelta = delta.T.dot(X[:, 1])
    grad1 = (1.0 / m) * sumdelta

    XR = X[:, 1:X.shape[1]]
    sumdelta = delta.T.dot(XR)
    grad = (1.0 / m) * (sumdelta + l * theta[1:, 0])

    out = zeros(shape=(grad.shape[0], grad.shape[1] + 1))
    out[:, 0] = grad1
    out[:, 1:] = grad
    #print "grad = ", out.T.flatten()
    return out.T.flatten()

def compute_parameters(X, y):
    initial_theta = zeros(shape=(X.shape[1], 1))
    return array([fmin_bfgs(cost_function_reg, initial_theta, gradient_reg, (X, y, 0), disp=False)]).T

def predict(theta, X):
    h = sigmoid(X.dot(theta))
    return [h[it, 0] > 0.5 for it in range(h.shape[0])]

if __name__ == "__main__":
    R = int(sys.stdin.readline())
    U = int(sys.stdin.readline())
    N = int(sys.stdin.readline())
    # Build the training matrices...
    input_X, input_y = [], []
    for l in range(R):
        line = sys.stdin.readline().strip().split(' ')
        input_X.append([1.0] + map(float, line[1:]))
        input_y.append([1.0] if line[0] == 'M' else [0.0])
    max_in_X = max(map(max, input_X))
    X = array(input_X) / max_in_X
    y = array(input_y)
    # ... the test matrix...
    input_Xtest = []
    for l in range(U):
        line = sys.stdin.readline().strip().split(' ')
        input_Xtest.append([1.0] + map(float, line))
    Xtest = array(input_Xtest, float) / max_in_X
    # ... train the classifier...
    theta = compute_parameters(X, y)
    # ... and classify the unknown entries.
    prediction = predict(theta, Xtest)
    # Finally, add up the selected entries.
    print int(dot(prediction, map(lambda r: sum(r[1:]), input_Xtest)))





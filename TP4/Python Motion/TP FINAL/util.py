import numpy as np
import cv2 as cv

def space_translate(x, y, prev):
    if(type(prev) == None):
        return None
    for i in range(prev.shape[0]):
            prev[i][0][0] = prev[i][0][0] + x
            prev[i][0][1] = prev[i][0][1] + y
    return prev


def get_new_box_coordinates(prev, h, w):

    SIGMA_INTERVAL = 1

    prev_x = []
    prev_y = []

    for i in range(prev.shape[0]):
        prev_x.append(prev[i][0][0])
        prev_y.append(prev[i][0][1])

    x_mean = np.mean(np.asarray(prev_x))
    y_mean = np.mean(np.asarray(prev_y))

    x_std = np.std(np.asarray(prev_x))
    y_std = np.std(np.asarray(prev_y))

    for i in range(len(prev_x)):
        if (i >= len(prev_x)):
            break
        if (abs(prev_x[i] - x_mean) > SIGMA_INTERVAL * x_std):
            del prev_x[i]

    for i in range(len(prev_y)):
        if (i >= len(prev_y)):
            break
        if (abs(prev_y[i] - y_mean) > SIGMA_INTERVAL * y_std):
            del prev_y[i]

    x = int(x_mean - (w / 2))
    y = int(y_mean - (h / 2))

    return (x, y)
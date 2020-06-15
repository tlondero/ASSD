import cv2 as cv
import params as prm
import numpy as np

def captureROI(capture_device):

    prev = None
    while (prev is None):

        capture_device.read()
        ret, frame = capture_device.read()
        bbox = cv.selectROI("sparse optical flow", frame, False)
        x = bbox[0]
        y = bbox[1]
        w = bbox[2]
        h = bbox[3]
        prev_gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
        prev = cv.goodFeaturesToTrack(prev_gray[y:y+h, x:x+w], mask=None, **prm.feature_params)

    return prev, prev_gray, x, y, w, h


def space_translate(x, y, prev):
    if prev is None:
        return None
    for i in range(prev.shape[0]):
            prev[i][0][0] = prev[i][0][0] + x
            prev[i][0][1] = prev[i][0][1] + y
    return prev

def calculate_means_and_std(prev):

    prev_x = []
    prev_y = []

    for i in range(prev.shape[0]):
        prev_x.append(prev[i][0][0])
        prev_y.append(prev[i][0][1])

    x_mean = np.mean(np.asarray(prev_x))
    y_mean = np.mean(np.asarray(prev_y))
    var = np.sqrt((np.std(np.asarray(prev_x))**2 + np.std(np.asarray(prev_y))**2))

    return (x_mean, y_mean, var)

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

    x_mean = np.mean(np.asarray(prev_x))
    y_mean = np.mean(np.asarray(prev_y))

    x = int(x_mean - (w / 2))
    y = int(y_mean - (h / 2))

    return (x, y)

def recalculateFeatures(prev, prev_gray, h, w):
    x, y = get_new_box_coordinates(prev, h, w)  # New bounding box coordinates
    prev = cv.goodFeaturesToTrack(prev_gray[y:y + h, x:x + w], mask=None,
                                  **prm.feature_params)  # Applying shi-tomasi method
    prev = space_translate(x, y, prev)  # Coordinate transform from bounding box to camera window

    return prev, x, y

def measureFeatures(frame, prev, prev_gray, kalman):
    gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
    next_, status, error = cv.calcOpticalFlowPyrLK(prev_gray, gray, prev, None, **prm.lk_params)
    good_old = prev[status == 1]
    good_new = next_[status == 1]

    (mux, muy, var) = calculate_means_and_std(next_)
    kalman.predict()
    kalman.correct(float(mux), float(muy))

    prev_gray = gray.copy()
    prev = good_new.reshape(-1, 1, 2)

    return good_new, good_old, prev_gray, prev

def drawEstimate(good_new, good_old, frame, kalman):
    for i, (new, old) in enumerate(zip(good_new, good_old)):
        a, b = new.ravel()
        frame = cv.circle(frame, (int(a), int(b)), 3, prm.ft_color, -1)
        frame = cv.circle(frame,
                          (int(kalman.statePost[0][0]),
                           int(kalman.statePost[1][0])),
                          int(np.sqrt(kalman.errorCovPost[0][0] ** 2 + kalman.errorCovPost[1][1] * 2) * 100),
                          prm.kalman_color, 3)

    frame = cv.circle(frame, (int(kalman.statePost[0][0]), int(kalman.statePost[1][0])), int(np.sqrt(kalman.errorCovPost[0][0]**2 + kalman.errorCovPost[1][1]*2)*100), (0, 130, 255), 3)
    output = cv.add(frame, 0)
    cv.imshow("sparse optical flow", output)
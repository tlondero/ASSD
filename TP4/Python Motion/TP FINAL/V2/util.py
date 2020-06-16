import cv2 as cv
import params as prm
import numpy as np

def captureROI(capture_device):

    prev = None
    x, y, w, h, = 0, 0, 0, 0
    prev_gray = [[[]]]
    while (prev is None):

        capture_device.read()
        ret, frame = capture_device.read()
        bbox = cv.selectROI("sparse optical flow", frame, False)
        x = bbox[0]
        y = bbox[1]
        w = bbox[2]
        h = bbox[3]

        if prm.COLOR_ALGORITHM is True:
            selection = np.asarray(frame[y:y + h, x:x + w])
            b, g, r = [], [], []

            yy, xx, col = np.shape(selection)
            for i in range(yy):
                for j in range(xx):
                    b.append(selection[i, j, 0])
                    g.append(selection[i, j, 1])
                    r.append(selection[i, j, 2])
            median_b, median_g, median_r = np.median(b), np.median(g), np.median(r)

            bgr_mask = np.uint8([[[median_b, median_g, median_r]]])
            hsv_mask = cv.cvtColor(bgr_mask, cv.COLOR_BGR2HSV)

            lower_thr = np.array([np.int32(hsv_mask[0, 0, :])[0] - prm.HUE_VAR, np.int32(hsv_mask[0, 0, :])[1] - prm.SAT_VAR, np.int32(hsv_mask[0, 0, :])[2] - prm.VAL_VAR])
            upper_thr = np.array([np.int32(hsv_mask[0, 0, :])[0] + prm.HUE_VAR, np.int32(hsv_mask[0, 0, :])[1] + prm.SAT_VAR, np.int32(hsv_mask[0, 0, :])[2] + prm.VAL_VAR])

            hsv = cv.cvtColor(frame, cv.COLOR_BGR2HSV)
            mask = cv.inRange(hsv, lower_thr, upper_thr)
            frame = cv.bitwise_and(frame, frame, mask=mask)

            prev_gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
            prev = cv.goodFeaturesToTrack(prev_gray[y:y+h, x:x+w], mask=None, **prm.feature_params)

            return prev, prev_gray, x, y, w, h, lower_thr, upper_thr

        prev_gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
        prev = cv.goodFeaturesToTrack(prev_gray[y:y + h, x:x + w], mask=None, **prm.feature_params)

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

def measureFeatures(error_feature, frame, prev, prev_gray, kalman):
    gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
    kalman.predict()

    if prev is None:
        error_feature = True

    if not error_feature:
        next_, status, error = cv.calcOpticalFlowPyrLK(prev_gray, gray, prev, None, **prm.lk_params)

        if np.any(status):
            error_feature = False
            good_old = prev[status == 1]
            good_new = next_[status == 1]
            (mux, muy, var) = calculate_means_and_std(next_)
            kalman.correct(float(mux), float(muy))
            prev = good_new.reshape(-1, 1, 2)
        else:
            error_feature = True
            good_new = 0
            good_old = 0
            prev = 0
    else:
        error_feature = True
        good_new = 0
        good_old = 0
        prev = 0

    prev_gray = gray.copy()
    return error_feature, good_new, good_old, prev_gray, prev

def drawEstimate(error, good_new, good_old, frame, kalman, dyn_h, dyn_w):
    if not error:
        for i, (new, old) in enumerate(zip(good_new, good_old)):
            a, b = new.ravel()
            frame = cv.circle(frame, (int(a), int(b)), 3, prm.ft_color, -1)
    else:
        x = np.int(kalman.statePost[0][0])
        y = np.int(kalman.statePost[1][0])
        cv.putText(frame, 'Tracking failure', (20, 40), prm.font, 1, (0, 0, 255), 2, cv.LINE_AA)
        cv.rectangle(frame, (int(x - (dyn_w/2)), int(y - (dyn_h/2))), (int(x + (dyn_w/2)), int(y + (dyn_h/2))), prm.ROI_color, 4)

    frame = cv.circle(frame, (int(kalman.statePost[0][0]), int(kalman.statePost[1][0])), int(35), prm.kalman_color, 3)
    output = cv.add(frame, 0)
    cv.imshow("sparse optical flow", output)

def searchObject(kalman, dyn_h, dyn_w, h, w, frame, error):

    gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
    x = np.int(kalman.statePost[0][0])
    y = np.int(kalman.statePost[1][0])
    prev = cv.goodFeaturesToTrack(gray[int(y - (dyn_h/2)):int(y + (dyn_h/2)), int(x - (dyn_w/2)):int(x + (dyn_w/2))], mask=None,**prm.feature_params)  # Applying shi-tomasi method
    if prev is not None:
        error = False
        prev = space_translate(x - (dyn_w/2), y - (dyn_h/2), prev)  # Coordinate transform from bounding box to camera window
        dyn_h, dyn_w = h, w
    else:
        error = True
        dyn_h += 2
        dyn_w += 2
    return error, prev, dyn_h, dyn_w
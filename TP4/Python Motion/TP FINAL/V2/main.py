import cv2 as cv
import params as prm
import util as util
import kalman

kalman = kalman.KalmanFilter()

cap = cv.VideoCapture(cv.samples.findFile("gido.mp4"))
#cap = cv.VideoCapture(0)

lower_thr, upper_thr = [],[]

if prm.COLOR_ALGORITHM is True:
    prev, prev_gray, x, y, w, h, lower_thr, upper_thr = util.captureROI(cap)
else:
    prev, prev_gray, x, y, w, h= util.captureROI(cap)
prev = util.space_translate(x, y, prev)

frame = cap.read()

frame_num = 0
error = False
dyn_h = h
dyn_w = w
frame = 0
while(cap.isOpened()):

    frame_num += 1
    ret, frame_real = cap.read()

    if prm.COLOR_ALGORITHM is True:
        frame = frame_real
        hsv = cv.cvtColor(frame, cv.COLOR_BGR2HSV)
        mask = cv.inRange(hsv, lower_thr, upper_thr)
        frame = cv.bitwise_and(frame, frame, mask=mask)

    if((frame_num != 0 and frame_num%prm.RECALC_EVERY_FRAMES == 0 and not error)):
        frame_num = 0
        prev, x, y = util.recalculateFeatures(prev, prev_gray, h, w)

    if error:
        error, prev, new_dyn_h, new_dyn_w =  util.searchObject(kalman, dyn_h, dyn_w, h, w, frame, error)
        dyn_h, dyn_w = new_dyn_h, new_dyn_w

    if prm.COLOR_ALGORITHM is True:
        error, good_new, good_old, prev_gray, prev= util.measureFeatures(error, frame, prev, prev_gray, kalman)
    else:
        error, good_new, good_old, prev_gray, prev = util.measureFeatures(error, frame_real, prev, prev_gray, kalman)

    util.drawEstimate(error, good_new, good_old, frame_real, kalman, dyn_h, dyn_w, frame)

    if cv.waitKey(10) & 0xFF == ord('q'):
        break
    if  (cv.waitKey(10) & 0xFF == ord('r')):
        if prm.COLOR_ALGORITHM is True:
            prev, prev_gray, x, y, w, h, lower_thr, upper_thr = util.captureROI(cap)
        else:
            prev, prev_gray, x, y, w, h = util.captureROI(cap)
        prev = util.space_translate(x, y, prev)
        error = False
        dyn_w = w
        dyn_h = h

cap.release()
cv.destroyAllWindows()

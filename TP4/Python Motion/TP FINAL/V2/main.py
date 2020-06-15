import cv2 as cv
import params as prm
import util as util
import kalman

kalman = kalman.KalmanFilter()
cap = cv.VideoCapture(0)

prev, prev_gray, x, y, w, h = util.captureROI(cap)
prev = util.space_translate(x, y, prev)

frame_num = 0
while(cap.isOpened()):

    frame_num += 1
    ret, frame = cap.read()

    if((frame_num != 0 and frame_num%prm.RECALC_EVERY_FRAMES == 0)):
        frame_num = 0
        prev, x, y = util.recalculateFeatures(prev, prev_gray, h, w)

    good_new, good_old, prev_gray, prev= util.measureFeatures(frame, prev, prev_gray, kalman)

    util.drawEstimate(good_new, good_old, frame, kalman)

    if cv.waitKey(10) & 0xFF == ord('q'):
        break
    if  cv.waitKey(10) & 0xFF == ord('r'):
        prev, prev_gray, x, y, w, h = util.captureROI(cap)
        prev = util.space_translate(x, y, prev)

cap.release()
cv.destroyAllWindows()

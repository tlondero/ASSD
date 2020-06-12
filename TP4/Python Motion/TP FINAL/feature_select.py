import cv2 as cv
import numpy as np

cap = cv.VideoCapture(0)

ret, first_frame = cap.read()

bbox = cv.selectROI("Capture", first_frame, False)
x = bbox[0]
y = bbox[1]
w = bbox[2]
h = bbox[3]
print(f"Primera bounding box {bbox}")


# bbox1 = cv.selectROI("Capture", first_frame, False)
# x1 = bbox1[0]
# y1 = bbox1[1]
# w1 = bbox1[2]
# h1 = bbox1[3]
# print(f"Segunda bounding box {bbox1}")


prev_gray = cv.cvtColor(first_frame, cv.COLOR_BGR2GRAY)

# Parameters for Shi-Tomasi corner detection
feature_params = dict(maxCorners=300, qualityLevel=0.2,
                      minDistance=2, blockSize=7)

prev = cv.goodFeaturesToTrack(
    prev_gray[y:y+h, x:x+w], mask=None, **feature_params)


ret, frame = cap.read()


for p in prev:
    cv.Circle(frame, (p[0], p[1]), (0, 255, 0), -1)


cv.imshow("Capture", frame[y:y+h, x:x+w])


print(prev)

while(cap.isOpened()):

    # ret, frame = cap.read()

    # cv.imshow("Capture", frame[y:y+h, x:x+w])

    if cv.waitKey(10) & 0xFF == ord('q'):
        break

cap.destroy()
cv.destroyAllWindows()

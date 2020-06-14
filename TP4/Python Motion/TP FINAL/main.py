import cv2 as cv
import util as util
import numpy as np

# Parameters for Shi-Tomasi corner detection
feature_params = dict(maxCorners=1000, qualityLevel=0.99,
                      minDistance=2, blockSize=7)

# Parameters for Lucas-Kanade optical flow
lk_params = dict(winSize=(15, 15), maxLevel=4, criteria=(
    cv.TERM_CRITERIA_EPS | cv.TERM_CRITERIA_COUNT, 10, 0.03))

# The video feed is read in as a VideoCapture object
# cap = cv.VideoCapture("shibuya.mp4")
cap = cv.VideoCapture(0)

# Variable for color to draw optical flow track
color = (0, 255, 0)
prev = None
while(prev is None):
    # ret = a boolean return value from getting the frame, first_frame = the first frame in the entire video sequence
    ret, first_frame = cap.read()

    #Convert to gray-scale
    prev_gray = cv.cvtColor(first_frame, cv.COLOR_BGR2GRAY)

    # Aca vamos a seleccionar con el mouse el area donde aplicar shi-tomasi
    bbox = cv.selectROI("sparse optical flow", first_frame, False)

    x = bbox[0]
    y = bbox[1]
    w = bbox[2]
    h = bbox[3]

    # Finds the strongest corners in the first frame by Shi-Tomasi method - we will track the optical flow for these corners
    # https://docs.opencv.org/3.0-beta/modules/imgproc/doc/feature_detection.html#goodfeaturestotrack
    prev = cv.goodFeaturesToTrack(
        prev_gray[y:y+h, x:x+w], mask=None, **feature_params)

#Coordinate transform from bounding box to camera window
prev = util.space_translate(x, y, prev)

# Creates an image filled with zero intensities with the same dimensions as the frame - for later drawing purposes
mask = np.zeros_like(first_frame)

# ret = a boolean return value from getting the frame, frame = the current frame being projected in the video
ret, frame = cap.read()

#Frame counter
frame_num = 0
recalc = False
#Frame count until recalculation
RECALC_EVERY_FRAMES = 40

while(cap.isOpened()):

    frame_num += 1
    #Take camera frame
    ret, frame = cap.read()

    #Recalculation of optical flow points using confidence intervals and shi-tomasi method
    if((frame_num != 0 and frame_num%RECALC_EVERY_FRAMES == 0) or recalc):
        frame_num = 0
        x, y = util.get_new_box_coordinates(prev, h, w) #New bounding box coordinates
        prev = cv.goodFeaturesToTrack(prev_gray[y:y + h, x:x + w], mask=None, **feature_params) #Applying shi-tomasi method
        prev = util.space_translate(x, y, prev)  #Coordinate transform from bounding box to camera window
        recalc = False

    # Converts each frame to grayscale - we previously only converted the first frame to grayscale
    gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)

    # Calculates sparse optical flow by Lucas-Kanade method
    # https://docs.opencv.org/3.0-beta/modules/video/doc/motion_analysis_and_object_tracking.html#calcopticalflowpyrlk
    next_, status, error = cv.calcOpticalFlowPyrLK(
        prev_gray, gray, prev, None, **lk_params)



    # Selects good feature points for previous position
    good_old = prev[status == 1]

    # Selects good feature points for next position
    good_new = next_[status == 1]

    # Draws the optical flow tracks
    for i, (new, old) in enumerate(zip(good_new, good_old)):
        # Returns a contiguous flattened array as (x, y) coordinates for new point
        a, b = new.ravel()
        # Returns a contiguous flattened array as (x, y) coordinates for old point
        c, d = old.ravel()
        # Draws line between new and old position with green color and 2 thickness
        mask = cv.line(mask, (a, b), (c, d), color, 2)
        # Draws filled circle (thickness of -1) at new position with green color and radius of 3
        frame = cv.circle(frame, (a, b), 3, color, -1)

    mask = 0

    # Overlays the optical flow tracks on the original frame
    output = cv.add(frame, mask)

    # Updates previous frame
    prev_gray = gray.copy()

    # Updates previous good feature points
    prev = good_new.reshape(-1, 1, 2)

    # Opens a new window and displays the output frame
    cv.imshow("sparse optical flow", output)

    # Frames are read by intervals of 10 milliseconds. The programs breaks out of the while loop when the user presses the 'q' key
    if cv.waitKey(10) & 0xFF == ord('q'):
        break

# The following frees up resources and closes all windows
cap.release()
cv.destroyAllWindows()

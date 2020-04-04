import cv2
import numpy as np
import time


Ctrack = [255,255,255]#BGR


def dist(color1,color2):
    return np.abs(color1[0]-color2[0])+np.abs(color1[1]-color2[1])+np.abs(color1[2]-color2[2])

def clickPressed(event,x,y,flags,param):
    global Ctrack
    if(event == cv2.EVENT_LBUTTONDOWN):
        print("X = ",x," Y= ",y)
        Ctrack =  frame[y][x]

HEIGHT=480
WIDTH=640


currColor = [0,0,0]
prevColor = [0,0,0]
threshold= 100

time_count = 0
start_time=0

cap = cv2.VideoCapture(1)
cap.open(0)
PrevImg = np.zeros([HEIGHT, WIDTH, 3], np.uint8)
CurrImg = np.zeros([HEIGHT, WIDTH, 3], np.uint8)
ret=0
frame=0
NFrame = False

while(True):

    # Capture frame-by-frame
 #   frame = cv2.imread('test.PNG')
 #   cv2.setMouseCallback('image', clickPressed,Ctrack)
    if ret:
        end_time = time.time()
        time_count += end_time - start_time
        if (time_count > 0.01):
            PrevImg=np.copy(CurrImg)
            start_time = time.time()
            time_count = 0
            NFrame=True

    else:
        start_time = time.time()
        time_count = 0


    ret, frame = cap.read()

#    cv2.setMouseCallback('image', clickPressed)
    cv2.setMouseCallback('frame', clickPressed)
    # Our operations on the frame come here
    screen = frame

    count=0
    cols = len(frame[0])
    fils = len(frame)


    xposv=[]
    yposv=[]

    xpos=0
    ypos=0
    if(NFrame):
        for x in range(int(fils/10)):
            for y in range(int(cols/10)):
                prevColor = PrevImg[10*x][10*y]
                currentColor = frame[10*x][10*y]
                d = np.abs(float(currentColor[0]) - float(prevColor[0])) + np.abs(float(currentColor[1]) - float(prevColor[1])) + np.abs(
                    float(currentColor[2]) - float(prevColor[2]))
                if (d > threshold):
                    xposv.append(10*x)
                    yposv.append(10*y)
                    count += 1
        NFrame=False

    if(count>10):
        xpos=np.mean(xposv)
        ypos = np.mean(yposv)
        sigma= np.sqrt(np.std(xposv)**2+np.std(yposv)**2)
        xposv.clear()
        yposv.clear()
        CurrImg = np.copy(frame)
        screen = cv2.circle(screen, (int(ypos),int(xpos)),10 , (0,255,0),2)


    # Display the resulting frame

    cv2.imshow('frame',screen)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()


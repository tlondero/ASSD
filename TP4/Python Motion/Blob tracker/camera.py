import cv2
import numpy as np


Ctrack = [255,255,255]#BGR


def dist(color1,color2):
    return np.abs(color1[0]-color2[0])+np.abs(color1[1]-color2[1])+np.abs(color1[2]-color2[2])

def clickPressed(event,x,y,flags,param):
    global Ctrack
    if(event == cv2.EVENT_LBUTTONDOWN):
        print("X = ",x," Y= ",y)
        Ctrack =  frame[y][x]




currColor = [0,0,0]
threshold= 30
cap = cv2.VideoCapture(0)

while(True):
    # Capture frame-by-frame
 #   frame = cv2.imread('pic.jpg')
    frame = cv2.imread('test.PNG')
 #   ret, frame = cap.read()
 #   cv2.setMouseCallback('frame', clickPressed)
    cv2.setMouseCallback('image', clickPressed,Ctrack)
    # Our operations on the frame come here
    screen = frame

    count=0
    cols = len(frame[0])
    fils = len(frame)

    xposv=[]
    yposv=[]

    xpos=0
    ypos=0
    for x in range(int(fils/10)):
        for y in range(int(cols/10)):

             currentColor = frame[10*x][10*y]
             d = np.abs(float(currentColor[0]) - float(Ctrack[0])) + np.abs(float(currentColor[1]) - float(Ctrack[1])) + np.abs(
                float(currentColor[2]) - float(Ctrack[2]))
             if (d < 50):
                xposv.append(10*x)
                yposv.append(10*y)
                count += 1

    if(count>1):
        xpos=np.mean(xposv)
        xposv.clear()
        ypos = np.mean(yposv)
        yposv.clear()
        screen = cv2.circle(screen, (int(ypos),int(xpos)), 5, (0,255,0),2)
    # Display the resulting frame

    cv2.imshow('image',screen)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()


import cv2
import numpy as np
import time
from Blob import Blob

Ctrack = [255,0,0]#BGR


def dist(color1,color2):
    return np.abs(color1[0]-color2[0])+np.abs(color1[1]-color2[1])+np.abs(color1[2]-color2[2])

def clickPressed(event,x,y,flags,param):
    global Ctrack
    if(event == cv2.EVENT_LBUTTONDOWN):
        Ctrack =  frame[y][x]
        print("X = ",x," Y= ",y)
        print("Color BGR = ",Ctrack)


HEIGHT=480
WIDTH=640
Treshold = 70
blobTreshold=250
blobs = []

currColor = [0,0,0]
prevColor = [0,0,0]

time_count = 0
start_time=0

cap = cv2.VideoCapture(1)
cap.open(0)
ret=0
frame=0
NFrame = False


while(True):

    # Capture frame-by-frame

    if ret:
        end_time = time.time()
        time_count += end_time - start_time
        if (time_count > 0.01):
            start_time = time.time()
            time_count = 0
            NFrame=True

    else:
        start_time = time.time()
        time_count = 0


    ret, frame = cap.read()

    cv2.setMouseCallback('frame', clickPressed)

    # Our operations on the frame come here
    screen = frame

    count=0
    cols = len(frame[0])
    fils = len(frame)
    divfact=10

    xposv=[]
    yposv=[]

    xpos=0
    ypos=0
    if(NFrame):
        for x in range(int(fils/divfact)):
            for y in range(int(cols/divfact)):
                currentColor = frame[divfact * x][divfact * y]
                d = np.abs(float(currentColor[0]) - float(Ctrack[0])) + np.abs(
                    float(currentColor[1]) - float(Ctrack[1])) + np.abs(
                    float(currentColor[2]) - float(Ctrack[2]))
                if (d < Treshold):
                    if(len(blobs)>0):
                        for i in range(len(blobs)):
                            auxblob= Blob(divfact*x,divfact*y,blobTreshold)
                            if(blobs[i].same(auxblob)):
                                blobs[i].expandB(auxblob)
                            else:
                                blobs.append(Blob(divfact*x,divfact*y,blobTreshold))
                                count += 1
                    else:
                        blobs.append(Blob(divfact * x, divfact * y, blobTreshold))
        NFrame=False

    if(count>10):

        for i in range(len(blobs)):
            screen = cv2.rectangle(screen, (int(blobs[i].y ), int(blobs[i].x)),(int(blobs[i].y+blobs[i].h),int(blobs[i].x+blobs[i].w)), (0, 255, 0),thickness=1)
#            screen = cv2.circle(screen, (int(blobs[i].y+blobs[i].h/2), int(blobs[i].x+blobs[i].w/2)), 2, (0, 255, 0), 2)


        blobs.clear()



    # Display the resulting frame

    cv2.imshow('frame',screen)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()


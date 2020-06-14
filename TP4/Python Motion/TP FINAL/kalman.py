import cv2 as cv
import numpy as np
import matplotlib.pyplot as plt

dt = 1.                    #delta time
INITIAL_STATE_COV = 0.2
PROCESS_COV = 0.00001      #process covariance, si es chico entonces la estimacion tiene menos ruido pero es menos precisa
                           #si es grande la estimacion tiene mas ruido pero es mas precisa
MEAS_MATRIX = 1.
MEAS_NOISE_COV = 1e-1       #covarianza de medicion

kalman = cv.KalmanFilter(4, 2, 0) #se inicializa el filtro kalman con 4 variables de estado y 2 variables de medicion

kalman.transitionMatrix = np.array([[1., 0., dt, 0.],
                                    [0., 1., 0., dt],
                                    [0., 0., 1., 0.],
                                    [0., 0., 0., 1.]]) #Matriz F

kalman.measurementMatrix = MEAS_MATRIX * np.array([ [1, 0, 0, 0], [ 0, 1, 0, 0]])  #Matriz H, donde se dice que solo se
                                                                                #mide la posicion y no la velocidad
kalman.processNoiseCov = PROCESS_COV * np.identity(4)  #Matriz Q

kalman.measurementNoiseCov = MEAS_NOISE_COV * np.identity(2)  #Matriz R

kalman.errorCovPost = np.identity(4) * INITIAL_STATE_COV  #Matriz de covarianza inicial

kalman.statePost = np.array([0., 0., 0., 0.]).reshape(4, 1)  #Matriz de estado inicial

kalman.predict()                              #Asi se predice, la prediccion se guarda en las matrices de
                                                #statepre y errorcovpre.

kalman.correct((1, 1))       #Asi se anade una medicion como una tupla de posicion x y posicion y
                                                #la prediccion corregida se guarda en statePost y errorcovPost
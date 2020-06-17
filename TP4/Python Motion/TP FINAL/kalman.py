import cv2 as cv
import numpy as np
import matplotlib.pyplot as plt

dt = 1e-2                  #delta time
INITIAL_STATE_COV = 0.2
PROCESS_COV = 0.01      #process covariance, si es chico entonces la estimacion tiene menos ruido pero es menos precisa
PROCESS_COV2 = 0.0001
                           #si es grande la estimacion tiene mas ruido pero es mas precisa
MEAS_MATRIX = 1.
MEAS_NOISE_COV = 1e-1       #covarianza de medicion

kalman = cv.KalmanFilter(4, 2, 0) #se inicializa el filtro kalman con 4 variables de estado y 2 variables de medicion

kalman.transitionMatrix = np.array([[1., 0.],
                                    [0., 1.]]) #Matriz F

kalman.measurementMatrix = MEAS_MATRIX * np.array([ [1, 0], [ 0, 1]])  #Matriz H, donde se dice que solo se
                                                                                #mide la posicion y no la velocidad
kalman.processNoiseCov = PROCESS_COV * np.identity(2)  #Matriz Q

kalman.measurementNoiseCov = MEAS_NOISE_COV * np.identity(2)  #Matriz R

kalman.errorCovPost = np.identity(2) * INITIAL_STATE_COV  #Matriz de covarianza inicial



kalman2 = cv.KalmanFilter(4, 2, 0) #se inicializa el filtro kalman con 4 variables de estado y 2 variables de medicion

kalman2.transitionMatrix = np.array([[1., 0.],[0., 1.]]) #Matriz F

kalman2.measurementMatrix = MEAS_MATRIX * np.array([[1, 0], [ 0, 1]])  #Matriz H, donde se dice que solo se
                                                                                #mide la posicion y no la velocidad
kalman2.processNoiseCov = PROCESS_COV2 * np.identity(2)  #Matriz Q

kalman2.measurementNoiseCov = MEAS_NOISE_COV * np.identity(2)  #Matriz R

kalman2.errorCovPost = np.identity(2) * INITIAL_STATE_COV  #Matriz de covarianza inicial



real = []
estimated = []
estimated2 = []
measured = []
time = range(250)


kalman.statePost = np.array([0., 0.]).reshape(2, 1)     #Matriz de estado inicial
kalman2.statePost = np.array([0., 0.]).reshape(2, 1)     #Matriz de estado inicial

for i in time:
    kalman.predict()                                    #Prediccion
    kalman2.predict()
    x = 1 - np.e ** (-i/25)
    real.append(x)                                      #Genero valor reak
    measured.append(x + np.random.normal(scale = 0.1)) #Genero medicion ruidosa
    kalman.correct( (i, x + np.random.normal(scale = 0.1)) )                            #Correccion
    kalman2.correct( (i, x + np.random.normal(scale = 0.1)) )
    estimated.append(kalman.statePost[1][0])            #Guardo estimacion
    estimated2.append(kalman2.statePost[1][0])

plt.plot(time, real, color = 'green', label = 'Real')
plt.plot(time, measured, color = 'blue', label ='Medido')
plt.plot(time, estimated, color = 'red', label ='Estimado K_Q=0.01')
plt.plot(time, estimated2, color = 'orange', label = 'Estimado K_Q=0.0001')
plt.legend()
plt.show()


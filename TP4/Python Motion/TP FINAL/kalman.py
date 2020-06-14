import cv2 as cv
import numpy as np

"""
MODEL
"""
dt = 1.
INITIAL_STATE_COV = 0.2
PROCESS_COV = 0.05
MEAS_MATRIX = 1.
MEAS_NOISE_COV = 1e-1

kalman = cv.KalmanFilter(4, 2, 0)

kalman.transitionMatrix = np.array([[1., 0., dt, 0.],
                                    [0., 1., 0., dt],
                                    [0., 0., 1., 0.],
                                    [0., 0., 0., 1.]]) ##F

kalman.measurementMatrix = MEAS_MATRIX * np.array([ [1, 0, 0, 0], [ 0, 1, 0, 0]])  ##H

kalman.processNoiseCov = PROCESS_COV * np.identity(4)  ##Q

kalman.measurementNoiseCov = MEAS_NOISE_COV * np.identity(2)  ##R

kalman.errorCovPost = np.identity(4) * INITIAL_STATE_COV  ##P post

kalman.statePost = 0.1 * np.random.randn(4, 1)  ##X post

kalman.statePre = np.array([[0],[0],[0],[0]])


prediction =  kalman.predict()

kalman.predict()

# """
# UPDATE
# """
# def prediction(X_hat_t_1,P_t_1,F_t,B_t,U_t,Q_t):
#     X_hat_t=F_t.dot(X_hat_t_1)+(B_t.dot(U_t).reshape(B_t.shape[0],-1) )
#     P_t=np.diag(np.diag(F_t.dot(P_t_1).dot(F_t.transpose())))+Q_t
#     return X_hat_t,P_t
#
# """
# MEASURE
# """
# def update(X_hat_t, P_t, Z_t, R_t, H_t):
#     K_prime = P_t.dot(H_t.transpose()).dot(np.linalg.inv(H_t.dot(P_t).dot(H_t.transpose()) + R_t))
#     print("K:\n", K_prime)
#
#     X_t = X_hat_t + K_prime.dot(Z_t - H_t.dot(X_hat_t))
#     P_t = P_t - K_prime.dot(H_t).dot(P_t)
#
#     return X_t, P_t
#
# """MAIN LOOP"""
# for i in range(measurmens.shape[0]):
#     X_hat_t, P_hat_t = prediction(X_hat_t, P_t, F_t, B_t, U_t, Q_t)
#     print("Prediction:")
#     print("X_hat_t:\n", X_hat_t, "\nP_t:\n", P_t)
#
#     Z_t = measurmens[i].transpose()
#     Z_t = Z_t.reshape(Z_t.shape[0], -1)
#
#     print(Z_t.shape)
#
#     X_t, P_t = update(X_hat_t, P_hat_t, Z_t, R_t, H_t)
#     print("Update:")
#     print("X_t:\n", X_t, "\nP_t:\n", P_t)
#     X_hat_t = X_t
#     P_hat_t = P_t
#
#     print("=========================================")
#     print("Opencv Kalman Output:")
#     print("X_t:\n", opencvKalmanOutput[i])
""""""

import cv2 as cv

"""SHI-TOMASI ALGORITHM"""

feature_params = dict(maxCorners=1000,
                      qualityLevel=0.1,
                      minDistance=0.5,
                      blockSize=7)
RECALC_EVERY_FRAMES = 20
"""####################"""
"""LUCAS-KANADE ALGORITHM"""

lk_params = dict(winSize=(15, 15),
                 maxLevel=4,
                 criteria=(cv.TERM_CRITERIA_EPS | cv.TERM_CRITERIA_COUNT,
                10,
                0.03))

"""####################"""
"""KALMAN FILTER ALGORITHM"""

dt = 1e-2                   #delta time
INITIAL_STATE_COV = 0.2
PROCESS_COV = 0.05      #process covariance, si es chico entonces la estimacion tiene menos ruido pero es menos precisa, si es grande la estimacion tiene mas ruido pero es mas precisa
MEAS_MATRIX = 1.
MEAS_NOISE_COV = 1e-1       #covarianza de medicion

"""####################"""

ft_color = (0, 255, 0)
ROI_color = (255, 0, 0)
kalman_color = (0, 130, 255)
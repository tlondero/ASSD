""""""

import cv2 as cv

"""SHI-TOMASI ALGORITHM"""

feature_params = dict(maxCorners=1000,
                      qualityLevel=0.1,
                      minDistance=0.1,
                      blockSize=7)
RECALC_EVERY_FRAMES = 15
"""####################"""
"""LUCAS-KANADE ALGORITHM"""

lk_params = dict(winSize=(15, 15),
                 maxLevel=4,
                 criteria=(cv.TERM_CRITERIA_EPS | cv.TERM_CRITERIA_COUNT,
                10,
                0.03))

"""####################"""
"""KALMAN FILTER ALGORITHM"""

dt = 1                   #delta time
INITIAL_STATE_COV = 1
PROCESS_COV = 0.0006      #process covariance, si es chico entonces la estimacion tiene menos ruido pero es menos precisa, si es grande la estimacion tiene mas ruido pero es mas precisa
MEAS_MATRIX = 1.
MEAS_NOISE_COV = 0.4       #covarianza de medicion

"""####################"""

ft_color = (0, 255, 0)
ROI_color = (255, 0, 0)
kalman_color = (0, 130, 255)

"""####################"""
HUE_VAR = 8
SAT_VAR = 40
VAL_VAR = 40

COLOR_ALGORITHM = True
DEBUG_MODE = True

font = cv.FONT_HERSHEY_SIMPLEX

SEARCHING_ENLARGEMENT = 3
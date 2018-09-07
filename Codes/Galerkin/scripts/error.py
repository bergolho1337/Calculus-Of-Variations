# -*- coding: utf-8 -*-
import sys
import numpy as np
import math
import matplotlib.pyplot as plt

def readPoints (filename):
    file = open(filename,"r")

    line = file.readline()
    n = int(line)

    x = np.zeros(n)
    y = np.zeros(n)
    z = np.zeros(n)

    for i in range(n):
        line = file.readline()
        tokens = line.split()

        x[i] = float(tokens[0])
        y[i] = float(tokens[1])
        z[i] = float(tokens[2])

    return x, y, z

# Calculate the maximum error between the analitical and the aproximation
def calcError (x,y,z):
    n = len(x)
    error = 0.0
    for i in range(n):
        diff = math.fabs(y[i]-z[i])
        if (diff > error):
            error = diff
    return error

def main():

    points_filename = sys.argv[1]
    
    x,y,z = readPoints(points_filename)
    
    error = calcError(x,y,z)
    print("Maximum error = %g" % error)

if __name__ == "__main__":
    main()


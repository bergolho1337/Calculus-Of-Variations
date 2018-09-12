# -*- coding: utf-8 -*-
import sys
import numpy as np
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

def showPoints (x,y,z):
    #plt.ylim(0,10)
    plt.grid()
    plt.plot(x,y,label="analit",marker='o',markersize=4)
    plt.plot(x,z,label="aprox")
    plt.xlabel(u"x",fontsize=15)
    plt.ylabel(u"u",fontsize=15)
    plt.title(u"Solução Analítica x Solução Aproximada (n = 5)",fontsize=14)
    plt.legend(loc=0,fontsize=14)
    #plt.show()

def writeOutput (x,y,z):
    plt.savefig("output.pdf")

def main():

    points_filename = sys.argv[1]
    
    x,y,z = readPoints(points_filename)
    
    showPoints(x,y,z)

    writeOutput(x,y,z)

if __name__ == "__main__":
    main()


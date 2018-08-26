import sys
import math
import numpy as np
import matplotlib.pyplot as plt

def f (x):
    H = 1.0
    return H *( (x*x) * ((1 - x)*(1 - x)) )

def phi (x):
    H = 1.0
    EPSILON = 0.05
    l = math.sqrt(2.0 / H) * EPSILON
    return 0.5 * (1.0 + np.tanh( x / (2*l) ))

def plotFreeEnergyFunction (x):
    y = f(x)

    print x
    print
    print y

    plt.plot(x,y)
    plt.grid() 
    plt.xlabel(r'$\phi$', fontsize=18)
    plt.ylabel(r'$f$', fontsize=18)
    plt.show()
    #plt.savefig("free-energy.pdf")

def plotOrderParameterFunction (x):
    y = phi(x)

    print x
    print
    print y

    plt.clf()
    plt.plot(x,y)
    plt.grid() 
    plt.xlabel(r'$x$', fontsize=18)
    plt.ylabel(r'$\phi$', fontsize=18)
    #plt.show()
    plt.savefig("order-parameter.pdf")

def main():

    x = np.linspace(-1.0,1.0)
    #plotFreeEnergyFunction(x)
    plotOrderParameterFunction(x)


if __name__ == "__main__":
    main()


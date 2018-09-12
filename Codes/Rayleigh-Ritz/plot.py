import sys
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm

a = 1.0
b = 1.0

def polynomial (X,Y):
    c1 = float((3.0*a**2*b**2)/(2.0*(a**3*b + a*b**3))) 
    return c1*(X-a)*(Y-b)

def trigonometric (X,Y):
    #c1 = float( (32.0*a**2)/(np.pi**3) )
    c1 = float  ((32.0*a*b)/(np.pi**2))/( ( (np.pi**2*a)/(4.0*b) )+( (np.pi**2*b)/(4.0*a) ) )
    return c1*np.cos((np.pi*X)/(2*a))*np.cos((np.pi*Y)/(2*b))

def plotSolution(basis_id):
    fig = plt.figure()
    ax = fig.gca(projection='3d')

    # Make data.
    X = np.arange(0, 1, 0.1)
    Y = np.arange(0, 1, 0.1)
    X, Y = np.meshgrid(X, Y)

    if (basis_id == 1):
        Z = polynomial(X,Y)
    else:
        Z = trigonometric(X,Y)

    # Plot the surface.
    surf = ax.plot_surface(X, Y, Z, cmap=cm.coolwarm,
                        rstride=1, cstride=1, antialiased=False)
    ax.view_init(30,50)
    
    #plt.show()
    plt.savefig("output.pdf")

def calcError ():
    fig = plt.figure()
    ax = fig.gca(projection='3d')

    # Make data.
    X = np.arange(0, 1, 0.1)
    Y = np.arange(0, 1, 0.1)
    X, Y = np.meshgrid(X, Y)

    Z1 = polynomial(X,Y)
    Z2 = trigonometric(X,Y)
    E = np.abs(Z1-Z2)
    
    # Plot the surface.
    surf = ax.plot_surface(X, Y, E, cmap=cm.coolwarm,
                        rstride=1, cstride=1, antialiased=False)
    ax.view_init(30,50)
    
    #plt.show()
    plt.savefig("error.pdf")

def main():

    basis_id = int(sys.argv[1])
    
    plotSolution(basis_id)
    #calcError()


if __name__ == "__main__":
    main()

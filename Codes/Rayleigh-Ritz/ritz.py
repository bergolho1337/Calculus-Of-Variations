from sympy import *
import sys

def symbolicSolver (basis_id):
    x, y, a, b, c1 = symbols('x y a b c1')
    init_printing()

    if (basis_id == 1):
        print("[!] Using polynomials as basis function")
        phi0 = 0
        phi1 = (x-a)*(y-b)
    else:
        print("[!] Using trigonometric functions as basis function")
        phi0 = 0
        phi1 = sin((pi*x)/(2*a))*sin((pi*y)/(2*b))

    u = phi0 + c1*phi1

    dudx = diff(u,x)
    dudy = diff(u,y)

    I = ((dudx**2 + dudy**2) / 2) - 2*u
    if (basis_id == 1):
        result = integrate(integrate(I,(x,0,a)),(y,0,b))
    else:
        result = integrate(integrate(I,(x,-a,a)),(y,-b,b))
    result_exp = expand(result)

    dIdc1 = diff(result_exp,c1)
    #pprint(result_exp)
    pprint(dIdc1)

def main():

    basis_id = int(sys.argv[1])
    
    symbolicSolver(basis_id)

if __name__ == "__main__":
    main()

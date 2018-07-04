// This program solves the Exercise 4 from the List 1 

#include <iostream>
#include <cmath>

using namespace std;

double c1, c2, c3, c4;
const double h = 0.01;
const double XMIN = -2.0; const double XMAX = 2.0;
const double YMIN = -2.0; const double YMAX = 2.0;
const double ZMIN = -2.0; const double ZMAX = 2.0;

bool g (const double x, const double y, const double z)
{
    return (c1*x + c2*y + c3*z == c4);
}

double dist (const double x, const double y, const double z)
{
    return sqrt(x*x + y*y + z*z); 
}

int main (int argc, char *argv[])
{
    if (argc-1 != 4)
    {
        cout << "Usage:> " << argv[0] << " <c1> <c2> <c3> <c4>" << endl;
        cout << "Constraint equation: g(x,y,z) = c1*x + c2*y + c3*z = c4" << endl;
        exit(EXIT_FAILURE);
    }

    double ans = 1.0e+10;
    double x_ans = 100.0, y_ans = 100.0, z_ans = 100.0;
    
    c1 = atof(argv[1]); 
    c2 = atof(argv[2]); 
    c3 = atof(argv[3]);
    c4 = atof(argv[4]);

    int A = nearbyint((XMAX - XMIN) / h);
    int B = nearbyint((YMAX - YMIN) / h);
    int C = nearbyint((ZMAX - ZMIN) / h);

    for (int i = 0; i < A; i++)
    {
        double x = XMIN + i*h;
        for (int j = 0; j < B; j++)
        {
            double y = YMIN + j*h;
            for (int k = 0; k < C; k++)
            {
                double z = ZMIN + k*h;
                bool inPlane = g(x,y,z);
                if (inPlane)
                {
                    double d = dist(x,y,z);
                    if (d < ans)
                    {
                        ans = d;
                        x_ans = x; y_ans = y; z_ans = z;
                    }
                        
                }
            }
        }
    }

    cout << dist(c1,c2,c3) << endl;

    cout << "X = " << x_ans << endl;
    cout << "Y = " << y_ans << endl;
    cout << "Z = " << z_ans << endl;
    cout << "Distance = " << ans << endl;
    //cout << "sqrt(3) = " << sqrt(3) << endl;

    return 0;
}

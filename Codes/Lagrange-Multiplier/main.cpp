// This program solves the Exercise 3 from the List 1 

#include <iostream>
#include <cmath>

using namespace std;

bool g (const double x, const double y, const double z)
{
    return (x + y - z == 3);
}

double dist (const double x, const double y, const double z)
{
    return sqrt(x*x + y*y + z*z); 
}

int main ()
{
    double ans = 1.0e+10;
    double x_ans = 100.0, y_ans = 100.0, z_ans = 100.0;

    const double h = 0.5;
    const double xmin = -4.0; const double xmax = 4.0;
    const double ymin = -4.0; const double ymax = 4.0;
    const double zmin = -4.0; const double zmax = 4.0; 
    int A = nearbyint((xmax - xmin) / h);
    int B = nearbyint((ymax - ymin) / h);
    int C = nearbyint((zmax - zmin) / h);

    for (int i = 0; i < A; i++)
    {
        double x = xmin + i*h;
        for (int j = 0; j < B; j++)
        {
            double y = ymin + j*h;
            for (int k = 0; k < C; k++)
            {
                double z = zmin + k*h;
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

    cout << "X = " << x_ans << endl;
    cout << "Y = " << y_ans << endl;
    cout << "Z = " << z_ans << endl;
    cout << "Distance = " << ans << endl;
    cout << "sqrt(3) = " << sqrt(3) << endl;

    return 0;
}

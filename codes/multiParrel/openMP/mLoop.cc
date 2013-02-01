/*
g++ -fopenmp mLoop.cc
*/

#include <omp.h>
#include <stdio.h>

int main()
{
    double *force_X;
    double *WallY0_f;
    double *WallY1_f ;

    force_X = (double *)   calloc ((size_t) (nb), sizeof(double));
    WallY0_f = (double *)   calloc ((size_t) (nb), sizeof(double));
    WallY1_f = (double *)   calloc ((size_t) (nb), sizeof(double));

    int i,j,k;

    #pragma omp parallel for shared(force_X, force_Y, force_Z, WallY0_f, WallY1_f) private(k)
    for (k = 0; k < nbreInteractions ; ++k) {

        i = particle[k];
        j = Voisin[k];

        if (_paire[k]==0)
          {
            Sphere_Sphere(i,j,k);
            force_X[i] += FX[k];
            force_X[j] -= FX[k];
          }
         else if (_paire[k]==1)
          {
            Sphere_WallY0(i,k);
            force_X[i] -= FX[k];
            WallY0_f[i] -= FY[k];
          }
         else if (_paire[k]==2)
          {
            Sphere_WallY1(i,k);
            force_X[i] += FX[k];
            WallY1_f[i] += FY[k];
          }
    }
}


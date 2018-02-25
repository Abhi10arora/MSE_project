#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
  FILE *f, *fp;
  f = fopen("d","r");
  fp = fopen("output","w");

  int nx = 125, ny = 125, x, y, t, total_time = 4000;
  float count = 0, D_0 = 1.0, prefactor = 100.0, temp2;
  float dx = 1.0, dy = 1.0, dt = 0.1, temp = 0, temp1 = 0, eta_1[ny+2];

  float** eta = (float**)malloc((nx+2)*sizeof(float*));
  float** D_c = (float**)malloc((nx+2)*sizeof(float*));
  for(x = 0; x<nx+2; x++)
  {
    eta[x] = (float*)malloc((ny+2)*sizeof(float));
    D_c[x] = (float*)malloc((ny+2)*sizeof(float));
    for(y = 0; y<ny; y++)
    {
      if(y < 0.8*ny)
      {
        fscanf(f,"%f ", &temp2);
        D_c[x][y] = D_0 + prefactor*temp2;
        eta[x][y] = 0;
      }
      else
      {
        D_c[x][y] = 1;
        eta[x][y] = 1;
      }
    }
    fscanf(f,"\n");
  }

  // for(t = 1; t <= total_time; t++)
  // {
  //   for(y = 0; y<ny; y++)
  //   {
  //     eta_1[y] = 0;
  //     // eta[nx][y] = 0;
  //   }
  //   for(x = 0; x<nx; x++)
  //   {
  //     temp = 0;
  //     // eta[x][ny] = 0;
  //
  //     for(y = 0; y<ny; y++)
  //     {
  //       temp1 = eta[x][y];
  //       // eta[x][y] =  eta[x][y] + (D_c[x][y]*dt*(eta[x+1][y]-2*eta[x][y]+eta_1[y]))/(dx*dx) + (D_c[x][y]*dt*(eta[x][y+1]-2*eta[x][y]+temp))/(dy*dy);
  //       temp = temp1;
  //       eta_1[y] = temp1;
  //     }
  //   }
  //   if(t == total_time)
  //   {
  //     for(x=0; x<nx; x++)
  //     {
  //       for(y=0; y<ny; y++)
  //       {
  //         fprintf(fp,"%f ", eta[x][y]);
  //       }
  //       fprintf(fp,"\n");
  //     }
  //   }
  // }

  for(x = 0; x<nx+2; x++)
  {
    free(eta[x]);
    free(D_c[x]);
  }
  free(eta);
  free(D_c);
  fclose(f);
  fclose(f);
  return 0;
}

#include <stdio.h>
#include <math.h>

int main()
{
  FILE *f;
  f = fopen("output", "w");

  int nx = 100, ny = 100, x, y, t, total_time = 1600, count = 0, print_time = 50;
  float dx = 1.0, dy = 1.0, temp_11 = 0, temp_12 = 0, temp_21 = 0, temp_22 = 0, eta_temp1[ny], eta_temp2[ny];
  double per;
  float eta_1[nx+1][ny+1], eta_2[nx+1][ny+1], dt = 0.1, A = 1.0, B = 1.0, C = 1.0, L = 1.0, K = 1.0;

  for(x=0; x<nx; x++)
  {
    for(y=0; y<ny; y++)
    {
      if(((x-nx/2)*(x-nx/2) + (y-ny/2)*(y-ny/2)) <= 625)
      {
        eta_1[x][y] = 1;
        eta_2[x][y] = 0;
      }
      else
      {
        eta_1[x][y] = 0;
        eta_2[x][y] = 1;
      }
    }
  }

  for(t = 1; t <= total_time; t++)
  {
    for(y = 0; y<ny; y++)
    {
      eta_temp1[y] = eta_1[nx-1][y];
      eta_1[nx][y] = eta_1[0][y];

      eta_temp2[y] = eta_2[nx-1][y];
      eta_2[nx][y] = eta_2[0][y];
    }
    for(x = 0; x<nx; x++)
    {
      temp_11 = eta_1[x][ny-1];
      eta_1[x][ny] = eta_1[x][0];

      temp_21 = eta_2[x][ny-1];
      eta_2[x][ny] = eta_2[x][0];

      for(y = 0; y<ny; y++)
      {
        temp_12 = eta_1[x][y];
        eta_1[x][y] =  L*dt*(A*eta_1[x][y] - B*pow(eta_1[x][y],3) - 2*C*eta_1[x][y]*pow(eta_2[x][y],2)) + eta_1[x][y] + (2*K*L*dt*(eta_1[x+1][y]-2*eta_1[x][y]+eta_temp1[y]))/(dx*dx) + (2*K*L*dt*(eta_1[x][y+1]-2*eta_1[x][y]+temp_11))/(dy*dy);
        temp_11 = temp_12;
        eta_temp1[y] = temp_12;

        temp_22 = eta_2[x][y];
        eta_2[x][y] =  L*dt*(A*eta_2[x][y] - B*pow(eta_2[x][y],3) - 2*C*eta_2[x][y]*pow(temp_12,2)) + eta_2[x][y] + (2*K*L*dt*(eta_2[x+1][y]-2*eta_2[x][y]+eta_temp2[y]))/(dx*dx) + (2*K*L*dt*(eta_2[x][y+1]-2*eta_2[x][y]+temp_21))/(dy*dy);
        temp_21 = temp_22;
        eta_temp2[y] = temp_22;
      }
    }
    // if(t == print_time)
    // {
    //   for(x=0; x<nx; x++)
    //   {
    //     for(y=0; y<ny; y++)
    //     {
    //       if(eta_1[x][y] > 0.5)
    //       count++;
    //     }
    //   }
    //     per = (count*100.0)/(nx*ny);
    //     fprintf(f, "%lf", per);
    //     fprintf(f,"\n");
    //     count = 0;
    //     print_time = print_time + 50;
    // }

    if(t == print_time)
    {
      for(x=0; x<nx; x++)
      {
        for(y=0; y<ny; y++)
        {
          fprintf(f,"%f\n", eta_1[x][y]);
        }
        fprintf(f,"\n");
      }
      fprintf(f,"\n");
      print_time = print_time + 50;
    }
  }

  fclose(f);
  return 0;
}

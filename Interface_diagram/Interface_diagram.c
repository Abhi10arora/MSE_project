#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
  FILE *f;
  char* file[9] = {"1","2","3","4","5","6","7","8","9"};
  // f = fopen("1","w");

  int no_etas = 36, nx = 100, ny = 100, x, y, t, i, j = 0, total_time = 9000, count = 0, print_time = 1000, random_temp = 0;
  float dx = 2.0, dy = 2.0, temp_1 = 0, temp_2 = 0, eta_temp[ny], eta_temp_1[ny];
  double per, eta_sum[nx][ny];
  float dt = 0.1, A = 1.0, B = 1.0, C = 1.0, L = 1.0, K = 1.0;

  float*** eta = (float***)malloc(no_etas*sizeof(float**));

  for(i = 0; i<no_etas; i++)
  {
    eta[i] = (float**)malloc((nx+1)*sizeof(float*));
    // while(random_temp == 0 || random_temp > 99)
    // {
    //   random_temp = rand() % 100;
    //   // fprintf(f, "%d\n", random_temp);
    // }
    for(x=0; x<nx; x++)
    {
      eta[i][x] = (float*)malloc((ny+1)*sizeof(float));
      for(y=0; y<ny; y++)
      {
        random_temp = rand() % 100;
        eta[i][x][y] = random_temp/10000.0;
      }
    }
    // fprintf(f, "%f\n", eta[i][x-1][y-1]);
    // random_temp = 0;
  }

  for(t = 1; t <= total_time; t++)
  {
    if(t == print_time)
    {
      f = fopen(file[j], "w");
    }
    for(x = 0; x<nx; x++)
    {
      for(y = 0;y<ny; y++)
      {
        eta_sum[x][y] = 0;
        for(i = 0; i<no_etas; i++)
        {
          eta_sum[x][y] = eta_sum[x][y] + pow(eta[i][x][y], 2);
        }
      }
    }
    for(i = 0; i<no_etas; i++)
    {
      for(y = 0; y<ny; y++)
      {
        eta_temp[y] = eta[i][nx-1][y];
        eta_temp_1[y] = eta[i][0][y];
      }
      for(x = 0; x<nx; x++)
      {
        temp_1 = eta[i][x][ny-1];
        eta[i][x][ny] = eta[i][x][0];

        for(y = 0; y<ny; y++)
        {
          if(x == nx-1)
          {
            temp_2 = eta[i][x][y];
            eta[i][x][y] =  L*dt*(A*eta[i][x][y] - B*pow(eta[i][x][y],3) - 2*C*eta[i][x][y]*(eta_sum[x][y] - (eta[i][x][y]*eta[i][x][y]))) + eta[i][x][y] + (2*K*L*dt*(eta_temp_1[y]-2*eta[i][x][y]+eta_temp[y]))/(dx*dx) + (2*K*L*dt*(eta[i][x][y+1]-2*eta[i][x][y]+temp_1))/(dy*dy);
            temp_1 = temp_2;
            eta_temp[y] = temp_2;
          }
          else
          {
            temp_2 = eta[i][x][y];
            eta[i][x][y] =  L*dt*(A*eta[i][x][y] - B*pow(eta[i][x][y],3) - 2*C*eta[i][x][y]*(eta_sum[x][y] - (eta[i][x][y]*eta[i][x][y]))) + eta[i][x][y] + (2*K*L*dt*(eta[i][x+1][y]-2*eta[i][x][y]+eta_temp[y]))/(dx*dx) + (2*K*L*dt*(eta[i][x][y+1]-2*eta[i][x][y]+temp_1))/(dy*dy);
            temp_1 = temp_2;
            eta_temp[y] = temp_2;
          }
        }
      }
      if(t == print_time)
      {
        for(x=0; x<nx; x++)
        {
          for(y=0; y<ny; y++)
          {
            fprintf(f,"%f ", eta[i][x][y]);
          }
          fprintf(f,"\n");
        }
        fprintf(f,"\n");
      }
    }
    if(t == print_time)
    {
      print_time = print_time + 1000;
      j++;
      fclose(f);
    }
  }

  for(i = 0; i<no_etas; i++)
  {
    for(x = 0; x<nx+1; x++)
    {
      free(eta[i][x]);
    }
    free(eta[i]);
  }
  free(eta);
  // fclose(f);
  return 0;
}

#include <stdio.h>

int main()
{
  FILE *f;
  f = fopen("output.txt", "w");

  int nx = 100, ny = 100, x, y, t, total_time = 1600, count = 0, print_time = 50;
  float dx = 1.0, dy = 1.0, temp = 0, temp1 = 0, eta_1[ny];
  double per;
  float eta[nx+1][ny+1], dt = 0.1, A = 1.0, L = 1.0, K = 1.0;

  for(x=0; x<nx; x++)
  {
    for(y=0; y<ny; y++)
    {
      if(((x-nx/2)*(x-nx/2) + (y-ny/2)*(y-ny/2)) <= 625)
      eta[x][y] = 1;
      else
      eta[x][y] = 0;
    }
  }

  for(t = 1; t <= total_time; t++)
  {
    for(y = 0; y<ny; y++)
    {
      eta_1[y] = eta[nx-1][y];
      eta[nx][y] = eta[0][y];
    }
    for(x = 0; x<nx; x++)
    {
      temp = eta[x][ny-1];
      eta[x][ny] = eta[x][0];

      for(y = 0; y<ny; y++)
      {
        temp1 = eta[x][y];
        eta[x][y] =  -2*A*L*dt*eta[x][y]*(1-eta[x][y])*(1-2*eta[x][y]) + eta[x][y] + (2*K*L*dt*(eta[x+1][y]-2*eta[x][y]+eta_1[y]))/(dx*dx) + (2*K*L*dt*(eta[x][y+1]-2*eta[x][y]+temp))/(dy*dy);
        temp = temp1;
        eta_1[y] = temp1;
      }
    }
    if(t == print_time)
    {
      for(x=0; x<nx; x++)
      {
        for(y=0; y<ny; y++)
        {
          if(eta[x][y] > 0.5)
          count++;
        }
      }
        per = (count*100.0)/(nx*ny);
        fprintf(f, "%lf", per);
        fprintf(f,"\n");
        count = 0;
        print_time = print_time + 50;
        // {
        //   fprintf(f, "%f ", eta[x][50]);
        // }
    }
  }

  fclose(f);
  return 0;
}

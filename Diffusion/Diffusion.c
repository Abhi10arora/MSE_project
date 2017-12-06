#include <stdio.h>

int main()
{
  FILE *f;
  f = fopen("output.txt", "w");
  int nx = 100;
  float dx = 1.0, temp, temp1, flag, count = 1000.0;
  float c[nx], dt = 0.25, D = 1.0, t = 1000.0;

  for(int i=0; i<nx; i++)
  {
    if(i<(0.25*nx) || i>(0.75*nx))
    c[i] = 0;
    else
    c[i] = 1;
  }

  for(float i=dt; i<=t; i=i+dt)
  {
    for(int j=0; j<nx; j++)
    {
      if(j == 0)
      {
        temp = c[j];
        flag = c[j];
        c[j] = c[j] + (D*dt*(c[j+1]-2*c[j]+c[nx-1]))/(dx*dx);
      }
      else if(j == nx-1)
      {
        c[j] = c[j] + (D*dt*(flag-2*c[j]+temp))/(dx*dx);
      }
      else
      {
        temp1 = c[j];
        c[j] = c[j] + (D*dt*(c[j+1]-2*c[j]+temp))/(dx*dx);
        temp = temp1;
      }
    }
    if(i == count)
    {
      for(int j=0; j<nx; j++)
      {
        fprintf(f, "%f", c[j]);
        fprintf(f, "\n");
      }
      // fprintf(f, "\n \n");
      // count = count + 100;
    }
  }

  fclose(f);
  return 0;
}

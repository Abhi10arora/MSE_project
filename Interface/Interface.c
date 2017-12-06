#include <stdio.h>

int main()
{
  FILE *f;
  f = fopen("output.txt", "w");

  int nx = 100, i, j;
  float dx = 1.0, temp = 0, temp1 = 0, count = 100.0;
  float N[nx+1], dt = 0.1, A = 1.0, L = 1.0, K = 1.0, t = 4000.0;

  for(i=0; i<nx; i++)
  {
    if(i<(0.25*nx) || i>(0.75*nx))
    N[i] = 0;
    else
    N[i] = 1;
  }

  for(i=1; i<=t; i++)
  {
    temp = N[nx-1];
    N[nx] = N[0];
    for(j = 0; j<nx; j++)
    {
      temp1 = N[j];
      N[j] =  N[j] + (2*K*L*dt*(N[j+1]-2*N[j]+temp))/(dx*dx) - 2*A*L*dt*N[j]*(1-N[j])*(1-2*N[j]);
      temp = temp1;
    }
    if(i == 4000)
    {
      for(j=0; j<nx; j++)
      {
        fprintf(f, "%f", N[j]);
        fprintf(f, "\n");
      }
    }
  }

  fclose(f);
  return 0;
}

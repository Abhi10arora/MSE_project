#include <stdio.h>
#include <stdlib.h>

int main()
{
  FILE *f, *area;
  f = fopen("output", "r");
  area = fopen("area", "w");

  int i, n = 32, nx = 100, ny = 100, x, y, count = 0;
  float temp, per = 0;
  double eta[nx][ny];
  char s = '1';

  for(i = 0; i<n; i++)
  {
    // s = s + i;
    // FILE *fn;
    // fn = fopen(s, "w");

    for(x = 0; x<nx; x++)
    {
      for(y = 0; y<ny; y++)
      {
        fscanf(f,"%lf\n", &eta[x][y]);
        // fprintf(fn, "%f\n", temp);
        if(eta[x][y] > 0.5)
        count++;
      }
      fscanf(f,"\n");
    }
    per = (count*100.0)/(nx*ny);
    fprintf(area, "%f", per);
    fprintf(area,"\n");
    count = 0;
    fscanf(f,"\n");
    // fclose(fn);
  }
  fclose(f);
  fclose(area);
}

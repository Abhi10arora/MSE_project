#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
  FILE *f, *fp;
  char* file[4] = {"1","3","6","9"};
  char* file_output[4] = {"a","b","c","d"};
  // f = fopen("1","w");

  int no_etas = 36, nx = 100, ny = 100, x, y, t, i, j, k;
  float count = 0;
  int temp;

  float*** eta = (float***)malloc(no_etas*sizeof(float**));
  for(i = 0; i<no_etas; i++)
  {
    eta[i] = (float**)malloc((nx+1)*sizeof(float*));
    for(x=0; x<nx; x++)
    {
      eta[i][x] = (float*)malloc((ny+1)*sizeof(float));
    }
  }

  for(j = 0; j<4; j++)
  {
    f = fopen(file[j],"r");
    fp = fopen(file_output[j],"w");
    for(i = 0; i<no_etas; i++)
    {
      for(x=0; x<nx; x++)
      {
        for(y=0; y<ny; y++)
        {
          fscanf(f,"%f ",&eta[i][x][y]);
        }
        fscanf(f,"\n");
      }
      fscanf(f,"\n");
    }

    for(x=0; x<nx; x++)
    {
      for(y=0; y<ny; y++)
      {
        for(i = 0; i<no_etas; i++)
        {
          for(k = i+1; k<no_etas; k++)
          {
            count = count + pow(eta[i][x][y], 2)*pow(eta[k][x][y], 2);
          }
        }
        if((16*count) > 1)
        {
          temp = 1;
          fprintf(fp, "%d ", temp);
        }
        else
        {
          temp = 0;
          fprintf(fp, "%d ", temp);
        }
        count = 0;
      }
      fprintf(fp, "\n");
    }
    fclose(f);
    fclose(fp);
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

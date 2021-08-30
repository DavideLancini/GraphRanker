#include <stdio.h>
#include <stdlib.h>
int main ()
{
  int row, column;
  int d = 4;
  int maxLine;
  int l;
  long temp;
  char *ptr;
  char *ptrEnd;
  long ret;

  maxLine = 12*d;

  char st[maxLine];

  int *graphMatrix = (int *) malloc (d * d * sizeof (int));

  for (row = 0; row < d; row++){
    fgets(st, maxLine, stdin);
    ptr = &st[0];
    for (column = 0; column < d; column++){
      ret = strtol(ptr, &ptr, 10);
      ptr = ptr + sizeof (char);
      *(graphMatrix + row * d + column) = (int)ret;
      if(row == column || column == 0)
        *(graphMatrix + row * d + column) = 0; //diagonal and column 0 is useless for our usage
    }
  }


  printf("\nPRINT: \n");
  for (row = 0; row < d; row++){
    for (column = 0; column < d; column++){
      printf("%d ", *(graphMatrix + row * d + column));
    }
    printf("\n");
  }
  return 0;
}   
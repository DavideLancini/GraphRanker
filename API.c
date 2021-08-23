#include <stdio.h>
#include <stdlib.h>

int evaluateGraph(){}

void main(){
  //allocate constants
  int d,k;
  //read parameters
  scanf("%d %d", &d, &k);

  //allocate necessary structures
  int *graphMatrix = (int *) malloc (d * d * sizeof (int));
  int graphIndex = 0;
  int *topK = (int *) malloc (2*k * sizeof (int));
  int trashold = 0; //minimum evaluation to join the top
  int evaluation,row,column; //temp

  //read command
  char command[14];
  while(1){
    scanf("%s", command);
    //TopK
    if(command[0] == 'T'){
      for(int i = 0; i<graphIndex && i<99;i++){
        printf ("%d ", *(topK + i * 2));
      }
    }
    //Aggiungigrafo
    else{
      //read graph
      for (row = 0; row < d; row++)
        for (column = 0; column < d; column++)
          scanf("%d", (graphMatrix + row * d + column));
          if(row == column)
            *(graphMatrix + row * d + column) = 0; //diagonal is useless
      //evaluate graph
      evaluation = evaluateGraph(d, graphMatrix);
      //update TopK
      //increase Index
      graphIndex++;
    }
  }

  return;
}

int evaluateGraph(int d, int *graphMatrix){
  //alllocate activationVector
  int *activeRow = (int *) malloc (d * sizeof (int)); //temp
  int sum = 0;
  int min = 0;
  int minPos[2];
  //reset activation vector
  *(activeRow) = 1;
  for(int i=1;i<d;i++)
    *(activeRow + i) = 0;
  //set first
  for(int i=1;i<d;i++){
    if(*(graphMatrix + i) != 0){ //finding the first non zero value in the row 0
      min = *(graphMatrix + i);
      minPos[0]=0;
      minPos[1]=i;
      break;
    }
    if(i==d-1){ //row 0 is filled with zero, no connection possible
      return 0;
    }
  }
  for(int i = 0; i<d;i++){ //check for minimum in the active rows


  }
  //erease column of the minimum
  //activate row of the minimum
  //update sum



}
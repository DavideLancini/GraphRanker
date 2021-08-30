#include <stdio.h>
#include <stdlib.h>

void readGraph(int *graphMatrix);
void printGraph(int *graphMatrix);
void evaluateGraph(int *graphMatrix);

void printTop(int *topK);
void addTop(int *topK);

int d,k,evaluation,graphIndex,trashold,maxLine;
char command[14];

void main(){
  //read parameters
  scanf("%d %d", &d, &k);
  maxLine = 12*d;
  graphIndex = 0;
  trashold = 0;

  //allocate necessary structures
  int *graphMatrix = (int *) malloc (d * d * sizeof (int));
  int *topK = (int *) malloc (2*k * sizeof (int)); //index, evaluation

  while(1){
    scanf("%s", command);
    if(command[0] == 'T'){ //TopK
      printTop(topK);
    }
    else{ //AggiungiGrafo
      readGraph(graphMatrix);
      //printGraph(graphMatrix); //DEBUG
      evaluateGraph(graphMatrix);
      if(evaluation >= trashold){
        addTop(topK);
      }
      graphIndex++;
    }
  }
  return; //Unreachable
}

void readGraph(int *graphMatrix){
  char *ptr;
  char st[maxLine];
  long ret;
  for (int row = 0; row < d; row++){
    scanf("%s", st);
    //fgets(st, maxLine, stdin); COULD BE BETTER
    ptr = &st[0];
    for (int column = 0; column < d; column++){
      ret = strtol(ptr, &ptr, 10);
      ptr = ptr + sizeof (char);
      *(graphMatrix + row * d + column) = (int)ret;
      if(row == column || column == 0)
        *(graphMatrix + row * d + column) = 0; //diagonal and column 0 is useless for our usage
    }
  }
}

void printGraph(int *graphMatrix){
  printf("\nPRINT: \n");
  for (int row = 0; row < d; row++){
    for (int column = 0; column < d; column++){
      printf("%d ", *(graphMatrix + row * d + column));
    }
    printf("\n");
  }
}

void evaluateGraph(int *graphMatrix){
  //allocate activationVector
  int *activeRow = (int *) malloc (d * sizeof (int)); //store the active rows
  //TODO: better way for active rows: store the index (one less for cycle)
  int min = 0;
  int minPos[2];
  //reset activation vector
  *(activeRow) = 1;
  for(int i=1;i<d;i++)
    *(activeRow + i) = 0;
  //SETUP
  for(int i=1;i<d;i++){
    if(*(graphMatrix + i) != 0){ //finding the first non zero value in the row 0
      min = *(graphMatrix + i);
      minPos[0]=0;
      minPos[1]=i;
      break;
    }
    if(i==d-1){ //reached when row 0 is filled with zero, no connection possible
      evaluation = 0;
      return;
    }
  }

  //MAIN CYCLE
  for(int i = 0; i<d;i++){ //cycle in dimension
    for(int j = 0; i<d;i++){ //cycle in active rows
      if(*(activeRow + j) == 1){ //if the row is active
        //TODO:cycle in that row for the minimum
      }
    }
    //TODO: minimum found
    //TODO:erease column of the minimum
    //TODO:activate row of the minimum
    //TODO:add minimum value to the row
    //TODO:update evaluation
  }
  return;
}

void printTop(int *topK){
  for(int i = 0; i<graphIndex && i<k;i++){
    printf ("%d ", *(topK + i * 2));
  }
}

void addTop(int *topK){
  //Se grafici meno di k inserisco in fondo

  *(TopK + 2*graphIndex) = graphIndex; //Insert on bottom

  //Se grafici più di k
  //Search from bottom
  //Change founded with current
  //Search for new minimum trashold

}
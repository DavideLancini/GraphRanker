#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int index;
  int evaluation;
  struct node *next;
} Node;

void readGraph(int dimension, int *graphMatrix);
void printGraph(int dimension, int *graphMatrix);
int evaluateGraph(int dimension, int *graphMatrix);

int topIsSaturated;
void printTop(Node *topHead);
void addTop(int index, int evaluation, Node *topHead);

void main(){
  int d,k,evaluation,graphIndex,trashold,maxLine;
  char command[14];

  //read parameters
  scanf("%d %d", &d, &k);
  maxLine = 12*d;
  graphIndex = 0;
  trashold = 0;
  topIsSaturated = 0;

  //allocate necessary structures
  int *graphMatrix = (int *) malloc (d * d * sizeof (int));
  Node *topHead = NULL;

  while(1){
    scanf("%s", command);
    if(command[0] == 'T'){ //TopK
      printTop(topHead);
    }
    else{ //AggiungiGrafo
      readGraph(d, graphMatrix);
      //printGraph(graphMatrix); //DEBUG
      evaluation = evaluateGraph(d, graphMatrix);
      addTop(graphIndex, evaluation, topHead);
      graphIndex++;
      if(graphIndex = k-1) //the list is filled
        topIsSaturated=1;
    }
  }
  return; //Unreachable
}

void readGraph(int dimension, int *graphMatrix){
  char *ptr;
  char st[dimension * dimension];
  long ret;
  for (int row = 0; row < dimension; row++){
    scanf("%s", st);
    //fgets(st, maxLine, stdin); COULD BE BETTER
    ptr = &st[0];
    for (int column = 0; column < dimension; column++){
      ret = strtol(ptr, &ptr, 10);
      ptr = ptr + sizeof (char);
      *(graphMatrix + row * dimension + column) = (int)ret;
      if(row == column || column == 0)
        *(graphMatrix + row * dimension + column) = 0; //diagonal and column 0 is useless for our usage
    }
  }
}

void printGraph(int dimension, int *graphMatrix){
  printf("\nPRINT: \n");
  for (int row = 0; row < dimension; row++){
    for (int column = 0; column < dimension; column++){
      printf("%d ", *(graphMatrix + row * dimension + column));
    }
    printf("\n");
  }
}

int evaluateGraph(int dimension, int *graphMatrix){
  int evaluation = 0;
  //allocate activationVector
  int *activeRow = (int *) malloc (dimension * sizeof (int)); //store the active rows
  //TODO: better way for active rows: store the index (one less for cycle)
  int min = 0;
  int minPos[2];
  //reset activation vector
  *(activeRow) = 1;
  for(int i=1;i<dimension;i++)
    *(activeRow + i) = 0;
  //SETUP
  for(int i=1;i<dimension;i++){
    if(*(graphMatrix + i) != 0){ //finding the first non zero value in the row 0
      min = *(graphMatrix + i);
      minPos[0]=0;
      minPos[1]=i;
      break;
    }
    if(i==dimension-1){ //reached when row 0 is filled with zero, no connection possible
      return 0;
    }
  }

  //MAIN CYCLE
  for(int i = 0; i<dimension;i++){ //cycle in dimension
    for(int j = 0; i<dimension;i++){ //cycle in active rows
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
  return evaluation;
}

void printTop(Node *topHead){
    Node *ptr = topHead;
    while(ptr!=NULL){
        printf("%d ", ptr->index);
        ptr=ptr->next;
    }
}

void addTop(int index, int evaluation, Node *topHead){
  //Se grafici meno di k inserisco in fondo
  //Se grafici più di k
  //Search from bottom
  //Change founded with current
  //Search for new minimum trashold
}
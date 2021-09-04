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
Node *addTop(int index, int evaluation, Node *topHead);
Node *insertNode(int index, int evaluation, Node *topHead);

void main(){
  int d,k,evaluation,graphIndex;
  graphIndex = 0;
  topIsSaturated = 0;
  char command[14];

  //read parameters
  scanf("%d %d", &d, &k);

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
      topHead = addTop(graphIndex, evaluation, topHead);
      graphIndex++;
      if(graphIndex = k-1) //the list is filled
        topIsSaturated=1;
    }
  }
  return; //Unreachable
}

/*
 * Read a line than extract int discarding "," all is saved after the given pointer
 */
void readGraph(int dimension, int *graphMatrix){
  char *ptr;
  char st[12 * dimension];
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

/*
 * DEBUG ONLY: Print the entire matrix
 */
void printGraph(int dimension, int *graphMatrix){
  printf("\nPRINT: \n");
  for (int row = 0; row < dimension; row++){
    for (int column = 0; column < dimension; column++){
      printf("%.11d ", *(graphMatrix + row * dimension + column));
    }
    printf("\n");
  }
}

/*
 * Take a graph and evaluates it.
 * External cycle: keep count on how many rows are active (i)
 * Active Row Cycle: cycle in the active row
 * In Row Cycle: cycle in that row for the minimum
 * Minimum Found (XColumn, Xvalue): 
 *  add(XV) to sum
 *  delete Column(XC)
 *  activate Row(XC),
 *  add(XV) in Row(XC) 
 */
int evaluateGraph(int dimension, int *graphMatrix){
  int evaluation = 0;
  int minimumPosition = 0;
  int minimumValue = 0;
  //allocate activationVector
  int *activeRow = (int *) malloc (dimension * sizeof (int)); //store the active rows

  for(int i=1; i <= dimension ; i++){ //External Cycle
    for(int j=0; j < i; j++){ //Active Row Cycle
      for(int k=0; k < dimension; k++){ //In Row Cycle
        //TODO: Confront for the minimum (ignore zeros)
      }
    }
    //TODO: Minimum Found, do all the good stuff
  }
}

/*
 * Print the top list with a space in between
 */
void printTop(Node *topHead){
    Node *ptr = topHead;
    while(ptr!=NULL){
        printf("%d ", ptr->index);
        ptr=ptr->next;
    }
}

/*
 * Search for an equal or lower score, inserts a node before it
 * Particular case 1: it's the new head node
 * Particular case 2: it's the new end node
 */
Node *addTop(int index, int evaluation, Node *topHead){
  Node *newNode = malloc( sizeof(Node));
  newNode->index = index;
  newNode->evaluation = evaluation;
  Node *tmpPtr;
  tmpPtr = topHead;

  if(tmpPtr->evaluation <= evaluation){ //Particular case 1
    newNode->next = tmpPtr;
    return newNode;
  }

  Node *tmpNext;
  tmpNext = tmpPtr->next;

  while(tmpNext != NULL){
    if(tmpNext->evaluation <= evaluation){ // equal or lower score found
      tmpPtr->next = newNode;
      newNode->next = tmpNext;
      return topHead;
    }
  }
  tmpPtr->next = newNode;
  newNode->next = NULL;
  return topHead;
}

/*
 * Check if the evaluation is worth keeping.
 * If is worth delete the head (witch is the worst and newest score)
 * And call addNode
 */
Node *insertNode(int index, int evaluation, Node *topHead){ //remove head then add node
  if(evaluation >= topHead->evaluation){
      return topHead; //not good enough to be inserted
  }else{
    Node *toDelete;
    toDelete = topHead;
    topHead = topHead->next;
    free(toDelete);
    return addTop(index,evaluation,topHead);
  }
}
#include <stdio.h>
#include <stdlib.h>

/*TODO:
*/

typedef struct node {
  int index;
  long long evaluation;
  struct node *next;
} Node;

// GRAPH FUNCTIONS
void readGraph(int dimension, int *graphMatrix);
long long evaluateGraph(int dimension, int *graphMatrix);
int searchMinimumInRow(int dimension, int *start);
// TOP FUNCTIONS
void printTop(Node *topHead);
Node *addNode(int index, long long evaluation, Node *topHead);
Node *insertNode(int index, long long evaluation, Node *topHead);
// DEBUG ONLY
void printGraph(int dimension, int *graphMatrix);
void printRow(int dimension, int *start);

int main(){
  int d,k,evaluation,graphIndex;
  graphIndex = 0;
  k=0;
  d=0;
  char c;

  //read d
  c = getchar_unlocked();
  while(c>47 && c<58){
    d = d*10 + (c - 48);
    c = getchar_unlocked();
  }
  //read k
  c = getchar_unlocked();
  while(c>47 && c<58){
    k = k*10 + (c - 48);
    c = getchar_unlocked();
  }

  //allocate necessary structures
  int *graphMatrix = (int *) malloc (d * d * sizeof (int));
  Node *topHead = NULL;

  while(1){
    c = getchar_unlocked();
    if(c != EOF){
      if(c == 'T'){ //TopK
      c = getchar_unlocked(); //Ignoring all the other stuff
      c = getchar_unlocked();
      c = getchar_unlocked();
      c = getchar_unlocked();
      printTop(topHead);
    }
    else{ //AggiungiGrafo
      c = getchar_unlocked(); 
      c = getchar_unlocked();
      c = getchar_unlocked();
      c = getchar_unlocked();
      c = getchar_unlocked();
      c = getchar_unlocked();
      c = getchar_unlocked();
      c = getchar_unlocked();
      c = getchar_unlocked();
      c = getchar_unlocked();
      c = getchar_unlocked();
      c = getchar_unlocked();
      c = getchar_unlocked();

      readGraph(d, graphMatrix);
      //printGraph(d, graphMatrix);

      evaluation = evaluateGraph(d, graphMatrix);
      // printf("   DEBUG EVAL: %d\n", evaluation); //DEBUG

      if(graphIndex < k){
        topHead = addNode(graphIndex, evaluation, topHead);
      }else{
        topHead = insertNode(graphIndex, evaluation, topHead);
      }

      graphIndex++;
    }
    }else{
      return 0; //Unreachable
    }
  }
}

/*
 * Read a line than extract int discarding "," all is saved after the given pointer
 */
void readGraph(int dimension, int *graphMatrix){
  char c;
  int value = 0;

  int position = 0;
  int comma = 0;
  int totCommas = dimension * dimension;

  while(comma < totCommas){
    c = getchar_unlocked();
    if(c>47 && c<58){
      value = value*10 + (c - 48);
    }else{
      comma++;
      *(graphMatrix + position) = value;
      position++;
      // printf("%d ", value);
      value = 0;
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
      printf("%.6d ", *(graphMatrix + row * dimension + column));
    }
    printf("\n");
  }
}

/*
 * Search minimum position in a row given the start and the dimension
 * Return 0 if no minimum is found
 */
int searchMinimumInRow(int dimension, int *start){
  long long minimumValue = __INT64_MAX__;
  int minimumPosition = 0;
  int tmp;
  for(int i = 0; i<dimension;i++){
    tmp = *(start + i);
    if(tmp!=0 && tmp < minimumValue){
      minimumValue = tmp;
      minimumPosition = i;
    }
  }
  return minimumPosition;
}

/*
 * DEBUG ONLY: Print a dynamic array
 */
void printRow(int dimension, int *start){
  for(int i=0; i<dimension; i++){
    printf("%d ", *(start+i));
  }
  printf("\n");
}

/*
 * Print the top list with a space in between
 */
void printTop(Node *topHead){
    Node *ptr = topHead;
    if(ptr!=NULL){
      printf("%d", ptr->index);
      ptr=ptr->next;
    }
    while(ptr!=NULL){
      printf(" %d", ptr->index);
      ptr=ptr->next;
    }
    printf("\n");
}

/*
 * Search for an equal or lower score, inserts a node before it
 * Particular Case 0: it's the first ever node
 * Particular case 1: it's the new head node
 * Particular case 2: it's the new end node
 */
Node *addNode(int index, long long evaluation, Node *topHead){
  Node *newNode = malloc(sizeof(Node));
  newNode->index = index;
  newNode->evaluation = evaluation;


  if(topHead == NULL){
    newNode->next = NULL;
    return newNode;
  }

  if(evaluation >= topHead->evaluation){ //Particular case 1
    newNode->next = topHead;
    return newNode;
  }

  Node *tmpPtr;
  tmpPtr = topHead;
  Node *tmpNext;
  tmpNext = tmpPtr->next;
  while(tmpNext != NULL){
    if(evaluation >= tmpNext->evaluation){ // equal or better score found
      tmpPtr->next = newNode;
      newNode->next = tmpNext;
      return topHead;
    }else{
      tmpPtr = tmpNext;
      tmpNext = tmpPtr->next;
    }
  }

  //Particular Case 2
  tmpPtr->next = newNode;
  newNode->next = NULL;
  return topHead;
}

/*
 * Check if the evaluation is worth keeping.
 * If is worth delete the head (witch is the worst and newest score)
 * And call addNode
 */
Node *insertNode(int index, long long evaluation, Node *topHead){ //remove head then add node
  if(evaluation >= topHead->evaluation){
      return topHead; //not good enough to be inserted
  }else{
    Node *toDelete;
    toDelete = topHead;
    topHead = topHead->next;
    free(toDelete);
    return addNode(index,evaluation,topHead);
  }
}

/*
 * Take a graph and evaluates it.
 * prepare graph and first row minimum
 * External cycle: keep count on how many rows are active (i)
 * Active Row Cycle: cycle in the active row
 * In Row Cycle: cycle in that row for the minimum
 * Minimum Found (XColumn, Xvalue): 
 *  add(XV) to sum
 *  delete Column(XC)
 *  activate Row(XC),
 *  add(XV) in Row(XC) 
 */
long long evaluateGraph(int dimension, int *graphMatrix){
  // ALLOCATION
  long long evaluation;
  int minimumValue, minimumRow, minimumColumn;
  int tmpValue, tmpRow, tmpColumn;
  int nonZeroFound;
  int i,j,row, column;
  int *activeRow = (int *) malloc (dimension * sizeof (int)); //store the active rows
  int *activeRowMinimumPosition = (int *) malloc (dimension * sizeof (int)); //store the active rows

  // PREPARATION
  evaluation = 0;
  minimumRow = 0;
  minimumColumn = 0;
  for(i=0;i<dimension;i++){ //ereasing column 0 and diagonal
    *(graphMatrix + i*dimension) = 0;
    *(graphMatrix + i*dimension + i) = 0;
  }
  *activeRow = 0; //set row 0 active
  for(int k=0;k<dimension;k++){ //bulid all minimums
    *(activeRowMinimumPosition + k) = searchMinimumInRow(dimension, graphMatrix + (k*dimension));
  }

  // COMPUTATION
  for(i=0; i < dimension ; i++){ //External Cycle
    minimumValue = __INT32_MAX__;
    nonZeroFound = 0;

    // SEARCH FOR GLOBAL MINIMUM
    for(j=0; j <= i; j++){ //Active Row Cycle
      tmpRow = *(activeRow + j); //Row to analyze
      tmpColumn = *(activeRowMinimumPosition + tmpRow); //Minimum to analyze
      tmpValue = *(graphMatrix + dimension*tmpRow + tmpColumn);
      if(tmpValue != 0){
        nonZeroFound = 1;
        if(tmpValue < minimumValue){
          minimumValue=tmpValue;
          minimumColumn=tmpColumn;
          minimumRow=tmpRow;
        }
      }
    }

    // TAKE ACTION
    if(nonZeroFound == 0){//Some Nodes are Unreachable
      return evaluation;
    }else{//Minimum Found

      evaluation += minimumValue; //add to sum

      *(activeRow + i + 1) = minimumColumn; //activate row

      for(column=0; column <dimension; column++){ //update row
        if(*(graphMatrix + minimumColumn*dimension + column) !=0)
          *(graphMatrix + minimumColumn*dimension + column) += minimumValue;
      }
      
      for(row = 0; row<dimension; row++){ //delete column
        *(graphMatrix + dimension*row + minimumColumn) = 0;
      }

      //search minimum in activated row
      *(activeRowMinimumPosition + minimumColumn) = searchMinimumInRow(dimension, graphMatrix + (minimumColumn*dimension));

      //search minimum in used row
      *(activeRowMinimumPosition + minimumRow) = searchMinimumInRow(dimension, graphMatrix + (minimumRow*dimension));
      //printf("%d\n", *(activeRowMinimumPosition + minimumRow));

      //check for deleted minimum
      for(j=0;j< dimension ;j++){
        if(*(activeRowMinimumPosition + j) == minimumColumn){
          *(activeRowMinimumPosition + j) = searchMinimumInRow(dimension, graphMatrix + j*dimension);
        }
      }
    }
  }
  return evaluation;
}
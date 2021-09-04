#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int index;
  long long evaluation;
  struct node *next;
} Node;

void readGraph(int dimension, int *graphMatrix);
void printGraph(int dimension, int *graphMatrix);
long long evaluateGraph(int dimension, int *graphMatrix);

int ignore;
void printTop(Node *topHead);
Node *addNode(int index, long long evaluation, Node *topHead);
Node *insertNode(int index, long long evaluation, Node *topHead);

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
      //printf("   DEBUG EVAL: %d\n", evaluation); //DEBUG

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
long long evaluateGraph(int dimension, int *graphMatrix){
  long long evaluation = 0;
  int minimumPosition = 0;
  int minimumValue = 0;
  int tmp;
  int nonZeroFound;
  int i,j,row, column;
  //allocate activationVector
  int *activeRow = (int *) malloc (dimension * sizeof (int)); //store the active rows

  //ereasing column 1 and diagonal
  for(row=0;row<dimension;row++){
    for(column=0;column<dimension;column++){
      if(column==0 || row == column){
        *(graphMatrix + row*dimension + column)=0;
      }
    }
  }

  for(i=0; i < dimension ; i++){ //External Cycle
    minimumValue = __INT_MAX__;
    nonZeroFound = 0;
    for(j=0; j <= i; j++){ //Active Row Cycle
      row = *(activeRow + j); //Row to search into
      for(column=0; column < dimension; column++){ //In Row Cycle
        tmp = *(graphMatrix + dimension*row + column);

        if(tmp != 0){
          nonZeroFound = 1;
          if(tmp <= minimumValue){
            minimumValue = tmp;
            minimumPosition = column;
          }
        }
      }
    }
    if(nonZeroFound == 0){
      return evaluation;
    }else{ //Minimum Found

      // printf("DEBUG Minimum Found: %d (%d,%d)\n", minimumValue, row, minimumPosition);
      evaluation += minimumValue; //add to sum

      *(activeRow + i + 1) = minimumPosition; //activate row

      for(column=0; column <dimension; column++){ //update row
        if(*(graphMatrix + minimumPosition*dimension + column) !=0)
          *(graphMatrix + minimumPosition*dimension + column) += minimumValue;
      }
      
      for(row = 0; row<dimension; row++){ //delete column
        *(graphMatrix + dimension*row + minimumPosition) = 0;
      }
    }
  }
  return evaluation;
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
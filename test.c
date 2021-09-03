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
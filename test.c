/*
 * Simple list manipulation exercise.
 * 1. Create a list of integers.
 * 2. Print the list.
 * 3. Sort the list.
 * 4. Print the list
 * 5. Free the list nodes.
 */

#include <stdlib.h>
#include <stdio.h>

struct node {
    int value ;
    struct node *next ;
} ;

extern struct node *mk_node(int v) ;
extern void print_list(struct node *head) ;
extern struct node *sort_list(struct node *head) ;
extern void free_list(struct node *head) ;

#define NVALUES (6)

int initial_contents[] = { 3, 8, 2, 5, 1, 9 } ;

/*
 * Main driver program. Create the list from the initial_contents,
 * print it, sort it, print it, free it, and return.
 */

int main() {
    struct node *head = NULL ;
    struct node *curp ;

    int i ;

    /*
     * Put the initial values into the list. This algorithm
     * will result in the values being inserted in reverse
     * order of the array.
     */
    for( i = 0 ; i < NVALUES ; i++ ) {
        curp = mk_node( initial_contents[i] ) ;
        curp->next = head ;
        head = curp ;
    }

    print_list(head) ;
    head = sort_list(head) ;
    print_list(head) ;
    free_list(head) ;

    return 0 ;
}

/*
 * Return a new node with 'v' as the label and a NULL next link.
 */

struct node *mk_node(int v) {
    struct node *newp = malloc( sizeof(struct node) ) ;
    newp->value = v;
    newp->next = NULL;  

    return newp ; // Place holder
}

/*
 * Print the list headed by 'head', one value per line.
 */

void print_list(struct node *head) {
    printf("List: ");
    struct node *ptr = head;
    while(ptr!=NULL){
        printf("%d ", ptr->value);
        ptr=ptr->next;
    }
    putchar('\n');
}    

/*
 * Sort the list headed by 'head', returning a pointer to the node
 * that ends up at the head of the list.
 */

struct node *sort_list(struct node *head) {
    struct node *tmpPtr;
    struct node *tmpNxt;

    tmpPtr = head;
    tmpNxt = head->next;

    int a, tmp;

    while(tmpNxt != NULL){
        a = tmpPtr->value;
        while(tmpNxt != tmpPtr && tmpNxt->value < a){
            tmp = a;
            tmpPtr->value = tmpNxt->value;
            tmpNxt->value = tmp;
            tmpPtr = tmpPtr->next;
        }
        tmpPtr = head;
        tmpNxt = tmpNxt->next;
    }

    return tmpPtr ; // Place holder
}

/*
 * Free all the nodes in the list headed by 'head'.
 */

void free_list(struct node *head) {
    //struct node *releasep ;
    //while( head != NULL ){
//      releasep = head;
//      head = head->next ;
//
//      free(releasep->value) ;
//      free(releasep) ;
//  }
}
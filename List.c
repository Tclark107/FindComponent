//-----------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
//
// Tristan Clark
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
   int data;
   struct NodeObj* next;
   struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
   Node front;
   Node back;
   int length;
   int cursor;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = NULL;
   N->prev = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty List object.
List newList(void){
   List L;
   L = malloc(sizeof(ListObj));
   L->front = L->back = NULL;
   L->length = 0;
   L->cursor = -1;
   return(L);
}

// this access function is misplaced but it will make it so much easier for me
// isEmpty()
// Returns true (1) if L is empty, otherwise returns false (0)
int isEmpty(List L){
   if( L==NULL ){
      printf("List Error: calling isEmpty() on NULL List reference\n");
      exit(1);
   }
   return(L->length==0);
}


// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.S
// must create delete funtions before this will work
void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL) {
      while (!isEmpty(*pL)) { 
         deleteFront(*pL); 
      }
      free(*pL);
      *pL = NULL;
   }
}


// Access functions -----------------------------------------------------------

// length()
// Returns the length of L.
int length(List L){
   if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(1);
   }
   return(L->length);
}

// index()
// Returns index of cursor element if defined, -1 otherwise.
int index(List L) {
   if( L==NULL ){
      printf("List Error: calling index() on NULL List reference\n");
      exit(1);
   }
   return(L->cursor);
}

// front()
// Returns the value at the front of L.
// Pre: !isEmpty(L)
int front(List L){
   if( L==NULL ){
      printf("List Error: calling front() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling front() on an empty List\n");
      exit(1);
   }
   return(L->front->data);
}

// back()
// Returns the value at the back of L.
// Pre: !isEmpty(L)
int back(List L){
   if( L==NULL ){
      printf("List Error: calling back() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling back() on an empty List\n");
      exit(1);
   }
   return(L->back->data);
}

// get()
// Returns cursor element of L. 
// Pre: length()>0, index()>=0
int get(List L) {
   if( L==NULL ){
      printf("List Error: calling get() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling get() on an empty List\n");
      exit(1);
   }
   if(index(L) < 0) {
      printf("List Error: calling get() when cursor is undefined\n");
      exit(1);
   }
   Node N = L->front;
   for(int i = 0; i < L->cursor; i++) N = N->next;
   return (N->data);
}

// equals()
// Returns true (1) iff Lists A and B are in same
// state, and returns false (0) otherwise.
int equals(List A, List B){
   int eL = 0;
   Node N = NULL;
   Node M = NULL;

   if( A==NULL || B==NULL ){
      printf("List Error: calling equals() on NULL List reference\n");
      exit(1);
   }

   eL = ( A->length == B->length );
   N = A->front;
   M = B->front;
   while( eL && N!=NULL){
      eL = (N->data==M->data);
      N = N->next;
      M = M->next;
   }
   return eL;
}

// Manipulation procedures ----------------------------------------------------

// clear()
// Resets L to its original empty state.
void clear(List L){
   Node N = NULL;
   Node M = NULL;
   for(N = L->front; N != NULL; ) {
      M = N->next;
      deleteFront(L);
      N = M;
   }
   L->cursor = -1;
}

// moveFront()
// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L) {
   if( L==NULL ){
      printf("List Error: calling moveFront() on NULL List reference\n");
      exit(1);
   }
   if(!isEmpty(L)) L->cursor = 0;  
}

// moveBack()
// If L is non-empty, sets cursor under the back element,
 // otherwise does nothing.
void moveBack(List L) {
   if( L==NULL ){
      printf("List Error: calling moveBack() on NULL List reference\n");
      exit(1);
   }
   if(!isEmpty(L)) L->cursor = L->length - 1;  
}

// movePrev()
// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L) {
   if( L==NULL ){
      printf("List Error: calling movePrev() on NULL List reference\n");
      exit(1);
   }
   if(L->cursor > -1) L->cursor--;
} 

// moveNext()
// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L) {
   if( L==NULL ){
      printf("List Error: calling moveNext() on NULL List reference\n");
      exit(1);
   }
   if(L->cursor > -1 && L->cursor < length(L)) L->cursor++;
   if(L->cursor == length(L)) L->cursor = -1;
}

// prepend()
// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, int data) {
   if( L==NULL ){
      printf("List Error: calling prepend() on NULL List reference\n");
      exit(1);
   }
   Node N = newNode(data);
   if(isEmpty(L)) {
      L->front = L->back = N;
   } else {
      N->next = L->front;
      L->front->prev = N;
      L->front = N;
   }
   L->length++;
   L->cursor++;
}

// append()
// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, int data) {
   if( L==NULL ){
      printf("List Error: calling append() on NULL List reference\n");
      exit(1);
   }
   Node N = newNode(data);
   if(isEmpty(L)) {
      L->front = L->back = N;
   } else {
      L->back->next = N;
      N->prev = L->back; 
      L->back = N;
   }
   L->length++;
}

// insertBefore()
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int data) {
   if( L==NULL ){
      printf("List Error: calling insertBefore() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling insertBefore() on an empty List\n");
      exit(1);
   }
   if(index(L) < 0) {
      printf("List Error: calling insertBefore() when cursor is undefined\n");
      exit(1);
   } 

   if(L->cursor > 0) {
      Node N = newNode(data);
      Node M = L->front;
      for(int i = 0; i < L->cursor; i++) M = M->next;
      M->prev->next = N;
      N->prev = M->prev;
      N->next = M;
      M->prev = N;
      L->length++;
      L->cursor++;
   } else {
      prepend(L,data);
   }
}

// insertAfter()
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int data) {
   if( L==NULL ){
      printf("List Error: calling insertAfter() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling insertAfter() on an empty List\n");
      exit(1);
   }
   if(index(L) < 0) {
      printf("List Error: calling insertAfter() when cursor is undefined\n");
      exit(1);
   } 

   if(L->cursor < L->length-1) {
      Node N = newNode(data);
      Node M = L->front;
      for(int i = 0; i < L->cursor; i++) M = M->next;
      M->next->prev = N;
      N->next = M->next;
      N->prev = M;
      M->next = N;
      L->length++;
   } else {
      append(L,data);
   }
}

// deleteFront()
// Delete the front element. Pre: length()>0
void deleteFront(List L) {
   if( L==NULL ){
      printf("List Error: calling deleteFront() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling deleteFront() on an empty List\n");
      exit(1);
   }
   Node N = L->front;
   if(length(L) > 1) {
      L->front->next->prev = NULL;
      L->front = L->front->next;
   } else {
      L->front = L->back = NULL;
   }
   L->length--;
   L->cursor--;
   freeNode(&N);
}

// deleteBack()
// Delete the front element. Pre: length()>0
void deleteBack(List L) {
   if( L==NULL ){
      printf("List Error: calling deleteBack() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling deleteBack() on an empty List\n");
      exit(1);
   }
   Node N = L->back;
   if(length(L) > 1) {
      L->back->prev->next = NULL;
      L->back = L->back->prev;
   } else {
      L->front = L->back = NULL;
   }
   if(index(L) == length(L)-1) L->cursor = -1;
   L->length--;
   freeNode(&N);
}

// delete()
// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L) {
   if( L==NULL ){
      printf("List Error: calling delete() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling delete() on an empty List\n");
      exit(1);
   }
   if(index(L) < 0) {
      printf("List Error: calling delete() when cursor is undefined\n");
      exit(1);
   }
   if(index(L) == 0) {
      deleteFront(L);
   } else if (index(L)== length(L)-1){
      deleteBack(L);
   } else {
      Node N = L->front->next;
      for(int i = 1; i < L->cursor; i++) N = N->next;
      N->prev->next = N->next;
      N->next->prev = N->prev;
      N->next = NULL;
      N->prev = NULL;
      L->length--;
      freeNode(&N);
   }
   L->cursor = -1;
}
 

// Other Functions ------------------------------------------------------------

int numOfDigits(long x) {
   int count = 0;
   while(x!= 0) {
      count++;
      x/=10;
   }
   return count;
}

// printList()
// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
void printList(FILE* out, List L){
   Node N = NULL;

   if( L==NULL ){
      printf("List Error: calling printList() on NULL List reference\n");
      exit(1);
   }

   for(N = L->front; N != NULL; N = N->next){
      fprintf(out ,"%d ", N->data);
   }
}

// copyList()
// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L) {
   if( L==NULL ){
      printf("List Error: calling printList() on NULL List reference\n");
      exit(1);
   }
   List C = newList();
   Node N = NULL;
   for(N = L->front; N != NULL; N = N->next) {
      append(C,N->data);
   }
   return C;
}

// concatList()
// Returns a new List which is the concatenation of
// A and B. The cursor in the new List is undefined,
// regardless of the states of the cursors in A and B.
// The states of A and B are unchanged.
List concatList(List A, List B) {
   if( B==NULL || A==NULL ){
      printf("List Error: calling printList() on NULL List reference\n");
      exit(1);
   }
   List C = copyList(A);
   Node N = NULL; 
   for(N = B->front; N != NULL; N = N->next) {
      append(C,N->data);
   }
   return C;
}

#pragma once
//-----------------------------------------------------------------------------
// List.h
// Header file for List ADT
// John Abendroth
// CruzID: jabendro
// Assignment: PA3
//-----------------------------------------------------------------------------

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

// Exported type
typedef struct ListObj* List;

//Constructors & Destructors -------------------------------------

// newList()
// Creates and returns a new empty List
List newList(void);

// freeList(List *pL);
// Frees all memory associated with *pL and sets *pL to null
void freeList(List* pL);

// Access functions ----------------------------------------

// length()
// Returns the number of elements in the List L
int length(List L);

// index()
// Returns the index of cursor element if defined, or -1 otherwise
int index(List L);

// front()
// Returns front element of List L
// Pre: length() > 0
long front(List L);

// back()
// Returns back element of List L
// Pre: length() > 0
long back(List L);

// get()
// Returns cursor element of List L
// Pre: length() > 0, index() >= 0
long get(List L);

/*
// equals()
// Returns true (1) iff Lists A and B are in same state, and returns false (0) otherwise
int equals(List A, List B);
*/

// Manipulation procedures ----------------------------------------------------

// clear()
// Resets List L to its original empty state
void clear(List l);

// moveFront()
// If L is non-empty, sets cursor under the front element, otherwise does nothing
void moveFront(List L);

// movePrev()
// If cursor is defined and not at front, move cursor one step toward the front of L. if cursor is defined and at front, cursor beceomes undefined; if cursor is undefined do nothing
void movePrev(List L);

//moveBack()
//If L is non-empty, sets cursor under the back element, otherwise does nothing
void moveBack(List L);

// moveNext()
// If cursor is defined and not at back, move cursor one
 // step toward the back of L; if cursor is defined and at
 // back, cursor becomes undefined; if cursor is undefined
 // do nothing
void moveNext(List L);

// set()
// Overwrites the cursor element with x
// Pre: length() > 0, index() >= 0
void set(List L, long x);

// prepend()
// Insert new element into L. If L is non-empty, insertion takes place before front element
void prepend(List L, long data);

// append()
// Insert new element into L. If L is non-empty insertion takes place after back element
void append(List L, long data);

// insertBefore()
// insert new element before cursor
// Pre: length() > 0, index() > 0
void insertBefore(List L, long data);

// insertAfter()
// Insert new element before cursor 
// Pre: length() > 0, index() >= 0
void insertAfter(List L, long data);

// deleteFront()
// Delete the front element
// Pre: length() > 0
void deleteFront(List L);

// deleteBack()
// Delete the back element
// Pre: length() > 0
void deleteBack(List L);

// delete()
// Delete cursor element, making cursor undefined
// Pre: length() > 0, index() >= 0
void delete(List L);

// Other operations -----------------------------------------------------------

// printList()
// Prints to the file pointed to by out, a string representation of L consisting of a psace separated sequence of integers, with front on left
void printList(FILE* out, List L);

// copyList()
// Returns a new List representing the samme integer sequence as L. The cursor in the new list is undefined, regardless of the state of the cursor in L. The state of L is unchanged
List copyList(List l);

#endif

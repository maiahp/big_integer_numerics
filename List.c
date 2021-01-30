/*
* Maiah Pardo, mapardo
* 2020 Fall CSE 101 PA1
* List.c
* Implementation file for List ADT
* The List ADT is a Doubly Linked List that includes a cursor for iteration. The cursor underscores up to one element in the List, and the default cursor state is "undefined".
*/

#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
    LIST_ELEMENT data;
    struct NodeObj* next;
    struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
    Node front;     // references node at the front of list
    Node back;      // references back of list
    Node cursor;    // the node which is pointed to by cursor
    int index;      // the cursor index; starts at 0
    int length;     // number of elements; starts at 1
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Creates and returns a new Node.
Node newNode(LIST_ELEMENT data) {
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->next = NULL;
    N->prev = NULL;
    return(N);
}

// freeNode()
// Frees all heap memory associated with *pN, and sets
// *pN to NULL.
void freeNode(Node *pN) {
    if ((pN != NULL && *pN != NULL)) {
        free(*pN);
        *pN = NULL;
    }
}

// newList()
// Creates and returns a new empty List.
List newList(void) {
    List L = malloc(sizeof(ListObj));
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->index = -1;  // cursor is initially undefined
    L->length = 0;
    return(L);
}

// freeList()
// Frees all heap memory associated with *pL, and sets
// *pL to NULL.
void freeList(List* pL) {
    if((pL != NULL) && (*pL != NULL)) {
        if (length(*pL) != 0) { // if the list has data, delete it first
            clear(*pL);
        }
        free(*pL);     // delete heap memory
        *pL = NULL;    // set pointer to the List to null
    }
}

// Access functions -----------------------------------------------------------

// length()
// Returns the number of elements in L.
int length(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling length() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return(L->length);
}

// index()
// Returns index of cursor element if defined, -1 otherwise.
int index(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling index() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return(L->index); // index is either defined or -1
}

// front()
// Returns front element of L. Pre: length()>0
LIST_ELEMENT front(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling front() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 0) { // precondition, L can't be empty
        fprintf(stderr, "List Error: calling front() on empty List\n");
        exit(EXIT_FAILURE);
    }
    return(L->front->data);
}

// back()
// Returns back element of L. Pre: length()>0
LIST_ELEMENT back(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling back() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 0) { // precondition, L can't be empty
        fprintf(stderr, "List Error: calling back() on empty List\n");
        exit(EXIT_FAILURE);
    }
    return(L->back->data);
}
    
// get()
// Returns cursor element of L. Pre: length()>0, index()>=0
LIST_ELEMENT get(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling get() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 0) { // pre condition: L is not empty
        fprintf(stderr, "List Error: calling get() on empty List\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) == -1) { // pre condition: cursor is defined
        fprintf(stderr, "List Error: calling get() on List with undefined cursor\n");
        exit(EXIT_FAILURE);
    }
    return(L->cursor->data);
}


// Manipulation procedures ----------------------------------------------------

// clear()
// Resets L to its original empty state.
void clear(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling clear() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    while(L->front != NULL) {
        deleteFront(L); // updates length of L and should set L's front and back to null
    }
    L->cursor = NULL;
    L->index = -1;
}

// moveFront()
// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling moveFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) > 0) { // if L is non empty
        L->cursor = L->front;
        L->index = 0;
    } // if L is empty, do nothing
}

// moveBack()
// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void moveBack(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling moveBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) > 0) { // if L is non empty
        L->cursor = L->back;
        L->index = length(L)-1;
    } // if L is empty, do nothing
}

// movePrev()
// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling movePrev() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if ((L->index >= 0) && (L->cursor != L->front)) { // when cursor is defined and not at front node
        // move cursor to previous node
        L->cursor = L->cursor->prev;
        L->index--;
    } else if (L->cursor == L->front){ // if cursor is at the front of the list
        // it becomes undefined
        L->cursor = NULL;
        L->index = -1;
    } // if cursor is undefined, do nothing
}

// moveNext()
// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling moveNext() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if ((L->index >= 0) && (L->cursor != L->back)) { // cursor is defined and not at back
        // move cursor forward one node
        L->cursor = L->cursor->next;
        L->index++;
    } else if (L->cursor == L->back){ // cursor is at back of the list
        // it becomes undefined
        L->cursor = NULL;
        L->index = -1;
    }
}

// prepend()
// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, LIST_ELEMENT data) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling prepend() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    
    Node nodeToInsert = newNode(data);
    
    if (length(L) == 0) { // L is initially empty
        L->front = nodeToInsert;
        L->back = nodeToInsert;
        // cursor is not defined here because the list was empty, don't update
    } else { // L has elements
        nodeToInsert->next = L->front; // new node's next is L's front
        L->front->prev = nodeToInsert; // L's front's prev is new node
        L->front = nodeToInsert; // new front of L is the new node
        
        if (L->index >= 0) { // if the cursor is defined
            L->index++;  // cursor stays pointed to the same node, but its index is shifted +1
        }
    }
    L->length++;
}

// append()
// Insert new element into L. If L is non-empty,
 // insertion takes place after back element.
void append(List L, LIST_ELEMENT data) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling append() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    
    Node nodeToInsert = newNode(data);
    
    if (length(L) == 0) { // L is initially empty
        L->front = nodeToInsert;
        L->back = nodeToInsert;
        // cursor is not defined because the list was empty, don't update
    } else { // L has elements
        nodeToInsert->prev = L->back; // new node's prev is L's back
        L->back->next = nodeToInsert; // L's back's next is new node
        L->back = nodeToInsert; // new back of L is the new node
        // if cursor is defined, it will stay at same node and index will have correct value
    }
    L->length++;
}

// insertBefore
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, LIST_ELEMENT data) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling insertBefore() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 0) { // pre condition: L is not empty
        fprintf(stderr, "List Error: calling insertBefore() on empty List\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) == -1) { // pre condition: cursor is defined
        fprintf(stderr, "List Error: calling insertBefore() when cursor is undefined\n");
        exit(EXIT_FAILURE);
    }

    if (index(L) == 0) { // cursor is at front of list
        prepend(L, data); // new node will be the front of the list
    } else { // cursor is at some other place in list
        Node nodeToInsert = newNode(data);
        // insert before the cursor
        L->cursor->prev->next = nodeToInsert;
        nodeToInsert->prev = L->cursor->prev;
        nodeToInsert->next = L->cursor;
        L->cursor->prev = nodeToInsert;
        
        // index is updated +1
        L->index++;
        
        // update length
        L->length++;
    }
}

// insertAfter()
// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, LIST_ELEMENT data) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling insertAfter() on NULL List reference.\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 0) { // pre condition: L is not empty
        fprintf(stderr, "List Error: calling insertAfter() on empty List\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) == -1) { // pre condition: cursor is defined
        fprintf(stderr, "List Error: calling insertAfter() when cursor is undefined\n");
        exit(EXIT_FAILURE);
    }
    
    if (index(L) == length(L)-1) { // if cursor is at the back of the list
        append(L, data); // add to the back
    } else { // cursor is at some other place in list
        Node nodeToInsert = newNode(data);
        // insert after the cursor
        L->cursor->next->prev = nodeToInsert;
        nodeToInsert->next = L->cursor->next;
        nodeToInsert->prev = L->cursor;
        L->cursor->next = nodeToInsert;

        // inserting after the cursor, we don't update index of cursor
        L->length++; // update length
    }
}

// deleteFront()
// Delete the front element. Pre: length()>0
void deleteFront(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling deleteFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 0) {
        fprintf(stderr, "List Error: calling deleteFront() on empty List\n");
        exit(EXIT_FAILURE);
    }
    
    Node nodeToDelete = L->front;
    
    if (L->index != -1) { // case: if the cursor is defined
        if (L->cursor == L->front) { // if the cursor is the front element
            // it becomes undefined
            L->cursor = NULL;
            L->index = -1;
        } else { // the cursor is not at front element
            // cursor will point to correct node but index of cursor must be decremented
            L->index--;
        }
    }
    
    if (length(L) == 1) { // case: L has 1 element
        // delete the node and the list is empty
        L->front = NULL;
        L->back = NULL;
    } else { // case: L has more than one element
        Node newFront = L->front->next; // new front is element after front
        newFront->prev = NULL; // new front's prev is null
        L->front = newFront; // set L's front as new front
    }
    
    freeNode(&nodeToDelete);
    L->length--; // update length of L
}

// deleteBack()
// Delete the back element. Pre: length()>0
void deleteBack(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling deleteBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 0) {
        fprintf(stderr, "List Error: calling deleteBack() on empty List\n");
        exit(EXIT_FAILURE);
    }
    
    Node nodeToDelete = L->back;
    
    if (L->index != -1) { // case: if the cursor is defined
        if (L->cursor == L->back) { // if cursor is the back element
            // it becomes undefined
            L->cursor = NULL;
            L->index = -1;
        } // if cursor is not the back element, we do nothing
    }
    
    if (length(L) == 1) { // case: L has 1 element
        // delete the node and the list is empty
        L->front = NULL;
        L->back = NULL;
    } else { // case: L has more than one element
        Node newBack = L->back->prev; // new back is back's prev
        newBack->next = NULL; // set new back's next as null
        L->back = newBack;
    }
    
    freeNode(&nodeToDelete);
    L->length--;
}

// delete()
// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling delete() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 0) { // pre condition: List is not empty
        fprintf(stderr, "List Error: calling delete() on empty List\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) == -1) { // pre condition: cursor is defined
        fprintf(stderr, "List Error: calling delete() on List with undefined cursor\n");
        exit(EXIT_FAILURE);
    }
    
    Node nodeToDelete = L->cursor;
    
    if (length(L) == 1) { // If L only has 1 element, it is now empty
        clear(L);
        return;
    } else if (nodeToDelete == L->front) { // node to delete is the front of L
        Node newFront = L->front->next;
        newFront->prev = NULL;
        L->front = newFront;
        
    } else if (nodeToDelete == L->back) { // node to delete is the back of L
        Node newBack = L->back->prev;
        newBack->next = NULL;
        L->back = newBack;
        
    } else { // node to delete is somewhere in the middle of L
        nodeToDelete->prev->next = nodeToDelete->next;
        nodeToDelete->next->prev = nodeToDelete->prev;
    }
    
    // make cursor undefined
    L->cursor = NULL;
    L->index = -1;
    
    // update length
    L->length--;
    
    // delete node
    freeNode(&nodeToDelete);
}

// set()
// Overwrites the cursor element with x.
// Pre: length()>0, index()>=0
void set(List L, LIST_ELEMENT x) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling delete() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 0) { // pre condition: List is not empty
        fprintf(stderr, "List Error: calling delete() on empty List\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) == -1) { // pre condition: cursor is defined
        fprintf(stderr, "List Error: calling delete() on List with undefined cursor\n");
        exit(EXIT_FAILURE);
    }
    
    // overwrite cursor element with x
    L->cursor->data = x;
}


// Other operations -----------------------------------------------------------

// printList()
// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
void printList(FILE* out, List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling printList() on NULL List reference.\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 0) {
        // list is empty, do nothing
        return;
    }
    
    // can't use cursor to traverse, must preserve cursor
    Node currNode = L->front;
    while (currNode != NULL) {
        fprintf(out, LIST_ELEMENT_TOSTRING, currNode->data);
        if (currNode != L->back) { // to avoid an extra space when printing end of list
            fprintf(out, " ");
        }
        currNode = currNode->next;
    }
}

// copyList()
// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling copyList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    
    List copyL = newList();
    
    Node currL = L->front;
    while (currL != NULL) {
        append(copyL, currL->data);
        currL = currL->next;
    }
    // cursor of copyL stays undefined
    return copyL;
}

// concatList()
// Returns a new List which is the concatenation of
// A and B. The cursor in the new List is undefined,
// regardless of the states of the cursors in A and B.
// The states of A and B are unchanged.
List concatList(List A, List B) {
    if ((A == NULL) || (B == NULL)) {
        fprintf(stderr, "List Error: calling concatList() on one or both NULL List references\n");
        exit(EXIT_FAILURE);
    }
    
    List resultList = newList();
    
    // iterate through A and add to resultList
    Node currA = A->front;
    while (currA != NULL) {
        append(resultList, currA->data);
        currA = currA->next;
    }
    
    Node currB = B->front;
    while (currB != NULL) {
        append(resultList, currB->data);
        currB = currB->next;
    }
    
    // cursor of B stays undefined
    return resultList;
}

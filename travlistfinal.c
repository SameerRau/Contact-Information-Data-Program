/*
 * Sameer Rau
 * 9/22/14
 * CSCI 2113 Project 1
 * travlist.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "travlist.h"
#include "listdata.h"

// ==============================================================
// Utility operations
// ==============================================================

// Creates and returns an empty list.
struct TList *create_empty_list() {
	
	struct TList *list = malloc(sizeof(struct TList));
	
	list->first = NULL;
	list->last_left = NULL;
	
	return list;
}

// Clears (empties) the specified list and frees all memory.
/* Empty list: [][] first --> NULL, last_left --> NULL. */
/* Singleton (left) list [A][] first --> A, last_left --> A (last_left->next == NULL), or Singleton (right) list [][B] first --> B, last_left --> NULL. */
 /* Complex list: [A B][C D E] first --> A, last_left --> B. */
void clear_list(struct TList *list) {
	
	struct LNode* ptr1 = list->first;   //points to the first piece of data in the list.
	struct LNode* ptr2 = list->first;

    if(ptr1 != NULL) { 
 
        while(ptr1->next != NULL) { 
        	
        	ptr2 = ptr1->next;
        
            free(ptr1); //frees data memory at this position.
            
            ptr1 = ptr2;
        } 
        
        free(ptr1);
        free(list);
	}
}

// Swaps the elements in the second half of list1 with the elements in the second half of list2.
void swap_list_rights(struct TList *list1, struct TList *list2) {
	
	struct LNode* temp; //used to temporarily store elements in list1 and list2, so data is not lost when swapped.
	
	/* Performs the swap as long as there are elements in the last left position in both lists. */
	if(list1->last_left != NULL && list2->last_left != NULL) { 
		temp = list1->last_left->next;
		list1->last_left->next = list2->last_left->next;
		list2->last_left->next = temp;
	}
	
	/* Performs the swap as long as there are no elements in list1 but elements in list 2 at the last left position. */
	else if(list1->last_left == NULL && list2->last_left != NULL) {
		temp = list1->first;
		list1->first = list2->last_left->next;
		list2->last_left->next = temp;
	}
	
	/* Performs the swap as long as there are elements in list1 but no elements in list 2 at the last left position. */
	else if(list1->last_left != NULL && list2->last_left == NULL) {
		temp = list1->last_left->next;
		list1->last_left->next = list2->first;
		list2->first = temp;
	}
	
	/* There are no elements in list1 or list 2 at the last left position. */
	else {
		temp = list1->first;
		list1->first = list2->first;
		list2->first = temp;
	}
}

// Prints the list to standard output.
void print_list(struct TList *list) {
	struct LNode *left_ptr;
	struct LNode *right_ptr;
	
	//print left list
	
	printf("[ ");
	
	if (list->last_left != NULL ) { // left list is non-empty
		left_ptr = list->first;
		
		while (left_ptr != list->last_left->next) {
			
			print_data(left_ptr->data);
			printf(" ");
			left_ptr = left_ptr->next;
		}
	}
	
	printf("]");

	// print right list
	
	printf("[ ");
	if (list->first != NULL ) { // at least one element is in the list
	
		right_ptr =
			(list->last_left == NULL) ?
				list->first : list->last_left->next;
		
		while (right_ptr != NULL) {
			
			print_data(right_ptr->data);
			printf(" ");
			right_ptr = right_ptr->next;
		}
	}
	
	printf("]");
}

// ==============================================================
// Size functions (no side effects)
// ==============================================================

// Returns the size of the left list.
int list_left_size(struct TList *list) {
	
	struct LNode *lpointer;
	int listsize = 0;
	
	/* The left list as at least one element. */
	if(list->first != NULL && list->last_left != NULL) {
		lpointer = list->first;
		
		while(lpointer != list->last_left->next) {
			listsize++;
			lpointer = lpointer->next;
		}
		
		return listsize;
	}
	
	/* if the left list is empty, returns a size of 0. */
	else {
		return 0;
	}
}

// Returns the size of the right list.
int list_right_size(struct TList *list) {
	
	struct LNode *rpointer;
	int listsize = 0;
	
	/* If there are elements in the left list at the first and last positions. */
	if(list->first != NULL && list->last_left != NULL) {
		
		rpointer = list->first;
		
		while(rpointer != NULL) {
			listsize++;
			rpointer = rpointer->next;
		}
		
		return listsize;
	}
	
	/* There are elements at the last position of the left list and first position of the right list. */
	else if(list->last_left != NULL && list->last_left->next != NULL) {
		
		rpointer = list->last_left->next;
		
		while(rpointer != NULL) {
			listsize++;
			rpointer = rpointer->next;
		}
		
		return listsize;
	}
	
	/* No elements in the right list. */
	else {
		return 0;
	}
}


// ==============================================================
// Insert operation
// ==============================================================
  
// Adds the specified data to the first position in the right list.
void list_insert(struct TList *list, struct LData *data) {

	struct LNode *nextnode = malloc(sizeof(struct LNode)); //memory allocation to allow insertion to take place.
	nextnode->data = data;

	/*If there is an element at the last position of the left list. */
	if(list->last_left != NULL) {
		nextnode->next = list->last_left->next;
		nextnode = list->last_left->next;
	}
	
	/*There is already an element at the first position. */
	else if(list->first != NULL) {
		nextnode->next = list->first;
		nextnode = list->first;
	}
	
	/*If no element at last_left and first position, the element can simply be inserted without problem. */
	else {
		nextnode = list->first;
		nextnode->next = NULL;
	}
}

// ==============================================================
// Remove operation
// ==============================================================

// Removes and returns the first element in the right list.
// Assumes that the right list is not empty.
struct LData *list_remove(struct TList *list) {
	
	struct LNode *firstnode; 
	struct LData *data;
	
	/*If there is not last element in the left list */
	if(list->last_left == NULL) {
		
		/*If the next node in the right list (after the first) is empty; there is no data after the first. */
		if(list->first->next == NULL) {
		
			firstnode = list->first;
			data->data = firstnode->data;
			
			free(firstnode);
			
			return data->data;
		}
		
		/*The next node is not empty; there is data after the first element. */
		else {
			
			firstnode = list->first;
			data = list->first->next;
			list->first = data;
			return firstnode->data;
		}
	}
	
	/*There are elements in the left list. */
	else {
		
		/*The rest of the right list is NULL after the first node. */
		if(list->last_left->next->next == NULL) {
			
			firstnode = list->last_left->next;
			
			free(firstnode);
				
			return firstnode->data;
		}
		
		/*There is at least one element after the first node in the right list. */
		else {
			
			firstnode = list->last_left->next;
			data = list->last_left->next->next;
			firstnode = data;
			
			return firstnode->data;
		}
	}
}

// ==============================================================
// Cursor operations
// ==============================================================

// Resets the cursor to the beginning of the list
void reset_list_cursor(struct TList *list) {
	
	list->last_left = NULL;
}

// Advances the cursor in the list by one element
// Assumes that the right list is not empty
void advance_list_cursor(struct TList *list) {
	
	if(list->last_left == NULL) {
		list->last_left = list->first;
	}
	
	else {
		list->last_left = list->last_left->next;
	}
}

// Advances the cursor to the end of the list
void advance_list_cursor_to_end(struct TList *list) {
	
	if(list->last_left == NULL) {
		
		list->last_left = list->first;
	
		/*continues to loop until the last position of the list is reached. */
		while(list->last_left->next != NULL) {
			list->last_left = list->last_left->next;
		}
	}
}





/*
 * travlistaux.c
 */

#include <stdio.h>
#include "listdata.h"
#include "travlist.h"

// Checks if the left part of the list is empty.
int left_is_empty(struct TList *list) {
    
	return list_left_size(list) == 0;
}

// Checks if the right part of the list is empty.
int right_is_empty(struct TList *list) {
    
    return list_right_size(list) == 0;
}

// Adds the specified data to the end of the list and resets the cursor.
void add_last(struct TList *list, struct LData *data) {
    
    advance_list_cursor_to_end(list);
    list_insert(list, data);
    reset_list_cursor(list);
}

// Adds the specified data to the beginning of the list and resets the cursor.
void add_first(struct TList *list, struct LData *data) {
	
	reset_list_cursor(list);
	list_insert(list, data);
	reset_list_cursor(list);
}

// Adds the specified data to the end of the left list.
void inject(struct TList *list, struct LData *data) {
    
    list_insert(list, data);
    advance_list_cursor(list);
}

// Adds the specified data just after the n-th element in the list.
// Assumes that there are at least n elements in the list.
void insert_after(struct TList *list, int n, struct LData *data) {
   
    int pos = list_left_size(list);
    int counter = 0;
    
    reset_list_cursor(list);
    
    while(counter != n) {
        counter++;
        advance_list_cursor(list);
    }
    
    list_insert(list, data);
    reset_list_cursor(list);
    counter = 0;
    
    while(counter != pos) {
        counter++;
        advance_list_cursor(list);
    }
}

// Swap all the elements of two lists and reset their cursors.
void swap_list(struct TList *list1, struct TList *list2) {
    
    reset_list_cursor(list1);
    reset_list_cursor(list2);
    swap_list_rights(list1, list2);
}

// Insert all the elements from list2 into list1 at the cursor position.
// list2 becomes empty and the length of the left part of list1 is unchanged.
// Assumes that the left part of list2 is empty.`
// Example: (input) list1 = [ A B C ][ D E F ] list2 = [ ][ X Y Z ]
// Example: (output) list1 = [ A B C ][ X Y Z D E F ] list2 = [ ][ ]
void insert_list(struct TList *list1, struct TList *list2) {
    
    int size = list_left_size(list1);
    int counter;
    
    inject(list1, list_remove(list2));
    reset_list_cursor(list1);
    
    while(counter != size) {
        counter++;
        advance_list_cursor;
    }
}

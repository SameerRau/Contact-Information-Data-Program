/*
 * Sameer Rau
 * 9/22/14
 * CSCI 2113 Project 1
 * listdata.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listdata.h"

// Creates and returns an empty data record.
// name = "", age = 0, and sex = 0.
struct LData *create_empty_data() {
	struct LData *data;

	data = malloc(sizeof(struct LData)); //memory allocation for data
	data->name = ""; //default settings for name, age, and sex.
	data->age = 0;
	data->sex = 0; //default setting is male.
	
	return data;
}

// Creates and returns a data record with the specified values
struct LData *create_data(char *name, int age, int sex) {
	
	struct LData *data;
	
	data = malloc(sizeof(struct LData)); //memory allocation for data.
    data->name = name;
    data->age = age;
    data->sex = sex;
   
	return data; 
}

// Resets the information in data to default values (see create_empty_data)
void clear_data(struct LData *data) {
	
	create_empty_data();
}

// Checks if the two data structures are equal.
int are_equal_data(struct LData *data1, struct LData *data2) {
	
	if(strcmp(data1->name, data2->name) == 0) { //uses "strcmp" to compare the two strings of name.
		if((data1->age) == (data2->age)) { //if data is equal, checks for age as the next condition, otherwise returns 0.
			if((data1->sex) == (data2->sex)) {
				return 1;
			}
		}
	}
	
	//if one of the variables is not equal.
	else {
		return 0;
	}
}

// Prints the data in the form: name-age-sex
// sex should be printed as "male" or "female"
// Example: "Joe-20-male"
void print_data(struct LData *data) {
	char* m; //since there are no strings in c, char* designate variables for male and female, respectively.
	char* f;
	
	//if the sex is female.
	if(data->sex==1) {
		f = "female";
		printf("%s-%d-%s", data->name, data->age, f);
	}
	
	//if the sex is male.
	else {
		m = "male";
		printf("%s-%d-%s", data->name, data->age, m);
	}
}

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum class command {
	actual,
	next,
	prev,
	add_beg,
	add_end,
	add_act,
	del_beg,
	del_end,
	del_val,
	del_act,
	print_forward,
	print_backward,
	mistake_enter,
	not_found,
};

enum class which_way {
	forward,
	backwards,
};

struct two_direct {
	int value;
	two_direct* nap; //next and previous
};

class XOR_LINKED_LIST {
	two_direct* head;
	two_direct* tail;
	two_direct* actual;
	two_direct* actual_neighbour_left;
	two_direct* actual_neighbour_right;
	int elements_count;
public:
	//This function is used in constructor, so it's before it. It's only for code size reduction purposes.
	void ResetTheList();

	XOR_LINKED_LIST();
	//Returns XOR of two adresses
	two_direct* XOR(two_direct* x, two_direct* y) const;
	//Adds element to the beggining of the list. It's a base for other functions, so includes all possibilities.
	void ADD_BEG(const int add_value);
	//Adds element to the end of the list. It uses ADD_BEG
	void ADD_END(const int add_value);
	//Adds element before actual. Uses ADD_BEG function.
	void ADD_ACT(const int add_value);
	//If possible prints the value of element actual points to
	void ACTUAL();
	//Makes actual pointer go forward and reads it's new value. If there are no elements or only one there is no need to move anything.
	void NEXT();
	//Makes actual pointer go backward and reads it's new value. If there are no elements or only one there is no need to move anything.
	void PREV();
	//Deletes current head of the list and moves elements. It's a base function, so contains all possibilities.
	void DEL_BEG();
	//Deletes last element on the list.
	void DEL_END();
	//Deletes given value from the list. All of it's occurences!
	void DEL_VAL(const int del_value);
	//Deletes the value actual points to. It moves actual to the previous element or if not possible then to the tail.
	void DEL_ACT();
	//Prints the list forward or backwards, depending on the given argument.
	void PRINT(which_way frontorback) const;
	//Depending on the input command returns value from the command enum class
	command GetMyCommand(char* order) const;

	~XOR_LINKED_LIST();
};
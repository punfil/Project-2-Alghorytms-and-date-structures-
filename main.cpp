#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "XOR_LINKED_LIST.h"

#define MAX_LINE_LENGTH 20

int main() {
	char current_order[MAX_LINE_LENGTH];
	XOR_LINKED_LIST myobject;
	//Number variable for adding to the list commands.
	int number = 0;
	char delimiter[] = " ";
	//We break the loop using CTRL+Z.
	while (fgets(current_order, MAX_LINE_LENGTH, stdin)) {
		char* order = strtok(current_order, delimiter);
		//Cutting off \n makes no difference for numbers, but makes a huge one for GetMyCommand function! (we compare string's without \n).
		if (order[strlen(order) - 1] == '\n')
			order[strlen(order) - 1] = '\0';
		char* cnumber = strtok(nullptr, delimiter);
		//If there is second word in the line it's argument for function, that should be an integer.
		if (cnumber != nullptr) {
			number = atoi(cnumber);
		}
		command com = myobject.GetMyCommand(order);
		switch (com) {
		case command::actual:
			myobject.ACTUAL();
			break;
		case command::next:
			myobject.NEXT();
			break;
		case command::prev:
			myobject.PREV();
			break;
		case command::add_beg:
			myobject.ADD_BEG(number);
			break;
		case command::add_end:
			myobject.ADD_END(number);
			break;
		case command::add_act:
			myobject.ADD_ACT(number);
			break;
		case command::del_beg:
			myobject.DEL_BEG();
			break;
		case command::del_end:
			myobject.DEL_END();
			break;
		case command::del_val:
			myobject.DEL_VAL(number);
			break;
		case command::del_act:
			myobject.DEL_ACT();
			break;
		case command::print_forward:
			myobject.PRINT(which_way::forward);
			break;
		case command::print_backward:
			myobject.PRINT(which_way::backwards);
			break;
		case command::not_found:
			printf("Command not found\n");
			break;
		}
	}
	return 0;
}
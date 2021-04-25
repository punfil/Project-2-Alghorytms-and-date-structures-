#include "XOR_LINKED_LIST.h"

//This function is used in constructor, so it's before it. It's only for code size reduction purposes.
void XOR_LINKED_LIST::ResetTheList() {
	head = nullptr;
	tail = nullptr;
	actual = nullptr;
	actual_neighbour_left = nullptr;
	actual_neighbour_right = nullptr;
}

XOR_LINKED_LIST::XOR_LINKED_LIST() {
	ResetTheList();
	//Some might say unnecessary, but definitely makes the code easier to understand and makes hardly any performance difference.
	elements_count = 0;
}
//Returns XOR of two adresses
two_direct* XOR_LINKED_LIST::XOR(two_direct* x, two_direct* y) const {
	return (two_direct*)((uintptr_t)(x) ^ (uintptr_t)(y));
}
//Adds element to the beggining of the list. It's a base for other functions, so includes all possibilities.
void XOR_LINKED_LIST::ADD_BEG(const int add_value) {
	two_direct* temp = (two_direct*)malloc(sizeof(two_direct));
	if (temp == nullptr) {
		printf("Error allocating memory. Please try again later :/");
		return;
	}
	temp->value = add_value;
	temp->nap = XOR(head, nullptr);
	//If there are elements on the list then move current head to the second position.
	if (elements_count) {
		head->nap = XOR(temp, head->nap);
	}
	//If there are no elements then set all variables to the current element.
	else if (!elements_count) {
		tail = temp;
		actual = temp;
		actual_neighbour_left = temp;
		actual_neighbour_right = temp;
	}
	//If actual was first then the new head becomes it's left neighbour.
	if (actual == head) {
		actual_neighbour_left = temp;
	}
	elements_count++;
	head = temp;
}
//Adds element to the end of the list. It uses ADD_BEG
void XOR_LINKED_LIST::ADD_END(const int add_value) {
	//If the list is empty we utilisise the base function and quit the function. It makes no difference.
	if (!elements_count) {
		ADD_BEG(add_value);
		return;
	}
	two_direct* temp = (two_direct*)malloc(sizeof(two_direct));
	if (temp == nullptr) {
		printf("Error allocating memory. Please try again later :/");
		return;
	}
	temp->value = add_value;
	temp->nap = XOR(tail, nullptr);
	//If there are elements on the list, then we need to move tail to the pre-last position.
	if (elements_count) {
		tail->nap = XOR(temp, tail->nap);
	}
	//If actual was last then the new element becomes it's right neighbour.
	if (actual == tail) {
		actual_neighbour_right = temp;
	}
	elements_count++;
	tail = temp;
}
//Adds element before actual. Uses ADD_BEG function.
void XOR_LINKED_LIST::ADD_ACT(const int add_value) {
	//If there are no elements then it does not make a difference.
	if (!elements_count) {
		ADD_BEG(add_value);
		return;
	}
	two_direct* temp = (two_direct*)malloc(sizeof(two_direct));
	if (temp == nullptr) {
		printf("Error allocating memory. Please try again later :/");
		return;
	}
	temp->value = add_value;
	//If actual was head, then it needs to be moved forward.
	if (actual == head) {
		temp->nap = XOR(actual, nullptr);
		actual->nap = XOR(temp, actual->nap);
		head = temp;
	}
	//If actual was tail it needs to be moved properly as well...
	else if (actual == tail) {
		temp->nap = XOR(actual_neighbour_left, actual);
		actual_neighbour_left->nap = XOR(XOR(actual_neighbour_left->nap, actual), temp);
		actual->nap = XOR(temp, nullptr);
	}
	//Else means the actual is somewhere in the center of the list.
	else {
		two_direct* left_prev = XOR(actual_neighbour_left->nap, actual);
		actual_neighbour_left->nap = XOR(left_prev, temp);
		temp->nap = XOR(actual_neighbour_left, actual);
		actual->nap = XOR(temp, actual_neighbour_right);
	}
	//The new added element definitely becomes left neighbour of actual.
	actual_neighbour_left = temp;
	elements_count++;
}
//If possible prints the value of element actual points to
void XOR_LINKED_LIST::ACTUAL() {
	if (actual != nullptr) {
		printf("%d\n", actual->value);
	}
	else
		printf("%s\n", "NULL");
}
//Makes actual pointer go forward and reads it's new value. If there are no elements or only one there is no need to move anything.
void XOR_LINKED_LIST::NEXT() {
	if (elements_count > 1) {
		actual_neighbour_left = actual;
		//Next after tail is head, it works like cyclic list
		if (actual == tail) {
			actual = head;
			actual_neighbour_right = XOR(nullptr, head->nap);
		}
		//If actual is pre-last then we need to move right neighbour to head.
		else if (actual_neighbour_right == tail) {
			actual_neighbour_right = head;
			actual = tail;
		}
		else {
			actual_neighbour_left = actual;
			actual = actual_neighbour_right;
			actual_neighbour_right = XOR(actual_neighbour_right->nap, actual_neighbour_left);
		}
	}
	ACTUAL();
}
//Makes actual pointer go backward and reads it's new value. If there are no elements or only one there is no need to move anything.
void XOR_LINKED_LIST::PREV() {
	if (elements_count > 1) {
		actual_neighbour_right = actual;
		//Before head is tail, it works like cyclic list
		if (actual == head) {
			actual = tail;
			actual_neighbour_left = XOR(nullptr, tail->nap);
		}
		//If actual is first after head then we need to move left neighbour to tail.
		else if (actual_neighbour_left == head) {
			actual_neighbour_left = tail;
			actual = head;
		}
		else {
			actual_neighbour_right = actual;
			actual = actual_neighbour_left;
			actual_neighbour_left = XOR(actual_neighbour_right, actual_neighbour_left->nap);
		}
	}
	ACTUAL();
}
//Deletes current head of the list and moves elements. It's a base function, so contains all possibilities.
void XOR_LINKED_LIST::DEL_BEG() {
	//Nothing to do if list is empty :)
	if (elements_count) {
		two_direct* head_next = XOR(head->nap, nullptr);
		//If and else if to make sure actual and it's neighbours are properly seated.
		if (actual == head) {
			actual = tail;
			actual_neighbour_left = XOR(tail->nap, nullptr);
			actual_neighbour_right = head_next;
		}
		else if (actual_neighbour_left == head) {
			actual_neighbour_left = tail;
		}
		//If there is more than one element then we need to change to XOR of the next next element.
		if (elements_count > 1) {
			head_next->nap = XOR(head_next->nap, head);
		}
		free(head);
		head = head_next;
		elements_count--;
		//Utilisation of this function just makes everything easier. Reset's the list to base state (all pointers = nullptr) if there are no elements.
		if (!elements_count)
			ResetTheList();
	}
}
//Deletes last element on the list.
void XOR_LINKED_LIST::DEL_END() {
	if (tail != nullptr) {
		two_direct* tail_prev = XOR(tail->nap, nullptr);
		//If and else if to make sure actual and it's neighbours are properly seated.
		if (actual == tail) {
			actual = head;
			actual_neighbour_right = XOR(head->nap, nullptr);
			actual_neighbour_left = tail_prev;
		}
		else if (actual_neighbour_right == tail) {
			actual_neighbour_right = head;
		}
		//If there is more than one element then we need to change to XOR of the previous previous element.
		if (elements_count > 1) {
			tail_prev->nap = XOR(tail_prev->nap, tail);
		}
		free(tail);
		tail = tail_prev;
		elements_count--;
		//Utilisation of this function just makes everything easier. Reset's the list to base state (all pointers = nullptr) if there are no elements.
		if (!elements_count)
			ResetTheList();
	}
}
//Deletes given value from the list. All of it's occurences!
void XOR_LINKED_LIST::DEL_VAL(const int del_value) {
	//Deletes element from the beginning while it contains given value. It reduces conditions count.
	for (; head != nullptr && head->value == del_value;)
		DEL_BEG();
	//Deletes element from the end while it contains given value. It reduces conditions count.
	for (; tail != nullptr && tail->value == del_value;)
		DEL_END();
	//If there are no element's we have nothing to do :)
	if (elements_count) {
		two_direct* current = XOR(head, nullptr);
		two_direct* next = nullptr;
		two_direct* previous = nullptr;
		//While we did not reach the end of the list
		for (; current != nullptr;) {
			next = XOR(previous, current->nap);
			//prev!=nullptr is conservative approach (never will be false), because first element will never contain value to be deleted - look line 253
			if (current->value == del_value && previous != nullptr) {
				//Facilitates the function. We use conditions already stated higher in the code.
				if (current == actual) {
					DEL_ACT();
				}
				else {
					previous->nap = XOR(XOR(previous->nap, current), next);
					next->nap = XOR(XOR(next->nap, current), previous);
					free(current);
					elements_count--;
				}
				//If we deleted an element then we need to adjust our pointers we use to navigate on the list.
				current = next;
				next = XOR(previous, current->nap);
				continue;
			}
			previous = current;
			current = next;
		}
	}
	//If there are no more elements on the list then bring it back to initial state.
	if (!elements_count)
		ResetTheList();
}
//Deletes the value actual points to. It moves actual to the previous element or if not possible then to the tail.
void XOR_LINKED_LIST::DEL_ACT() {
	//No elements = no work to do
	if (!elements_count) return;
	//One element = simple work
	if (elements_count == 1) { free(head); ResetTheList(); elements_count--; return; }
	//If actual is head then we can treat is as the first element.
	if (actual == head) {
		DEL_BEG();
		return;
	}
	// If actual is tail then we can treat it as the last element
	else if (actual == tail) {
		DEL_END();
		return;
	}
	//Reason for this condition is that when this situation happens we need to move the actual left nieghbour's pointer to the tail.
	else if (actual_neighbour_left == head) {
		actual_neighbour_left = tail;
		head->nap = XOR(actual->nap, head);
		actual_neighbour_right->nap = XOR(head, XOR(actual, actual_neighbour_right->nap));
		free(actual);
		actual = head;
	}
	else {
		actual_neighbour_left->nap = XOR(XOR(actual_neighbour_left->nap, actual), actual_neighbour_right);
		actual_neighbour_right->nap = XOR(XOR(actual, actual_neighbour_right->nap), actual_neighbour_left);
		free(actual);
		actual = actual_neighbour_left;
		actual_neighbour_left = XOR(actual_neighbour_right, actual_neighbour_left->nap);
	}
	elements_count--;
}
//Prints the list forward or backwards, depending on the given argument.
void XOR_LINKED_LIST::PRINT(which_way frontorback) const {
	two_direct* current;
	if (frontorback == which_way::forward)
		current = head;
	else
		current = tail;
	two_direct* previous = nullptr;
	two_direct* next = nullptr;
	while (current != nullptr) {
		printf("%d ", current->value);
		next = XOR(previous, current->nap);
		previous = current;
		current = next;
	}
	if (elements_count) {
		printf("\n");
		return;
	}
	printf("%s\n", "NULL");
}
//Depending on the input command returns value from the command enum class
command XOR_LINKED_LIST::GetMyCommand(char* order) const{
	if (!strcmp(order, "ACTUAL"))
		return command::actual;
	if (!strcmp(order, "NEXT"))
		return command::next;
	if (!strcmp(order, "PREV"))
		return command::prev;
	if (!strcmp(order, "ADD_BEG"))
		return command::add_beg;
	if (!strcmp(order, "ADD_END"))
		return command::add_end;
	if (!strcmp(order, "ADD_ACT"))
		return command::add_act;
	if (!strcmp(order, "DEL_BEG"))
		return command::del_beg;
	if (!strcmp(order, "DEL_END"))
		return command::del_end;
	if (!strcmp(order, "DEL_VAL"))
		return command::del_val;
	if (!strcmp(order, "DEL_ACT"))
		return command::del_act;
	if (!strcmp(order, "PRINT_FORWARD"))
		return command::print_forward;
	if (!strcmp(order, "PRINT_BACKWARD"))
		return command::print_backward;
	if (!strcmp(order, ""))
		return command::mistake_enter;
	return command::not_found;
}
XOR_LINKED_LIST::~XOR_LINKED_LIST() {
	two_direct* current = head;
	two_direct* previous = nullptr;
	two_direct* next = nullptr;
	while (current != nullptr) {
		next = XOR(previous, current->nap);
		if (previous != nullptr) free(previous);
		previous = current;
		current = next;
	}
}
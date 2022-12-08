#pragma once
#include "list.h"

typedef struct Stack {
	int cnt;
	FC* top;
}stack;

void stack_push(FC* d, stack* stk);
FC* stack_pop(stack* stk);
void initStack(stack* stk);
void print_stack(stack* stk);
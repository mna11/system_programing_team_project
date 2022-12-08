#include "stack.h"

void stack_push(FC* d, stack* stk) {
	d->next_top = stk->top;
	stk->top = d;
	stk->cnt++;
}

FC* stack_pop(stack* stk) {
	FC* t = stk->top;
	stk->top = stk->top->next_top;
	stk->cnt--;
	return t;
}

void initStack(stack* stk) {
	stk->cnt = 0;
	stk->top = NULL;
}

void print_stack(stack* stk)
{
	for (stack* p = stk; p->top != NULL; p->top = p->top->next_top) {
		print_list(p->top);
	}
}
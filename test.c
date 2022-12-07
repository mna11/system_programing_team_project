#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct FileContents {
	char data;
	struct FileContents* next;
	struct FileContents* next_top;
}FC;

typedef struct Stack {
	int cnt;
	FC* top;
}stack;

FC* head_insert(FC* head, char value) {
	head->data = value;
	return head;
}

FC* insertVal(FC* pre, char value)
{
	FC* p = (FC*)malloc(sizeof(FC));
	p->data = value;
	pre->next = p;
	return p;
}

void push(FC* d, stack* stk) {
	d->next_top = stk->top;
	stk->top = d;
	stk->cnt++;
}

void initialize(stack* stk) {
	stk->cnt = 0;
	stk->top = NULL;
}

void print_list(FC* head)
{
	for (FC* p = head; p != NULL; p = p->next)
		printf("%c -> ", p->data);
	printf("NULL \n");
}

void print_stack(stack* stk)
{
	for (stack* p = stk; p->top != NULL; p->top = p->top->next_top) {
		print_list(p->top);
	}
}

int main(void) {
	stack* stk = (stack*)malloc(sizeof(stack));
	FC* cur;
	FC* post;
	char word, pre = '\0';

	initialize(stk);

	while (scanf("%c", &word) == 1) {
		if (word == '\n') continue;
		if ((pre != '\0' && isdigit(pre) > 0) && isdigit(word) > 0 || word == '.') {
			cur = insertVal(cur, word);
		}
		else {
			FC* tmp = (FC*)malloc(sizeof(FC));
			cur = head_insert(tmp, word);
			push(tmp, stk);
		}

		pre = word;
	}
	print_stack(stk);
	return 0;
}


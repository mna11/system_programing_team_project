#include "list.h"

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

void print_list(FC* head)
{
	for (FC* p = head; p != NULL; p = p->next)
		printf("%c -> ", p->data);
	printf("NULL \n");
}
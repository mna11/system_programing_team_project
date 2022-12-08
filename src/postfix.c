#include "postfix.h"

char priority(char data1, char data2) {
	char tmp1, tmp2;
	if ((data1 == '+') || (data1 == '-') || (data1 == '('))
		tmp1 = 1;
	else
		tmp1 = 2;
	if ((data2 == '+') || (data2 == '-') || (data2 == '('))
		tmp2 = 1;
	else
		tmp2 = 2;
	return tmp2 - tmp1;
}

char isOperator(char op) {
	char res = 0;
	if (op == '+')
		res = op;
	else if (op == '-')
		res = op;
	else if (op == '*')
		res = op;
	else if (op == '/')
		res = op;
	else if (op == '(')
		res = op;
	else if (op == ')')
		res = op;
	else
		res = 0;
	return res;
}

queue* toPostFix() {
	stack* stk = (stack*)malloc(sizeof(stack));
	queue* post = (queue*)malloc(sizeof(queue));
	FC* cur;
	FC* popData;
	char word, pre = '\0';
	initStack(stk);
	initQueue(post);

	while (scanf("%c", &word) == 1) {
		if (word == '\n') continue;
		if ((pre != '\0' && isdigit(pre) > 0) && isdigit(word) > 0 || word == '.' || pre == '.') {
			cur = insertVal(cur, word);
		}
		else {
			if (isOperator(word)) {
				FC* tmp = (FC*)malloc(sizeof(FC));
				if (word == ')') {
					while (1) {
						popData = stack_pop(stk);
						if (popData->data == '(') {
							break;
						}
						else {
							queue_push(popData, post);
						}
					}
				}
				else if (word == '(') {
					cur = head_insert(tmp, word);
					stack_push(tmp, stk);
				}
				else {
					while (1) {
						if (stk->top == NULL) {
							cur = head_insert(tmp, word);
							stack_push(tmp, stk);
							break;
						}
						else {
							popData = stack_pop(stk);
							if (priority(popData->data, word) == 1 || popData->data == '(') {
								stack_push(popData, stk);
								cur = head_insert(tmp, word);
								stack_push(tmp, stk);
								break;
							}
							else {
								queue_push(popData, post);
							}
						}
					}
				}
			}
			else {
				FC* tmp = (FC*)malloc(sizeof(FC));
				cur = head_insert(tmp, word);
				queue_push(tmp, post);
			}
		}
		pre = word;
	}

	while (stk->top != NULL) {
		popData = stack_pop(stk);
		queue_push(popData, post);
	}

	return post;
}
#include "postfix.h"
#include "multiply.h"
#include "minus.h"
#include "plus.h"
#include "division.h"

LINK evaluate(queue* postfix);

int main(void) {
	queue* postfix = toPostFix(); //큐형태의 postfix가 만들어짐
	digit_matching(postfix); //자릿수 세팅함
	print_queue(postfix); //테스트용
	LINK result = evaluate(postfix);
	print_list_test(result);
	return 0;
}

LINK evaluate(queue* postfix) {
	stack* stk = (stack*)malloc(sizeof(stack));
	initStack(stk);
	LINK res = (LINK)malloc(sizeof(LINK));
	for (LINK p = postfix->front; p != NULL; p = p->next_rear) {
		if (p->d == '+' && p->cnt > 1 || p->d == '-' && p->cnt > 1) {
			stack_push(p, stk);
		}
		else {
			LINK d1;
			LINK d2;
			d2 = stack_pop(stk);
			d1 = stack_pop(stk);
			if (p->d == '+') {
				if (d1->d == '+' && d2->d == '+') {
					res = plus(d1, d2);
				}
				else if (d1->d == '+' && d2->d == '-') {
					d2->d = '+';
					res = minus(d1, d2);
				}
				else if (d1->d == '-' && d2->d == '+') {
					d1->d == '+';
					res = minus(d2, d1);
				}
				else { // d1->d == '-' && d2->d == '-'
					res = plus(d1, d2);
				}
			}
			else if (p->d == '-') {
				if (d1->d == '+' && d2->d == '+') {
					res = minus(d1, d2);
				}
				else if (d1->d == '+' && d2->d == '-') {
					d2->d = '+';
					res = plus(d1, d2);
				}
				else if (d1->d == '-' && d2->d == '+') {
					d2->d == '-';
					res = plus(d2, d1);
				}
				else { //d1->d == '-' && d2->d == '-'
					d2->d = '+';
					d1->d = '+';
					res = minus(d2, d1);
				}
			}
			else if (p->d == '*') {
				res = multiply(d1, d2);
			}
			else if (p->d == '/') {
				//res = division(d1, d2);
			}
			stack_push(res, stk);
		}
	}
	res = stack_pop(stk);
	free(stk);
	return res;
}
#include "postfix.h"
#include "multiply.h"
#include "minus.h"

LINK evaluate(queue* postfix);

int main(void) {
	queue* postfix = toPostFix(); //큐형태의 postfix가 만들어짐
	digit_matching(postfix); //자릿수 세팅함
	LINK result = evaluate(postfix);
	print_list_test(result);
	//print_queue(postfix); //테스트용
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
					//res = 더하기(d1, d2);
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
					//res = 더하기(d1, d2);
				}
			}
			else if (p->d == '-') {
				if (d1->d == '+' && d2->d == '+') {
					res = minus(d1, d2);
					//print_list_test(res);
				}
				else if (d1->d == '+' && d2->d == '-') {
					d2->d = '+';
					//res = 더하기(d1, d2);
				}
				else if (d1->d == '-' && d2->d == '+') {
					d2->d == '-';
					//res = 더하기(d2, d1);
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
				//res = 나누기(d1, d2);
			}
			stack_push(res, stk);
		}
	}
	res = stack_pop(stk);
	free(stk);
	return res;
}
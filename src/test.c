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
		if (p->d == '+' && p->cnt > 0 || p->d == '-' && p->cnt > 0) {
			stack_push(p, stk);
		}
		else {
			LINK d1;
			LINK d2;
			d2 = stack_pop(stk);
			d1 = stack_pop(stk);
			if (p->d == '+') {
				//res = 더하기(d1, d2);
			}
			else if (p->d == '-') {
				res = minus(d1, d2);
			}
			else if (p->d == '*') {
				res = multiply(d1, d2);
			}
			else if (p->d == '/') {
				//res = 나누기(d1, d2);
			}
			stack_push(res, stk);
		}
		print_list_test(res);
	}
	res = stack_pop(stk);

	return res;
}
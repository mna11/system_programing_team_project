#include "postfix.h"
#include "multiply.h"
#include "minus.h"
#include "plus.h"

LINK evaluate(queue* postfix);

int main(void) {
	printf("[ ======= Welcome to infinite calulator made by TEAM 7! ======= ] \n");
	printf("Enter the expression in infix notation.\n");
	printf("Input  : ");
	queue* postfix = toPostFix(); //큐형태의 postfix가 만들어짐
	digit_matching(postfix); //자릿수 세팅함
	//print_queue(postfix); //테스트용
	LINK result = evaluate(postfix); 
	printf("Result : ");
	print_list(result); //계산 결과 출력
	putchar('\n');
	free_all(result);
	return 0;
}

LINK evaluate(queue* postfix) {
	stack* stk = (stack*)malloc(sizeof(stack));
	initStack(stk);
	LINK res = (LINK)malloc(sizeof(LINK));
	for (LINK p = postfix->front; p != NULL; p = p->next_rear) {
		if (p->d == '+' && p->cnt > 1 || p->d == '-' && p->cnt > 1) { //숫자가 들어온 경우 스택에 넣어줌
			stack_push(p, stk);
		}
		else { //연산자가 들어온 경우
			LINK d1;
			LINK d2;
			d2 = stack_pop(stk); // 스택의 위에서 두 수를 가져옴
			d1 = stack_pop(stk);

			//연산자와 수의 부호를 비교해서 알맞은 계산 함수를 호출함
			if (p->d == '+') {
				if (d1->d == '+' && d2->d == '+') {
					res = plus(d1, d2);
				}
				else if (d1->d == '+' && d2->d == '-') {
					d2->d = '+';
					res = minus(d1, d2);
				}
				else if (d1->d == '-' && d2->d == '+') {
					d1->d = '+';
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
					d2->d = '-';
					res = plus(d1, d2);
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
			stack_push(res, stk); //결과는 스택에 넣음
		}
	}
	res = stack_pop(stk); //스택에는 결과 하나만 남아있으므로 팝한 것이 결과이다.
	free(stk);
	return res;
}
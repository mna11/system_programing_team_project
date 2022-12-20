#include "stack.h"

void stack_push(LINK d, stack* stk) {
	d->next_top = stk->top; //d의 next_top에 현재 스택의 top을 기억시킴, d가 나중에 팝될 경우, 다음 top 위치를 지정시키기 위해
	stk->top = d; //스택의 탑에 d를 지정함 
	stk->cnt++; //스택의 데이터 수를 증가시킴 
}

LINK stack_pop(stack* stk) {
	LINK t = stk->top; //스택의 탑 값을 FC* t에 저장시킴
	stk->top = stk->top->next_top; //현재 탑 전의 탑으로 바꿈 (스택을 쌓는다 생각했을 때, 위에서 두번째 데이터로 탑을 바꾼다는 말임)
	stk->cnt--; //스택의 데이터 수를 감소시킴
	return t; //팝한 탑 값을 반환함 
}

void initStack(stack* stk) {
	stk->cnt = 0; //초기상태 설정이므로 데이터 수는 0이다.
	stk->top = NULL; //초기상태 설정이므로 NULL
}

void print_stack(stack* stk)
{
	for (stack* p = stk; p->top != NULL; p->top = p->top->next_top) { //스택의 탑이 NULL이 될때까지 다 비워냄
		print_list(p->top); //리스트를 출력함 
	}
}
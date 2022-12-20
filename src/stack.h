#pragma once
#include "function.h"

typedef struct Stack {
	int cnt;
	LINK top; //팝을 위해 top을 기억함
}stack;

void stack_push(LINK d, stack* stk); //스택에게 FC* d를 푸시함 
LINK stack_pop(stack* stk); //스택의 top 데이터를 팝함
void initStack(stack* stk); //스택의 초기상태 만들기
void print_stack(stack* stk); // 스택을 출력함 (테스트 용)
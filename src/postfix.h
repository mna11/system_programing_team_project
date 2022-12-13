#pragma once
#include "stack.h"
#include "queue.h"

char priority(char data1, char data2); //연산자 우선순위 체크함
char isOperator(char op); //연산자인지 아닌지 판단함
queue* toPostFix(); //입력 파일 데이터를 받아서 queue 형태의 postfix를 반환함
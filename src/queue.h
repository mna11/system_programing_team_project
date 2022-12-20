#pragma once
#include "function.h"

typedef struct Queue {
	int cnt; //데이터 개수 (테스트 용)
	LINK front; //팝을 위해 앞을 기억함
	LINK rear; //데이터가 푸시요청을하면 뒤부분에 붙여야하니 뒤를 기억함 
}queue;

int queEmpty(queue* que); //큐가 비어있는지 체크함
void queue_push(LINK d, queue* que); //큐에 FC* d를 푸시함
LINK queue_pop(queue* que); //큐의 front를(가장 앞에 있는 데이터) 팝함
void initQueue(queue* que); //큐의 초기상태 만드는 것
void digit_matching(queue* que); //큐를 순회하며 digit_matching_list()를 호출하여 자릿수 세팅을 함
void print_queue(queue* que); //큐를 출력하는 (테스트용)
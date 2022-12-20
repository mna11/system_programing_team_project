#include "queue.h"
//각 함수별 용도 설명은 헤더파일에 있음

int queEmpty(queue* que) {
	return que->cnt == 0; //만약 큐에 들어있는 데이터수가 0이라면 1, 아니라면 0을 반환
}

void queue_push(LINK d, queue* que) {
	if (queEmpty(que)) {
		que->front = d; //만약에 큐가 비어있다면 front에 저장함.
	}
	else {
		que->rear->next_rear = d; //지금까지의 뒤가 다음 뒤를 가리키게 만듬 (아직은 값이 갱신되지 않은 거임)
	}
	que->rear = d; //큐의 뒤에 값을 저장함. (값의 갱신)
	que->cnt++; //큐에 들어있는 데이터 수를 증가시킴
}

LINK queue_pop(queue* que) {
	if (queEmpty(que))
		return NULL; //큐가 비어있는데 팝을 할려하므로 NULL을 리턴함
	LINK tmp = que->front; // 현재 front 값을 저장함 
	que->front = tmp->next_rear; // front 값 갱신  
	que->cnt--; // 데이터 수를 감소
	return tmp; // front 였던 것을 반환해줌 
}

void initQueue(queue* que) {
	que->front = que->rear = NULL; // 초기상태이므로 front, rear 모두 NULL 
	que->cnt = 0; //초기 상태이므로 데이터 수는 0임
}

void digit_matching(queue* que) {
	int que_cnt = que->cnt;
	for (LINK p = que->front; p != NULL; p = p->next_rear) {  // 큐 순회
		digit_matching_list(p); // 호출하여 자릿수 세팅
	}
}

void print_queue(queue* que) {
	for (LINK p = que->front; p != NULL; p = p->next_rear) { // 큐 순회
		print_list_test(p); //리스트를 출력함 
	}
}
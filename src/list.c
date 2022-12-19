#include "list.h"

//각 함수별 용도 설명은 헤더파일에 있음

FC* head_insert(FC* head, char value) {
	head->data = value;
	head->cnt = 0;
	head->dot = -1;
	return head;
}

FC* insertVal(FC* pre, char value) {
	FC* p = (FC*)malloc(sizeof(FC));
	p->data = value;
	pre->next = p; //새로 다음 리스트 공간을 만들고 이어 붙임 
	return p; // 이어 붙인 리스트 공간을 반환함 
}

void digit_matching_list(FC* head) {
	int cnt = head->cnt;
	int dot = head->dot != -1 ? head->dot : cnt + 1; //점이 없을 경우 그냥 뒤집어주는 것이므로, cnt - (cnt - dot) - n이 cnt - 1 -  n이 되어 cnt, cnt -1, cnt -2 처럼 되게 함.
	int n = 1;
	for (FC* p = head; p != NULL; p = p->next) {
		p->digit = dot - n++; // 식은 cnt - (cnt - dot) - n이다. 예시를 들면 123.12의 cnt = 5, dot = 3이므로 1의 자릿수는 5 - (5 - 3) - 1 = 2이다. 그러므로 123.12의 수의 각각 자릿수는 2 1 0 -1 -1 -2이다.  
		if (p->data == '.') n--; //소수점 아래 첫번째 수가 자릿수가 -1이어야 하므로
	}
}

void print_list(FC* head)
{
	printf("[%d %d]   ", head->cnt, head->dot);
	for (FC* p = head; p != NULL; p = p->next)	{ //리스트 끝까지 출력함
		printf("%c[%d] -> ", p->data, p->digit);
	}
	printf("NULL \n");
}
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//FileContents는 입력 파일 값을 저장하는 연결리스트이다.
typedef struct FileContents {
	char data; //데이터
	int digit; //자릿수
	int cnt; //총 연결된 리스트 개수
	int dot; //점 위치 (-1일시 점은 없다는 뜻)

	struct FileContents* next; // 다음 값 위치를 저장 
	struct FileContents* prev; // 이전 값 위치를 저장

	struct FileContents* next_top; // 스택을 위해 자신이 팝되었을 때, 다음 탑 위치를 기억함 (ex) 스택가 [1,2,3]일때, 2가 1의 위치를 기억하고, 3이 2의 위치를 기억하는 거임 )
	struct FileContents* next_rear; // 큐를 위해 자신이 팝되었을 때, 다음 뒤의 위치를 기억함 (ex) 큐가 [1,2,3]일때, 1이 2의 위치를 기억하고, 2가 3의 위치를 기억하는 거임)
}FC;

//예를 들어 12345+3456가 들어온 경우
//1,+,3은 head_insert
//나머지는 insertVal로 이어서 받는다.

FC* head_insert(FC* head, char value); //기존 FC에 이어하는 것이 아니라 새로운 FC를 생성하고 값을 넣을 떄 사용함
FC* insertVal(FC* pre, char value); //기존 FC에 이어하는 경우에 사용함
void digit_matching_list(FC* head); //자릿수 매칭해주는 함수
void print_list(FC* head); //출력(테스트용)
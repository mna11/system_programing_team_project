#include "postfix.h"
#include <assert.h>
DATA priority(DATA data1, DATA data2) {
	DATA tmp1, tmp2;
	if ((data1 == '+') || (data1 == '-') || (data1 == '('))
		tmp1 = 1;
	else
		tmp1 = 2;
	if ((data2 == '+') || (data2 == '-') || (data2 == '('))
		tmp2 = 1;
	else
		tmp2 = 2;
	return tmp2 - tmp1;
	//tmp2 = 원래 스택의 탑, tmp1 = 새로 들어온 값
	//원래 스택의 탑의 우선순위가 더 큰 경우, 스택의 탑만 큐에 넣어줌
}

DATA isOperator(DATA op) {
	DATA res = 0;
	if (op == '+')
		res = op;
	else if (op == '-')
		res = op;
	else if (op == '*')
		res = op;
	else if (op == '/')
		res = op;
	else if (op == '(')
		res = op;
	else if (op == ')')
		res = op;
	else
		res = 0;
	return res; //res이 0이 아니면 연산자라는 뜻이다. 
}

queue* toPostFix() {
	FILE* fp = fopen("a.txt", "w");
	FILE* fp_r;
	stack* stk = (stack*)malloc(sizeof(stack)); //데이터를 읽고 일단 저장할 공간 
	queue* post = (queue*)malloc(sizeof(queue)); //postfix 순서대로 값을 저장할 공간 
	LINK header; // 헤더 부분임
	LINK cur;
	int parenthesis_check = 0;
	LINK popData; //스택의 탑을 팝한걸 저장할 공간
	DATA word, pre = '\0'; //word는 새로운 데이터, pre는 바로 이전 데이터
	initStack(stk); //초기설정
	initQueue(post); //초기설정

	while (scanf("%c", &word) == 1) {
		if (word == '(') parenthesis_check++;
		else if (word == ')') parenthesis_check--;
		fputc(word, fp);
	}
	fclose(fp);
	fp_r = fopen("a.txt", "r");

	/*
	while (1) {
		word 
	}*/

	while (1) { //데이터를 읽어와서 word에 저장함 
		word = fgetc(fp_r);
		if (feof(fp_r) != 0) {
			fclose(fp_r);
			break;
		}
		if (word == '\n' || isspace(word)) continue; //[예외처리] 공백과 줄넘김은 무시함 -> 123 456 이런 입력이 들어왔을시 123456의 수로 받아들이게 됨.
		if (isdigit(pre) && isdigit(word) || pre == '.') {
			if (pre == '.' && word == '.') continue;
			//이전 데이터가 숫자였고 이번 데이터도 숫자라면 연결리스트에 이어서 저장시킴 || 소수도 이어서 저장해야하므로 .도 체크해줌
			header->cnt++;
			cur = insert(cur, word);
		}
		else if (word == '.') {
			if (header->dot != -1) { //[예외처리] 점이 두번 이상 들어온 경우, 이후 들어온 점들은 없앰
				pre = word;
				continue;
			}
			else {
				header->dot = header->cnt + 1;
				cur = last_link(header);
			}
		}
		else {
			if (isOperator(word)) { // 만약 연산자라면 
				if (word == ')') { // 닫는 괄호가 입력될 경우

					if (parenthesis_check) parenthesis_check = 0; // [예외처리] 매칭되는 여는 괄호가 없는 경우, continue 시킴 
					else {
						pre = word;
						continue;
					}

					while (1) {
						popData = stack_pop(stk); //여는 괄호가 나올때까지 팝시킴
						if (popData->d == '(') {
							break;
						}
						else {
							queue_push(popData, post); //팝 시킨걸 큐에 넣음
						}
					}
				}
				else if (word == '(') { //여는 괄호가 입력될 경우
					parenthesis_check = 1;
					if (isdigit(pre)) { // [예외처리] 만약 10(10...) 이렇게 들어온 경우 10 * (10 ...)으로 판단함 
						word = '*';
						while (1) {
							if (stk->top == NULL) { // 스택이 비어있을 경우, 그냥 넣어줌
								header = char_to_list(word);
								stack_push(header, stk);
								break;
							}
							else { // 비어있지 않은 경우, top부분하고 우선순위 비교를 해야함
								popData = stack_pop(stk);
								if (priority(popData->d, word) == 1 || popData->d == '(') { //만약 word의 우선순위가 더 크거나, top부분이 (인 경우
									stack_push(popData, stk);
									header = char_to_list(word);
									stack_push(header, stk); // 둘다 스택에 다시 넣어주고 break
									break;
								}
								else {
									queue_push(popData, post); //아닌 경우는 큐에 top 부분을 넣어줌 
									//[-, +]인 경우 -를 그냥 넣어준다. 
									//while문 이므로 이후 [+]라면 +도 넣어줌 
								}
							}
						}
					}
					word = '(';
					header = char_to_list(word); //새로 넣어주고
					stack_push(header, stk); //스택에 푸시시킴
				}
				else { // 괄호 외의 연산자일 경우임 
					while (1) {
						if (stk->top == NULL) { // 스택이 비어있을 경우, 그냥 넣어줌
							header = char_to_list(word);
							stack_push(header, stk);
							break;
						}
						else { // 비어있지 않은 경우, top부분하고 우선순위 비교를 해야함
							popData = stack_pop(stk);
							if (priority(popData->d, word) == 1 || popData->d == '(') { //만약 word의 우선순위가 더 크거나, top부분이 (인 경우
								stack_push(popData, stk);
								header = char_to_list(word);
								stack_push(header, stk); // 둘다 스택에 다시 넣어주고 break
								break;
							}
							else {
								queue_push(popData, post); //아닌 경우는 큐에 top 부분을 넣어줌 
								//[-, +]인 경우 -를 그냥 넣어준다. 
								//while문 이므로 [+]라면 +도 넣어줌 
							}
						}
					}
				}
			}
			else { //연산자가 아니라 숫자인 경우
				header = char_to_list('+'); //새로 헤드를 만들고
				cur = insert(header, word);
				insert(cur, '.');
				header->cnt+=2;
				queue_push(header, post); //큐에 넣어줌 
			}
		}
		pre = word;
	}

	while (stk->top != NULL) { //스택을 비워준다.
		popData = stack_pop(stk);
		if (popData->d == '(') continue; // [예외처리] 만약 여는괄호가 스택에 남은 경우 -> 매칭되는 닫는 괄호가 안들어왔다는 뜻이므로 큐에 안넣어줌
		queue_push(popData, post);
	}

	free(stk);
	return post; // postfix를 반환해준다. 
}
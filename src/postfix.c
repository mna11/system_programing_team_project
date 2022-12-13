#include "postfix.h"

//각 함수별 용도 설명은 헤더파일에 있음

char priority(char data1, char data2) {
	char tmp1, tmp2;
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

char isOperator(char op) {
	char res = 0;
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
	stack* stk = (stack*)malloc(sizeof(stack)); //데이터를 읽고 일단 저장할 공간 
	queue* post = (queue*)malloc(sizeof(queue)); //postfix 순서대로 값을 저장할 공간 
	FC* cur; //현재 저장할 곳 (숫자 다음 숫자가 오는 경우, cur = insertVal(cur, 데이터)로 이어가고 
	//그 외에는 cur = head_insert(cur, 데이터)로 cur를 초기화해줌)
	//예를 들어보면 123+456일 경우, cur는 아래와 같이 변한다. 
	//1이 들어와 head를 만듬, 계속 숫자이므로 2, 3도 받아 cur->d = 1이고 cur = 1 -> 2 -> 3 -> NULL 인 연결리스트가 됨, 
	//+가 들어와 head를 만듬, cur->d = +이고 cur = + -> NULL 인 연결리스트가 됨.
	//4가 들어와 head를 만듬, 계속 숫자이므로 5, 6도 받아 cur->d = 4이고 cur = 4 -> 5 -> 6 -> NULL인 연결리스트가 됨. 

	FC* popData; //스택의 탑을 팝한걸 저장할 공간
	char word, pre = '\0'; //word는 새로운 데이터, pre는 바로 이전 데이터
	initStack(stk); //초기설정
	initQueue(post); //초기설정 

	while (scanf("%c", &word) == 1) { //데이터를 읽어와서 word에 저장함 
		if (word == '\n') continue; //줄넘김은 패스시킴
		if ((pre != '\0' && isdigit(pre) > 0) && isdigit(word) > 0 || word == '.' || pre == '.') {
			//이전 데이터가 숫자였고 이번 데이터도 숫자라면 연결리스트에 이어서 저장시킴 || 소수도 이어서 저장해야하므로 .도 체크해줌
			cur = insertVal(cur, word);
		}
		else {
			if (isOperator(word)) { // 만약 연산자라면 
				FC* tmp = (FC*)malloc(sizeof(FC));
				if (word == ')') { // 닫는 괄호가 입력될 경우
					while (1) {
						popData = stack_pop(stk); //여는 괄호가 나올때까지 팝시킴
						if (popData->data == '(') {
							break;
						}
						else {
							queue_push(popData, post); //팝 시킨걸 큐에 넣음
						}
					}
				}
				else if (word == '(') { //여는 괄호가 입력될 경우
					cur = head_insert(tmp, word); //새로 넣어주고
					stack_push(tmp, stk); //스택에 푸시시킴
				}
				else { // 괄호 외의 연산자일 경우임 
					while (1) {
						if (stk->top == NULL) { // 스택이 비어있을 경우, 그냥 넣어줌
							cur = head_insert(tmp, word);
							stack_push(tmp, stk);
							break;
						}
						else { // 비어있지 않은 경우, top부분하고 우선순위 비교를 해야함
							popData = stack_pop(stk);
							if (priority(popData->data, word) == 1 || popData->data == '(') { //만약 word의 우선순위가 더 크거나, top부분이 (인 경우
								stack_push(popData, stk);
								cur = head_insert(tmp, word);
								stack_push(tmp, stk); // 둘다 스택에 다시 넣어주고 break
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
				FC* tmp = (FC*)malloc(sizeof(FC));
				cur = head_insert(tmp, word); //새로 헤드를 만들고
				queue_push(tmp, post); //큐에 넣어줌 
			}
		}
		pre = word;
	}

	while (stk->top != NULL) { //스택을 비워준다.
		popData = stack_pop(stk);
		queue_push(popData, post);
	}

	return post; // postfix를 반환해준다. 
}
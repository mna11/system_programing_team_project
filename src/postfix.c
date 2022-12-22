#include "postfix.h"

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
	FILE* input = fopen("in", "w"); //입력을 받고 파일로 저장하는 담당
	FILE* input_reading; //in 파일을 읽어오는 담당
	FILE* writer_checking; //in 파일을 읽으면서 일부 수정하는 담당

	stack* stk = (stack*)malloc(sizeof(stack)); //postfix 변환을 위해 연산자를 잠시 저장하는 공간
	queue* post = (queue*)malloc(sizeof(queue)); //postfix 순서대로 값을 저장할 공간 
	LINK header; // 연결 리스트의 헤더 부분임
	LINK cur; // 현재 연결 리스트 위치 

	int parenthesis_check = 0; // 괄호 개수 체크, 0이면 짝이 맞음
	int is_not_math_expression = 0; // 1이면 숫자, 연산자 외의 입력이 들어왔다. 0이면 안들어왔다.
	int demical_point_check = 1; // 소수점 체크 (만약 2번 들어왔을 때, 1이라면 오류메세지를 띄워줌)
	int space_between_num = 0; // 1이면 숫자 사이에 빈 공간이 있다. 0이면 없다. ex) 123 456

	LINK popData; //스택의 탑을 팝한걸 저장할 공간
	DATA word, pre = '\0'; //word는 새로운 데이터, pre는 바로 이전 데이터

	initStack(stk); //초기설정
	initQueue(post); //초기설정

	while (scanf("%c", &word) == 1) { // 입력받아서 새로운 파일로 저장하는 과정, 괄호 체크랑 수식 체크를 진행함.
		putchar(word);
		if (word == '(') parenthesis_check++; 
		else if (word == ')') parenthesis_check--;
		else if (!isdigit(word) && !isOperator(word) && !isspace(word) && word != '\n' && word != '.') is_not_math_expression = 1;
		fputc(word, input);
	}
	fclose(input);

	input_reading = fopen("in", "r");
	writer_checking = fopen("real_input", "w");


	if (parenthesis_check) { // 각각의 상황에 맞게 에러메세지를 출력함.
		printf("\n[Invalid expression] The parentheses do not match.\n");
		printf("                     (Errors can occur during the process.)\n\n");
	}
	if (is_not_math_expression) {
		printf("\n[Invalid expression] Invalid value entered.\n");
		printf("                     (Errors can occur during the process.)\n\n");
	}

	while (1) { //수가 알맞지 않은 여는 괄호 제거, 수식 표현 이외의 다른 문자 제거, 수 사이의 공백이 있는지 체크를 진행함. 
		word = fgetc(input_reading);
		int check = parenthesis_check;

		if (feof(input_reading) != 0) {
			fclose(input_reading);
			fclose(writer_checking);
			break;
		}
		if (word == '(') {
			if (check > 0) {
				check--;
				continue;
			}
			fputc(word, writer_checking);
			pre = word;
		}
		else if (isdigit(word) || word == '\n' || word == '.' || word == ')') {
			fputc(word, writer_checking);
			pre = word;
		}
		else if (isOperator(word)) { // 닫는 괄호를 제외한 연산자일 경우.
			if (word == '/') {
				printf("\n[Invalid expression] This calculator does not support division.\n");
				printf("                     (Please correct the expression and try again.)\n\n");
				printf("Program exit\n");
				exit(1);
			}
			char tmp = fgetc(input_reading);
			while (isspace(tmp)) {
				tmp = fgetc(input_reading); //공백이 한두칸이 아닐 수도 있으니 공백이 끝날때까지 받아봄.
			} 
			if (tmp != '(' && isOperator(tmp)) { // * ( 와 같이 연산자 다음 (가 오는 경우는 정상적이므로 제외함
				printf("\n[Invalid expression] Invalid sign expression.\n");
				printf("                     (Please correct the expression and try again.)\n\n");
				printf("Program exit\n");
				exit(1);
			}
			fseek(input_reading, -1, SEEK_CUR); //파일 위치를 다시 돌려놓음.
			fputc(word, writer_checking);
			pre = word;
		}
		else if (isspace(word)) {
			char tmp = fgetc(input_reading);
			while (isspace(tmp)) {
				tmp = fgetc(input_reading); //공백이 한두칸이 아닐 수도 있으니 공백이 끝날때까지 받아봄.
			}
			if (!space_between_num && isdigit(pre) && isdigit(tmp)) { //예를 들어 123 456이 입력이 되면 에러메세지를 띄우고 123456으로 계산할 수 있도록 공백을 날림.
				space_between_num = 1;
			}
			else {
				fputc(word, writer_checking);
			}
			fseek(input_reading, -1, SEEK_CUR); //파일 위치를 다시 돌려놓음.
			pre = word;
		}
	}

	if (space_between_num) { // 상황에 맞는 에러메세지 출력함.
		printf("\n[Invalid expression] There is a space between the number and the number.\n");
		printf("                     (Errors can occur during the process.)\n\n");
	}

	pre = '\0';
	parenthesis_check = 0;
	input_reading = fopen("real_input", "r");

	while (1) { //데이터를 읽어와서 word에 저장함 
		word = fgetc(input_reading);
		if (feof(input_reading) != 0) {
			fclose(input_reading);
			break;
		}
		if (word == '\n' || isspace(word)) continue; //공백과 줄넘김은 무시함.

		if (isdigit(pre) && isdigit(word) || pre == '.') { //이전 데이터가 숫자였고 이번 데이터도 숫자라면 연결리스트에 이어서 저장시킴 || 소수도 저장해야하므로 .도 이어서 저장
			if (pre == '.' && word == '.') continue;
			header->cnt++;
			cur = insert(cur, word);
		}
		else if (word == '.') {
			if (header->dot != -1) { // 한 수에 점이 두번 이상 들어온 경우, 두번째 점부터는 날림.
				if (demical_point_check) { // 상황에 맞는 에러메세지 출력함.
					printf("\n[Invalid expression] A number has more than one decimal point.\n");
					printf("                     (Errors can occur during the process.)\n\n");
					demical_point_check = 0; // 한번만 띄워주기 위해 바꿈.
				}
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

					if (parenthesis_check) parenthesis_check = 0; // 만약 여는 괄호 전에 먼저 닫는 괄호가 온다면 날려줌. (여기서 parenthesis_check는 여는 괄호가 전에 나왔다면 1)
					else {
						pre = word;
						continue;
					}

					while (1) { //여는 괄호가 나올때까지 팝시킴
						popData = stack_pop(stk); 
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
					if (isdigit(pre)) { // 만약 10(10...) 이렇게 들어온 경우 10 * (10 ...)으로 판단함 
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
		if (popData->d == '(') continue; // ) ( 이런 경우를 대비해서 날려줌.
		queue_push(popData, post);
	}

	free(stk);
	return post; // postfix를 반환해준다. 
}
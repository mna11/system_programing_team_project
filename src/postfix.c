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
	//tmp2 = ���� ������ ž, tmp1 = ���� ���� ��
	//���� ������ ž�� �켱������ �� ū ���, ������ ž�� ť�� �־���
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
	return res; //res�� 0�� �ƴϸ� �����ڶ�� ���̴�. 
}

queue* toPostFix() {
	FILE* input = fopen("input", "w"); //�Է��� �ް� ���Ϸ� �����ϴ� ���
	FILE* input_reading; //input ������ �о���� ���
	FILE* writer_checking; //input ������ �����鼭 �Ϻ� �����ϴ� ���

	stack* stk = (stack*)malloc(sizeof(stack)); //postfix ��ȯ�� ���� �����ڸ� ��� �����ϴ� ����
	queue* post = (queue*)malloc(sizeof(queue)); //postfix ������� ���� ������ ���� 
	LINK header; // ���� ����Ʈ�� ��� �κ���
	LINK cur; // ���� ���� ����Ʈ ��ġ 

	int parenthesis_check = 0; // ��ȣ ���� üũ, 0�̸� ¦�� ����
	int is_not_math_expression = 0; // 1�̸� ����, ������ ���� �Է��� ���Դ�. 0�̸� �ȵ��Դ�.
	int demical_point_check = 1; // �Ҽ��� üũ (���� 2�� ������ ��, 1�̶�� �����޼����� �����)
	int space_between_num = 0; // 1�̸� ���� ���̿� �� ������ �ִ�. 0�̸� ����. ex) 123 456

	LINK popData; //������ ž�� ���Ѱ� ������ ����
	DATA word, pre = '\0'; //word�� ���ο� ������, pre�� �ٷ� ���� ������

	initStack(stk); //�ʱ⼳��
	initQueue(post); //�ʱ⼳��

	while (scanf("%c", &word) == 1) {
		putchar(word);
		if (word == '(') parenthesis_check++;
		else if (word == ')') parenthesis_check--;
		else if (!isdigit(word) && !isOperator(word) && !isspace(word) && word != '\n' && word != '.') is_not_math_expression = 1;

		fputc(word, input);
	}
	fclose(input);

	input_reading = fopen("input", "r");
	writer_checking = fopen("real_input", "w");

	if (parenthesis_check) {
		printf("\n[Invalid expression] The parentheses do not match.\n");
		printf("                     (Errors can occur during the process.)\n\n");
	}
	if (is_not_math_expression) {
		printf("\n[Invalid expression] Invalid value entered.\n");
		printf("                     (Errors can occur during the process.)\n\n");
	}

	while (1) {
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
		else if (isdigit(word) || isOperator(word) || word == '\n' || word == '.') {
			fputc(word, writer_checking);
			pre = word;
		}
		else if (isspace(word)) {
			char tmp = fgetc(input_reading);
			if (!space_between_num && isdigit(pre) && isdigit(tmp)) {
				space_between_num = 1;
			}
			else {
				fputc(word, writer_checking);
			}
			fseek(input_reading, -1, SEEK_CUR);
			pre = word;
		}
	}

	if (space_between_num) { //[����ó��] ���� ��� 123 456�� �Է��� �Ǹ� �����޼����� ���� 123456���� �����
		printf("\n[Invalid expression] There is a space between the number and the number.\n");
		printf("                     (Errors can occur during the process.)\n\n");
	}

	pre = '\0';
	input_reading = fopen("real_input", "r");

	while (1) { //�����͸� �о�ͼ� word�� ������ 
		word = fgetc(input_reading);
		if (feof(input_reading) != 0) {
			fclose(input_reading);
			break;
		}
		if (word == '\n' || isspace(word)) continue; //����� �ٳѱ��� ������

		if (isdigit(pre) && isdigit(word) || pre == '.') {
			if (pre == '.' && word == '.') continue;

			//���� �����Ͱ� ���ڿ��� �̹� �����͵� ���ڶ�� ���Ḯ��Ʈ�� �̾ �����Ŵ || �Ҽ��� �̾ �����ؾ��ϹǷ� .�� üũ����
			header->cnt++;
			cur = insert(cur, word);
		}
		else if (word == '.') {
			if (header->dot != -1) { //[����ó��] ���� �ι� �̻� ���� ���, ���� ���� ������ ����
				if (demical_point_check) { //[����ó��] �����޼����� �����
					printf("\n[Invalid expression] A number has more than one decimal point.\n");
					printf("                     (Errors can occur during the process.)\n\n");
					demical_point_check = 0;
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
			if (isOperator(word)) { // ���� �����ڶ�� 
				if (word == ')') { // �ݴ� ��ȣ�� �Էµ� ���

					if (!parenthesis_check) parenthesis_check = 0; // [����ó��] ��Ī�Ǵ� ���� ��ȣ�� ���� ���, continue ��Ŵ 
					else {
						pre = word;
						continue;
					}

					while (1) {
						popData = stack_pop(stk); //���� ��ȣ�� ���ö����� �˽�Ŵ
						if (popData->d == '(') {
							break;
						}
						else {
							queue_push(popData, post); //�� ��Ų�� ť�� ����
						}
					}
				}
				else if (word == '(') { //���� ��ȣ�� �Էµ� ���
					parenthesis_check = 1;
					if (isdigit(pre)) { // [����ó��] ���� 10(10...) �̷��� ���� ��� 10 * (10 ...)���� �Ǵ��� 
						word = '*';
						while (1) {
							if (stk->top == NULL) { // ������ ������� ���, �׳� �־���
								header = char_to_list(word);
								stack_push(header, stk);
								break;
							}
							else { // ������� ���� ���, top�κ��ϰ� �켱���� �񱳸� �ؾ���
								popData = stack_pop(stk);
								if (priority(popData->d, word) == 1 || popData->d == '(') { //���� word�� �켱������ �� ũ�ų�, top�κ��� (�� ���
									stack_push(popData, stk);
									header = char_to_list(word);
									stack_push(header, stk); // �Ѵ� ���ÿ� �ٽ� �־��ְ� break
									break;
								}
								else {
									queue_push(popData, post); //�ƴ� ���� ť�� top �κ��� �־��� 
									//[-, +]�� ��� -�� �׳� �־��ش�. 
									//while�� �̹Ƿ� ���� [+]��� +�� �־��� 
								}
							}
						}
					}
					word = '(';
					header = char_to_list(word); //���� �־��ְ�
					stack_push(header, stk); //���ÿ� Ǫ�ý�Ŵ
				}
				else { // ��ȣ ���� �������� ����� 
					while (1) {
						if (stk->top == NULL) { // ������ ������� ���, �׳� �־���
							header = char_to_list(word);
							stack_push(header, stk);
							break;
						}
						else { // ������� ���� ���, top�κ��ϰ� �켱���� �񱳸� �ؾ���
							popData = stack_pop(stk);
							if (priority(popData->d, word) == 1 || popData->d == '(') { //���� word�� �켱������ �� ũ�ų�, top�κ��� (�� ���
								stack_push(popData, stk);
								header = char_to_list(word);
								stack_push(header, stk); // �Ѵ� ���ÿ� �ٽ� �־��ְ� break
								break;
							}
							else {
								queue_push(popData, post); //�ƴ� ���� ť�� top �κ��� �־��� 
								//[-, +]�� ��� -�� �׳� �־��ش�. 
								//while�� �̹Ƿ� [+]��� +�� �־��� 
							}
						}
					}
				}
			}
			else { //�����ڰ� �ƴ϶� ������ ���
				header = char_to_list('+'); //���� ��带 �����
				cur = insert(header, word);
				insert(cur, '.');
				header->cnt+=2;
				queue_push(header, post); //ť�� �־��� 
			}
		}
		pre = word;
	}

	while (stk->top != NULL) { //������ ����ش�.
		popData = stack_pop(stk);
		queue_push(popData, post);
	}

	free(stk);
	return post; // postfix�� ��ȯ���ش�. 
}
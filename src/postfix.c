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
	FILE* fp = fopen("a.txt", "w");
	FILE* fp_r;
	stack* stk = (stack*)malloc(sizeof(stack)); //�����͸� �а� �ϴ� ������ ���� 
	queue* post = (queue*)malloc(sizeof(queue)); //postfix ������� ���� ������ ���� 
	LINK header; // ��� �κ���
	LINK cur;
	int parenthesis_check = 0;
	LINK popData; //������ ž�� ���Ѱ� ������ ����
	DATA word, pre = '\0'; //word�� ���ο� ������, pre�� �ٷ� ���� ������
	initStack(stk); //�ʱ⼳��
	initQueue(post); //�ʱ⼳��

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

	while (1) { //�����͸� �о�ͼ� word�� ������ 
		word = fgetc(fp_r);
		if (feof(fp_r) != 0) {
			fclose(fp_r);
			break;
		}
		if (word == '\n' || isspace(word)) continue; //[����ó��] ����� �ٳѱ��� ������ -> 123 456 �̷� �Է��� �������� 123456�� ���� �޾Ƶ��̰� ��.
		if (isdigit(pre) && isdigit(word) || pre == '.') {
			if (pre == '.' && word == '.') continue;
			//���� �����Ͱ� ���ڿ��� �̹� �����͵� ���ڶ�� ���Ḯ��Ʈ�� �̾ �����Ŵ || �Ҽ��� �̾ �����ؾ��ϹǷ� .�� üũ����
			header->cnt++;
			cur = insert(cur, word);
		}
		else if (word == '.') {
			if (header->dot != -1) { //[����ó��] ���� �ι� �̻� ���� ���, ���� ���� ������ ����
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

					if (parenthesis_check) parenthesis_check = 0; // [����ó��] ��Ī�Ǵ� ���� ��ȣ�� ���� ���, continue ��Ŵ 
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
		if (popData->d == '(') continue; // [����ó��] ���� ���°�ȣ�� ���ÿ� ���� ��� -> ��Ī�Ǵ� �ݴ� ��ȣ�� �ȵ��Դٴ� ���̹Ƿ� ť�� �ȳ־���
		queue_push(popData, post);
	}

	free(stk);
	return post; // postfix�� ��ȯ���ش�. 
}
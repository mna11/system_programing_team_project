#include "postfix.h"

int main(void) {
	queue* postfix = toPostFix(); //큐형태의 postfix가 만들어짐
	digit_matching(postfix); //자릿수 세팅함
	print_queue(postfix); //테스트용
	return 0;
}

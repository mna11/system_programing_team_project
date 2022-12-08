#include "postfix.h"

int main(void) {
	queue* postfix = toPostFix();
	print_queue(postfix);
	return 0;
}

#include "queue.h"

int queEmpty(queue* que) {
	return que->cnt == 0;
}

void queue_push(FC* d, queue* que) {
	if (queEmpty(que)) {
		que->front = d;
	}
	else {
		que->rear->next_rear = d;
	}
	que->rear = d;
	que->cnt++;
}

FC* queue_pop(queue* que) {
	if (queEmpty(que))
		return NULL;
	FC* tmp = que->front;
	que->front = tmp->next_rear;
	que->cnt--;
	return tmp;
}

void initQueue(queue* que) {
	que->front = que->rear = NULL;
	que->cnt = 0;
}

void print_queue(queue* que) {
	for (queue* p = que; que->front != NULL; p->front = p->front->next_rear) {
		print_list(p->front);
	}
}
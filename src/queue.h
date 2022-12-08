#pragma once
#include "list.h"

typedef struct Queue {
	int cnt;
	FC* front;
	FC* rear;
}queue;

int queEmpty(queue* que);
void queue_push(FC* d, queue* que);
FC* queue_pop(queue* que);
void initQueue(queue* que);
void print_queue(queue* que);
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct FileContents {
	char data;
	struct FileContents* next;
	struct FileContents* next_top;
	struct FileContents* next_rear;
}FC;

FC* head_insert(FC* head, char value);
FC* insertVal(FC* pre, char value);
void print_list(FC* head);
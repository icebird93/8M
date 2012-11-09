#include <stdlib.h>
#include <stdio.h>

#include "console.h"

int main(int argc, char *argv[])
{
	clear_screen();
	redraw_header();

	go_to(10,10);
	printf("X");

	getchar();
}
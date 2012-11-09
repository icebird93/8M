/**
 * control.c
 *
 * Das Library dass für die Behandlung des Spiels sorgt. (Zum Beispiel Menus)
 */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>

#include "console.h"
#include "control.h"

/**
 * menu
 * @Return: int
 * @Params: keine
 *
 * Zeigt den Benuter das Menu, und wartet auf einen Tastendruck [1-9] und rückgebt dieses Wert
 */
int menu()
{
	int selected;

	printf("\n [1] 21");

	set_color(BLACK, GREEN);
	printf("\n\n [H] Hall of Fame");

	set_color(BLACK, RED);
	printf("\n\n [9] Beenden");

	set_color(BLACK, WHITE);
	printf("\n\n # Gewaehlte Funktion: ");

	do
	{
		selected=getch();
	} while((selected<'1' || selected>'9') && tolower(selected)!='h');

	return selected-'0';
}
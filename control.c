/**
 * control.c
 *
 * Das Library dass für die Behandlung des Spiels sorgt. (Zum Beispiel Menus)
 */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <direct.h>
#include <string.h>

#include "console.h"
#include "control.h"

// Aktueller Verzeichnis
char *cwd;

/**
 * @function	menu
 * @result	int
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
	printf("\n\n [Q] Beenden");

	set_color(BLACK, WHITE);
	printf("\n\n # Gewaehlte Funktion: ");

	do
	{
		selected=read_key();
	} while((selected<'1' || selected>'9') && selected!='h' && selected!='q' && selected!=KEY_ESC);

	if(selected>='1' && selected<='9')
		return selected-'0';
	else
		return selected;
}

/**
 * @function	read_text_file
 * @result	int
 *
 * Liest ein File ein und gibt aus
 */
int read_text_file(char *filename)
{
	FILE *f;
	char *path;

	path=(char*)malloc((strlen(get_cwd())+strlen(filename)+1)*sizeof(char));
	sprintf(path, "%s/%s", get_cwd(), filename);

	f=fopen(path, "r");
	if(f)
	{
		rewind(f);
		while(!feof(f))
			printf("%c", fgetc(f));
		fclose(f);
	}
	printf("\n");

	return 0;
}

/**
 * @function	get_cwd
 * @result	char* (string)
 *
 * Gibt das aktuelle Verzeichnis zurück mit der Hilfe von getcwd in <direct>
 */
char* get_cwd()
{
	if(!cwd)
		cwd=getcwd(NULL, 0);
	return cwd;
}
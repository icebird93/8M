/**
 * control.c
 * @header	control.h
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
	printf("\n [2] 21 (Mehr Spieler Multi)");
	printf("\n [3] Catch Me");
	printf("\n [4] Guess");

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
 * @function	init_player
 *
 * Liest ein die Datei der Spieler
 */
void init_player()
{
	player_name=(char*)malloc(30*sizeof(char));
	printf("Willkommen in 8M!\nWaehlen Sie einen Name (fur die Bestenlisten): ");
	scanf("%s", player_name);
	if(player_name[29]!='\0')
		player_name[29]='\0';
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

	path=(char*)malloc((strlen(get_cwd())+strlen(filename)+2)*sizeof(char));
	sprintf(path, "%s/%s", get_cwd(), filename);

	if(DEBUG_MODE)
		printf("[%s]\n", path);

	f=fopen(path, "r");
	if(f)
	{
		rewind(f);
		while(!feof(f))
			printf("%c", fgetc(f));
		fclose(f);
	}
	else
	{
		if(DEBUG_MODE)
			printf("[%s] File Read Error\n", filename);
		return 0;
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
	static char *cwd;
	if(cwd==NULL)
		cwd=getcwd(NULL, 0);
	return cwd;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "highscore.h"
#include "console.h"
#include "control.h"

/*
 * @function highscore
 *
 * Liest ein, aktualisiert, schreibt aus (wenn nötig) und zeignet die Bestenliste auf dem Bildschirm an
 */
void highscore(char *filename, unsigned int score, int difficulty)
{
	item *hs;
	hs=read_highscore(filename);
	if(update_highscore(&hs, update_item(create_item(), player_name, score, difficulty)))
		write_highscore(filename, hs);
	display_highscore(filename, difficulty);
}

/*
 * @function display_highscore
 *
 * Schreibt in filename gespeicherte Bestenliste auf den Bildschirm aus
 */
void display_highscore(char *filename, int difficulty)
{
	int ch, rank;
	item *head, *p;

	set_color(BLACK, WHITE);
	printf("\n\n\n ###################");
	printf("\n ### Bestenliste ###");
	printf("\n ###################");

	/* Liste einlesen */
	head=read_highscore(filename);
	
	if(head==NULL)
	{
		set_color(BLACK, RED);
		printf("\n\n # Es gibt noch keine Eintraege in dieser Bestenliste");
		set_color(BLACK, WHITE);
		return;
	}

	/* Liste ausschreiben */
	set_color(BLACK, YELLOW);
	for(p=head, rank=0; p!=NULL && rank<=MAX_HIGHSCORE_ITEM; p=p->next)
		if(difficulty==0 || p->difficulty==difficulty)
		{
			rank++;
			printf("\n\n %d. %-32s\t%5d\t[%d]", rank, p->name, p->points, p->difficulty);
		}	
	set_color(BLACK, WHITE);
}

/*
 * @function update_highscore
 * @result	int
 *
 * Hinzufügt i (in die passende Position) wenn es in Top 10 ist
 */
int update_highscore(item **head, item *i)
{
	item *p, *p_next;

	if(*head==NULL)
	{
		*head=i;
		return 1;
	}

	if((*head)->points<=i->points)
	{
		i->next=*head;
		*head=i;
		return 1;
	}

	p=*head;
	while(p->next!=NULL && p->next->points>i->points)
		p=p->next;

	// i hinzufügen
	p_next=p->next;
	p->next=i;
	i->next=p_next;

	return 1;
}

/*
 * @function read_highscore
 * @result	item pointer
 *
 * Liest die Bestenliste (gespeichert in filename) in head (verkettete Liste)
 */
item* read_highscore(char *filename)
{
	int n, i;
	char *path;
	FILE *f;
	item *head=NULL, *p;
	
	path=(char*)malloc((strlen(get_cwd())+strlen(filename)+2)*sizeof(char));
	sprintf(path, "%s/%s", get_cwd(), filename);
	
	if(DEBUG_MODE)
		printf("[Read][%s]\n", path);

	f=fopen(path, "rb");
	if(f)
	{
		rewind(f);
		fread(&n, sizeof(int), 1, f);
		for(i=0; i<n; i++)
		{
			p=create_item();
			fread(p, sizeof(item), 1, f);
			p->next=NULL;
			add_item(&head, p);
		}
		fclose(f);
		return head;
	}
	else
	{
		if(DEBUG_MODE)
			printf("[%s] File Read Error\n", filename);
		return NULL;
	}
}

/*
 * @function write_highscore
 *
 * Schreibt die head (verkettete Liste) in Bestenliste (gespeichert in filename)
 */
void write_highscore(char *filename, item *head)
{
	int n;
	char *path;
	FILE *f;
	item *p;

	if(head==NULL)
		return;
	
	path=(char*)malloc((strlen(get_cwd())+strlen(filename)+2)*sizeof(char));
	sprintf(path, "%s/%s", get_cwd(), filename);

	if(DEBUG_MODE)
		printf("[Write][%s]\n", path);

	f=fopen(path, "wb");
	if(f)
	{
		n=count_items(head);
		fwrite(&n, sizeof(int), 1, f); 
		for(p=head; p!=NULL; p=p->next)
			fwrite(p, sizeof(item), 1, f); 
		fclose(f);
	}
	else
	{
		if(DEBUG_MODE)
			printf("[%s] File Write Error\n", filename);
		return;
	}
}

/*
 * @function clear_highscore
 *
 * Löscht die gewählte Bestenliste
 */
int clear_highscore(char *filename)
{
	char *path;
	path=(char*)malloc((strlen(get_cwd())+strlen(filename)+2)*sizeof(char));
	sprintf(path, "%s/%s", get_cwd(), filename);
	return remove(path);
}

/*
 * @function create_item
 * @return struct_highscore_item (item) pointer
 *
 * Ein neues Element entwerfen
 */
item* create_item()
{
	item *i;
	i=(item*)malloc(sizeof(item));
	if(i==NULL)
	{
		fputs("highscore.c (create_item): malloc() failure", stderr);
		if(DEBUG_MODE)
			printf("\n # [highscore.c] malloc() Fehler");
		exit(-1);
	}
	i->next=NULL;
	return i;
}

/*
 * @function add_item
 *
 * Ein neues Element zu der Liste hinzufügen (am Ende wird i gelegt)
 */
void add_item(item **head, item *i)
{
	item *p;

	if(*head==NULL)
	{
		*head=i;
		return;
	}

	for(p=*head; p->next!=NULL; p=p->next);
	p->next=i;
}

/*
 * @function update_item
 * @result	item pointer
 *
 * Das Element wird durch die Funktion aktuialisiert
 */
item* update_item(item *i, char *name, unsigned int points, int difficulty)
{
	// Eingang kontrollieren
	if(strlen(name)>30)
		name[31]='\0';

	strcpy(i->name, name);
	i->difficulty=difficulty;
	i->points=points;

	return i;
}

/*
 * @function remove_item
 *
 * Das Element wird gelöscht
 */
void remove_item(item **head, item **i)
{
	item *p;
	for(p=*head; p->next!=*i; p=p->next);
	p->next=(item*)(*i)->next;
	free(*i);
}

/*
 * @function count_items
 * @result	
 * 
 */
int count_items(item *head)
{
	int count;
	item *p;
	for(p=head, count=0; p!=NULL; p=p->next, count++);
	return count;
}
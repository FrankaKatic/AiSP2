/*2.	U datoteci studenti.txt nalaze se studenti i njihovi id-evi <id ime prezime>,
u datoteci kolokvij1.txt i kolokvij2.txt su spremljeni rezultati kolokvija <id rezultat> (format obe datoteke).
Potrebno je uèitati studente iz datoteke studenti.txt i spremiti ih u vezanu listu, a zatim iz druge i trece datoteke
uèitati rezultate kolokvija i spremiti ih u vezane liste. Potrebno je ispisati sve one studente koji su polozili i prvi
i drugi kolokvij (bodovi >50).
-----kolokvij1.txt <id><rezultat>
-----kolokvij2.txt <id><rezultat>
-----studenti.txt<id><ime><prezime>
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _studenti;
typedef struct _studenti studenti;
typedef studenti* position;

struct _kolokvij;
typedef struct _kolokvij kolokvij;
typedef kolokvij* pozicija;

struct _studenti {

	int id;
	char ime[20];
	char prezime[20];

	position next;
};

struct _kolokvij {

	int id;
	int rezultat;

	pozicija next;
};

int Citanjedatstudenti(position head);
int SpremanjeListeStudenti(position head, int id, char ime[20], char prezime[20]);
int CitanjeDatKolokvij(pozicija head, char filename[20]);
int Spremanjulistukolokvij(pozicija head, int id, int rezultat);
int CitanjeListeStudenti(position head_stud, pozicija head_kol1, pozicija head_kol2);
int Kolikojedobio(int id, pozicija head);


int main()
{
	studenti head_studenti;
	kolokvij head_k1;
	kolokvij head_k2;

	head_studenti.next = NULL;
	head_k1.next = NULL;
	head_k2.next = NULL;

	int result = 0;
	result = Citanjedatstudenti(&head_studenti);
	if (result == -1)
	{
		printf("nije uspija procitat");
		return -1;
	}

	result = CitanjeDatKolokvij(&head_k1, "kolokvij1.txt");
	result = CitanjeDatKolokvij(&head_k2, "kolokvij2.txt");

	printf("studenti koji su prosli su:\n");
	result = CitanjeListeStudenti(&head_studenti, &head_k1, &head_k2);


	return 0;
}

int Citanjedatstudenti(position head) {

	char buffer[1024] = "\0";
	int id = 0;
	char ime[20] = "\0";
	char prezime[20] = "\0";

	FILE* file;
	file = fopen("studenti.txt", "r");

	if (file == NULL)
	{
		printf("nije se otvorila prva");
		return -1;
	}

	while (!feof(file))
	{
		strcpy(buffer, "\0");
		id = 0;
		strcpy(ime, "\0");
		strcpy(prezime, "\0");

		fgets(buffer, 1024 - 1, file);
		if (strlen(buffer) > 1)
		{
			sscanf(buffer, " %d %s %s", &id, ime, prezime);
		}
		int result = SpremanjeListeStudenti(head, id, ime, prezime);
		if (result == -1)
		{
			printf("nije se spremilo");
			return -1;
		}

	}
	fclose(file); //NE ZABORAVI!!!

	return 0;
}

int SpremanjeListeStudenti(position head, int id, char ime[20], char prezime[20])
{
	position temp;
	temp = (position)malloc(sizeof(studenti));


	if (temp == NULL)
	{
		printf("nije se alociralo");
		return -1;
	}
	temp->id = id;
	strcpy(temp->ime, ime);
	strcpy(temp->prezime, prezime);


	while (head->next != NULL)
	{
		head = head->next;
	}

	temp->next = NULL;
	head->next = temp;

	return 0;
}

int CitanjeDatKolokvij(pozicija head, char filename[20])
{
	char buffer[1024] = "\0";
	int id = 0;
	int rezultat = 0;

	FILE* file;
	file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("nije se otvorila");
		return -1;

	}

	while (!feof(file))
	{
		strcpy(buffer, "\0");
		id = 0;
		rezultat = 0;

		fgets(buffer, 1024 - 1, file);
		if (strlen(buffer) > 1)
		{
			sscanf(buffer, "%d %d", &id, &rezultat);
		}
		int result = Spremanjulistukolokvij(head, id, rezultat);

		if (result == -1)
		{
		printf("nije se spremilo u listu kol");
		return -1;
		}
	}


	fclose(file);
	return 0;
}

int Spremanjulistukolokvij(pozicija head, int id, int rezultat)
{
	pozicija temp;
	temp = (pozicija)malloc(sizeof(kolokvij));

	if (temp == NULL)
	{
		printf("nije se alociralo");
		return -1;
	}
	temp->id = id;
	temp->rezultat = rezultat;
	
	while (head->next != NULL)
	{
		head = head->next;

	}
	temp->next = NULL;
	head->next = temp;

	return 0;
}

int CitanjeListeStudenti(position head_stud, pozicija head_kol1, pozicija head_kol2)
{
	if (head_stud->next == NULL)
	{
		printf("NULL");
	}
	else
	{
		head_stud = head_stud->next;
		
		while (head_stud != NULL)
		{
			int kol1 = Kolikojedobio(head_stud->id, head_kol1);
			int kol2 = Kolikojedobio(head_stud->id, head_kol2);

			if (kol1 >= 50 && kol2 >= 50)
				printf("\n%s %s\t %d", head_stud->ime, head_stud->prezime, (kol1 + kol2)/2);
			
			head_stud = head_stud->next;
		}
	}



	return 0;
}

int Kolikojedobio(int id, pozicija head)
{

	while (head != NULL)
	{
		if (id == head->id)
		{
			return head->rezultat;
		}
		head = head->next;
	}

	return 0;
}
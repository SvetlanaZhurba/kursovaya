#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 

#define number 10 //количество кабинетов константа
#define rec 24 //макс количество записей ко врачу на время приема(6 часов)
#define doc 50 //макс возможное количество врачей, 10 кабинетов по 5 рабочих дней



struct clinic //структура описания кабинета 1 день работы
{
	int f;//если данные заполнены, то 1, в противном случае 0
	int weekday;//день недели
	char name[25];//фамилия врача
	char doctor[25];//специализация врача
	int start;//начало приема
	int end;//конец приема (для простоты реализовано 6 часов приема)
	int n;//количество записанных человек
	//struct rec_time record;//структура записей на прием
};

struct office //структура кабинета по дням недели
{
	int number_room;//номер кабинета
	struct clinic medic[5];/*описание кабинета, 5 рабочих дней,
						   поэтому 5 описаний на каждый день*/
};

int i;
struct office spisok[number];


void add();
void dell();
void record_add(int, int, int);
void modification(int, int);
void out_ABC();
void out_load();
void output(struct clinic[], int);
void out_doctor_ABC();
void poisk_time_doctor();
int random();


int main()
{
	int j, a;
	FILE *file;

	file = fopen("clinik.txt", "r");
	for (i = 0; i<number; i++)
	{
		spisok[i].number_room = i + 1;
	}
	if (file != NULL)
	{
		for (i = 0; i<number; i++)
		{
			fscanf(file, "%i", &spisok[i].number_room);
			for (j = 0; j<5; j++)
			{
				fscanf(file, "%i", &spisok[i].medic[j].f);
				if (spisok[i].medic[j].f == 1)
				{
					fscanf(file, "%s%s%i%i", &spisok[i].medic[j].name, &spisok[i].medic[j].doctor,
						&spisok[i].medic[j].start, &spisok[i].medic[j].end);
						fscanf(file, "%i", &spisok[i].medic[j].n);

				}
			}
		}
	}
	fclose(file);

	do{

		printf("\n Viberite deistvie:\n\n\n");
		printf("1. Vvod/Izmenenie zapisi\n\n");
		printf("2. Udalenie zapisi\n\n");
		printf("3. Vivod zagruski kabineta\n\n");
		printf("4. Vivod doctorov\n\n");
		printf("5. Vivod spiska vrachey\n\n");
		printf("6. Poisk vrachey po spezialnosti\n\n");
		printf("7. Exit\n\n (1-7):");
		scanf("%d", &a);

		switch (a)
		{
		case 1: system("cls");
			add();
			break;
		case 2: system("cls");
			dell();
			break;
		case 3: system("cls");
			out_load();
			break;
		case 4: system("cls");
			printf("Doctora po alfavitu\n\n");
			out_ABC();
			break;
		case 5: system("cls");
			out_doctor_ABC();
			break;
		case 6: system("cls");
			poisk_time_doctor();
			break;
		case 7: system("cls");
			break;
		default: printf("\n\nERROR!!! Please enter number 1-7...\n\n");
		}
	} while (a != 7);

	file = fopen("clinik.txt", "w");
	for (i = 0; i<number; i++)
	{
		spisok[i].number_room = i + 1;
	}
	if (file != NULL)
	{
		for (i = 0; i<number; i++)
		{
			fprintf(file, "%i ", spisok[i].number_room);
			for (j = 0; j<5; j++)
			{
				fprintf(file, "%i ", spisok[i].medic[j].f);
				if (spisok[i].medic[j].f == 1)
				{
					fprintf(file, "%s %s %i %i ", spisok[i].medic[j].name, spisok[i].medic[j].doctor,
						spisok[i].medic[j].start, spisok[i].medic[j].end);
					fprintf(file, "%i ", spisok[i].medic[j].n);

				}
			}
			fprintf(file, "\n");
		}
	}
	fclose(file);

	return 0;
}

void add()
{
	int pr;
	int num;
	int day;

	do{
		printf("Vvedite nomer kabineta (1 - 10): ");
		scanf("%i", &num);
		num--;
	} while (num >= number);

	do{
		printf("Vvedite den' nedeli (1 - 5): ");
		scanf("%i", &day);
		day--;
	} while (day >= 5);

	if (spisok[num].medic[day].f == 1)
	{
		printf("Deistvitelno hotite ismenit' dannie?(1 - da, 0 - net)");
		scanf("%i", &pr);
		if (pr)
			modification(num, day);
	}
	else
		modification(num, day);
}



int load_add()
{
	srand(time(NULL));
	return rand() % 31;
}

void modification(int num, int day)
{
	system("cls");
	printf("Vvedite dannie\n\n");
	printf("familia doctora: ");
	scanf("%s", &spisok[num].medic[day].name);
	printf("doctor: ");
	scanf("%s", &spisok[num].medic[day].doctor);
	printf("nachalo priema: ");
	scanf("%i", &spisok[num].medic[day].start);
	spisok[num].medic[day].end = spisok[num].medic[day].start + 6;
	spisok[num].medic[day].f = 1;
	spisok[num].medic[day].weekday = day + 1;
	spisok[num].medic[day].n = load_add();


}

void dell()
{
	int num;
	int day;

	do{
		printf("Vvedite nomer kabineta (1 - 10): ");
		scanf("%i", &num);
		num--;
	} while (num >= number);

	do{
		printf("Vvedite den' nedeli (1 - 5): ");
		scanf("%i", &day);
		day--;
	} while (day >= 5);
	spisok[num].medic[day].f = 0;
	printf("\nZapis' udalena!\n");
}

void out_load()
{
	int num;
	printf("Zagruska kabineta\n\n");
	do{
		printf("Vvedite nomer kabineta (1 - 10): ");
		scanf("%i", &num);
		num--;
	} while (num >= number);

	for (i = 0; i<5; i++)
	{
		printf("\nDen' %i\n\n", i + 1);
		if (spisok[num].medic[i].f)
		{
			printf("\n kolichestvo zapusei - %i\n\n", spisok[num].medic[i].n);
			
		}
		else
		{
			printf("Kabinet ne rabotaet\n");
		}
	}
}

void output(struct clinic doctor[], int counter)
{
	for (i = 0; i<counter; i++)
	{
		if (strcmp(doctor[i].name, doctor[i + 1].name) != 0)
			printf("%s, %s\n", doctor[i].name, doctor[i].doctor);
	}
}

void out_ABC()
{
	int j, counter = 0;
	struct clinic doctor[doc];
	struct clinic temp;

	for (i = 0; i<number; i++)
		for (j = 0; j<5; j++)
			if (spisok[i].medic[j].f)
			{
				doctor[counter] = spisok[i].medic[j];
				counter++;
			}

	for (i = 0; i<counter - 1; i++)
		for (j = i + 1; j<counter; j++)
			if (strcmp(doctor[i].name, doctor[j].name) > 0)
			{
				temp = doctor[i];
				doctor[i] = doctor[j];
				doctor[j] = temp;
			}

	output(doctor, counter);
}

void out_doctor_ABC()
{
	char doct[25];
	int j, counter = 0;
	struct clinic doctor[doc];
	struct clinic temp;

	printf("Vvedite doctora: ");
	scanf("%s", &doct);

	for (i = 0; i<number; i++)
		for (j = 0; j<5; j++)
			if (spisok[i].medic[j].f == 1)
				if (strcmp(spisok[i].medic[j].doctor, doct) == 0)
				{
					doctor[counter] = spisok[i].medic[j];
					counter++;
				}

	for (i = 0; i<counter - 1; i++)
		for (j = i + 1; j<counter; j++)
			if (strcmp(doctor[i].name, doctor[j].name) > 0)
			{
				temp = doctor[i];
				doctor[i] = doctor[j];
				doctor[j] = temp;
			}

	output(doctor, counter);
}

void poisk_time_doctor()
{
	char doct[25];
	int time;
	int day, j;

	printf("Vvedite doctora: ");
	scanf("%s", &doct);
	printf("Vvedite den'(1-5): ");
	scanf("%i", &day);
	printf("Vvedite vremay: ");
	scanf("%i", &time);
	for (i = 0; i<number; i++)
		for (j = 0; j<5; j++)
			if (spisok[i].medic[j].f == 1)
				if ((strcmp(spisok[i].medic[j].doctor, doct) == 0) &&
					spisok[i].medic[j].weekday == day &&
					spisok[i].medic[j].start <= time &&
					spisok[i].medic[j].end > time)
				{
					printf("%s %s, %i:00 - %i:00", spisok[i].medic[j].doctor, spisok[i].medic[j].name,
						spisok[i].medic[j].start, spisok[i].medic[j].end);
				}
}

#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 

#define number 10 //количество кабинетов
#define rec 31 //максимальное количество записей в день
#define doc 50 //максимальное количество врачей

struct doctor //структура описания врача
{
	char name[30];
	char spec[30];
	int id;
};

struct clinic //сруктура описания кабинета на 1 день работы
{
	int f;
	int weekday; //день недели
	struct doctor medik; //описание врача
	int start;
	int end;
	int n; //количество записей на прием

};

struct office //структура описания работы кабинета за неделю
{
	int number_room; //номер кабинета
	struct clinic medic[5]; //описание работы кабинета на 5 дней
};

int i, count_doc = 0; //счетчик записей
struct office spisok[number]; //массив кабинетов
struct doctor medic_sp[doc]; //массив врачей


void add(); //заполнение данных для одного рабочего дня для одного кабинета
void dell(); //удаление данных одного рабочего дня кабинета
void modification(int, int); //выбор нужного врача по номеру
void out_ABC(); //сортировка и вывод фамилий враей по алфавиту
void out_load(); //вывод загрузки кабинета по дням недели
void out_doctor_ABC(); //вывод списка фамилий врачей по алфавиту по выбранной специальности
void poisk_time_doctor(); //поиск доктора по специальности и времени приема
void add_doctor(); //добавление нового доктора
void output(struct doctor); // вывод фамилии, специальности и id доктора
int random(); // для вывода загруженности кабинета


int main()
{
	int j, a = 0;
	FILE *file;
	file = fopen("clinik.txt", "a");
	fclose(file);
	
	file = fopen("clinik.txt", "r");
	for (i = 0; i<number; i++)
	{
		spisok[i].number_room = i + 1;
	}
	fseek(file, 0L, SEEK_SET);
	if (file != NULL)
	{
		for (i = 0; i<number; i++)
		{
			fscanf(file, "%i", &spisok[i].number_room);
			for (j = 0; j<5; j++)
			{
				spisok[i].medic[j].weekday = j + 1;
				fscanf(file, "%i", &spisok[i].medic[j].f);
				if (spisok[i].medic[j].f == 1)
				{
					fscanf(file, "%s%s%i%i%i", &spisok[i].medic[j].medik.name, &spisok[i].medic[j].medik.spec,
						&spisok[i].medic[j].medik.id, &spisok[i].medic[j].start, &spisok[i].medic[j].end);
					fscanf(file, "%i", &spisok[i].medic[j].n);

				}
			}
		}
	}
	fclose(file);

	file = fopen("doctor.txt", "a");
	fclose(file);
	file = fopen("doctor.txt", "r");
	if (file != NULL)
		for (i = 0; i<doc; i++)
		{
			if (!feof(file))
			{
				fscanf(file, "%s%s%i", &medic_sp[i].name, &medic_sp[i].spec, &medic_sp[i].id);
				count_doc++;
				if (medic_sp[i].id == 0)
					count_doc--;
			}
			else
				break;
		}
	//printf("\n\n%i\n\n", count_doc);
	fclose(file);

	do{
		if (count_doc == 0)
			printf("Vvedite doctorov!!!\n\n");
		printf("\n Viberite deistvie:\n\n\n");
		printf("1. Vvod/Izmenenie zapisi\n\n");
		printf("2. Udalenie zapisi\n\n");
		printf("3. Vivod zagruski kabineta\n\n");
		printf("4. Vivod doctorov\n\n");
		printf("5. Vivod spiska vrachey\n\n");
		printf("6. Poisk vrachey po spezialnosti\n\n");
		printf("7.Vvod novogo doctora\n\n");
		printf("8 Exit\n\n (1-8):");
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
			add_doctor();
			break;
		case 8: system("cls");
			break;
		default: printf("\n\nERROR!!! Please enter number 1-7...\n\n");
		}
	} while (a != 8);

	file = fopen("doctor.txt", "w");
	if (file != NULL)
	{
		for (i = 0; i<count_doc; i++)
		{
			fprintf(file, "%s %s %i", medic_sp[i].name, medic_sp[i].spec, medic_sp[i].id);
			if (i != count_doc - 1)
				fprintf(file, "\n");
		}
	}
	fclose(file);

	file = fopen("clinik.txt", "w");
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
					fprintf(file, "%s %s %i %i %i ", spisok[i].medic[j].medik.name, spisok[i].medic[j].medik.spec,
						spisok[i].medic[j].medik.id, spisok[i].medic[j].start, spisok[i].medic[j].end);
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
		if (num >= number || num < 0)
			printf("\n Vvedite nomer 1-10!!!\n\n");
	} while (num >= number || num < 0);

	do{
		printf("Vvedite den' nedeli (1 - 5): ");
		scanf("%i", &day);
		day--;
		if (day >= 5 || day < 0)
			printf("\n Vvedite den' 1-5!!!\n\n");
	} while (day >= 5 || day < 0);

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

void add_doctor()
{
	int Id = count_doc;
	int pr = 0;
	system("cls");
	printf("Vvedite imya: ");
	scanf("%s", &medic_sp[count_doc].name);
	printf("Vvedite special'nost': ");
	scanf("%s", &medic_sp[count_doc].spec);
	do{
		int pr = 0;
		for (i = 0; i < count_doc; i++)
			if ((Id + 1) == medic_sp[i].id)
			{
				pr = 1;
				Id += 1;
				break;
			}
		if (pr == 0)
			medic_sp[count_doc].id = (Id + 1);
	} while (pr);
	count_doc++;
}

void output(struct doctor medic_sp)
{
	{
		printf("%s ", medic_sp.name);
		printf("%s ", medic_sp.spec);
		printf("%i\n", medic_sp.id);
	}
}

int load_add()
{
	srand(time(NULL));
	return rand() % rec;
}

void modification(int num, int day)
{
	int n;
	printf("Vvedite dannie\n\n");
	for (i = 0; i < count_doc; i++)
		output(medic_sp[i]);
	printf("\n Vvedite nomer id: ");
	scanf("%i", &n);
	for (i = 0; i < count_doc; i++)
		if (n == medic_sp[i].id)
		{
			spisok[num].medic[day].medik = medic_sp[i];
			break;
		}
	printf("nachalo priema: ");
	scanf("%i", &spisok[num].medic[day].start);
	spisok[num].medic[day].end = spisok[num].medic[day].start + 6;
	spisok[num].medic[day].f = 1;
	spisok[num].medic[day].weekday = day + 1;
	spisok[num].medic[day].n = load_add();
}

void dell()
{
	int j;
	int num;
	int day;
	int pr = 0;
	for (i = 0; i<number; i++)
		for (j = 0; j<5; j++)
			if (spisok[i].medic[j].f)
			{
				pr = 1;
				break;
			}
	if (pr == 0)
	{
		printf("\n\nUdalyat' nechego!!!"); 
		return; 
	}
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


void out_ABC()
{
	int j, counter = 0;
	struct doctor temp;

	for (i = 0; i<count_doc - 1; i++)
		for (j = i + 1; j<count_doc; j++)
			if (strcmp(medic_sp[i].name, medic_sp[j].name) > 0)
			{
				temp = medic_sp[i];
				medic_sp[i] = medic_sp[j];
				medic_sp[j] = temp;
			}
	for (i = 0; i<count_doc; i++)
		output(medic_sp[i]);
}

void out_doctor_ABC()
{
	char doct[25];
	int j, counter = 0;
	struct doctor doctr[doc];
	struct doctor temp;

	printf("Vvedite doctora: ");
	scanf("%s", &doct);

	for (i = 0; i<doc; i++)
		if (strcmp(medic_sp[i].spec, doct) == 0)
		{
			doctr[counter] = medic_sp[i];
			counter++;
		}
	if (counter != 0 && counter != 1)
	{
		for (i = 0; i < counter - 1; i++)
			for (j = i + 1; j < counter; j++)
				if (strcmp(doctr[i].name, doctr[j].name) > 0)
				{
					temp = doctr[i];
					doctr[i] = doctr[j];
					doctr[j] = temp;
				}
	}
	if (counter != 0)
		for (i = 0; i < counter; i++)
			output(doctr[i]);


}

void poisk_time_doctor()
{
	char doct[30];
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
				if ((strcmp(spisok[i].medic[j].medik.spec, doct) == 0) &&
					spisok[i].medic[j].weekday == day &&
					spisok[i].medic[j].start <= time &&
					spisok[i].medic[j].end > time)
				{
					printf("%s %s, %i:00 - %i:00", spisok[i].medic[j].medik.name, spisok[i].medic[j].medik.spec,
						spisok[i].medic[j].start, spisok[i].medic[j].end);
				}
}

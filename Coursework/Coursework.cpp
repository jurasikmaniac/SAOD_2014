// Coursework.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "rusmenu.h"
#include "AVLtree.h"

FILE *fi;
//флаг сортировки
char checkIndex = 0;



int _tmain(int argc, _TCHAR* argv[])
{
	
	SetLoc(866);
	
	T_Queue queue;
	
	
	queue.head =queue.tail = NULL;
	while (true)
	{
		system("CLS");
		PrintMenu();
		switch (_getch())
		{
		case '1':	OpenBase(queue);	system("pause");break;
		//можно занять 1.5GB оперативной памяти!
		//case '1':	for (int i = 0; i < 1000; i ++ ){ OpenBase(queue); }system("pause"); break;
		case '2':	showQueue(queue);	system("pause");break;
		case '3':	sortMerge(queue);	system("pause");break;
		case '4':	Search();			system("pause");break;
		case '5':	freeQueue(queue);	return 0;		
		default:	break;
		}
	}
	freeQueue(queue);
	system("pause");
	return 0;
}
//Устанавливает кодировку ввода и вывода в консоли
inline void SetLoc(UINT loc)
{		
	SetConsoleCP(loc);
	SetConsoleOutputCP(loc);
}
//Выводит на консоль меню
inline void PrintMenu()
{
	puts("___________________________________");
	printf_s("%s\n", TextMenuId[0]);
	printf_s("%s\n", TextMenuId[1]);
	printf_s("%s\n", TextMenuId[2]);
	printf_s("%s\n", TextMenuId[3]);
	printf_s("%s\n", TextMenuId[4]);
	puts("___________________________________");
}
//Считывание базы данных в динамическую память
void OpenBase(T_Queue& b)
{
	readFilename();
	unitBase *p;
	p = (unitBase*)malloc(sizeof(unitBase));
	while (fread_s(p->fio, sizeof(p->fio), sizeof(p->fio), 1, fi))
	{
		p = (unitBase*)malloc(sizeof(unitBase));
		//fseek(fi, 1, SEEK_CUR);
		fread_s(&p->numUnit, sizeof(p->numUnit), sizeof(p->numUnit), 1, fi);
		//fseek(fi, 1, SEEK_CUR);
		fread_s(p->job, sizeof(p->job), sizeof(p->job), 1, fi);
		//fseek(fi, 1, SEEK_CUR);
		fread_s(p->dob, sizeof(p->dob), sizeof(p->dob), 1, fi);
		//fseek(fi, 2, SEEK_CUR);

		addToQueue(b, p);		
	}
	fclose(fi);	
	checkIndex = 0;
}



//добавления в очередь
void addToQueue(T_Queue &queue, unitBase *num)
{
	T_Data *p;
	p = (T_Data*)malloc(sizeof(T_Data));	// выделяем память

	p->next = NULL;							// присваеваем указателю на следующий элемент в списке значение NUL
	p->data = num;

	if (queue.head != NULL)					// если голова не пустая, то меняем значение следующего элемента в хвосте на новый элемент очереди
		queue.tail->next = p;
	else
		queue.head = p;
	queue.tail = p;							// присваеваем хвосту сзначение нового элемента очереди
}

//Безопасное открытие файла на чтение
void readFilename()
{
	errno_t err;
	char FileName[]= "testBase2.dat";
	err = fopen_s(&fi, FileName, "rb");
		if (err == 0)
		{
			//printf_s("The file ""%s"" was opened\n", FileName);
		}
		else
		{
			printf_s("The file ""%s"" was not opened, try again\n", FileName);
		}	
}
//отображения элементов базы
void showQueue(T_Queue &queue)
{
	T_Data *p;
	p = queue.head;
	UINT8 i=0;
	printf_s("\n%s\n", TextMenuId[5]);
	while (p != NULL) {
		printf_s("%s", p->data->fio);
		printf_s("%03d\t", p->data->numUnit);
		printf_s("%s\t", p->data->job);
		printf_s("%s\n", p->data->dob);
		p = p->next;
		i++;
		if (i==20)
		{
			puts("ESC for exit, anykey for continue");
			if(_getch()==27)return;
			i=0;
		} 
	}
	printf("\n");
}
//освобождения памяти из под списка
void freeQueue(T_Queue &queue)
{
	T_Data *p, *temp;
	p = queue.head;

	while (p != NULL) {
		temp = p;
		p = p->next;
		free(temp);
	}
	queue.head = queue.tail = NULL;
}
//объединения списков
void merge(T_Queue &queue_a, int q, T_Queue &queue_b, int r, T_Queue &queue_c)
{
	T_Data *a, *b;

	a = queue_a.head;
	b = queue_b.head;
	//DO (q ≠ 0 и r ≠ 0)
	//	IF (a → Data ≤ b → Data)
	//		<Переместить элемент из списка a в очередь c>
	//		q:=q-1
	//	ELSE
	//		<Переместить элемент из списка b в очередь c>
	//		r:=r-1
	//	FI
	//OD
	//DO (q > 0)
	//	<переместить элемент из списка a в очередь c>
	//	q:=q-1
	//OD
	//DO (r > 0)
	//	<Переместить элемент из списка b в очередь c>
	//	r:=r-1
	//OD

	while ((q != 0) && (r != 0)) {				// DO (q ≠ 0 и r ≠ 0)				
		if (LessDayAndFio(a->data, b->data)) {				// IF (a → Data ≤ b → Data)
			if (queue_c.head != NULL)			// <Переместить элемент из списка a в очередь c>
				queue_c.tail->next = a;
			else
				queue_c.head = a;
			queue_c.tail = a;

			a = a->next;		

			q--;								// q:=q-1
		}
		else {									// ELSE
			if (queue_c.head != NULL)			// <Переместить элемент из списка b в очередь c>
				queue_c.tail->next = b;
			else
				queue_c.head = b;
			queue_c.tail = b;

			b = b->next;
			r--;								// r:=r-1
		}
	}
	
	while (q > 0) {								// DO (q > 0)
		if (queue_c.head != NULL)				// <переместить элемент из списка a в очередь c>
			queue_c.tail->next = a;
		else
			queue_c.head = a;
		queue_c.tail = a;
		a = a->next;

		q--;									// q:=q-1
	}
	while (r > 0) {								// DO (r > 0)
		if (queue_c.head != NULL)				// <Переместить элемент из списка b в очередь c>
			queue_c.tail->next = b;
		else
			queue_c.head = b;
		queue_c.tail = b;
		b = b->next;

		r--;									// r:=r-1
	}

	queue_a.head = a;
	queue_b.head = b;
}

//разделения списка
void split(T_Queue &queue, T_Queue &queue_a, T_Queue &queue_b, int &n)
{
	T_Data *k, *p;

	n = 1;
	queue_a.head = queue.head;
	queue_b.head = queue.head->next;

	k = queue_a.head;
	p = queue_b.head;

	while (p != NULL) {
		k->next = p->next;
		k = p;
		p = p->next;
		n++;		
	}
}

//Сортировка базы методом прямого включения
void sortMerge(T_Queue &queue)
{
	if (queue.head==NULL)
	{
		return;
	}
	T_Queue queue_a, queue_b, queue_c[2];

	int n, p, m,
		i, r, q;
	//  Обозначим		n – количество элементов в S
	//	queue_a, queue_b – рабочие списки
	//	queue_c=(c0, c1) – массив из двух очередей
	//	p – предполагаемый размер серии
	//	q – фактический размер серии в списке a
	//	r – фактический размер серии в списке b 
	//	m – текущее количество элементов в списках a и b
	//	i – номер активной очереди 
	
	queue_a.head = queue_a.tail =
		queue_b.head = queue_b.tail = NULL;

	split(queue, queue_a, queue_b, n);

	p = 1;
	while (p < n) {

		queue_c[0].head = queue_c[0].tail =
			queue_c[1].head = queue_c[1].tail = NULL;

		i = 0; m = n;
		while (m > 0) {
			if (m >= p) q = p;
			else q = m;
			m = m - q;

			if (m >= p) r = p;
			else r = m;
			m = m - r;

			merge(queue_a, q, queue_b, r, queue_c[i]);
			i = 1 - i;
		}

		queue_a.head = queue_c[0].head;
		queue_b.head = queue_c[1].head;
		p *= 2;

	}

	queue_c[0].tail->next = NULL;
	queue.head = queue_c[0].head;
	
	T_Data *temp;
	int day=0;
	temp = queue.head;
	for (size_t i = 0; i < 31; i++)
	{
		index[i] = NULL;
	}
	while (temp != NULL) {
		day = (temp->data->dob[0] - 48) * 10 + (temp->data->dob[1] - 48) - 1;
		if (index[day] == NULL)
		{
			index[day] = temp;
		}
		temp = temp->next;
		
	}
	checkIndex = 1;
}

//Сравнение(Лексикографическое) строк
//1 если s1<s2, 2 если S1=S2, 0 если S1>S2
int Compare(char s1[], char s2[], int number)

{
	int i;
	i = 0;
	do
	{
		if (s1[i]<s2[i]) return 1;
		else if (s1[i]>s2[i]) return 0;
		else i++;
	} while (i<number);
	return 2;
}
//Сравнение даты рождения  1 если < 2 если =, 0 если >
int CompareDate(char *s1, char *s2)
{
	char ss1[2], ss2[2];
	int result;
	ss1[0] = s1[6]; ss1[1] = s1[7];
	ss2[0] = s2[6]; ss2[1] = s2[7];
	result = Compare(ss1, ss2, 2);
	if (result == 1)
	{
		return 1;
	}
	if (result == 0)
	{
		return 0;
	}
	ss1[0] = s1[3]; ss1[1] = s1[4];
	ss2[0] = s2[3]; ss2[1] = s2[4];
	result = Compare(ss1, ss2, 2);
	if (result == 1)
	{
		return 1;
	}
	if (result == 0)
	{
		return 0;
	}
	ss1[0] = s1[0]; ss1[1] = s1[1];
	ss2[0] = s2[0]; ss2[1] = s2[1];
	result = Compare(ss1, ss2, 2);
	if (result == 1)
	{
		return 1;
	}
	if (result == 0)
	{
		return 0;
	}
	return 2;
}
//сравнение дня рождения+ФИО
int LessDayAndFio(unitBase *p, unitBase *q)
{
	 
	if (p->dob[0]<q->dob[0]) return 1;
	else if (p->dob[0]>q->dob[0]) return 0;
	else if (p->dob[1]<q->dob[1]) return 1;
	else if (p->dob[1]>q->dob[1]) return 0;
	else if (Compare(p->fio, q->fio, 30)) return 1;
	else return 0;
}
//поиск по ключу в отсортированной базе, затем постороение дерева и поиск в нём
void Search()

{
	//Если база неотсортирована, то выходим
	if (!checkIndex)
	{
		puts("Sort base");
		return;
	}
	int Key = 0;
	//Считываем дату рождения
	while (true)
	{
		puts(TextMenuId[6]);
		scanf_s("%d",&Key);
		if (Key <= 31 && Key >= 1 && index[Key-1] != NULL)
		{
			break;
		}
	}
	Key--;
	T_Data *temp;
	T_Queue Found;
	node *root=NULL;
	Found.head = Found.tail = NULL;
	temp = index[Key];
	
	//Формируем очередь из найденых элементов в базе
	while (temp!=NULL)
	{
		
		if ((temp->data->dob[0] - 48) * 10 + (temp->data->dob[1] - 48) - 1 != Key)
		{
			temp = NULL;
			break;
		}		
		addToQueue(Found, temp->data);
		temp = temp->next;		
	}
	temp = Found.head;
	count = 0;
	//Выводим на печать содержимое очереди и заполняем дерево
	while (temp != NULL)
	{		
		printf_s("%s ", temp->data->fio);
		printf_s("%03d\t", temp->data->numUnit);
		printf_s("%s\t", temp->data->job);
		printf_s("%s\n", temp->data->dob);	
		root = insert(root, temp->data);
		temp = temp->next;
		count++;
	}
	printf_s("added  lists:%u\n", count);
	char date[10];
	//showwtree(root);

	puts(TextMenuId[7]);
	fflush(stdin);
	scanf_s("%s", date, _countof(date));
	find(root, date);
	count = 0;
	//Очищаем очередь после окончания поиска
	freeQueue(Found);
	////Очищаем дерево после окончания поиска
	freetree(root);
	root = NULL;
	printf_s("deleted lists:%u\n",count);	
}
// tree.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "stdtree.cpp"
node* root1 = NULL;

int _tmain(int argc, _TCHAR* argv[])
{
	SetLoc(1251);
	node* root = NULL;
	nodeAVL* rootAVL = NULL;
	
	int arr[10000], n,key, comp = 0;
	while (true)
	{

		puts("1 лаба");
		puts("2 лаба");
		puts("3 лаба");
		puts("4 лаба");
		puts("0 выход");
		
		switch (_getch())
		{

		case '1':			/*	Лабараторная работа №1
			2
		       / \
		      1  3
		          \
		          5
			 / \
			4   6

						*/

			root = insert(root, 2);
			root = insert(root, 1);
			root = insert(root, 3);
			root = insert(root, 5);
			root = insert(root, 4);
			root = insert(root, 6);
			
			/*root = insertRTS(root, 2);
			root = insertRTS(root, 1);
			root = insertRTS(root, 3);
			root = insertRTS(root, 5);
			root = insertRTS(root, 4);
			root = insertRTS(root, 6);*/
			show(root);
			//root = _del(root, 5);
			roundLToR(root);
			freetree(root);
			root = NULL;
				
			
			system("pause");
			break;
		case '2':
			/*
			Лабораторная работа №2
			*/
			srand(time(NULL));
			//СДП
			puts("Введите число вершин СДП");
			n = 0;
			scanf_s("%d", &n);
			gen_random_uniq(n, arr, 1, n);
			for (int i = 0; i < n; i++)
			{
				root = insert(root, arr[i]);
			}
			show(root);
			puts("введите ключ:");
			scanf_s("%d", &key);
			search(root, key, comp);
			printf_s("\nколичество сравнений: %d\n", comp);
			comp = 0;
			//roundLToR(root);
			freetree(root);
			root = NULL;
			//ИСДП
			puts("Введите число вершин ИСДП");
			n = 0;
			scanf_s("%d", &n);
			gen_random_uniq(n, arr, 1, n);
			qs(arr, 0, n - 1);
			root = IBTS(arr, 0, n - 1);
			show(root);
			puts("введите ключ:");
			scanf_s("%d", &key);
			search(root, key, comp);
			printf_s("\nколичество сравнений: %d\n", comp);
			comp = 0;
			freetree(root);
			root = NULL;
			system("pause");
			break;
			/*
			Лабораторная работа №3
			*/
		case '3':
			srand(time(NULL));
			//AVL
			puts("Введите число вершин AVL");
			n = 0;
			scanf_s("%d", &n);
			gen_random_uniq(n, arr, 1, n);
			for (int i = 0; i < n; i++)
			{
				insertAVL(&root1, arr[i]);
			}
			show(root1);
			printf_s("\nСреднее количество поворотов %6.3f\n", (float)R / n);
			
			freetree(root1);
			root1 = NULL;
			system("pause");
			break;
		case '4':
			srand(time(NULL));
			//AVL
			puts("Введите число вершин ДБ-дерева");
			n = 0;
			scanf_s("%d", &n);
			gen_random_uniq(n, arr, 1, n);
			for (int i = 0; i < n; i++)
			{
				insertBB(&root1, arr[i]);
			}
			show(root1);
			freetree(root1);
			root1 = NULL;
			system("pause");
			break;
		case '0': return 0;
		default:
			break;
		}
	}
	system("pause");

	
	return 0;
}

// tree.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "stdtree.cpp"

int _tmain(int argc, _TCHAR* argv[])
{
	SetLoc(1251);
	node* root = NULL;
	bool b;
	int arr[9] = {0,2,1,3,5,4,6,7,8};
/*	Лабараторная работа №1
			2
		   / \
		  1   3
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
	printf_s("Size tree = %d\n", sizetree(root));
	printf_s("H tree = %d\n", heighttree(root));
	printf_s("mean H tree = %6.3f\n", meanheight(root));
	printf_s("CRC tree = %d\n", CRCtree(root));
	b = checksearch(root);
	printf_s("search tree ? %c\n", b? 'Y':'N');
	roundLToR(root);
	search(root, 2);
	root = _del(root, 5);
	b = checksearch(root);
	printf_s("search tree ? %c\n", b ? 'Y' : 'N');
	printf_s("CRC tree = %d\n", CRCtree(root));
	roundLToR(root);
	root = _del(root, 3);
	b = checksearch(root);
	printf_s("search tree ? %c\n", b ? 'Y' : 'N');
	printf_s("CRC tree = %d\n", CRCtree(root));
	roundLToR(root);
	qs(arr, 0, 8);
	node *ibts = IBTS(arr, 0, 8);
	roundLToR(ibts);
	system("pause");
	freetree(root);
	freetree(ibts);
	return 0;
}

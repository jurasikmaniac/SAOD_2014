// tree.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "stdtree.cpp"

int _tmain(int argc, _TCHAR* argv[])
{
	SetLoc(1251);
	node* root = NULL;
	bool b;
	root = insert(root, 15);
	root = insert(root, 20);
	root = insert(root, 10);
	root = insert(root, 50);
	root = insert(root, 60);
	root = insert(root, 30);
	root = insert(root, 80);
	root = insert(root, 100);
	printf_s("Size tree = %d\n", sizetree(root));
	printf_s("H tree = %d\n", heighttree(root));
	printf_s("mean H tree = %6.3f\n", meanheight(root));
	printf_s("CRC tree = %d\n", CRCtree(root));
	b = checksearch(root);
	printf_s("search tree = %d\n", b? 1:0);
	roundLToR(root);
	roundDown(root);
	roundUP(root);
	system("pause");
	freetree(root);
	return 0;
}

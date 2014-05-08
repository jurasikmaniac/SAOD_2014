//Кодировка
inline void SetLoc(UINT loc)
{
	SetConsoleCP(loc);
	SetConsoleOutputCP(loc);
}
//Вставка в дерево
node* insert(node* p, INT32 k)
{
	if (!p) return new node(k);
	if (k < p->Data)
		p->left = insert(p->left, k);
	else
		p->right = insert(p->right, k);
	return p;
}

//Обход слева направо(p: pVertex)
//IF(p ≠ NIL)
//Обход слева направо(p→Left)
//Печать(p→Data)
//Обход слева направо(p→Right)
//FI
void roundLToR(node* p)
{
	if (p)
	{
		roundLToR(p->left);
		printf_s("\nData = %d\n", p->Data);
		roundLToR(p->right);
	}
}
void roundDown(node* p)
{
	if (p)
	{
		printf_s("\nData = %d\n", p->Data);
		roundLToR(p->left);		
		roundLToR(p->right);
	}
}
void roundUP(node* p)
{
	if (p)
	{
		roundLToR(p->left);
		roundLToR(p->right);
		printf_s("\nData = %d\n", p->Data);
	}
}
//Удалить дерево
void freetree(node* tree)
{
	if (tree)
	{
		freetree(tree->right);
		freetree(tree->left);
		delete tree;
		tree = NULL;
	}

}
//Размер дерева
INT32 sizetree(node* p)
{
	if (p == NULL)
	{
		return 0;
	}
	else
	{
		return 1 + sizetree(p->left) + sizetree(p->right);
	}
}
//Высота дерева
INT32 heighttree(node* p)
{
	if (p == NULL)
	{
		return 0;
	}
	else
	{
		return  1 + max(heighttree(p->left), heighttree(p->right));
	}
}
//Сумма длин путей
INT32 slp(node* p, INT32 l)
{
	if (!p)
	{
		return 0;
	}
	else
	{
		return l + slp(p->left, l++) + slp(p->right, l++);
	}
}
//Средняя высота
inline float meanheight(node* p)
{
	return (float)slp(p, 1) / sizetree(p);
}
//Контрольная сумма
INT32 CRCtree(node* p)
{
	if (!p)
	{
		return 0;
	}
	else
	{
		return p->Data + CRCtree(p->left) + CRCtree(p->right);
	}
}
//проверка на дерево поиска
bool checksearch(node* p)
{	
	if (p)
	{
		if (p->left)
		{
			if (p->Data <= p->left->Data)
			{
				return false;
			}
			if (!checksearch(p->left))
			{
				return false;
			}
		}
		if (p->right)
		{
			if (p->Data >= p->right->Data)
			{
				return false;
			}
			if (!checksearch(p->right))
			{
				return false;
			}
		}
	}
	return true;
}

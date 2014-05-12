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
	if (p->Data == k)
	{
		printf_s("данные с ключом %d уже есть", k);
		return p;
	}
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
		return l + slp(p->left, l + 1) + slp(p->right, l + 1);
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


//поиск вершины с ключом Х
node* search(node *p, INT32 X)
{
	if (p)
	{
		if (p->Data < X)
		{
			search(p->right, X);
		}
		else
		{
			if (p->Data > X)
			{
				search(p->left, X);
			}
			else
			{
				puts("вершина найдена");
				return p;
			}
		}
	}
	else
	{
		puts("вершина не найдена");
		return p;
	}	
}
//обмен двух переменных
void swap(int &a, int &b)
{
	int c = a;
	a = b;
	b = c;
}

//Сортировка массива
void qs(int* s_arr, int first, int last)
{
	int i = first, j = last, x = s_arr[(first + last) / 2];

	do {
		while (s_arr[i] < x) i++;
		while (s_arr[j] > x) j--;

		if (i <= j) {
			if (i < j) swap(s_arr[i], s_arr[j]);
			i++;
			j--;
		}
	} while (i <= j);

	if (i < last)
		qs(s_arr, i, last);
	if (first < j)
		qs(s_arr, first, j);
}
//Построение ИСДП
node* IBTS(int* s_arr, INT32 L, INT32 R)
{
	if (L > R)
	{
		return NULL;
	}
	//INT32 m = (float)(L + R) / 2 + 0.5;
	INT32 m = (L + R) / 2;
	node *p = new node(s_arr[m]);
	p->left = IBTS(s_arr, L, m - 1);
	p->right = IBTS(s_arr, m + 1, R);
	return p;
}

//удаление вершины методичка, не работает
void del(node *root, INT32 X)
{
	node *s = NULL;
	node *r = NULL;
	node *q = NULL;
	node **p = &root;
	while (*p != NULL)
	{
		if ((*p)->Data < X) p = &((*p)->right);
		else if ((*p)->Data > X) p = &((*p)->left);	
		else break;
	}
	if (p != NULL)
	{
		q = *p;
		if (q->left == NULL) *p = q->right;
		else if (q->right == NULL) *p = q->left;
		else { r = q->left; s = q; }
		if (r)
		{
			while (r->right != NULL)
			{
				s = r;
				r = r->right;
			}

			s->right = r->left;
			r->left = q->left;
			r->right = q->right;
			*p = r;

		}
	}
	delete q;
	
}

node *_del(node *root, INT32 key)
{
	node *p = NULL;
	node *p2 = NULL;

	if (!root) return root; /* вершина не найдена */

	if (root->Data == key) { /* удаление корня */
		/* это означает пустое дерево */
		if (root->left == root->right){
			free(root);
			return NULL;
		}
		/* или если одно из поддеревьев пустое */
		else if (root->left == NULL) {
			p = root->right;
			free(root);
			return p;
		}
		else if (root->right == NULL) {
			p = root->left;
			free(root);
			return p;
		}
		/* или есть оба поддерева */
		else {
			p2 = root->right;
			p = root->right;
			while (p->left) p = p->left;
			p->left = root->left;
			free(root);
			return p2;
		}
	}
	if (root->Data < key) root->right = _del(root->right, key);
	else root->left = _del(root->left, key);
	return root;
}

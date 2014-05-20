//Кодировка
inline void SetLoc(UINT loc)
{
	SetConsoleCP(loc);
	SetConsoleOutputCP(loc);
}
//Вставка в дерево поиска, рекурсивная
node* insert(node* p, INT32 k)
{
	if (!p) return new node(k);
	if (p->Data == k)
	{
		printf_s("\nданные с ключом %d уже есть\n", k);
		return p;
	}
	if (k < p->Data)
		p->left = insert(p->left, k);
	else
		p->right = insert(p->right, k);
	return p;
}
//Вставка в дерево, алгоритм методички, немного доведенный до рабочего, после завершения функции все указатели обнулялись,ВСЕ!
//Возможно это сработает и с удалением
node* insertRTS(node *root, INT32 D)
{
	node **p = &root;//указатель на указатель
	while (*p != NULL)
	{
		if (D < (*p)->Data) p = &((*p)->left);//меньше, идем налево
		else if (D > (*p)->Data) p = &((*p)->right);//больше идем направо
		else
		{
			printf_s("\nданные с ключом %d уже есть\n", D);//иначе D уже есть
			return root;
		}
	}
	if (*p == NULL)
	{
		*p = new node(D);
		(*p)->left = NULL;
		(*p)->right = NULL;
	}
	return root;
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
//Высота дерева, нуууу очень долго считает при n>1000
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
node* search(node *p, INT32 X,INT32 &comp)
{
	if (p)
	{
		comp++;
		if (p->Data < X)
		{
			
			search(p->right, X, comp);
		}
		else
		{
			comp++;
			if (p->Data > X)
			{
				
				search(p->left, X, comp);
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
//переделал, всё арвно не заработало
node* del(node *root, INT32 X)
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
	return root;
	
}
//удаление вершины
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


//уникакальное случайное число
void gen_random_uniq(int arr_size, int *parr, int range_min, int range_max) {

	int i, j;
	int dup_flag;
	int rand_val, range_width = range_max - range_min + 1;


	if (range_width<1 || arr_size<0 || arr_size>range_width) {
		fprintf(stderr, "gen_random_uniq(): Invalid arguments\n"); exit(1);
	}

	for (i = 0; i<arr_size; i++) {
		for (;;) {
			rand_val = range_min + rand() % range_width;
			dup_flag = 0;
			for (j = 0; j<i; j++) {
				if (rand_val == parr[j]) { dup_flag = 1; break; }
			}
			if (!dup_flag) { break; }
		}
		parr[i] = rand_val;
	}

} /* gen_random_uniq() */

//информация по древву
inline void show(node* root)
{	
	printf_s("Размер дерева = %d\n", sizetree(root));
	printf_s("сумма длин = %d\n", slp(root, 1));
	printf_s("высота дерева = %d\n", heighttree(root));
	printf_s("средняя высота = %6.3f\n", meanheight(root));
	printf_s("CRC tree = %d\n", CRCtree(root));
	printf_s("Дерево поиска? %c\n", checksearch(root) ? 'Y' : 'N');
}



/* LL поворот
q = p→Left;
q→Balance = 0;
p→Balance = 0;
p→Left = q→Right;
q→Right = p;
p = q;
*/

/* LR поворот
q = p→Left; r = q→Right;
IF (r→Balance<0){ p→Balance = +1} ELSE{ p→Balance = 0;}
IF (r→Balance>0){ q→Balance = –1} ELSE{ q→Balance = 0;}
r→Balance = 0;
p→Left = r→Right;
q→Right = r→Left;
r→Left = q;
r→Right = p;
p = r;
*/

/* RR поворот
q = p→Right;
q→Balance = 0;
p→Balance = 0;
p→ Right= q→ Left;
q→ Left = p;
p = q;
*/

/* RL поворот
q = p→ Right;
r = q→ Left;
IF (r→Balance>0){ p→Balance = -1;} ELSE{ p→Balance = 0;}
IF (r→Balance<0){ q→Balance = 1;} ELSE {q→Balance = 0;}
r→Balance = 0;
p→ Right= r→ Left;
q→ Left= r→ Right;
r→ Left = p;
r→Right = q;
p = r;
*/

bool rost = false;

bool HR = true;
bool VR = true;

int R = 0;

//Добавление в АВЛ дерево
void insertAVL(node **p, INT32 D)
{
	node *q = NULL;
	node *r = NULL;
	if (*p==NULL)
	{
		*p = new node(D, 0);
		rost = true;		
	}
	else
	{
		if ((*p)->Data > D)
		{
			insertAVL(&(*p)->left, D);
			if (rost)//выросла левая ветвь
			{
				if ((*p)->Balance > 0)
				{
					(*p)->Balance = 0;
					rost = false;
				}
				else 
				if ((*p)->Balance == 0)
				{
					(*p)->Balance = (-1);
				}
				else 
				{
					R++;
					if ((*p)->left->Balance < 0)
					{
						q = (*p)->left;
						q->Balance = 0;
						(*p)->Balance = 0;
						(*p)->left = q->right;
						q->right = (*p);
						(*p) = q;
					}
					else
					{
						q = (*p)->left; r = q->right;
						if (r->Balance<0){ (*p)->Balance = 1; }
						else{ (*p)->Balance = 0; }
						if (r->Balance>0){ q->Balance = (-1); }
						else{ q->Balance = 0; }
						r->Balance = 0;
						(*p)->left = r->right;
						q->right = r->left;
						r->left = q;
						r->right = (*p);
						(*p) = r;
					}
					rost = false;
				}
			}
		}
			else if ((*p)->Data < D)
			{
				insertAVL(&(*p)->right, D);
				if (rost)//выросла правая ветвь
				{
					if ((*p)->Balance < 0)
					{
						(*p)->Balance = 0;
						rost = false;
					}
					else if ((*p)->Balance == 0)
					{
						(*p)->Balance = 1;
					}
					else
					{
						R++;
						if ((*p)->right->Balance > 0)
						{
							q = (*p)->right;
							q->Balance = 0;
							(*p)->Balance = 0;
							(*p)->right = q->left;
							q->left = (*p);
							(*p) = q;
						}
						else
						{
							q = (*p)->right;
							r = q->left;
							if (r->Balance > 0){ (*p)->Balance = -1; }
							else{ (*p)->Balance = 0; }
							if (r->Balance < 0){ q->Balance = 1; }
							else{ q->Balance = 0; }
							r->Balance = 0;
							(*p)->right = r->left;
							q->left = r->right;
							r->left = (*p);
							r->right = q;
							(*p) = r;

						}
						rost = false;
					}
				}
				else
				{
					//puts("Такая вершина уже есть");
				}
			}
		
	}
}

//Добавление в БД дерево
void insertBB(node **p, INT32 D)
{
	node *q = NULL;	
	if (*p == NULL)
	{
		*p = new node(D, 0);
		VR = true;
		HR = false;
	}
	else
	{
		if ((*p)->Data > D)
		{
			insertBB(&(*p)->left, D);
			if (VR == true)
			{
				if ((*p)->Balance == 0)
				{
					q = (*p)->left;
					(*p)->left = q->right;
					q->right = (*p);
					(*p) = q;
					q->Balance = 1;
					VR  = false; 
					HR = true;
				}
				else
				{
					(*p)->Balance = 0;
					HR = true;
				}
			}
			else
			{
				HR = false;
			}
		}
		else
		{
			if ((*p)->Data < D)
			{
				insertBB(&(*p)->right, D);
				if (VR == true)
				{
					(*p)->Balance = 1;
					VR = false;
					HR = true;
				}
				else
				{
					if (HR == true)
					{
						if ((*p)->Balance > 0)
						{
							q = (*p)->right;
							(*p)->right = q->left;
							(*p)->Balance = 0;
							q->Balance = 0;
							q->left = (*p);
							(*p) = q;
							VR = true;
							HR = false;
						}
						else
						{
							HR = false;
						}
					}
				}
			}
		}

	}
}




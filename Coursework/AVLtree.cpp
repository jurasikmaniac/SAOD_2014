




unsigned char height(node* p)
{
	return p ? p->height : 0;
}

int bfactor(node* p)
{
	return height(p->right) - height(p->left);
}

void fixheight(node* p)
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl>hr ? hl : hr) + 1;
}

node* rotateright(node* p) // правый поворот вокруг p
{
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

node* rotateleft(node* q) // левый поворот вокруг q
{
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

node* balance(node* p) // балансировка узла p
{
	fixheight(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; // балансировка не нужна
}

node* insert(node* p, unitBase * k) // вставка ключа k в дерево с корнем p
{
	if (!p) return new node(k);
	if (CompareDate(k->dob,p->key->dob)==1)
		p->left = insert(p->left, k);
	else
		p->right = insert(p->right, k);
	return balance(p);
}

node* findmin(node* p) // поиск узла с минимальным ключом в дереве p 
{
	return p->left ? findmin(p->left) : p;
}

void find(node* p, char* k)
{
	if (p)
	{
		if (CompareDate(k, p->key->dob) == 2)
		{ 
			puts("+");
			printf_s("%s ", p->key->fio);
			printf_s("%03d\t", p->key->numUnit);
			printf_s("%s\t", p->key->job);
			printf_s("%s\n", p->key->dob);
			find(p->right, k);
			find(p->left, k);
		}
		else
		if (CompareDate(k, p->key->dob) == 0)
		{
			find(p->right, k);
		}
		else 
			find(p->left, k);

	}
}
node* removemin(node* p) // удаление узла с минимальным ключом из дерева p
{
	if (p->left == 0)
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

node* remove(node* p, unitBase*k) // удаление ключа k из дерева p
{
	if (!p) return 0;
	if (CompareDate(k->dob, p->key->dob) == 1)
		p->left = remove(p->left, k);
	else if (CompareDate(k->dob, p->key->dob) == 0)
		p->right = remove(p->right, k);
	else //  k == p->key 
	{
		node* q = p->left;
		node* r = p->right;
		delete p;
		if (!r) return q;
		node* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}
void freetree(node* tree)//освободить память из под дерева
{
	if (tree)
	{
		freetree(tree->right);
		freetree(tree->left);
		delete tree;
		count++;
		tree = NULL;
	}
	
}

void showwtree(node* p)
{
	if (p)
	{
		puts(p->key->dob);
		showwtree(p->left);
		showwtree(p->right);
	}
}



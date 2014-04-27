
struct unitBase{
	char fio[30];
	UINT16 numUnit;
	char job[22];
	char dob[10];
};
//элемент очереди
struct T_Data{
	unitBase *data;
	T_Data *next;
}*index[31];
//очередь
struct T_Queue{
	T_Data *head;
	T_Data *tail;
};

struct node // структура для представления узлов дерева
{
	unitBase *key;
	unsigned char height;
	node* left;
	node* right;
	node(unitBase * k) { key = k; left = right = 0; height = 1; }
};
long count = 0;


inline void SetLoc(UINT);
inline void PrintMenu();
void readFilename();
void OpenBase(T_Queue&);
int Compare(char *, char *, int);
int CompareDate(char *, char *);

int LessDayAndFio(unitBase*, unitBase*);
void Search();

void addToQueue(T_Queue&, unitBase*);
void showQueue(T_Queue&);
void freeQueue(T_Queue&);
void sortMerge(T_Queue&);
void split(T_Queue&, T_Queue&, T_Queue&, int&);
void merge(T_Queue&, int, T_Queue&, int, T_Queue&);

unsigned char height(node* );
int bfactor(node*);
void fixheight(node*);
node* rotateright(node*); // правый поворот вокруг p
node* rotateleft(node*); // левый поворот вокруг q
node* balance(node*); // балансировка узла p
node* insert(node*, unitBase *); // вставка ключа k в дерево с корнем p
node* findmin(node*); // поиск узла с минимальным ключом в дереве p 
void find(node*, char *);
node* removemin(node*); // удаление узла с минимальным ключом из дерева p
node* remove(node*, unitBase *); // удаление ключа k из дерева p
void freetree(node*);
#include "AVLtree.cpp"
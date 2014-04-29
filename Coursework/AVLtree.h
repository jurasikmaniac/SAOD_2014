//структура с данными
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
// структура для представления узлов дерева
struct node 
{
	unitBase *key;
	unsigned char height;
	node* left;
	node* right;
	node(unitBase * k) { key = k; left = right = 0; height = 1; }
};
//контроль удаленных узлов дерева
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
node* rotateright(node*);
node* rotateleft(node*);
node* balance(node*);
node* insert(node*, unitBase *);
node* findmin(node*);
void find(node*, char *);
node* removemin(node*);
node* remove(node*, unitBase *);
void freetree(node*);
#include "AVLtree.cpp"
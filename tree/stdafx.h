// stdafx.h: ���������� ���� ��� ����������� ��������� ���������� ������
// ��� ���������� ������ ��� ����������� �������, ������� ����� ������������, ��
// �� ����� ����������
//

#pragma once

#include "targetver.h"
#include <conio.h>
#include <cmath>
#include <cstdio>
#include <ctype.h> 
#include <clocale>
#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include <ctime>


//������� ������
struct node
{
	INT8  Balance;
	INT32 Data;
	node* left;
	node* right;	
	node(INT32 k) { Data = k; left = right = NULL; }
	node(INT32 k, INT8  B) { Data = k; Balance = B; left = right = NULL; }
};
struct nodeAVL
{
	INT32 Data;
	INT8  Balance;
	nodeAVL* left;
	nodeAVL* right;
	nodeAVL(INT32 k, INT8  B) { Data = k; Balance = B; left = right = NULL; }
};

// TODO: ���������� ����� ������ �� �������������� ���������, ����������� ��� ���������

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


//������� ������
struct node
{
	INT32 Data;
	node* left;
	node* right;	
	node(INT32 k) { Data = k; left = right = NULL; }
};

// TODO: ���������� ����� ������ �� �������������� ���������, ����������� ��� ���������

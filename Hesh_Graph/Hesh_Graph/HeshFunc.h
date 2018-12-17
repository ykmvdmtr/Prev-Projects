#pragma once

typedef struct info_t { //������ ���-�������
	int value;
	bool use;
} TInfo;

TInfo* GetTable(size_t size); //���������� ������� �������� size
size_t GetHashKey(size_t size, int key); //��������� ����
size_t GetNextKey(size_t size, int key); //� ������ ��������� - ��������� ���� ���������
bool AddToTable(TInfo *Tb, size_t size, int key); //������� ������� � ���-�������											  
// �������� �� ����� count ����� � ��������� �������� � table
void LoadTable(FILE* f, TInfo table[], size_t size, size_t count);
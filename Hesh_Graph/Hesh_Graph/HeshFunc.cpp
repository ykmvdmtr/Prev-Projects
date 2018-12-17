#include"stdafx.h"

TInfo* GetTable(size_t size) { //���������� ������� �������� size
	return (TInfo*)malloc(size*sizeof(TInfo));
}
size_t GetHashKey(size_t size, int key) { //��������� ����
	return key % size;
}
size_t GetNextKey(size_t size, int key) { //� ������ ��������� - ��������� ���� ���������
	return ++key == size ? 0 : key;
}
bool AddToTable(TInfo *Tb, size_t size, int key) { //������� ������� � ���-�������
	//��������� �������� ������� �����
	int secondKey = GetHashKey(size, key);
	int baseKey = secondKey;
	bool isAdd; //��� �������� ����� ����������

	// ������� � ���������� ����� �������� ����� ��������� �����
	while (Tb[baseKey].use && ((baseKey = GetNextKey(size, baseKey)) != secondKey)) {
		;
	}

	//�������� �� ��������� (������ �� �������� �������)
	isAdd = (Tb[baseKey].use == false);

	//���� ��, �� ���������
	if (isAdd) {
		Tb[baseKey].value = key;
		Tb[baseKey].use = true;
	}

	return isAdd;
}
// �������� �� ����� count ����� � ��������� �������� � table
void LoadTable(FILE* f, TInfo table[], size_t size, size_t count) {
	int value;
	while ((count--) && (fscanf(f, "%d", &value) == 1)) {
		if (AddToTable(table, size, value) == false) {
			fprintf(stderr, "error: conflict, value %d not added ...\n", value);
		}
	}
}
#include"stdafx.h"

TInfo* GetTable(size_t size) { //возвращает таблицу размером size
	return (TInfo*)malloc(size*sizeof(TInfo));
}
size_t GetHashKey(size_t size, int key) { //первичный ключ
	return key % size;
}
size_t GetNextKey(size_t size, int key) { //В случае коолизиии - вторичный ключ вычисляем
	return ++key == size ? 0 : key;
}
bool AddToTable(TInfo *Tb, size_t size, int key) { //функция вставки в хэш-таблицу
	//Вычисляем значение первого ключа
	int secondKey = GetHashKey(size, key);
	int baseKey = secondKey;
	bool isAdd; //это значение будем возвращать

	// Начиная с первичного ключа пытаемся найти свободное место
	while (Tb[baseKey].use && ((baseKey = GetNextKey(size, baseKey)) != secondKey)) {
		;
	}

	//Проверка на занятость (сможем ли добавить элемент)
	isAdd = (Tb[baseKey].use == false);

	//Если да, то добавляем
	if (isAdd) {
		Tb[baseKey].value = key;
		Tb[baseKey].use = true;
	}

	return isAdd;
}
// Загрузка из файла count чисел и помещение значение в table
void LoadTable(FILE* f, TInfo table[], size_t size, size_t count) {
	int value;
	while ((count--) && (fscanf(f, "%d", &value) == 1)) {
		if (AddToTable(table, size, value) == false) {
			fprintf(stderr, "error: conflict, value %d not added ...\n", value);
		}
	}
}
#pragma once

typedef struct info_t { //ячейка хеш-таблицы
	int value;
	bool use;
} TInfo;

TInfo* GetTable(size_t size); //возвращает таблицу размером size
size_t GetHashKey(size_t size, int key); //первичный ключ
size_t GetNextKey(size_t size, int key); //В случае коолизиии - вторичный ключ вычисляем
bool AddToTable(TInfo *Tb, size_t size, int key); //функция вставки в хэш-таблицу											  
// Загрузка из файла count чисел и помещение значение в table
void LoadTable(FILE* f, TInfo table[], size_t size, size_t count);
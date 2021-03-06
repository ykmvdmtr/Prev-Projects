// Hesh_Graph.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


int main() {
	const char CFile[] = "file.txt";

	// Количество элементов в хеш-таблице
	const size_t size = 20;
	// Создаём таблицу
	TInfo* table = GetTable(size);

	// Открываем файл
	FILE* f = fopen(CFile, "r");
	if (f == NULL) {
		perror(CFile);
		return EXIT_FAILURE;
	}

	// Загружаем данные из файла в таблицу
	LoadTable(f, table, size, 15);

	fclose(f);

	// Вывод используемых элементов таблицы
	printf("only used elements: ");
	PrintTable(table, size, false);
	printf("\n");

	// Вывод всей хеш-таблицы
	printf("all elements: ");
	PrintTable(table, size, true);
	printf("\n");

	int value, key;
	size_t count;

	// Просим пользователя ввести искомое значение
	printf("find value : ");
	scanf("%d", &value);

	// Если ключ был найден
	if ((key = GetValue(table, size, value, &count)) != -1) {
		// Выводим ключ и количество попыток
		printf("key %d, attempt %d\n", key, count);
	}
	else {
		// Элемент был не найден
		fprintf(stderr, "value %d not found ...\n", value);
	}

	return EXIT_SUCCESS;
}


#include "stdafx.h"

int size_table(T_Table *Tb) { //возвращает размер таблицы
	int size(0);
	if (!Tb) return 0;
	while ((((Tb + size)->namevert) >= 'a') && (((Tb + size)->namevert) <= 'z'))
		size++;
	return size;
}
int find_Vert(T_Table *Tb, char V) { //ищет вхождение вершины в таблицу и возвращает индекс ее в таблице
	int ind(0);
	int size = size_table(Tb);
	if (!Tb) return size;
	for (ind; ((Tb + ind)->namevert != V) && ind < size; ind++);
	return ind;
}
int find_Ind(T_Table *Tb, int ind) { //ищет индекс в таблице
	int res(0);
	int size = size_table(Tb);
	for (res, res; ((Tb + res)->nxt != ind) && res < size; res++);
	return res;
}
void Menu1(T_Table **Tb) { //функция работы с первой таблицей
	int size;
	char name;
	std::cout << "Введите название вершины: ";
	std::cin >> name;
	size = size_table(*Tb);
	(*Tb) = (T_Table*)realloc(*Tb, (size + 1) * sizeof(T_Table));
	(*Tb)[size].namevert = name;
	(*Tb)[size].nxt = (-1);
}
void Menu2(T_Table **Tb, T_Table **SP) { //функции работы с основной таблицей
	if (!(*Tb)) {
		std::cout << "Нет графа! Создайте граф!\n";
		return;
	}
start:
	char namest, namefin;
	std::cout << "Введите исходную вершину: ";
	std::cin >> namest;
	std::cout << "Введите вершину, смежную с данной: ";
	std::cin >> namefin;



	int size1 = size_table(*Tb);
	int size2 = size_table(*SP);
	int indx = find_Vert(*Tb, namest);
	int tmp = find_Vert(*Tb, namefin);
	if (indx == size1 || tmp == size1) {
		std::cout << "ERROR(find_Vert)\n ТАКОЙ ВЕРШИНЫ НЕТ! Попробуйте еще раз!\n";
		goto start;
	}

	if ((*Tb)[indx].nxt == (-1)) {
		//'Это когда добавляем первую смежную вершину
		(*Tb)[indx].nxt = size2;
		(*SP) = (T_Table*)realloc(*SP, (size2 + 1) * sizeof(T_Table));
		(*SP)[size2].namevert = namefin;
		(*SP)[size2].nxt = (-1);
	}
	else {
		int tmp = (*Tb)[indx].nxt;
		while ((*SP)[tmp].nxt != (-1))
			tmp = (*SP)[tmp].nxt;
		(*SP) = (T_Table*)realloc(*SP, (size2 + 1) * sizeof(T_Table));
		(*SP)[tmp].nxt = size2;
		(*SP)[size2].namevert = namefin;
		(*SP)[size2].nxt = (-1);
	}
}
void Menu3(T_Table **Tb, T_Table **SP) {
	if (!(*Tb)) {
		std::cout << "Нет графа! Создайте граф!\n";
		return;
	}
	char namedel;
	std::cout << "Введите вершину, которую следует удалить (с ней удаляться все смежные с ней ребра): ";
	std::cin >> namedel;

	int size1 = size_table(*Tb);
	int size2 = size_table(*SP);
	//прорабатываем первую таблицу
	for (int i = 0; i < size2; i++) {
		if ((*SP)[(*SP)[i].nxt].namevert == namedel) {
			if ((*SP)[(*SP)[i].nxt].nxt == (-1)) {
				int tmp = (*SP)[i].nxt;
				(*SP)[i].nxt = (-1);
				(*SP)[tmp].namevert = DEL;
				(*SP)[tmp].nxt = DELN;
			}
			else {
				int tmp = (*SP)[i].nxt;
				(*SP)[i].nxt = (*SP)[(*SP)[i].nxt].nxt;
				(*SP)[tmp].namevert = DEL;
				(*SP)[tmp].nxt = DELN;
			}
		}
	}
	//прорабатываем вторую таблицу
	for (int i = 0; i < size1; i++) {
		int tmp = (*Tb)[i].nxt;
		if (tmp == (-1))
			continue;
		if ((*SP)[tmp].namevert == namedel) {
			if ((*SP)[tmp].nxt == (-1)) {
				(*Tb)[i].nxt = (-1);
				(*SP)[tmp].namevert = DEL;
				(*SP)[tmp].nxt = (-100);
			}
			else {
				(*Tb)[i].nxt = (*SP)[tmp].nxt;
				(*SP)[tmp].namevert = DEL;
				(*SP)[tmp].nxt = (-100);
			}
		}
	}
	//и удаляем вершину из исходной таблицы
	int indx = find_Vert(*Tb, namedel);
	int tempI = (*Tb)[indx].nxt;
	if (tempI != (-1)) {
		while ((*SP)[tempI].nxt != (-1)) {
			int tempII = tempI;
			tempI = (*SP)[tempI].nxt;
			(*SP)[tempII].nxt = DELN;
			(*SP)[tempII].namevert = DEL;
		}
	}
	for (indx; indx < size1 - 1; indx++) {
		(*Tb)[indx].namevert = (*Tb)[indx + 1].namevert;
		(*Tb)[indx].nxt = (*Tb)[indx + 1].nxt;
	}

	(*Tb) = (T_Table*)realloc(*Tb, (size1 - 1) * sizeof(T_Table));
	size1--; //уменьшаем размер таблицы
	int countdel(0);
	for (int i = 0; i < size2; i++) { //перписываем удаленные элементы в конец таблицы
		if ((*SP)[i].namevert == DEL) {
			countdel++;
			for (int j = 0; j < i; j++) {
				if ((*SP)[j].nxt>i) (*SP)[j].nxt--;
			}
			for (int j = i; j < size2 - 1; j++) {
				int indinf = find_Ind(*Tb, j + 1);
				if (indinf == size1) {
					(*SP)[j].namevert = (*SP)[j + 1].namevert;
					if ((*SP)[j + 1].nxt == (-1))
						(*SP)[j].nxt = (*SP)[j + 1].nxt;
					else
						(*SP)[j].nxt = (*SP)[j + 1].nxt - 1;
				}
				else {
					(*Tb)[indinf].nxt--;
					(*SP)[j].namevert = (*SP)[j + 1].namevert;
					if ((*SP)[j + 1].nxt == (-1))
						(*SP)[j].nxt = (*SP)[j + 1].nxt;
					else
						(*SP)[j].nxt = (*SP)[j + 1].nxt - 1;
				}
			}
		}
	}
	(*SP) = (T_Table*)realloc(*SP, (size2 - countdel + 1) * sizeof(T_Table)); //уменьшаем вторую таблицу
}

void print_help() {
	std::cout << "____________\n"
		<< "MENU: \n"
		<< "1. Добавить новую вершину в графе\n"
		<< "2. Исключить вершину из графа (ребра, смежные с данной вершиной также удалятся)\n"
		<< "3. Добавить смежные вершины\n"
		<< "X. EXIT\n";
}


void print_table(T_Table *Tb) {
	int size = size_table(Tb);
	for (int i = 0; i < size; i++) {
		if ((Tb + i)->nxt == DELN)
			std::cout << (Tb + i)->namevert << " | " << (Tb + i)->nxt << " ЗДЕСЬ НЕТ СВЯЗИ! (Это ребро удалилось)\n";
		else
			std::cout << (Tb + i)->namevert << " | " << (Tb + i)->nxt << " (index = " << i << ")\n";
	}
	std::cout << "____________\n";
}
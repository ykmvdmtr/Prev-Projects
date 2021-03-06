// Tree.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

int main() {
	setlocale(LC_ALL, "RUS");
	tree_t *tree[MAX_tr];
	char c = 0;
	int CtTr = 0; //счетчик количества деревьев

	FILE *tmpf = fopen("trying.txt", "a");
	cout << "Привет! Вы используете программу, позволяющую работать с двочиным деревом поиска." << endl;
	Menu_prev();
	while (c != 'X') {
		cin >> c;
		switch (c) {
		case '1':
			tree[CtTr] = NULL;
			CtTr++; // инкремир. кол-во деревьев
			cout << "Успешно добавили дерево!\nЧто дальше?\n>>>";
			break;
		case '2':
			if (CtTr == 0) { cout << "Нет деревьев! Создайте списки!\n>>>"; break; }
			if (CtTr == 1) {
				printf("Вы имеете %d дерево. С каким их них будем работать? (отсчет идет с нуля): ", CtTr); m_help(CtTr, tree);
			}
			else
				if (CtTr>1 && CtTr<5) {
					printf("Вы имеете %d дерева. С каким их них будем работать? (отсчет идет с нуля): ", CtTr); m_help(CtTr, tree);
				}
				else
					if (CtTr >= 5) {
						printf("Вы имеете %d деревьев. С каким их них будем работать? (отсчет идет с нуля): ", CtTr); m_help(CtTr, tree);
					}
			int n;
			cin >> n;
			if (n<0 || n>CtTr - 1) { cout << "Ошибка. Таких деревьев нет\nЧто дальше?\n>>>"; break; }
			cout << "Супер! Работаем с этим деревом\n";
			f1(tree, n);
			system("cls");
			Menu_prev();
			break;
			case '3':
			{
				if (CtTr == 0) { cout << "Нет деревьев! Создайте деревья!\n>>>"; break; }
				cout << "С какими деревьями будем работать?( два числа ввести): \n";
				m_help(CtTr, tree);
				int k, m;
				cin >> k >> m;
				if (k<0 || k>CtTr - 1 || m<0 || m>CtTr - 1) { cout << "Ошибка. Таких деревьев нет\nЧто дальше?\n>>>"; break; }
				cout << "Супер! Работаем с этими списками\n";
				tree[CtTr] = NULL;
				CtTr++;
				f2(tree, k, m, CtTr);
				system("cls");
				Menu_prev();
				break;
			}
		case 'X':
			cout << "THE END.\n";
			break;
		default:
			printf("Неверно введена команда! Попробуй еще раз.\n >>>");
		}
	}
	return 0;
}



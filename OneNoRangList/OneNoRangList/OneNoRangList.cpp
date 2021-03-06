// OneNoRangList.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


int main()
{
	setlocale(LC_ALL, "RUS");

	list_t *lst[10]; //здесь будут храниться списки
	char c = 0;
	int CtLnk = 0; //счетчик количества список

	cout << "Привет! Вы используете программу, позволяющую работать с односвязными линейными списками." << endl;
	Menu_prev();
	while (c != 'X') {
		cin >> c;
		switch (c) {
		case '1':
			lst[CtLnk] = create_list();
			CtLnk++; // инкремир. кол-во списков
			cout << "Успешно добавили список!\nЧто дальше?\n>>>";
			break;
		case '2':
			if (CtLnk == 0) { cout << "Нет списков! Создайте списки!\n>>>"; break; }
			if (CtLnk == 1) {
				printf("Вы имеете %d список. С каким их них будем работать? (отсчет идет с нуля): ", CtLnk); m_help(CtLnk, lst);
			}
			else
				if (CtLnk>1 && CtLnk<5) {
					printf("Вы имеете %d списка. С каким их них будем работать? (отсчет идет с нуля): ", CtLnk); m_help(CtLnk, lst);
				}
				else
					if (CtLnk >= 5) {
						printf("Вы имеете %d списков. С каким их них будем работать? (отсчет идет с нуля): ", CtLnk); m_help(CtLnk, lst);
					}
			int n;
			cin >> n;
			if (n<0 || n>CtLnk - 1) { cout << "Ошибка. Таких списков нет\nЧто дальше?\n>>>"; break; }
			cout << "Супер! Работаем с этим списком\n";
			f1(lst, n);
			clrscr();
			Menu_prev();
			break;
		case '3':
			if (CtLnk == 0) { cout << "Нет списков! Создайте списки!\n>>>"; break; }
			cout << "С какими списками будем работать?( два числа ввести): \n";
			m_help(CtLnk, lst);
			int k, m;
			cin >> k >> m;
			if (k<0 || k>CtLnk - 1 || m<0 || m>CtLnk - 1) { cout << "Ошибка. Таких списков нет\nЧто дальше?\n>>>"; break; }
			cout << "Супер! Работаем с этими списками\n";
			f2(lst, k, m, CtLnk);
			clrscr();
			Menu_prev();
			break;
		case 'X':
			cout << "THE END.\n";
			break;
		default:
			printf("Неверно введена команда! Попробуй еще раз.\n >>>");
		}
	}
	return 0;
}


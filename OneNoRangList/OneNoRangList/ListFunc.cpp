#include "stdafx.h"

list_t* create_list() {
	list_t *lt = (list_t*)malloc(sizeof(list_t)); //выделяем память под массив

	lt->root = NULL;
	/*lt->tail = lt->root;*/

	return lt;
}
int list_size(list_t *lt) { //возвращает размер списка
	list_node_t * tmproot = lt->root;
	int count = 0;
	while (lt->root) {
		lt->root = lt->root->nxt;
		count++;
	}
	lt->root = tmproot;
	return count;
}
void list_push(list_t *lt, int key) { //в начало списка
	list_node_t *nd = (list_node_t*)malloc(sizeof(list_node_t));
	nd->key = key;
	nd->nxt = lt->root;

	lt->root = nd;
}
void list_push_back(list_t *lt, int key) {
	list_node_t *nd = (list_node_t*)malloc(sizeof(list_node_t));
	nd->key = key;
	nd->nxt = NULL;
	list_node_t *tmproot = lt->root;

	if (lt->root == NULL)
		lt->root = nd;
	while (lt->root->nxt)
		lt->root = lt->root->nxt;
	lt->root->nxt = nd;
	lt->root = tmproot;
}
list_node_t * find_node(list_t *lt, int n) {
	if (lt->root == NULL) { cout << "Error(find node)!" << endl; return NULL; }
	else {
		int count = 0;
		while (count < n && lt->root) {
			lt->root = lt->root->nxt;
		}
	}
	return lt->root;
}
int find_key(list_t * lt, int key) {
	list_node_t * tmpLT = lt->root;
	while ((lt->root) && (lt->root->key != key)) {
		lt->root = lt->root->nxt;
	}
	if (lt->root) { lt->root = tmpLT; return 1; }
	else { lt->root = tmpLT; return 0; }
}
int delete_node(list_t *lt, int n) { //удаление элемента
	int k;

	if (lt->root == NULL) { cout << "Error(delete node)!" << endl; return 0; }
	else {
		if (lt->root->nxt) {
			list_node_t *prev = find_node(lt, n - 1);
			list_node_t *elm = prev->nxt;
			k = elm->key;
			prev->nxt = elm->nxt;
			free(elm);
		}
		else { //если только один элемент существует
			k = lt->root->key;
			free(lt->root);
			lt->root = NULL;
		}
	}
	return k;
}
void push_list_k(list_t * lt, int key, int k) {
	list_node_t *node = (list_node_t *)malloc(sizeof(list_node_t));
	node->key = key;
	list_node_t *prev = find_node(lt, k - 1);
	node->nxt = prev->nxt;
	prev->nxt = node;
}
void print_list(list_t *lt) {
	list_node_t *tmproot = lt->root;
	if (lt->root == NULL) { cout << "Error(print list)!" << endl; return; }
	else {
		while (lt->root) {
			printf("%d\n", lt->root->key);
			lt->root = lt->root->nxt;
		}
	}
	lt->root = tmproot;
}
void list_pop(list_t *lt) { //удаление из начала списка
	if (lt->root == NULL) {
		/* Список пуст */
		cout << "List is empty(list_pop)!" << endl;
		return;
	}

	list_node_t *nd = lt->root;
	lt->root = nd->nxt;
	free(nd);

	if (lt->root == NULL) {
		//Это был последний элемент 
		lt->root = NULL;
		lt->tail = NULL;
	}
}
void read_list(list_t *lt) {
	char namef[80];
	cout << "Введите название файла" << endl;
	fscanf(stdin, "%s", namef);
	FILE *f = fopen(namef, "r");
	if (f == NULL) { cout << "Error!(read_list)" << endl; return; }
	int x;
	while (fscanf(f, "%d", &x) != EOF)
		list_push(lt, x);
	printf("Считано успешно\nЧто дальше?\n>>>");
	fclose(f);
}
void save_list(list_t *lt) {
	char namef[80];
	cout << "Введите название файла" << endl;
	fscanf(stdin, "%s", namef);
	FILE *f = fopen(namef, "a");
	if (f == NULL) { cout << "Error!(save_list)" << endl; return; }

	list_node_t *tmproot = lt->root;
	while (lt->root) {
		fprintf(f, "%d ", lt->root->key);
		lt->root = lt->root->nxt;
	}
	fclose(f);
	lt->root = tmproot;
}
void com_lists(list_t *lt1, list_t *lt2, list_t *LT) {
	list_node_t * tmproot1 = lt1->root;
	list_node_t * tmproot2 = lt2->root;
	int temp;

	while (lt1->root) {
		if ((temp = find_key(LT, lt1->root->key)) == 0) list_push(LT, lt1->root->key);
		lt1->root = lt1->root->nxt;

	}
	while (lt2->root) {
		if ((temp = find_key(LT, lt2->root->key)) == 0) list_push(LT, lt2->root->key);
		lt2->root = lt2->root->nxt;
	}
	lt1->root = tmproot1;
	lt2->root = tmproot2;
}
void change_n_m(list_t * lt1, list_t * lt2) {
	list_node_t *tmproot1 = lt1->root;
	list_node_t *tmproot2 = lt2->root;
	cout << "Какой элемент первого и второго списка будем менять?(введите два числа):" << endl;
	int key1, key2, size1, size2;
	cin >> key1 >> key2;
	if ((size1 = list_size(lt1))<key1 || (size2 = list_size(lt2))<key2) { cout << "Увы! Но размер списка меньше числа, которое вы ввели" << endl; return; }
	int delkey1 = delete_node(lt1, key1); //сохранили значение удаленного элемента
	int delkey2 = delete_node(lt2, key2); // ----
	push_list_k(lt1, delkey2, key1);
	push_list_k(lt2, delkey1, key2);

	lt1->root = tmproot1;
	lt2->root = tmproot2;
}
void dif_lists(list_t *lt1, list_t * lt2, list_t * LT) {
	list_node_t * tmproot1 = lt1->root;
	list_node_t * tmproot2 = lt2->root;

	int size1 = list_size(lt1);
	int size2 = list_size(lt2);
	int max = (size1>size2) ? size1 : size2;
	int temp;
	int n = 0;
	while (lt1->root&&n<max) {
		if ((temp = find_key(lt2, lt1->root->key)) == 0) list_push(LT, lt1->root->key);
		lt1->root = lt1->root->nxt;
		n++;
	}
	/*n = 0;
	lt1->root = tmproot1;
	while(lt2->root&&n<max){
	if((temp = find_key(lt1,lt2->root->key))==0) list_push(LT,lt2->root->key);
	lt2->root = lt2->root->nxt;
	n++;
	}*/
	lt1->root = tmproot1;
	lt2->root = tmproot2;
}
void intersection_lists(list_t * lt1, list_t *lt2, list_t *LT) {
	list_node_t * tmproot1 = lt1->root;
	list_node_t * tmproot2 = lt2->root;
	int temp;

	while (lt1->root) {
		if ((temp = find_key(lt2, lt1->root->key)) == 1) list_push(LT, lt1->root->key);
		lt1->root = lt1->root->nxt;
	}

	lt1->root = tmproot1;
	lt2->root = tmproot2;
}

void Menu_prev() {
	cout << "\n____________________\n"
		<< "MENU\n"
		<< "1. Добавить список\n"
		<< "2. Выбрать список для работы с ним\n"
		<< "3. Работа с несколькими списками\n"
		<< "X. EXIT\n>>>";
}
void f1(list_t **lst, int n) {
	char c;
	//FILE *in=fopen("input.txt", "r");
	cout << "\n____________________\n"
		<< "MENU\n"
		<< "1. Добавить элемент в начало списка\n"
		<< "2. Удалить n-ый элемент\n"
		<< "3. Считать список из файла \n"
		<< "4. Вывести список на экран\n"
		<< "5. Сохранить список в файл\n"
		<< "6. Удалить из начала списка\n"
		<< "7. Вставить элемент в конец спсика\n"
		/*<<"5. Вхождение в список элемента с заданным ключом\n"   */
		<< "X. EXIT\n>>>";
	while (c != 'X') {
		cin >> c;
		switch (c) {
		case '1':
			cout << "Введите значение узла:\n>>>";
			int key;
			cin >> key;
			list_push(lst[n], key);
			cout << "Успешно\nЧто дальше?\n>>>";
			break;
		case '2':
			cout << "Какой по счету элемент следует удалить?: ";
			int k, delelm;
			cin >> k;
			delelm = delete_node(lst[n], k);
			cout << "Успешно! Мы удалили элемент со значением: " << delelm << "\nЧто дальше?\n>>>";
			break;
		case '3':
			read_list(lst[n]);
			break;
		case '4':
			print_list(lst[n]);
			cout << "Успешно!\nЧто дальше?\n>>>";
			break;
		case '5':
			save_list(lst[n]);
			cout << "Успешно!\nЧто дальше?\n>>>";
			break;
		case '6':
			list_pop(lst[n]);
			cout << "Успешно!\nЧто дальше?\n>>>";
			break;
		case '7':
			cout << "Введите значение узла:\n>>>";
			int key1;
			cin >> key1;
			list_push_back(lst[n], key1);
			cout << "Успешно!\nЧто дальше?\n>>>";
			break;
		case 'X':
			cout << "THE END.\n";
			break;
		default:
			printf("Неверно введена команда! Попробуй еще раз.\n >>>");
		}
	}
	c = 0; //для повторного захода в функцию необходимо засунуть туда нуль
}
void f2(list_t **lst, int n, int m, int CtLnk) {
	char c;
	cout << "\n____________________\n"
		<< "MENU\n"
		<< "1. Объединить два списка\n"
		<< "2. Поменять k-ый элемент первого списка с m-ым элементом второго списка\n"
		<< "3. Вычесть два списка\n"
		<< "4. Найти пересечение двух списков\n"
		<< "X. EXIT\n>>>";
	int count0 = 0;
	while (c != 'X') {
		cin >> c;
		switch (c) {
		case '1':
		{
			lst[CtLnk + count0] = create_list();
			com_lists(lst[n], lst[m], lst[CtLnk + count0]);
			print_list(lst[CtLnk + count0]);
			count0++;
			cout << "Успешно!\nЧто дальше?\n>>>";
			break;
		}
		case '2':
		{
			change_n_m(lst[n], lst[m]);
			cout << "Успешно!\nЧто дальше?\n>>>";
			break;

		}
		case '3':
		{
			lst[CtLnk + count0] = create_list();
			dif_lists(lst[n], lst[m], lst[CtLnk + count0]);
			print_list(lst[CtLnk + count0]);
			count0++;
			cout << "Успешно!\nЧто дальше?\n>>>";
			break;
		}
		case '4':
			lst[CtLnk + count0] = create_list();
			intersection_lists(lst[n], lst[m], lst[CtLnk + count0]);
			print_list(lst[CtLnk + count0]);
			count0++;
			cout << "Успешно!\nЧто дальше?\n>>>";
			break;
		case 'X':
			cout << "THE END.\n";
			break;
		default:
			printf("Неверно введена команда! Попробуй еще раз.\n >>>");
		}
	}
}
void m_help(int numb, list_t **lst) {
	int i = 0;
	cout << "\n----------\n";
	for (i; i<numb; i++) {
		if (lst[i]->root)
			cout << i << " - " << i + 1 << "-ый список" << endl;
		else
			cout << i << " - " << i + 1 << "-ый список (EMPTY)" << endl;
	}
	cout << "----------\n" << ">>>";
}

void clrscr(void) {
	char a[80];
	printf("\033[2J");
	printf("\033[0;0f");
}

int main()
{
	list_t *lst[10]; //здесь будут храниться списки
	char c;
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
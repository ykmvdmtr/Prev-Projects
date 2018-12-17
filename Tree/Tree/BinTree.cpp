#include"stdafx.h"

tree_t *new_node(char *wd, tree_t *par) {
	tree_t *nt = (tree_t*)malloc(sizeof(tree_t));
	nt->word = (char*)malloc(strlen(wd) + 1 * sizeof(char));
	nt->count = 1;
	strcpy(nt->word, wd);
	nt->parrent = par; //записываем узел родителя

	nt->left = nt->right = NULL;

	return nt;
}
tree_t *addtree(tree_t *tr, char *w, tree_t *par) {
	int tmp;


	if (!tr)
		tr = new_node(w, par);
	else {
		if ((tmp = strcmp(w, tr->word)) == 0) tr->count++;
		else {
			if (tmp < 0) tr->left = addtree(tr->left, w, tr);
			else
				tr->right = addtree(tr->right, w, tr);
		}
	}
	return tr;
}
tree_t *find_node(tree_t *tr, char *w) {
	tree_t *tmp = tr;
	int tp = 0;
	while (tr && (tp = strcmp(w, tr->word))) {
		if (tp < 0) tr = tr->left;
		else tr = tr->right;
	}
	if (tr) return tr;
	else return NULL;
}
char *maxRinL(tree_t *tr) { //самый правый элемент в левом поддереве
	char *tw = (char*)malloc(MAX_w);
	if (!tr->left) { /*cout << "\n***Error(not node in maxRinL)!\n";*/ return NULL; }
	else {
		tr = tr->left;
		while (tr->right)
			tr = tr->right;
	}
	strcpy(tw, tr->word);

	return tw;
}
char *maxLinR(tree_t *tr) { //самый левый элемент правого поддерева
	char *tw = (char*)malloc(MAX_w);
	if (!tr->right) { /*cout << "\n***Error(not node in maxLinR)!\n";*/ return NULL; }
	else {
		tr = tr->right;
		while (tr->left)
			tr = tr->left;
	}
	strcpy(tw, tr->word);

	return tw;
}
int delelm(tree_t **tr, char *w) {
	int temp = 0;
	tree_t *tmptm = find_node(*tr, w);
	if (!tmptm) { cout << "Такого узла нет!\nЧто дальше?\n>>>"; return (-1); }
	char *retw = (char*)malloc(MAX_w);
	if (tmptm->count > 1) {
		int tempi = help_delelm(tmptm->word, tmptm->count);
		tmptm->count = tmptm->count - tempi;
		return 2;
	}
	//дальше должны рассмотреть 2 случая:
	//1. Найденный элемент является листком (нет детей)
	if ((!(tmptm->left)) && (!(tmptm->right))) {
		strcpy(retw, tmptm->word);
		if (tmptm == *tr) {
			free(*tr);
			*tr = NULL;
		}
		else {
			if ((temp = strcmp(tmptm->word, tmptm->parrent->word)) > 0) tmptm->parrent->right = NULL;
			else tmptm->parrent->left = NULL;
			free(tmptm);
		}
		return 0;
	}
	//2. 
	else {
		char *ptr = (char*)malloc(MAX_w);
		strcpy(retw, tmptm->word);
		if ((ptr = maxRinL(tmptm))) {
			tree_t *tmptm1 = find_node(tmptm, maxRinL(tmptm));
			strcpy(tmptm->word, tmptm1->word); //второй аргумент - произвольный из двух (строчка выше)
			if ((tmptm1->parrent) == tmptm)  tmptm->left = NULL;
			else
				tmptm1->parrent->right = NULL;

			free(tmptm1);
		}
		else {
			ptr = maxLinR(tmptm);
			tree_t *tmptm2 = find_node(tmptm, maxLinR(tmptm));
			strcpy(tmptm->word, tmptm2->word);
			if ((tmptm2->parrent) == tmptm) tmptm->right = NULL;
			else
				tmptm2->parrent->left = NULL;

			free(tmptm2);
		}
		return 0;
	}


}
void delall(tree_t **tr) { //неэффективно по времени и сложности(в свободное время переделать)
	while (*tr)
		delelm(tr, (*tr)->word);
}
void view_tree(tree_t *tr, tree_t **TR) { //обход всего дерева, с добавлением узла
	if (tr) {
		for(int i=0; i<tr->count; i++) //ведь нужно добавить все разы
			(*TR) = addtree(*TR, tr->word, NULL);
		view_tree(tr->left, TR);
		view_tree(tr->right, TR);
	}
}
void new_tree(tree_t **tr) { //восстановления дерева по обходам
	char s1[MAX_w], s2[MAX_w];
	cout << "Введите обход ПКЛ" << endl;
	scanf("%s", s1);
	cout << "Введите обход КПЛ" << endl;
	scanf("%s", s2);
	
	
	p1(tr, s1, s2);
}
void p1(tree_t **tr, char *s1, char *s2) {
	if (s1 && s2) {
		char tmp[2], tmp1[MAX_w], tmp2[MAX_w];
		strncpy(tmp, s2, 1);
		tmp[1] = '\0';
		(*tr) = addtree(*tr, tmp, NULL); //добавление корня
		int i = 0;
		while (s1[i] != s2[0]) {
			tmp1[i] = s1[i];
			i++;
		}
		tmp1[i] = '\0';
		i = +2;
		int j = 0;
		while (s1[i] != '\0') {
			tmp2[j] = s1[i];
			i++;
			j++;
		}
		tmp2[j] = '\0';
		p1(tr, tmp1, tmp2);
	}
}




void read_tree(tree_t **tr) {
	const char *SEPARATORS = "!,./_&?*+- ";
	char namef[80];
	cout << "Введите название файла" << endl;
	fscanf(stdin, "%s", namef);
	FILE *f = fopen(namef, "r");
	if (f == NULL) { cout << "Error!(read_list)" << endl; return; }
	char S[MAX_w];
	char *ptr = 0;
	fgets(S, MAX_w, f);
	ptr = strtok(S, SEPARATORS);
	(*tr) = addtree(*tr, ptr, NULL);
	ptr = strtok(0, SEPARATORS);
	while (ptr) {
		(*tr) = addtree(*tr, ptr, NULL);
		ptr = strtok(0, SEPARATORS);
	}
	printf("Считано успешно\nЧто дальше?\n>>>");
	fclose(f);
}

void print_tree(tree_t *tr, int k) {
	if (tr) {
		print_tree(tr->right, k + 1);
		printf("%*s - %i\n", 5 * k, tr->word, tr->count);
		print_tree(tr->left, k + 1);
	}
}
void save_tree(FILE *out, tree_t *tr, int k) {
	if (tr) {
		save_tree(out, tr->right, k + 1);
		fprintf(out, "%*s - %i\n", 5 * k, tr->word, tr->count);
		save_tree(out, tr->left, k + 1);
	}
}

void intersect_tr(tree_t *tr1, tree_t *tr2, tree_t **TR) {
	view_tree(tr1, TR);
	view_tree(tr2, TR);
}
void diff_tr(tree_t *tr1, tree_t *tr2, tree_t **TR) {
	/*
	Мы возьмем первое дерево и запихнем его в TR (как и в объединении). Потом пройдемся по всему второму дереву,
	смотря каждый элемент. Если допустим f-2 в первом дереве, а во втором f-1 То должно остаться f-1. Однако, если
	в первом дереве f-1 а во втором f-2, то вершину эту нек включаем вовсе.
	*/
	if (tr1) {
		tree_t *tmp = find_node(tr2, tr1->word);
		if (tmp) {
			if (tr1->count > tmp->count)
				for (int i = 0; i < tr1->count - tmp->count; i++)
					(*TR) = addtree(*TR, tr1->word, NULL);
		}
		else
			for (int i = 0; i < tr1->count; i++) 
				(*TR) = addtree(*TR, tr1->word, NULL);
		
		diff_tr(tr1->left, tr2, TR);
		diff_tr(tr1->right,tr2, TR);
	}
}


void Menu_prev() {
	cout << "____________________\n"
		<< "MENU\n"
		<< "1. Добавить дерево\n"
		<< "2. Выбрать дерево для работы с ним\n"
		<< "3. Работа с несколькими деревьями\n"
		<< "X. EXIT\n>>>";
}
void m_help(int numb, tree_t **tree) {
	int i = 0;
	cout << "\n----------\n";
	for (i; i<numb; i++) {
		if (!tree[i])
			cout << i << " - " << i + 1 << "-ое дерево (EMPTY)" << endl;
		else
			cout << i << " - " << i + 1 << "-ое дерево" << endl;
	}
	cout << "----------\n" << ">>>";
}
void f1(tree_t **tree, int n) {
	char c = 0;
	char *tmpw;
	//FILE *in=fopen("input.txt", "r");
	cout << "\n____________________\n"
		<< "MENU\n"
		<< "1. Добавить элемент в дерево\n"
		<< "2. Удалить n-ый элемент\n"
		<< "3. Считать дерево из файла \n"
		<< "4. Вывести дерево на экран\n"
		<< "5. Сохранить список в файл\n"
		<< "8. Удалить все дерево\n"
		<< "9. Создание дерева по обходам\n"
		<< "X. EXIT\n>>>";
	while (c != 'X') {
		cin >> c;
		switch (c) {
		case '1':
		{
			tmpw = (char*)malloc(MAX_w * sizeof(char));
			cout << "Введите значение узла:\n>>>";
			scanf("%s", tmpw);
			//fgets(tmpw, MAX_w, stdin);
			tree[n] = addtree(tree[n], tmpw, NULL);
			cout << "Успешно\nЧто дальше?\n>>>";
			break;
		}
		case '2':
		{
			char tmpel[5];
			cout << "Элемент с каким значением следует удалить?: ";
			scanf("%s", tmpel);
			int tmpint = delelm(&tree[n], tmpel);
			if (tmpint == 0) cout << "Успешно! Мы удалили элемент со значением: " << tmpel << "\nЧто дальше?\n>>>";
			else {
				if (tmpint == 2) cout << "Успешно! Мы удалили данный элемент нужное количество раз!\nЧто дальше?\n>>>";
			}
			break;
		}
		case '3':
			read_tree(&tree[n]);
			break;
		case '4':
			print_tree(tree[n], 0);
			cout << "Успешно!\nЧто дальше?\n>>>";
			break;
		case '5':
		{
			FILE *f = fopen("out.txt", "a");
			save_tree(f, tree[n], 0);
			cout << "Успешно!\nЧто дальше?\n>>>";
			fclose(f);
			break;
		}
		case '8':
		{
			delall(&tree[n]);
			cout << "Успешно!\nЧто дальше?\n>>>";
			break;
		}
		case '9':
		{
			new_tree(&tree[n]);
			print_tree(tree[n], 0);
			cout << "Успешно!\nЧто дальше?\n>>>";
			break;
		}
		case 'X':
			cout << "THE END.\n";
			break;
		default:
			printf("Неверно введена команда! Попробуй еще раз.\n >>>");
		}
	}
	c = 0; //для повторного захода в функцию необходимо засунуть туда нуль
}
void f2(tree_t **tree, int n, int m, int CtTr) {
	char c = 0;
	char *tmpw;
	//FILE *in=fopen("input.txt", "r");
	cout << "\n____________________\n"
		<< "MENU\n"
		<< "1. Объединить два дерева\n"
		<< "2. Вычесть два дерева\n"
		<< "X. EXIT\n>>>";
	int count0 = 0;
	while (c != 'X') {
		cin >> c;
		switch (c) {
		case '1':
		{
			tree[CtTr] = NULL;
			intersect_tr(tree[n], tree[m], &tree[CtTr]);
			print_tree(tree[CtTr], 0);
			count0++;
			break;
		}
		case '2':
		{
			tree[CtTr] = NULL;
			diff_tr(tree[n], tree[m], &tree[CtTr]);
			print_tree(tree[CtTr], 0);

			break;
		}
		case 'X':
			cout << "THE END.\n";
			break;
		default:
			printf("Неверно введена команда! Попробуй еще раз.\n >>>");
		}
	}
	c = 0; //для повторного захода в функцию необходимо засунуть туда нуль
}
int help_delelm(char *w, int k) {
	int n = k + 1;
	cout << "Вы имеете " << k << " элементов со значением " << w << "\nСколько нужно удалить? : ";
	cin >> n;
	while ((n > k) || (n < 0)) {
		cout << "\nОшибка! Ну-ка попробуй еще раз: ";
		cin >> n;
	}
	return n;
}
/*void clrscr(void) { Это для NetBeans.
char a[80];
printf("\033[2J");
printf("\033[0;0f");
}*/
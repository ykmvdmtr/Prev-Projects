#include "stdafx.h"

list_t* create_list() {
	list_t *lt = (list_t*)malloc(sizeof(list_t)); //�������� ������ ��� ������

	lt->root = NULL;
	/*lt->tail = lt->root;*/

	return lt;
}
int list_size(list_t *lt) { //���������� ������ ������
	list_node_t * tmproot = lt->root;
	int count = 0;
	while (lt->root) {
		lt->root = lt->root->nxt;
		count++;
	}
	lt->root = tmproot;
	return count;
}
void list_push(list_t *lt, int key) { //� ������ ������
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
int delete_node(list_t *lt, int n) { //�������� ��������
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
		else { //���� ������ ���� ������� ����������
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
void list_pop(list_t *lt) { //�������� �� ������ ������
	if (lt->root == NULL) {
		/* ������ ���� */
		cout << "List is empty(list_pop)!" << endl;
		return;
	}

	list_node_t *nd = lt->root;
	lt->root = nd->nxt;
	free(nd);

	if (lt->root == NULL) {
		//��� ��� ��������� ������� 
		lt->root = NULL;
		lt->tail = NULL;
	}
}
void read_list(list_t *lt) {
	char namef[80];
	cout << "������� �������� �����" << endl;
	fscanf(stdin, "%s", namef);
	FILE *f = fopen(namef, "r");
	if (f == NULL) { cout << "Error!(read_list)" << endl; return; }
	int x;
	while (fscanf(f, "%d", &x) != EOF)
		list_push(lt, x);
	printf("������� �������\n��� ������?\n>>>");
	fclose(f);
}
void save_list(list_t *lt) {
	char namef[80];
	cout << "������� �������� �����" << endl;
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
	cout << "����� ������� ������� � ������� ������ ����� ������?(������� ��� �����):" << endl;
	int key1, key2, size1, size2;
	cin >> key1 >> key2;
	if ((size1 = list_size(lt1))<key1 || (size2 = list_size(lt2))<key2) { cout << "���! �� ������ ������ ������ �����, ������� �� �����" << endl; return; }
	int delkey1 = delete_node(lt1, key1); //��������� �������� ���������� ��������
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
		<< "1. �������� ������\n"
		<< "2. ������� ������ ��� ������ � ���\n"
		<< "3. ������ � ����������� ��������\n"
		<< "X. EXIT\n>>>";
}
void f1(list_t **lst, int n) {
	char c;
	//FILE *in=fopen("input.txt", "r");
	cout << "\n____________________\n"
		<< "MENU\n"
		<< "1. �������� ������� � ������ ������\n"
		<< "2. ������� n-�� �������\n"
		<< "3. ������� ������ �� ����� \n"
		<< "4. ������� ������ �� �����\n"
		<< "5. ��������� ������ � ����\n"
		<< "6. ������� �� ������ ������\n"
		<< "7. �������� ������� � ����� ������\n"
		/*<<"5. ��������� � ������ �������� � �������� ������\n"   */
		<< "X. EXIT\n>>>";
	while (c != 'X') {
		cin >> c;
		switch (c) {
		case '1':
			cout << "������� �������� ����:\n>>>";
			int key;
			cin >> key;
			list_push(lst[n], key);
			cout << "�������\n��� ������?\n>>>";
			break;
		case '2':
			cout << "����� �� ����� ������� ������� �������?: ";
			int k, delelm;
			cin >> k;
			delelm = delete_node(lst[n], k);
			cout << "�������! �� ������� ������� �� ���������: " << delelm << "\n��� ������?\n>>>";
			break;
		case '3':
			read_list(lst[n]);
			break;
		case '4':
			print_list(lst[n]);
			cout << "�������!\n��� ������?\n>>>";
			break;
		case '5':
			save_list(lst[n]);
			cout << "�������!\n��� ������?\n>>>";
			break;
		case '6':
			list_pop(lst[n]);
			cout << "�������!\n��� ������?\n>>>";
			break;
		case '7':
			cout << "������� �������� ����:\n>>>";
			int key1;
			cin >> key1;
			list_push_back(lst[n], key1);
			cout << "�������!\n��� ������?\n>>>";
			break;
		case 'X':
			cout << "THE END.\n";
			break;
		default:
			printf("������� ������� �������! �������� ��� ���.\n >>>");
		}
	}
	c = 0; //��� ���������� ������ � ������� ���������� �������� ���� ����
}
void f2(list_t **lst, int n, int m, int CtLnk) {
	char c;
	cout << "\n____________________\n"
		<< "MENU\n"
		<< "1. ���������� ��� ������\n"
		<< "2. �������� k-�� ������� ������� ������ � m-�� ��������� ������� ������\n"
		<< "3. ������� ��� ������\n"
		<< "4. ����� ����������� ���� �������\n"
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
			cout << "�������!\n��� ������?\n>>>";
			break;
		}
		case '2':
		{
			change_n_m(lst[n], lst[m]);
			cout << "�������!\n��� ������?\n>>>";
			break;

		}
		case '3':
		{
			lst[CtLnk + count0] = create_list();
			dif_lists(lst[n], lst[m], lst[CtLnk + count0]);
			print_list(lst[CtLnk + count0]);
			count0++;
			cout << "�������!\n��� ������?\n>>>";
			break;
		}
		case '4':
			lst[CtLnk + count0] = create_list();
			intersection_lists(lst[n], lst[m], lst[CtLnk + count0]);
			print_list(lst[CtLnk + count0]);
			count0++;
			cout << "�������!\n��� ������?\n>>>";
			break;
		case 'X':
			cout << "THE END.\n";
			break;
		default:
			printf("������� ������� �������! �������� ��� ���.\n >>>");
		}
	}
}
void m_help(int numb, list_t **lst) {
	int i = 0;
	cout << "\n----------\n";
	for (i; i<numb; i++) {
		if (lst[i]->root)
			cout << i << " - " << i + 1 << "-�� ������" << endl;
		else
			cout << i << " - " << i + 1 << "-�� ������ (EMPTY)" << endl;
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
	list_t *lst[10]; //����� ����� ��������� ������
	char c;
	int CtLnk = 0; //������� ���������� ������

	cout << "������! �� ����������� ���������, ����������� �������� � ������������ ��������� ��������." << endl;
	Menu_prev();
	while (c != 'X') {
		cin >> c;
		switch (c) {
		case '1':
			lst[CtLnk] = create_list();
			CtLnk++; // ��������. ���-�� �������
			cout << "������� �������� ������!\n��� ������?\n>>>";
			break;
		case '2':
			if (CtLnk == 0) { cout << "��� �������! �������� ������!\n>>>"; break; }
			if (CtLnk == 1) {
				printf("�� ������ %d ������. � ����� �� ��� ����� ��������? (������ ���� � ����): ", CtLnk); m_help(CtLnk, lst);
			}
			else
				if (CtLnk>1 && CtLnk<5) {
					printf("�� ������ %d ������. � ����� �� ��� ����� ��������? (������ ���� � ����): ", CtLnk); m_help(CtLnk, lst);
				}
				else
					if (CtLnk >= 5) {
						printf("�� ������ %d �������. � ����� �� ��� ����� ��������? (������ ���� � ����): ", CtLnk); m_help(CtLnk, lst);
					}
			int n;
			cin >> n;
			if (n<0 || n>CtLnk - 1) { cout << "������. ����� ������� ���\n��� ������?\n>>>"; break; }
			cout << "�����! �������� � ���� �������\n";
			f1(lst, n);
			clrscr();
			Menu_prev();
			break;
		case '3':
			if (CtLnk == 0) { cout << "��� �������! �������� ������!\n>>>"; break; }
			cout << "� ������ �������� ����� ��������?( ��� ����� ������): \n";
			m_help(CtLnk, lst);
			int k, m;
			cin >> k >> m;
			if (k<0 || k>CtLnk - 1 || m<0 || m>CtLnk - 1) { cout << "������. ����� ������� ���\n��� ������?\n>>>"; break; }
			cout << "�����! �������� � ����� ��������\n";
			f2(lst, k, m, CtLnk);
			clrscr();
			Menu_prev();
			break;
		case 'X':
			cout << "THE END.\n";
			break;
		default:
			printf("������� ������� �������! �������� ��� ���.\n >>>");
		}
	}
	return 0;
}
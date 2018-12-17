#pragma once

typedef struct list_node { //здесь узел определяем
	int key;
	struct list_node *nxt;
} list_node_t;

typedef struct list { //здесь список определяем
	list_node_t *root; //начало списка
	list_node_t *tail; //конец списка, хотя так и не понадобилось.....
} list_t;

typedef struct Node {
	int Hash;
	int value;
} node_t;

typedef node_t* hashtable;



list_t* create_list();
int list_size(list_t *lt);
void list_push(list_t *lt, int key);;
void list_push_back(list_t *lt, int key);
list_node_t * find_node(list_t *lt, int n);
int find_key(list_t * lt, int key);
int delete_node(list_t *lt, int n);
void push_list_k(list_t * lt, int key, int k);
void print_list(list_t *lt);
void list_pop(list_t *lt);
void read_list(list_t *lt);
void save_list(list_t *lt);
void com_lists(list_t *lt1, list_t *lt2, list_t *LT);
void change_n_m(list_t * lt1, list_t * lt2);
void dif_lists(list_t *lt1, list_t * lt2, list_t * LT);
void intersection_lists(list_t * lt1, list_t *lt2, list_t *LT);

void Menu_prev();
void f1(list_t **lst, int n);
void f2(list_t **lst, int n, int m, int CtLnk);
void m_help(int numb, list_t **lst);

void clrscr(void);

#pragma once

typedef struct list_node { //здесь узел определяем
	int key;
	struct list_node *nxt;
} list_node_t;

typedef struct list { //здесь список определяем
	list_node_t *root; //начало списка
	list_node_t *tail; //конец списка, хотя так и не понадобилось.....
} list_t;



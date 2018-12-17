#pragma once

typedef struct list_node { //����� ���� ����������
	int key;
	struct list_node *nxt;
} list_node_t;

typedef struct list { //����� ������ ����������
	list_node_t *root; //������ ������
	list_node_t *tail; //����� ������, ���� ��� � �� ������������.....
} list_t;



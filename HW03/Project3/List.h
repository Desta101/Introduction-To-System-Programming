#pragma once
#ifndef __LIST__
#define __LIST__

typedef void* DATA;
typedef struct node
{
	DATA			key;
	struct node*	next;
}NODE;

typedef struct
{
	NODE head;
}LIST;

int		initList(LIST* pList);
int		printList(LIST* pList, void(*print)(const void*));
NODE*	insertList(NODE* pNode, DATA Value);
NODE*	SortInsertList(NODE* head, DATA value, int(*compareFunc)(const void*, const void*));
int		saveAirportDataToFileList(LIST* pList, void(*print)(const void*), FILE *f);
int		deleteList(NODE* pNode, void(*freeFunc)(void*));
int		freeList(LIST* pList, void(*freeFunc)(void*));

#endif
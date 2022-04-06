/*
 ============================================================================
 Name        : HW03.c
 Author      : Shimon desta 203670286 and Tal saar 209151380
 Copyright   : Your copyright notice
 Description : Airport Manager in C
 ============================================================================
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "List.h"

int initList(LIST* pList)
{
	if (pList == NULL)
		return 0;

	pList->head.next = NULL;
	return 1;
}

int printList(LIST* pList, void(*print)(const void*))
{
	NODE *tmp;
	int	c = 0;

	if (!pList)
		return 0;

	tmp = pList->head.next;
	if (tmp == NULL)
		return 0;

	while (tmp->next != NULL)
	{
		print(tmp->key);
		printf("\n");
		tmp = tmp->next;
		c++;
	}
	print(tmp->key);
	c++;

	return c;
}

NODE* insertList(NODE* pNode, DATA Value)
{
	NODE* tmp;

	if (!pNode)
		return NULL;

	tmp = (NODE*)malloc(sizeof(NODE));	

	if (tmp != NULL) {
		tmp->key = Value;
		tmp->next = pNode->next;
		pNode->next = tmp;
	}
	return tmp;
}

NODE* SortInsertList(NODE* head, DATA value, int(*compareFunc)(const void*,const void*))
{
	if (head==NULL)
		return NULL;

	NODE* helper;
	if (head->next == NULL)
		return insertList(head, value);
	
	helper = head->next;
	while (helper != NULL) 
	{
		if(compareFunc(value, helper->key) < 0) 
			return insertList(head, value);

		if (helper->next == NULL)
			break;

		if (compareFunc(value, helper->key)>0 && compareFunc(value, helper->next->key)<0) 
		{
			return insertList(helper, value);
		}

		
		helper = helper->next;
	}
	
	return insertList(helper, value);
}




int deleteList(NODE* pNode, void(*freeFunc)(void*))
{
	NODE* tmp;

	if (!pNode )
		return 0;

	tmp = pNode->next;
	if (!tmp)
		return 0;

	pNode->next = tmp->next;
	if (freeFunc != NULL)
		freeFunc(tmp->key);
	free(tmp);
	return 1;
}

int freeList(LIST* pList, void(*freeFunc)(void*))
{
	NODE *tmp;

	if (!pList) 
		return 0;
	tmp = &(pList->head);
	int res = 1;
	while (res)
	{
		res = deleteList(tmp, freeFunc);
	}

	return 1;
}


int saveAirportDataToFileList(LIST* pList, void(*print)(const void*),FILE *f )
{
	NODE *tmp;
	int	c = 0;

	if (!pList)
		return 0;

	tmp = pList->head.next;
	if (tmp == NULL)
		return 0;

	while (tmp->next != NULL)
	{
		print(tmp->key,f);
		printf("\n");
		tmp = tmp->next;
		c++;
	}
	print(tmp->key,f);
	c++;

	return c;
}
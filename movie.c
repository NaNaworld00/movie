#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movie.h"

//����ü �����ϱ� 
typedef struct movInfo {
	char name[100];
	float score;
	int runTime;
	char madeIn[10]; //���� ���� 
} movInfo_t;

void* mv_genMvInfo(char* name, float score, int runTime, char* country) //�����ͷ� �� �׸� ����ü �������ִ� �κ� 
{
	movInfo_t* mvPtr;
	mvPtr = (movInfo_t*)malloc(sizeof(movInfo_t)); //���� �Ҵ� 
	
	strcpy(mvPtr->name, name);
	mvPtr->score = score;
	mvPtr->runTime = runTime;
	strcpy(mvPtr->madeIn, country); //���ڿ� ���� 

	return (void*)mvPtr;
	
}

void printMv(void* obj) //��ȭ ��� ���� ���ϴ� �Լ� 
{
	movInfo_t* mvPtr = (movInfo_t*)obj; 
	if (mvPtr == NULL)
	{
		printf("[ERROR] failed to print the movie Info! (object is NULL)\n");
	}
	printf("Name : %s (%s)\n", mvPtr->name, mvPtr->madeIn);
	printf("running time : %i, score : %f\n", mvPtr->runTime, mvPtr->score);
	printf("----------------------------------------\n");
	
	return;
}

int mv_printAll(void* obj, void* arg) //��� ��ȭ�� ����ϴ� �Լ� 
{
	movInfo_t* mvPtr = (movInfo_t*)obj;
	printMv(mvPtr);
	return 1;
}

int mv_printScore(void* obj, void* arg) //������ ���� ��ȭ�� ����ϴ� �Լ� 
{
	movInfo_t* mvPtr = (movInfo_t*)obj;
	if ((mvPtr->score) >= (*(float*)arg)) { //�� ��ȯ 
		printMv(mvPtr);
		return 1;
	}
	return 0;
}

int mv_printRunTime(void* obj, void* arg) //�󿵽ð��� ���� ��ȭ�� ����ϴ� �Լ� 
{
	movInfo_t* mvPtr = (movInfo_t*)obj;
	if ((mvPtr->runTime) >= (*(int*)arg)) { //�� ��ȯ 
		printMv(mvPtr);
		return 1;
	}
	return 0;
}

int mv_printCountry(void* obj, void* arg) //������ ���� ��ȭ�� ����ϴ� �Լ� 
{
	movInfo_t* mvPtr = (movInfo_t*)obj;
	if (strcmp(mvPtr->madeIn, (char*)arg) == 0) { //�� ��ȯ 
		printMv(mvPtr);
		return 1;
	}
	return 0;
}





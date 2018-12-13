#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movie.h"

//구조체 정의하기 
typedef struct movInfo {
	char name[100];
	float score;
	int runTime;
	char madeIn[10]; //변수 선언 
} movInfo_t;

void* mv_genMvInfo(char* name, float score, int runTime, char* country) //포인터로 각 항목에 구조체 복사해주는 부분 
{
	movInfo_t* mvPtr;
	mvPtr = (movInfo_t*)malloc(sizeof(movInfo_t)); //동적 할당 
	
	strcpy(mvPtr->name, name);
	mvPtr->score = score;
	mvPtr->runTime = runTime;
	strcpy(mvPtr->madeIn, country); //문자열 복사 

	return (void*)mvPtr;
	
}

void printMv(void* obj) //영화 출력 형태 정하는 함수 
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

int mv_printAll(void* obj, void* arg) //모든 영화를 출력하는 함수 
{
	movInfo_t* mvPtr = (movInfo_t*)obj;
	printMv(mvPtr);
	return 1;
}

int mv_printScore(void* obj, void* arg) //평점에 따라 영화를 출력하는 함수 
{
	movInfo_t* mvPtr = (movInfo_t*)obj;
	if ((mvPtr->score) >= (*(float*)arg)) { //형 변환 
		printMv(mvPtr);
		return 1;
	}
	return 0;
}

int mv_printRunTime(void* obj, void* arg) //상영시간에 따라 영화를 출력하는 함수 
{
	movInfo_t* mvPtr = (movInfo_t*)obj;
	if ((mvPtr->runTime) >= (*(int*)arg)) { //형 변환 
		printMv(mvPtr);
		return 1;
	}
	return 0;
}

int mv_printCountry(void* obj, void* arg) //국가에 따라 영화를 출력하는 함수 
{
	movInfo_t* mvPtr = (movInfo_t*)obj;
	if (strcmp(mvPtr->madeIn, (char*)arg) == 0) { //형 변환 
		printMv(mvPtr);
		return 1;
	}
	return 0;
}





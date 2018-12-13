#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movie.h"
#include "linkedList.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) { 
	
	FILE *fp; //영화 정보를 읽어오기 위한 포인터 선언 
	char name[200]; //영화명 변수 선언  
	char country[10]; //국가명 변수 선언  
	int runTime; //상영시간 변수 선언 
	float score; //영화 평점 변수 선언 
	
	int exit_flag = 0; //while 순환에 사용되는 플래그 변수 선언  
	int option; //사용자 선택 메뉴 옵션 변수 선언  
	void *list, *mvInfo; //영화 정보와 Linkedlist를 위한 포인터 선언 
	int (*repFunc)(void* obj, void* arg); //list_repeatFunc()를 사용하기 위한 포인터 선언  
	void *arg; //argument를 사용하기 위한 포인터 선언  
	int cnt; //정수 변수 선언 (영화 수 세기 위함) 

	//1. movie.dat 파일 읽기-----------------------------
	//1.1 파일 열기 
	fp = fopen("movie.dat", "r");
	printf("Reading the data files......\n");
	//1.2 목록 정리 
	list = list_genList();
	//1.3 파일에서 영화 정보를 각각 읽어와서 linkedlist에 입력 
	while (fscanf(fp, "%s %s %d %f", name,country,&runTime,&score) !=EOF) //End Of File - 파일의 끝 의미 
	{	
	    mvInfo = mv_genMvInfo(name,score,runTime,country); //영화 정보 정리 
		list_addTail(mvInfo, list);
	}
	printf("Read done!");
	printf("%i items are read\n\n\n", list_len(list));

	//1.4 파일 닫기 
	fclose(fp);
	//2. 프로그램 실행하기 
	while(exit_flag == 0)
	{
		//2.1 메뉴를 출력하고 메뉴 선택 입력받기 
		printf("-------------------- Menu --------------------\n");
		printf("1. print all the movies\n");
		printf("2. search for specific country movies\n");
		printf("3. search for specific runtime movies\n");
		printf("4. search for specific score movies\n");
		printf("5. exit\n");
		printf("-------------------- Menu --------------------\n");
		printf(" -- select an option : ");
		scanf("%d", &option);
		
		switch(option)
		{
			case 1: //모든 영화 출력하기 
				printf("\nprinting all the movies in the list.....\n\n\n");
				printf("----------------------------------------\n");
				repFunc = mv_printAll;
				arg = NULL; //arg - 구조체를 불러오는 조건 
				cnt = list_repeatFunc(repFunc, arg, list); //cnt - 출력된 영화의 수 계산 
		        printf("\n\n    - totally %i movies are listed!\n\n\n", cnt);
				break;
				
			case 2: //특정 나라의 영화 출력하기 
			    printf(" -- select a country : ");
			    arg = country;
			    scanf("%s", country);
			    printf("----------------------------------------\n");
                repFunc = mv_printCountry;
                cnt = list_repeatFunc(repFunc, arg, list);
		        printf("\n\n    - totally %i movies are listed!\n\n\n", cnt);
				break;
				
			case 3: //입력한 값보다 긴 상영시간을 가진 영화 출력하기 
                printf(" -- lowest runtime : ");
                arg = &runTime;
                scanf("%d", &runTime);
                printf("----------------------------------------\n");
                repFunc = mv_printRunTime;
                cnt = list_repeatFunc(repFunc, arg, list);
	        	printf("\n\n    - totally %i movies are listed!\n\n\n", cnt);
				break;
				
			case 4: //입력한 값보다 높은 평점을 받은 영화 출력하기 
				printf(" -- lowest score : ");
				arg = &score;
				scanf("%f", &score);
				printf("----------------------------------------\n");
				repFunc = mv_printScore;
				cnt = list_repeatFunc(repFunc, arg, list);
		        printf("\n\n    - totally %i movies are listed!\n\n\n", cnt);
				break;
				
			case 5: //실행 마침 
				printf("\n\nBye!\n\n");
				exit_flag = 1;
				
				break;
				
			default: //에러가 났을 때  
				printf("wrong command! input again\n");
				break;
		}
	}
	
	return 0;
}


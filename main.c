#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movie.h"
#include "linkedList.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) { 
	
	FILE *fp; //��ȭ ������ �о���� ���� ������ ���� 
	char name[200]; //��ȭ�� ���� ����  
	char country[10]; //������ ���� ����  
	int runTime; //�󿵽ð� ���� ���� 
	float score; //��ȭ ���� ���� ���� 
	
	int exit_flag = 0; //while ��ȯ�� ���Ǵ� �÷��� ���� ����  
	int option; //����� ���� �޴� �ɼ� ���� ����  
	void *list, *mvInfo; //��ȭ ������ Linkedlist�� ���� ������ ���� 
	int (*repFunc)(void* obj, void* arg); //list_repeatFunc()�� ����ϱ� ���� ������ ����  
	void *arg; //argument�� ����ϱ� ���� ������ ����  
	int cnt; //���� ���� ���� (��ȭ �� ���� ����) 

	//1. movie.dat ���� �б�-----------------------------
	//1.1 ���� ���� 
	fp = fopen("movie.dat", "r");
	printf("Reading the data files......\n");
	//1.2 ��� ���� 
	list = list_genList();
	//1.3 ���Ͽ��� ��ȭ ������ ���� �о�ͼ� linkedlist�� �Է� 
	while (fscanf(fp, "%s %s %d %f", name,country,&runTime,&score) !=EOF) //End Of File - ������ �� �ǹ� 
	{	
	    mvInfo = mv_genMvInfo(name,score,runTime,country); //��ȭ ���� ���� 
		list_addTail(mvInfo, list);
	}
	printf("Read done!");
	printf("%i items are read\n\n\n", list_len(list));

	//1.4 ���� �ݱ� 
	fclose(fp);
	//2. ���α׷� �����ϱ� 
	while(exit_flag == 0)
	{
		//2.1 �޴��� ����ϰ� �޴� ���� �Է¹ޱ� 
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
			case 1: //��� ��ȭ ����ϱ� 
				printf("\nprinting all the movies in the list.....\n\n\n");
				printf("----------------------------------------\n");
				repFunc = mv_printAll;
				arg = NULL; //arg - ����ü�� �ҷ����� ���� 
				cnt = list_repeatFunc(repFunc, arg, list); //cnt - ��µ� ��ȭ�� �� ��� 
		        printf("\n\n    - totally %i movies are listed!\n\n\n", cnt);
				break;
				
			case 2: //Ư�� ������ ��ȭ ����ϱ� 
			    printf(" -- select a country : ");
			    arg = country;
			    scanf("%s", country);
			    printf("----------------------------------------\n");
                repFunc = mv_printCountry;
                cnt = list_repeatFunc(repFunc, arg, list);
		        printf("\n\n    - totally %i movies are listed!\n\n\n", cnt);
				break;
				
			case 3: //�Է��� ������ �� �󿵽ð��� ���� ��ȭ ����ϱ� 
                printf(" -- lowest runtime : ");
                arg = &runTime;
                scanf("%d", &runTime);
                printf("----------------------------------------\n");
                repFunc = mv_printRunTime;
                cnt = list_repeatFunc(repFunc, arg, list);
	        	printf("\n\n    - totally %i movies are listed!\n\n\n", cnt);
				break;
				
			case 4: //�Է��� ������ ���� ������ ���� ��ȭ ����ϱ� 
				printf(" -- lowest score : ");
				arg = &score;
				scanf("%f", &score);
				printf("----------------------------------------\n");
				repFunc = mv_printScore;
				cnt = list_repeatFunc(repFunc, arg, list);
		        printf("\n\n    - totally %i movies are listed!\n\n\n", cnt);
				break;
				
			case 5: //���� ��ħ 
				printf("\n\nBye!\n\n");
				exit_flag = 1;
				
				break;
				
			default: //������ ���� ��  
				printf("wrong command! input again\n");
				break;
		}
	}
	
	return 0;
}


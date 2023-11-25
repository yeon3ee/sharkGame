//
// board.c
// sharkGame
//
// Created by CheyeonPark on 2023/11/21~2023/11/23.
//

#include <stdio.h>
#include <stdlib.h>
#include "board.h"

//board_status���� 
#define N_BOARD			15
//coin ���� 
#define N_COINPOS		12
#define MAX_COIN		4
//shark ����
#define MAX_SHARKSTEP		6
#define SHARK_INITPOS		-4 

#define N_PLAYER		3
#define MAX_DIE		6
#define N_BOARD		15 
 

//��������
//static�� int�տ� ��־� �ٸ� ���Ͽ��� ������ �� ������ ���� 
static int board_status[N_BOARD];//ĭ�� �ļտ���  
static int board_coin[N_BOARD];//���� 

static int board_sharkPosition;//��� ��ġ 

//���� �ʱ�ȭ  
int board_initBoard(void)
{
	int i;
	for(i=0;i<N_BOARD;i++)
	{
		board_status[i]=BOARDSTATUS_OK;
		board_coin[i]=0;	
	}
	
	board_sharkPosition=SHARK_INITPOS;
	
	for(i=0;i<N_COINPOS;i++)
	{
		int flag=0;
		while(flag==0)
		{
			int allocPos=rand()%N_BOARD;
			if(board_coin[allocPos]==0)
			{
				board_coin[allocPos]=rand()%MAX_COIN+1;
				flag=1;
			}
		}
	}
	return 0;
}
//������ ���� ��� 
int board_printBoardStatus(void)
{
	int i;
	
	printf("-------------------- BOARD STATUS --------------------\n");
	for(i=0;i<N_BOARD;i++)
	{
		printf("|");
		if(board_status[i]==BOARDSTATUS_NOK)
			printf("X");
		else
			printf("O");
	}
	printf("|\n");
	printf("-----------------------------------------------------\n");
	return 0;
}



//Ư�� ĭ �ļ� ����print 
int board_getBoardStatus(int pos)
{
	return board_status[pos];
	
}
int board_getBoardCoin(int pos)
{
    int coin = board_coin[pos];

    // �����ϰ� ������ �ֱ�� ����
    if (coin == 0 || (rand() % 4 == 0)) {
        int newCoin = rand() % MAX_COIN + 1;  // ������ ������ ����
        board_coin[pos] = newCoin;
        return newCoin;
    }

    board_coin[pos] = 0;  // ������ ���� �ʴ� ���
    return coin;
}
//��� ��ġ 
int board_getSharkPosition(void);
//��� ���� 
int board_stepShark(void)
{ 
	int step=rand()% MAX_SHARKSTEP+1;
	int i;
	for(i=board_sharkPosition+1;i<=board_sharkPosition+step;i++)
	{
		if(i>=0 && i<N_BOARD)
		board_status[i]=BOARDSTATUS_NOK;
	}
	
	board_sharkPosition +=step;
	
	return board_sharkPosition;
	
}

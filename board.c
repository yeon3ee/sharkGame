//
// board.c
// sharkGame
//
// Created by CheyeonPark on 2023/11/21~2023/11/23.
//

#include <stdio.h>
#include <stdlib.h>
#include "board.h"

//board_status정의 
#define N_BOARD			15
//coin 정의 
#define N_COINPOS		12
#define MAX_COIN		4
//shark 정의
#define MAX_SHARKSTEP		6
#define SHARK_INITPOS		-4 

#define N_PLAYER		3
#define MAX_DIE		6
#define N_BOARD		15 
 

//변수정의
//static을 int앞에 써넣어 다른 파일에서 접근할 수 없도록 제한 
static int board_status[N_BOARD];//칸의 파손여부  
static int board_coin[N_BOARD];//코인 

static int board_sharkPosition;//상어 위치 

//보드 초기화  
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
//보드판 상태 출력 
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



//특정 칸 파손 여부print 
int board_getBoardStatus(int pos)
{
	return board_status[pos];
	
}
int board_getBoardCoin(int pos)
{
    int coin = board_coin[pos];

    // 랜덤하게 코인을 주기로 결정
    if (coin == 0 || (rand() % 4 == 0)) {
        int newCoin = rand() % MAX_COIN + 1;  // 랜덤한 코인을 생성
        board_coin[pos] = newCoin;
        return newCoin;
    }

    board_coin[pos] = 0;  // 코인을 주지 않는 경우
    return coin;
}
//상어 위치 
int board_getSharkPosition(void);
//상어 전진 
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

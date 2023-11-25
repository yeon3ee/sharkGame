//
// main.c
// sharkGame
//
// Created by CheyeonPark on 2023/11/21.~2023/11/23. 
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h "//������ �����Ƿ� board.hȣ���� �����ϵ��� ������Ÿ����. 

#define MAX_CHARNAME		200
#define N_PLAYER		3
#define MAX_DIE		6
#define N_BOARD		15 
#define MAX_COIN_PER_BOARD		5
//player ���� 
#define N_PLAYER		3
#define PLAYERSTATUS_LIVE		0
#define PLAYERSTATUS_DIE		1
#define PLAYERSTATUS_END		2//���ڴ� ���� �ٸ��Ը� �����Ǹ� ��. 

int player_position[N_PLAYER];
char player_name[N_PLAYER][MAX_CHARNAME];
int player_coin[N_PLAYER];
int player_status[N_PLAYER]; //0-live, 1-die, 2-end
char player_statusString[3][MAX_CHARNAME] = {"LIVE","DIE","END"};


void opening(void)
{
	printf("==========================================================\n");
	printf("**********************************************************\n");
	printf("                  Happy SharkGame                 \n");
	printf("                Who is the Winner!!                \n");
	printf("**********************************************************\n");
	printf("==========================================================\n\n\n");

}

int rolldie(void)
{
	return rand()%MAX_DIE+1;
}

int game_end(void)
{
    int i;
    int flag_end=1;
    
    for (i = 0; i < N_PLAYER; i++)
    {
        if (player_status[i] == PLAYERSTATUS_LIVE)
        {
            flag_end=0;
			break;// Game is not over, at least one player is alive
        }
    }
    return flag_end; // Game is over, all players are either dead or have reached the end
}

int getAlivePlayer(void)
{
    int i;
    int cnt = 0;
    for (i = 0; i < N_PLAYER; i++)
    {
        if (player_status[i] == PLAYERSTATUS_END)
            cnt++;
    }
    return cnt;
}

char *getWinner(void)
{
    int i;
    int winner = 0;
    int max_coin = -1;

    for (i = 0; i < N_PLAYER; i++)
    {
        if (player_status[i] == PLAYERSTATUS_LIVE && player_coin[i] > max_coin)
        {
            max_coin = player_coin[i];
            winner = i;
        }
    }

    return player_name[winner];
}


void printPlayerPosition(int player)

{ 
	int i;
	for(i=0;i<N_BOARD;i++)
	{
		printf("|");
		if(i==player_position[player])
			printf("%c", player_name[player][0]);
		else
		{
			
			if(board_getBoardStatus(i)==BOARDSTATUS_NOK)
			printf("X");
			else
			printf(" ");
		}
	}
	printf("|\n");
	
}

void printPlayerStatus(void)
{ 
	int i=0;
	printf("-----------player status -----------\n");
	for(i=0;i<N_PLAYER;i++)
	{
		 printf("%s : pos %i, coin %i, status %s\n", player_name[i], player_position[i], player_coin[i],
		 	player_statusString[player_status[i]]);
		printPlayerPosition(i);
	}
	printf("------------------------------------\n");
}
void checkDie(void)
{ 
	int i;
	for(i=0;i<N_PLAYER;i++)
		if(board_getBoardStatus(player_position[i]) == BOARDSTATUS_NOK)
			player_status[i]=PLAYERSTATUS_DIE;
}

int main(int argc, char *argv[]) {
	int pos=0;
	int turn=0;
	int i;
	srand((unsigned)time(NULL));
	
	//0.opening
	opening(); //���� opening�Լ� ȣ��  
	//1. board �ʱ�ȭ&�÷��̾� �̸� ���� 
	board_initBoard();
	//2-1. �÷��̾��� ���� ���
	
	   
	//1-2: initialize player
	for(i=0;i<N_PLAYER;i++) 
	{
		player_position[i]=0;
		player_coin[i]=0;
		player_status[i]=PLAYERSTATUS_LIVE;
		printf("Player %i's name:",i);
		scanf("%s",player_name[i]);
	}
	//2. �ݺ���(�÷��̾� ��)
	do{
		int step=rolldie();
		int coinResult;
		char c;
		
		if(player_status[turn] != PLAYERSTATUS_LIVE)
		{
			turn=(turn+1)%N_PLAYER;
			continue;
		}
		
	
	   //2-1. ����&�÷��̾��� ���� ���
	   board_printBoardStatus();
	   for(i=0;i<N_PLAYER;i++)
	   		printPlayerPosition(i);
	   printPlayerStatus();
	   
	   //2-2. �ֻ��� ������
		printf("%s turn!!",player_name[turn]);
		printf("press any key to roll a die!");
		scanf("%d",&c); //���ӿ� ���� ������ ÷��. �ְŴ� �ްŴ� ���� ÷��  //�Է¹޾Ƽ� Ȱ������ ���� 
		fflush(stdin); //����½ÿ� ���ۿ���.  //���� fflush.  
		step=rolldie();
		
		board_printBoardStatus();
		
	   //2-3. �̵�
	   player_position[turn]+=step; 
	   
	   if(player_position[turn]>=N_BOARD)
	   {
	   	player_position[turn]=N_BOARD-1;
	   }
	   
	   if(player_position[turn]==N_BOARD-1)
	   		{
	   			player_status[turn]=PLAYERSTATUS_END;
	   			printf("player %s reached to the end!! (coin :%d)\n",  player_name[turn], player_coin[turn]);
			}
		printf("Die result : %d, player moved to %d!\n", step, player_position[turn]);
	   		
	   
	   //2-4. �����ݱ�
	   coinResult=board_getBoardCoin(player_position[turn]);
	   if(coinResult>0)
	   {
	   	player_coin[turn]+=coinResult;
	   	printf("-> Lucky! %s got %i coins \n",player_name[turn],coinResult);
	   }
       else
       	printf("-> No coins at this location!\n");
	   //2-5. ������
	   turn = (turn + 1) % N_PLAYER;
	   //turn+1�� �ȵ�. �÷��̾���� ���Ѵ�� �þ�Ե�. 0.1.2�� �ݺ��� �� �ְ� %N_PLAYER���� (wrap around)
	   //2-6. if(����: ��� �÷��̾ �ѹ��� ���� ��)
	   if(turn==0)
	   {
	   	//���� 
	   	int shark_pos=board_stepShark();
	   	printf("Shark moved to %i\n", shark_pos);
	   	//check die
	   	checkDie();
	   	 
	   }
	   		
	} while(!game_end());
	//3. ����(���� ���, ��� ��) 
	int alivePlayers=getAlivePlayer();
	char *winner = getWinner();
	
	printf("!!Game End!!\n"); //�������� 
	printf("%d players are alive!\n",alivePlayers); //������ ��� 
	printf("Winner is player %s\n", winner); //���� ��� 
	
	
	return 0;	
}


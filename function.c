#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include <math.h>
#include <time.h>
#include "interface.h"
#include "function.h"
#include "game.h"

//�����Զ�����׵�����
void doClickBox2(void){
	nowpage=1;
	firstClick=1;
	gameOver=FALSE; 
	toWhite();
	
	OpenConsole();
	
	while(1){
		printf("����������������.[9-%d]",Maxgridx);
		scanf("%d",&gridx);
		if(gridx>=9&&gridx<=Maxgridx) break;
		printf("������9-%d�ĺ��������\n",Maxgridx);
	}
	
	while(1){
		printf("�����������������.[9-%d]",Maxgridy);
		scanf("%d",&gridy);
		if(gridy>=9&&gridy<=Maxgridy) break;
		printf("������9-%d�����������\n",Maxgridy);
	}
	
	while(1){
		printf("��������Ҫ�ڷŵĵ�������.");
		scanf("%d",&mine); 
		if(mine>=gridx*gridy/8&&mine<=gridx*gridy/4) break;
		if(mine<gridx*gridy/8) printf("����ĵ�����������.\n");
		else printf("����ĵ�����������.\n");
	}
	CloseConsole();
	thex=ww/7*5.5;
	they=wh/2+(double)gridy/2*bw+1.7*bw;
	n=0; 
	howMangFlag=mine;
	
	gameBackGround();	
	
}

//����˵����Ϸ���� 
void doClickBox3(void){
	OpenConsole();
	printf("ʤ������������Ҫ�ڲ�����׵�����¾����ܿ�Ľ����е��׶���ǳ�������������͵����¿�ʼ������ɨ��Ҳ��һ���������ɷ֡�\n\n");
	printf("��β��������������һ���Ҽ���ǵ��ף�˫��������������Ҽ�һ��㣩���Կ���������ֵĿɵ����Χ��\n");
	printf("������һ�����֣���1����˵������Χ��8�ĸ�������1���ף���2���������ף���3���������ס������Դ����ơ�\n");
	printf("������������Χ����ȫɨ�����пո񣬲�����һ��һ�񷭿���ֱ��˫������Ϳ����ˡ���������Ǵ����ף��Ǿͻ�boom!һ�����¿�ʼ��\n");
	printf("\n����س����������ҳ��.\n");
	char ch;
	while((ch=getchar())!='\n');
	CloseConsole(); 
}

//������ʾ���а�
void doClickBox4(void){
	;
}

//���ڿ�ʼ�����Ѷ� 
void doClickBox6(void){
	nowpage=1;
	firstClick=1;
	gameOver=FALSE;
	toWhite();
	mine=10;
	gridx=gridy=9;
	howMangFlag=mine;
	thex=ww/7*5.5;
	they=wh/2+(double)gridy/2*bw+1.7*bw;
	n=0;
	gameBackGround(); 
}

//���ڿ�ʼ�м��Ѷ�
void doClickBox7(void){
	nowpage=1;
	firstClick=1;
	gameOver=FALSE;
	toWhite();
	mine=40;
	howMangFlag=mine;
	gridx=gridy=16;
	thex=ww/7*5.5;
	they=wh/2+(double)gridy/2*bw+1.7*bw;
	n=0;
	gameBackGround();
}

//���ڿ�ʼ�߼��Ѷ�
void doClickBox8(void){
	nowpage=1;
	firstClick=1;
	gameOver=FALSE;
	toWhite();
	mine=99;
	howMangFlag=mine;
	gridx=30;
	gridy=16;
	thex=ww/7*5.5;
	they=wh/2+(double)gridy/2*bw+1.7*bw;
	n=0;
	gameBackGround();
}

//���ڱ�ʾ�ؿ��˾�
void doRestartPageOne(void){
	cancelTimer(TIMER_BLINK1000);
	firstClick=1;
	nowpage=1;
	gameOver=FALSE;
	thex=ww/7*5.5;
	they=wh/2+(double)gridy/2*bw+1.7*bw;
	n=0;
	howMangFlag=mine;
	initAllBox();
	toWhite();
	gameBackGround();
	initArray();
} 

//���ڷ��س�ʼ����
void doRestartPageZero(void){
	doRestartPageOne();
	cancelTimer(TIMER_BLINK1000);
	toWhite();
	initGlobalVariable();
	initInterface();
} 

//���ڱ�ʾ��һ�ε����Ϸ��ʼ
void gameStart(void){
	initArray();
	firstClick=0;
	startTimer(TIMER_BLINK1000,mseconds1000);
} 

//��ʾ����Ҽ���� 
void rightclick(void){
	if(ud[arrayx][arrayy]==1) return;
	
	if(thingup[arrayx][arrayy]==0){
		if(howMangFlag==0){
			return;
		}
		howMangFlag--;
		MJKNumber(ww/7,wh/2+(double)gridy/2*bw+1.7*bw,howMangFlag);
		thingup[arrayx][arrayy]=1;
		if(howMangFlag==0) stopGame(judgeWinOrLose());
	}
	else if(thingup[arrayx][arrayy]==1){
		thingup[arrayx][arrayy]=2;
		howMangFlag++;
		MJKNumber(ww/7,wh/2+(double)gridy/2*bw+1.7*bw,howMangFlag);
	}
	else if(thingup[arrayx][arrayy]==2){
		thingup[arrayx][arrayy]=0;
	}
	oneBoxToWhite(arrayx,arrayy);
	unClickBox(arrayx,arrayy,thingup[arrayx][arrayy]);
} 

//���������
void leftclick(void){
	if(thingunder[arrayx][arrayy]==-1) stopGame(0); //���е���ֱ������ 
	
	changeNowArray();
	
	stopGame(judgeWinOrLose());
} 

//������˫�� 
void doubleclick(void){
	if(ud[arrayx][arrayy]==0) return;
	if(thingunder[arrayx][arrayy]==0) return;
	
	int count=0;
	if(wo(arrayx-1,arrayy-1)&&thingup[arrayx-1][arrayy-1]==1) count++;
	if(wo(arrayx-1,arrayy)&&thingup[arrayx-1][arrayy]==1) count++;
	if(wo(arrayx-1,arrayy+1)&&thingup[arrayx-1][arrayy+1]==1) count++;
	if(wo(arrayx,arrayy-1)&&thingup[arrayx][arrayy-1]==1) count++;
	if(wo(arrayx,arrayy+1)&&thingup[arrayx][arrayy+1]==1) count++;
	if(wo(arrayx+1,arrayy-1)&&thingup[arrayx+1][arrayy-1]==1) count++;
	if(wo(arrayx+1,arrayy)&&thingup[arrayx+1][arrayy]==1) count++;
	if(wo(arrayx+1,arrayy+1)&&thingup[arrayx+1][arrayy+1]==1) count++;
	
	if(count==thingunder[arrayx][arrayy]){
		int savex=arrayx,savey=arrayy;
		
		if(wo(arrayx-1,arrayy-1)&&ud[arrayx-1][arrayy-1]==0&&thingup[arrayx-1][arrayy-1]==0){
			arrayx--;arrayy--;
			leftclick();
		}
		arrayx=savex;arrayy=savey;
		
		if(wo(arrayx-1,arrayy)&&ud[arrayx-1][arrayy]==0&&thingup[arrayx-1][arrayy]==0){
			arrayx--;
			leftclick();
		}
		arrayx=savex;arrayy=savey;
		
		if(wo(arrayx-1,arrayy+1)&&ud[arrayx-1][arrayy+1]==0&&thingup[arrayx-1][arrayy+1]==0){
			arrayx--;arrayy++;
			leftclick();
		}
		arrayx=savex;arrayy=savey;
		
		if(wo(arrayx,arrayy-1)&&ud[arrayx][arrayy-1]==0&&thingup[arrayx][arrayy-1]==0){
			arrayy--;
			leftclick();
		}
		arrayx=savex;arrayy=savey;
		
		if(wo(arrayx,arrayy+1)&&ud[arrayx][arrayy+1]==0&&thingup[arrayx][arrayy+1]==0){
			arrayy++;
			leftclick();
		}
		arrayx=savex;arrayy=savey;
		
		if(wo(arrayx+1,arrayy-1)&&ud[arrayx+1][arrayy-1]==0&&thingup[arrayx+1][arrayy-1]==0){
			arrayx++;arrayy--;
			leftclick();
		}
		arrayx=savex;arrayy=savey;
		
		if(wo(arrayx+1,arrayy)&&ud[arrayx+1][arrayy]==0&&thingup[arrayx+1][arrayy]==0){
			arrayx++;
			leftclick();
		}
		arrayx=savex;arrayy=savey;
		
		if(wo(arrayx+1,arrayy+1)&&ud[arrayx+1][arrayy+1]==0&&thingup[arrayx+1][arrayy+1]==0){
			arrayx++;arrayy++;
			leftclick();
		}
		arrayx=savex;arrayy=savey;
	}
}











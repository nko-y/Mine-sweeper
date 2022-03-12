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

//用于自定义地雷的数量
void doClickBox2(void){
	nowpage=1;
	firstClick=1;
	gameOver=FALSE; 
	toWhite();
	
	OpenConsole();
	
	while(1){
		printf("请输入横向格子总数.[9-%d]",Maxgridx);
		scanf("%d",&gridx);
		if(gridx>=9&&gridx<=Maxgridx) break;
		printf("请输入9-%d的横向格子数\n",Maxgridx);
	}
	
	while(1){
		printf("请输入纵向格子总数.[9-%d]",Maxgridy);
		scanf("%d",&gridy);
		if(gridy>=9&&gridy<=Maxgridy) break;
		printf("请输入9-%d的纵向格子数\n",Maxgridy);
	}
	
	while(1){
		printf("请输入需要摆放的地雷数量.");
		scanf("%d",&mine); 
		if(mine>=gridx*gridy/8&&mine<=gridx*gridy/4) break;
		if(mine<gridx*gridy/8) printf("输入的地雷数量过少.\n");
		else printf("输入的地雷数量过多.\n");
	}
	CloseConsole();
	thex=ww/7*5.5;
	they=wh/2+(double)gridy/2*bw+1.7*bw;
	n=0; 
	howMangFlag=mine;
	
	gameBackGround();	
	
}

//用于说明游戏规则 
void doClickBox3(void){
	OpenConsole();
	printf("胜利条件：你需要在不点错雷的情况下尽可能快的将所有的雷都标记出来，如果你点错，就得重新开始，所以扫雷也有一定的运气成分。\n\n");
	printf("如何操作：左键翻开这一格，右键标记地雷，双击左键（或者左右键一起点）可以看到这个数字的可点击范围，\n");
	printf("你点出了一个数字，是1，就说明它周围的8的格子里有1个雷，是2就有两个雷，是3就有三个雷···以此类推。\n");
	printf("如果你把数字周围的雷全扫出后还有空格，不必再一格一格翻开，直接双击左键就可以了。但如果你标记错了雷，那就会boom!一切重新开始。\n");
	printf("\n输入回车键结束这个页面.\n");
	char ch;
	while((ch=getchar())!='\n');
	CloseConsole(); 
}

//用于显示排行榜
void doClickBox4(void){
	;
}

//用于开始初级难度 
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

//用于开始中级难度
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

//用于开始高级难度
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

//用于表示重开此局
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

//用于返回初始界面
void doRestartPageZero(void){
	doRestartPageOne();
	cancelTimer(TIMER_BLINK1000);
	toWhite();
	initGlobalVariable();
	initInterface();
} 

//用于表示第一次点击游戏开始
void gameStart(void){
	initArray();
	firstClick=0;
	startTimer(TIMER_BLINK1000,mseconds1000);
} 

//表示鼠标右键点击 
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

//鼠标左键点击
void leftclick(void){
	if(thingunder[arrayx][arrayy]==-1) stopGame(0); //点中地雷直接算输 
	
	changeNowArray();
	
	stopGame(judgeWinOrLose());
} 

//鼠标左键双击 
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











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

void introduction(void){
	OpenConsole();
	
	printf("声明：此版本还未完善排行榜&&由于左键双击库函数无法使用，这个功能虽然实现但不能使用.\n");
	
	printf("请输入您的用户名(虽然现在并没有什么用....)并以回车结尾：");
	
	scanf("%s",username); 
	
	CloseConsole();
}

void toWhite(void){
	SetEraseMode(TRUE);
	MovePen(0,0);
	StartFilledRegion(1);
	DrawLine(ww,0);
	DrawLine(0,wh);
	DrawLine(-ww,0);
	DrawLine(0,-wh);
	EndFilledRegion();
	SetEraseMode(FALSE);
} 

void drawStartBox(double x,double y,double len,double height,double t){
	MovePen(x,y);
	DefineColor("firstcolor",102.0/256,102.0/256,102.0/256);
	DefineColor("secondcolor",234.0/256,234.0/256,234.0/256);
	SetPenColor("secondcolor");
	StartFilledRegion(1);
	DrawLine(0,height);
	DrawLine(len,0);
	DrawLine(-height/t,-height/t);
	DrawLine(-len+(height/t*2),0);
	DrawLine(0,-height+(height/t*2));
	DrawLine(-height/t,-height/t);
	EndFilledRegion();
	
	MovePen(x,y);
	SetPenColor("firstcolor");
	StartFilledRegion(1);
	DrawLine(len,0);
	DrawLine(0,height);
	DrawLine(-height/t,-height/t);
	DrawLine(0,-height+(height/t*2));
	DrawLine(-len+(height/t*2),0);
	DrawLine(-height/t,-height/t);
	EndFilledRegion();
}

void drawDownBox(double x,double y,double len,double height,double t){
	MovePen(x,y);
	DefineColor("firstcolor",102.0/256,102.0/256,102.0/256);
	DefineColor("secondcolor",234.0/256,234.0/256,234.0/256);
	SetPenColor("firstcolor");
	StartFilledRegion(1);
	DrawLine(0,height);
	DrawLine(len,0);
	DrawLine(-height/t,-height/t);
	DrawLine(-len+(height/t*2),0);
	DrawLine(0,-height+(height/t*2));
	DrawLine(-height/t,-height/t);
	EndFilledRegion();
	
	MovePen(x,y);
	SetPenColor("secondcolor");
	StartFilledRegion(1);
	DrawLine(len,0);
	DrawLine(0,height);
	DrawLine(-height/t,-height/t);
	DrawLine(0,-height+(height/t*2));
	DrawLine(-len+(height/t*2),0);
	DrawLine(-height/t,-height/t);
	EndFilledRegion();
}

void drawtitle(double x,double y){
	drawDownBox(x-ww*0.05,y-wh*0.05,0.43*ww,0.25*wh,12);
	MovePen(x,y);
	SetPenSize(10);
	DefineColor("titlecolor",102.0/256,102.0/256,102.0/256);
	SetPenColor("titlecolor");
	DrawLine(0,0.15*wh);
	DrawLine(0.05*ww,-0.13*wh);
	DrawLine(0.05*ww,0.13*wh);
	DrawLine(0,-0.15*wh);
	MovePen(x+0.11*ww,y);
	DrawTextString(" i n e");
	
	MovePen(x+0.2*ww,y);
	DrawLine(0.06*ww,0);
	DrawLine(0,0.075*wh);
	DrawLine(-0.06*ww,0);
	DrawLine(0,0.075*wh);
	DrawLine(0.06*ww,0);
	MovePen(x+0.27*ww,y);
	DrawTextString(" w e e p e r"); 
	
}

void initInterface(void){
	//画背景
	DefineColor("background",192.0/256,192.0/256,192.0/256);
	SetPenColor("background");
	StartFilledRegion(1);
	DrawLine(ww,0);
	DrawLine(0,wh);
	DrawLine(-ww,0);
	DrawLine(0,-wh);
	EndFilledRegion();
	
	//画开始按钮 
	drawStartBox(box1x,box1y,boxw,boxh,7);
	SetPenColor("black");
	MovePen(box1x+0.3*boxw,box1y+0.4*boxh);
	DrawTextString("开 始"); 
	
	//画自定义按钮
	drawStartBox(box2x,box2y,boxw,boxh,7);
	SetPenColor("black");
	MovePen(box2x+0.25*boxw,box2y+0.4*boxh);
	DrawTextString("自定义");
	//画排行游戏规则 
	drawStartBox(box3x,box3y,boxw,boxh,7);
	SetPenColor("black");
	MovePen(box3x+0.2*boxw,box3y+0.4*boxh);
	DrawTextString("游戏规则");
	
	//画游戏排行榜 
	drawStartBox(box4x,box4y,boxw,boxh,7);
	SetPenColor("black");
	MovePen(box4x+0.25*boxw,box4y+0.4*boxh);
	DrawTextString("排行榜");
	
	//扫雷大标题
	drawtitle(0.05*ww,0.8*wh);
	
	SetPenSize(1);
	SetPenColor("black");
}


void initGlobalVariable(void){
	//界面的全局变量 
	username=(char*)malloc(sizeof(char)*100); 
	ww=GetWindowWidth();
	wh=GetWindowHeight();
	box1x=box3x=ww/16*8;box2x=box4x=ww/16*6;
	box1y=wh*0.55;box2y=wh*0.4;box3y=wh*0.25;box4y=wh/10;
	boxw=ww/8;
	boxh=wh/10;
	nowpage = 0;
	inWhichApperance=-1;
	inWhichTheOtherApperance=-1;
	isClickBox1=FALSE;
	box5x=0.65*ww;box5y=0.45*wh;box6w=box5w=0.2*ww;box5h=0.36*wh;
	box6x=box7x=box8x=box5x;
	box8y=0.45*wh;box7y=0.57*wh;box6y=0.69*wh;
	box6h=0.12*wh;
	//扫雷的全局变量
	bw=ww/40; 
	mseconds1000 = 1000;
}

bool isInBox(double x,double y,double len,double height,double cx,double cy){
	if(cx>=x&&cx<=x+len&&cy>=y&&cy<=y+height) return TRUE;
	return FALSE;
}

void changeTheBox(double mx,double my){
	if(isInBox(box1x,box1y,boxw,boxh,mx,my)){
					if(inWhichApperance!=1){
					inWhichApperance=1;
					SetEraseMode(TRUE);
					drawStartBox(box1x,box1y,boxw,boxh,7);
					MovePen(box1x+0.3*boxw,box1y+0.4*boxh);
					DrawTextString("开 始");
					SetEraseMode(FALSE);
					drawDownBox(box1x,box1y,boxw,boxh,7);
					SetPenColor("black");
					MovePen(box1x+0.3*boxw,box1y+0.4*boxh);
					DrawTextString("开 始");  
				}}
				else if(isInBox(box2x,box2y,boxw,boxh,mx,my)){
					if(inWhichApperance!=2){
					inWhichApperance=2;
					SetEraseMode(TRUE);
					drawStartBox(box2x,box2y,boxw,boxh,7);
					MovePen(box2x+0.25*boxw,box2y+0.4*boxh);
					DrawTextString("自定义");
					SetEraseMode(FALSE);
					drawDownBox(box2x,box2y,boxw,boxh,7);
					SetPenColor("black");
					MovePen(box2x+0.25*boxw,box2y+0.4*boxh);
					DrawTextString("自定义");
				}}
				else if(isInBox(box3x,box3y,boxw,boxh,mx,my)){
					if(inWhichApperance!=3){
					inWhichApperance=3;
					SetEraseMode(TRUE);
					drawStartBox(box3x,box3y,boxw,boxh,7);
					MovePen(box3x+0.2*boxw,box3y+0.4*boxh);
					DrawTextString("游戏规则");
					SetEraseMode(FALSE);
					drawDownBox(box3x,box3y,boxw,boxh,7);
					SetPenColor("black");
					MovePen(box3x+0.2*boxw,box3y+0.4*boxh);
					DrawTextString("游戏规则");
				}}
				else if(isInBox(box4x,box4y,boxw,boxh,mx,my)){
				 
					if(inWhichApperance!=4){
					inWhichApperance=4;
					SetEraseMode(TRUE);
					drawStartBox(box4x,box4y,boxw,boxh,7);
					MovePen(box4x+0.25*boxw,box4y+0.4*boxh);
					DrawTextString("排行榜");
					SetEraseMode(FALSE);
					drawDownBox(box4x,box4y,boxw,boxh,7);
					SetPenColor("black");
					MovePen(box4x+0.25*boxw,box4y+0.4*boxh);
					DrawTextString("排行榜");
				}} 
				else if(inWhichApperance!=0){
					inWhichApperance=0;
					SetEraseMode(TRUE);
					drawDownBox(box1x,box1y,boxw,boxh,7);
					MovePen(box1x+0.3*boxw,box1y+0.4*boxh);
					DrawTextString("开 始");
					SetEraseMode(FALSE);
					drawStartBox(box1x,box1y,boxw,boxh,7);
					SetPenColor("black");
					MovePen(box1x+0.3*boxw,box1y+0.4*boxh);
					DrawTextString("开 始");
					
					SetEraseMode(TRUE);
					drawDownBox(box2x,box2y,boxw,boxh,7);
					MovePen(box2x+0.25*boxw,box2y+0.4*boxh);
					DrawTextString("自定义");
					SetEraseMode(FALSE);
					drawStartBox(box2x,box2y,boxw,boxh,7);
					SetPenColor("black");
					MovePen(box2x+0.25*boxw,box2y+0.4*boxh);
					DrawTextString("自定义");
					
					SetEraseMode(TRUE);
					drawDownBox(box3x,box3y,boxw,boxh,7);
					MovePen(box3x+0.2*boxw,box3y+0.4*boxh);
					DrawTextString("游戏规则");
					SetEraseMode(FALSE);
					drawStartBox(box3x,box3y,boxw,boxh,7);
					SetPenColor("black");
					MovePen(box3x+0.2*boxw,box3y+0.4*boxh);
					DrawTextString("游戏规则");
					
					SetEraseMode(TRUE);
					drawDownBox(box4x,box4y,boxw,boxh,7);
					MovePen(box4x+0.25*boxw,box4y+0.4*boxh);
					DrawTextString("排行榜");
					SetEraseMode(FALSE);
					drawStartBox(box4x,box4y,boxw,boxh,7);
					SetPenColor("black");
					MovePen(box4x+0.25*boxw,box4y+0.4*boxh);
					DrawTextString("排行榜");
					
						}
}

void changeTheOtherBox(double mx,double my){
	DefineColor("theOtherBox",108.0/255,179.0/255,237.0/255);
	
	if(isInBox(box6x,box6y,box6w,box6h,mx,my)){
		if(inWhichTheOtherApperance!=6){
			drawTheChoice();
			inWhichTheOtherApperance=6;
			SetPenColor("theOtherBox");
			MovePen(box6x,box6y);
			StartFilledRegion(1);
			DrawLine(box6w,0);
			DrawLine(0,box6h);
			DrawLine(-box6w,0);
			DrawLine(0,-box6h);
			EndFilledRegion();
			DefineColor("fc1",200.0/255,200.0/255,200.0/255);
			SetPenColor("fc1");
			MovePen(box6x+box6w*0.35,box6y+box6h/2);
			DrawTextString("初 级");
		}
	}
	else if(isInBox(box7x,box7y,box6w,box6h,mx,my)){
		if(inWhichTheOtherApperance!=7){
			drawTheChoice();
			inWhichTheOtherApperance=7;
			SetPenColor("theOtherBox");
			MovePen(box7x,box7y);
			StartFilledRegion(1);
			DrawLine(box6w,0);
			DrawLine(0,box6h);
			DrawLine(-box6w,0);
			DrawLine(0,-box6h);
			EndFilledRegion();
			DefineColor("fc1",200.0/255,200.0/255,200.0/255);
			SetPenColor("fc1");
			MovePen(box7x+box6w*0.35,box7y+box6h/2);
			DrawTextString("中 级");
		}
	}
	else if(isInBox(box8x,box8y,box6w,box6h,mx,my)){
		if(inWhichTheOtherApperance!=8){
			drawTheChoice();
			inWhichTheOtherApperance=8;
			SetPenColor("theOtherBox");
			MovePen(box8x,box8y);
			StartFilledRegion(1);
			DrawLine(box6w,0);
			DrawLine(0,box6h);
			DrawLine(-box6w,0);
			DrawLine(0,-box6h);
			EndFilledRegion();
			DefineColor("fc1",200.0/255,200.0/255,200.0/255);
			SetPenColor("fc1");
			MovePen(box8x+box6w*0.35,box8y+box6h/2);
			DrawTextString("高 级");
		}
	}
	else{
		if(inWhichTheOtherApperance!=0){
			inWhichTheOtherApperance=0;
			drawTheChoice();
		}
	}
	
	SetPenColor("black");
}

void doClickBox1(void){
	if(isClickBox1==FALSE){
		isClickBox1=TRUE;
		drawTheChoice();
	}
	else{
		inWhichTheOtherApperance=-1;
		
		isClickBox1=FALSE;
		SetEraseMode(TRUE);
		StartFilledRegion(1);
		MovePen(box5x,box5y);
		DrawLine(box5w,0);
		DrawLine(0,box5h);
		DrawLine(-box5w,0);
		DrawLine(0,-box5h);
		EndFilledRegion();
		
		DefineColor("background",192.0/256,192.0/256,192.0/256);
		SetPenColor("background");
		SetEraseMode(FALSE);
		StartFilledRegion(1);
		MovePen(box5x,box5y);
		DrawLine(box5w,0);
		DrawLine(0,box5h);
		DrawLine(-box5w,0);
		DrawLine(0,-box5h);
		EndFilledRegion();
		SetPenColor("black");
	}
}

void drawTheChoice(void){
	//画边框
	DefineColor("fc1",200.0/255,200.0/255,200.0/255);
	SetPenColor("fc1");
	StartFilledRegion(1);
	MovePen(box5x,box5y);
	DrawLine(box5w,0);
	DrawLine(0,box5h);
	DrawLine(-box5w,0);
	DrawLine(0,-box5h);
	EndFilledRegion();
	
	//写字
	DefineColor("fwc",255.0/255,255.0/255,255.0/255);
	SetPenColor("fwc");
	MovePen(box6x+box6w*0.35,box6y+box6h/2);
	DrawTextString("初 级");
	MovePen(box7x+box6w*0.35,box7y+box6h/2);
	DrawTextString("中 级"); 
	MovePen(box8x+box6w*0.35,box8y+box6h/2);
	DrawTextString("高 级");
	 
	
	SetPenColor("black");
}

void MouseEventProcess(int x, int y, int button, int event){
	
	double mx, my;
	mx = ScaleXInches(x);
 	my = ScaleYInches(y);
	
	if(nowpage==0){
		switch(event){
			case BUTTON_DOWN:{
				if(isInBox(box1x,box1y,boxw,boxh,mx,my)){
					doClickBox1();
				}
				if(isClickBox1==FALSE){
					if(isInBox(box2x,box2y,boxw,boxh,mx,my)) doClickBox2();
					if(isInBox(box3x,box3y,boxw,boxh,mx,my)) doClickBox3();
					if(isInBox(box4x,box4y,boxw,boxh,mx,my)) doClickBox4();
				}
				
				if(isClickBox1==TRUE){
					if(isInBox(box6x,box6y,box6w,box6h,mx,my)) doClickBox6();
					if(isInBox(box7x,box7y,box6w,box6h,mx,my)) doClickBox7();
					if(isInBox(box8x,box8y,box6w,box6h,mx,my)) doClickBox8();
				}
				
				break;
			} 
			
			case BUTTON_DOUBLECLICK:{
				break;
			}
			
			case MOUSEMOVE:{
				if(isClickBox1==FALSE) changeTheBox(mx,my);
				if(isClickBox1==TRUE) changeTheOtherBox(mx,my);
				break;
			}
			
			case BUTTON_UP:{
				break;
			}
		}
	}
	
	else if(nowpage==1){
		
		arrayx=changeToX(mx);
		arrayy=changeToY(my);
		
		switch(event){
			case BUTTON_DOWN:{
			
				
				if(button == LEFT_BUTTON){  
					
					if(isInBox(ww/2-0.2,wh/2+(double)gridy/2*bw+1.5*bw,length,breadth,mx,my)) doRestartPageOne();//记住这里都是要用if-else结构 
					else if(isInBox(0.01*ww,0.90*wh,0.1*ww,0.08*wh,mx,my)) doRestartPageZero();
					
					else if(arrayx!=-1&&arrayy!=-1&&gameOver==FALSE){
						
						if(firstClick==1) gameStart();
						
						if(ud[arrayx][arrayy]==0&&thingup[arrayx][arrayy]==0){
							leftclick();
						} 
					}
				}
				
				else if(gameOver==FALSE){			//表示右键单击 ,且游戏还没有结束 
				
					if(arrayx!=-1&&arrayy!=-1){
						if(firstClick==1){
							gameStart();
							rightclick();
						}
						else{
							rightclick();
						} 
					}
				}
				
				break;
			}
			
			case BUTTON_DOUBLECLICK:{
				OpenConsole();
				if(button == LEFT_BUTTON) doubleclick();
				break;
			}
			
			default : break;
		}
	}
	
}







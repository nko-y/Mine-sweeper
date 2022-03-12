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

void gameBackGround(void){
	//背景颜色 
	DefineColor("background",192.0/256,192.0/256,192.0/256);
	SetPenColor("background");
	StartFilledRegion(1);
	DrawLine(ww,0);
	DrawLine(0,wh);
	DrawLine(-ww,0);
	DrawLine(0,-wh);
	EndFilledRegion();
	SetPenColor("black");
	
	//初始化扫雷棋盘
	initAllBox();
	
	//下外框
	drawDownBox(ww/2-(double)gridx/2*bw-(double)gridy*bw/50.0,wh/2-(double)gridy/2*bw-(double)gridy*bw/50.0,bw*(double)gridx+(double)gridy*bw/25.0,bw*(double)gridy+(double)gridy*bw/25.0,70);
	
	//操作框
	drawDownBox(ww/8,wh/2+(double)gridy/2*bw+bw,ww/8*6,bw*3,70);
	
	//计数器
	MJKNumber(ww/7,wh/2+(double)gridy/2*bw+1.7*bw,mine);
	
	//restart
	restart(ww/2-0.2,wh/2+(double)gridy/2*bw+1.5*bw,0.4,10,0.18);
	
	//计时器
	MJKNumber(ww/7*5.5,wh/2+(double)gridy/2*bw+1.7*bw,0);
	
	//返回按钮
	drawStartBox(0.01*ww,0.90*wh,0.1*ww,0.08*wh,20);
	MovePen(0.03*ww,0.93*wh);
	DefineColor("back",20.0/255,55.0/255,75.0/255);
	SetPenColor("back");
	DrawTextString("b a c k"); 
}

void oneBoxToClearWhite(int x,int y){
	DefineColor("clickColor",170.0/255,170.0/255,170.0/255);
	SetPenColor("clickColor");
	MovePen(ww/2+(x-(double)gridx/2)*bw,wh/2+(y-(double)gridy/2)*bw);
	StartFilledRegion(1);
	DrawLine(bw,0);
	DrawLine(0,bw);
	DrawLine(-bw,0);
	DrawLine(0,-bw);
	EndFilledRegion();
	SetPenColor("black");
}

void oneBoxToWhite(int x,int y){
	SetPenColor("white");
	
	MovePen(ww/2+(x-(double)gridx/2)*bw,wh/2+(y-(double)gridy/2)*bw);
	StartFilledRegion(1);
	DrawLine(bw,0);
	DrawLine(0,bw);
	DrawLine(-bw,0);
	DrawLine(0,-bw);
	EndFilledRegion();
	
	DefineColor("background",192.0/256,192.0/256,192.0/256);
	SetPenColor("background");
	MovePen(ww/2+(x-(double)gridx/2)*bw,wh/2+(y-(double)gridy/2)*bw);
	StartFilledRegion(1);
	DrawLine(bw,0);
	DrawLine(0,bw);
	DrawLine(-bw,0);
	DrawLine(0,-bw);
	EndFilledRegion();
	
	drawStartBox(ww/2+(x-(double)gridx/2)*bw,wh/2+(y-(double)gridy/2)*bw,bw,bw,10);	
	
	SetPenColor("black"); 
} 

void unClickBox(int x,int y,int number){
	drawStartBox(ww/2+(x-(double)gridx/2)*bw,wh/2+(y-(double)gridy/2)*bw,bw,bw,10);
	if(number==1){
		MovePen(ww/2+(x-(double)gridx/2)*bw+bw/3,wh/2+(y-(double)gridy/2)*bw+bw/5);
		SetPenColor("black");
		StartFilledRegion(1);
		DrawLine(bw/3,0);
		DrawLine(0,bw/20);
		DrawLine(-bw/3,0);
		DrawLine(0,-bw/20);
		EndFilledRegion();
		
		MovePen(ww/2+(x-(double)gridx/2)*bw+bw/1.85,wh/2+(y-(double)gridy/2)*bw+bw/5+bw/20);
		DrawLine(0,bw/5*2.5);
		
		SetPenColor("red");
		StartFilledRegion(1);
		DrawLine(0,-bw*0.3);
		DrawLine(-bw/4,bw*0.15);
		DrawLine(bw/4,bw*0.15);
		EndFilledRegion();
	}
	if(number==2){
		MovePen(ww/2+(x-(double)gridx/2)*bw+bw/2,wh/2+(y-(double)gridy/2)*bw+bw/3);
		SetPenSize(2);
		SetPenColor("black");
		DrawArc(bw/5,-90,270);
		MovePen(ww/2+(x-(double)gridx/2)*bw+bw/2,wh/2+(y-(double)gridy/2)*bw+bw/4);
		SetPenSize(3);
		DrawLine(0,0);
		
		SetPenSize(1);
	}
}

void clickBox(int x,int y,int number){
	MovePen(ww/2+(x-(double)gridx/2)*bw,wh/2+(y-(double)gridy/2)*bw);
	DefineColor("clickColor",170.0/255,170.0/255,170.0/255);
	SetPenColor("clickColor");
	StartFilledRegion(1);
	DrawLine(bw,0);
	DrawLine(0,bw);
	DrawLine(-bw,0);
	DrawLine(0,-bw);
	EndFilledRegion();
	
	DefineColor("firstcolor",102.0/256,102.0/256,102.0/256);
	SetPenColor("firstcolor");
	DrawLine(bw,0);
	DrawLine(0,bw);
	DrawLine(-bw,0);
	DrawLine(0,-bw);
	
	if(number==1){
		MovePen(ww/2+(x-(double)gridx/2)*bw+bw/3,wh/2+(y-(double)gridy/2)*bw+bw/4);
		DefineColor("oneColor",50.0/255,56.0/255,233.0/255);
		SetPenColor("oneColor");
		DrawTextString("1");
	}
	else if(number==2){
		MovePen(ww/2+(x-(double)gridx/2)*bw+bw/3,wh/2+(y-(double)gridy/2)*bw+bw/4);
		DefineColor("twoColor",30.0/255,150.0/255,30.0/255);
		SetPenColor("twoColor");
		DrawTextString("2");
	}
	else if(number==3){
		MovePen(ww/2+(x-(double)gridx/2)*bw+bw/3,wh/2+(y-(double)gridy/2)*bw+bw/4);
		DefineColor("threeColor",233.0/255,50.0/255,50.0/255);
		SetPenColor("threeColor");
		DrawTextString("3");
	}
	else if(number==4){
		MovePen(ww/2+(x-(double)gridx/2)*bw+bw/3,wh/2+(y-(double)gridy/2)*bw+bw/4);
		DefineColor("fourColor",95.0/255,55.0/255,95.0/255);
		SetPenColor("fourColor");
		DrawTextString("4");
	}
	else if(number==5){
		MovePen(ww/2+(x-(double)gridx/2)*bw+bw/3,wh/2+(y-(double)gridy/2)*bw+bw/4);
		DefineColor("fiveColor",241.0/255,155.0/255,95.0/255);
		SetPenColor("fiveColor");
		DrawTextString("5");
	}
	else if(number==6){
		MovePen(ww/2+(x-(double)gridx/2)*bw+bw/3,wh/2+(y-(double)gridy/2)*bw+bw/4);
		DefineColor("sixColor",241.0/255,222.0/255,198.0/255);
		SetPenColor("sixColor");
		DrawTextString("6");
	}
	else if(number==7){
		MovePen(ww/2+(x-(double)gridx/2)*bw+bw/3,wh/2+(y-(double)gridy/2)*bw+bw/4);
		DefineColor("sevenColor",0,0,0);
		SetPenColor("sevenColor");
		DrawTextString("7");
	}
	else if(number==8){
		MovePen(ww/2+(x-(double)gridx/2)*bw+bw/3,wh/2+(y-(double)gridy/2)*bw+bw/4);
		DefineColor("eightColor",1,1,1);
		SetPenColor("eightColor");
		DrawTextString("8");
	}
	else if(number==-1){
		MovePen(ww/2+(x-(double)gridx/2)*bw+bw/2+bw/4,wh/2+(y-(double)gridy/2)*bw+bw/4+bw/4);
		SetPenColor("black");
		StartFilledRegion(1);
		DrawArc(bw/4,0,360);
		EndFilledRegion();
		MovePen(ww/2+(x-(double)gridx/2)*bw+bw/10,wh/2+(y-(double)gridy/2)*bw+bw/4+bw/4);
		SetPenSize(2);
		DrawLine(bw/5*4,0);
		MovePen(ww/2+(x-(double)gridx/2)*bw+bw/2,wh/2+(y-(double)gridy/2)*bw+bw/10);
		DrawLine(0,bw/5*4);
		SetPenSize(3);
		MovePen(ww/2+(x-(double)gridx/2)*bw+bw/2+bw/4,wh/2+(y-(double)gridy/2)*bw+bw/4+bw/2);
		DrawLine(0,0);
		MovePen(ww/2+(x-(double)gridx/2)*bw+bw/2+bw/4,wh/2+(y-(double)gridy/2)*bw+bw/4);
		DrawLine(0,0);
		MovePen(ww/2+(x-(double)gridx/2)*bw+bw/2-bw/4,wh/2+(y-(double)gridy/2)*bw+bw/4+bw/2);
		DrawLine(0,0);
		MovePen(ww/2+(x-(double)gridx/2)*bw+bw/2-bw/4,wh/2+(y-(double)gridy/2)*bw+bw/4);
		DrawLine(0,0);
		SetPenColor("white");
		MovePen(ww/2+(x-(double)gridx/2)*bw+bw/2-bw/8,wh/2+(y-(double)gridy/2)*bw+bw/4+bw/4);
		DrawLine(0,0);
		SetPenSize(1);
		SetPenColor("black");
	}
} 

void initAllBox(void){
	int i,j;
	for(i=0;i<(double)gridx;i++){
		for(j=0;j<(double)gridy;j++){
			unClickBox(i,j,0);
		}
	}
}

int changeToX(double mx){
	int i;
	for(i=0;i<(double)gridx;i++){
		if(mx>ww/2-(double)gridx/2*bw+i*bw&&mx<ww/2-(double)gridx/2*bw+(i+1)*bw) return i;
	}
	return -1;
}

int changeToY(double my){
	int i;
	for(i=0;i<(double)gridy;i++){
		if(my>wh/2-(double)gridy/2*bw+i*bw&&my<wh/2-(double)gridy/2*bw+(i+1)*bw) return i;
	}
	return -1;
}

void MJKNumber(double x,double y,int n){
	int ge=n%10;
	int shi=(n/10)%10;
	int bai=(n/100)%10;
	MovePen(x,y);
	SetPenColor("black");
	StartFilledRegion(1);
	MJKDrawBox(0.6,0.4);	
	EndFilledRegion();
	SetPenColor("red");
	SetPenSize(2);
	MovePen(x+0.02,y+0.02);
	switch(bai){
		case 0:
			DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth-0.06));
	        DrawLine(-(length/3-0.04),0);
	        DrawLine(0,-(breadth-0.06));
	        break;
	    case 1:
	    	MovePen(x+length/3-0.02,y+0.02);
	    	DrawLine(0,(breadth-0.06));
	    	break;
	    case 2:
	    	MovePen(x+length/3-0.02,y+0.02);
	    	DrawLine(-(length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine(-(length/3-0.04),0);
	        break;
	    case 3:
	    	DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine(-(length/3-0.04),0);
	        DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine(-(length/3-0.04),0);
	        break;
	    case 4:
	    	MovePen(x+length/3-0.02,y+0.02);
	    	DrawLine(0,(breadth-0.06));
	    	DrawLine(0,-(breadth/2-0.03));
	    	DrawLine(-(length/3-0.04),0);
	    	DrawLine(0,(breadth/2-0.03));
	    	break;
	    case 5:
	    	DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine(-(length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine((length/3-0.04),0);
	        break;
	    case 6:
	    	DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine(-(length/3-0.04),0);
	        DrawLine(0,-(breadth/2-0.03));
	        DrawLine(0,(breadth-0.06));
	        DrawLine((length/3-0.04),0);
	        break;
	    case 7:
	    	MovePen(x+length/3-0.02,y+0.02);
	    	DrawLine(0,(breadth-0.06));
	    	DrawLine(-(length/3-0.04),0);
	    	break;
	    case 8:
	    	DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine(-(length/3-0.04),0);
	        DrawLine(0,-(breadth/2-0.03));
	        DrawLine(0,(breadth-0.06));
	        DrawLine((length/3-0.04),0);
	        DrawLine(0,-(breadth/2-0.03));
            break;
        case 9:
        	DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth-0.06));
	        DrawLine(-(length/3-0.04),0);
	        DrawLine(0,-(breadth/2-0.03));
	        DrawLine((length/3-0.04),0);
	        break;
	}
	MovePen(x+length/3+0.02,y+0.02);
	switch(shi){
		case 0:
			DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth-0.06));
	        DrawLine(-(length/3-0.04),0);
	        DrawLine(0,-(breadth-0.06));
	        break;
	    case 1:
	    	MovePen(x+length/3*2-0.02,y+0.02);
	    	DrawLine(0,(breadth-0.06));
	    	break;
	    case 2:
	    	MovePen(x+length/3*2-0.02,y+0.02);
	    	DrawLine(-(length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine(-(length/3-0.04),0);
	        break;
	    case 3:
	    	DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine(-(length/3-0.04),0);
	        DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine(-(length/3-0.04),0);
	        break;
	    case 4:
	    	MovePen(x+length/3*2-0.02,y+0.02);
	    	DrawLine(0,(breadth-0.06));
	    	DrawLine(0,-(breadth/2-0.03));
	    	DrawLine(-(length/3-0.04),0);
	    	DrawLine(0,(breadth/2-0.03));
	    	break;
	    case 5:
	    	DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine(-(length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine((length/3-0.04),0);
	        break;
	    case 6:
	    	DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine(-(length/3-0.04),0);
	        DrawLine(0,-(breadth/2-0.03));
	        DrawLine(0,(breadth-0.06));
	        DrawLine((length/3-0.04),0);
	        break;
	    case 7:
	    	MovePen(x+length/3*2-0.02,y+0.02);
	    	DrawLine(0,(breadth-0.06));
	    	DrawLine(-(length/3-0.04),0);
	    	break;
	    case 8:
	    	DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine(-(length/3-0.04),0);
	        DrawLine(0,-(breadth/2-0.03));
	        DrawLine(0,(breadth-0.06));
	        DrawLine((length/3-0.04),0);
	        DrawLine(0,-(breadth/2-0.03));
            break;
        case 9:
        	DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth-0.06));
	        DrawLine(-(length/3-0.04),0);
	        DrawLine(0,-(breadth/2-0.03));
	        DrawLine((length/3-0.04),0);
	        break;
	}
	MovePen(x+length/3*2+0.02,y+0.02);
	switch(ge){
		case 0:
			DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth-0.06));
	        DrawLine(-(length/3-0.04),0);
	        DrawLine(0,-(breadth-0.06));
	        break;
	    case 1:
	    	MovePen(x+length-0.02,y+0.02);
	    	DrawLine(0,(breadth-0.06));
	    	break;
	    case 2:
	    	MovePen(x+length-0.02,y+0.02);
	    	DrawLine(-(length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine(-(length/3-0.04),0);
	        break;
	    case 3:
	    	DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine(-(length/3-0.04),0);
	        DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine(-(length/3-0.04),0);
	        break;
	    case 4:
	    	MovePen(x+length-0.02,y+0.02);
	    	DrawLine(0,(breadth-0.06));
	    	DrawLine(0,-(breadth/2-0.03));
	    	DrawLine(-(length/3-0.04),0);
	    	DrawLine(0,(breadth/2-0.03));
	    	break;
	    case 5:
	    	DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine(-(length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine((length/3-0.04),0);
	        break;
	    case 6:
	    	DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine(-(length/3-0.04),0);
	        DrawLine(0,-(breadth/2-0.03));
	        DrawLine(0,(breadth-0.06));
	        DrawLine((length/3-0.04),0);
	        break;
	    case 7:
	    	MovePen(x+length-0.02,y+0.02);
	    	DrawLine(0,(breadth-0.06));
	    	DrawLine(-(length/3-0.04),0);
	    	break;
	    case 8:
	    	DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine(-(length/3-0.04),0);
	        DrawLine(0,-(breadth/2-0.03));
	        DrawLine(0,(breadth-0.06));
	        DrawLine((length/3-0.04),0);
	        DrawLine(0,-(breadth/2-0.03));
            break;
        case 9:
        	DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth-0.06));
	        DrawLine(-(length/3-0.04),0);
	        DrawLine(0,-(breadth/2-0.03));
	        DrawLine((length/3-0.04),0);
	        break;
	}
}

void MJKDrawBox(double x,double y){	
	DrawLine(x,0);
	DrawLine(0,y);
	DrawLine(-x,0);
	DrawLine(0,-y);
}

void restart(double x,double y,double len,double t,double r){
	MovePen(x,y);
	DefineColor("firstcolor",102.0/256,102.0/256,102.0/256);
	DefineColor("secondcolor",234.0/256,234.0/256,234.0/256);
	DefineColor("thirdcolor",255.0/256,255.0/256,0.0/256);
	SetPenColor("secondcolor");
	StartFilledRegion(1);
	DrawLine(0,len);
	DrawLine(len,0);
	DrawLine(-len/t,-len/t);
	DrawLine(-len+(len/t*2),0);
	DrawLine(0,-len+(len/t*2));
	DrawLine(-len/t,-len/t);
	EndFilledRegion();
	
	MovePen(x,y);
	SetPenColor("firstcolor");
	StartFilledRegion(1);
	DrawLine(len,0);
	DrawLine(0,len);
	DrawLine(-len/t,-len/t);
	DrawLine(0,-len+(len/t*2));
	DrawLine(-len+(len/t*2),0);
	DrawLine(-len/t,-len/t);
	EndFilledRegion();
	
	MovePen(x+len/2+r,y+len/2);
	StartFilledRegion(1);
	DrawArc(r,0,360);
	SetPenColor("thirdcolor");
	EndFilledRegion();
	SetPenColor("firstcolor");
	DrawArc(r,0,360);
	
	MovePen(x+len/2+r*sqrt(3)/4,y+len/2-r/4);
	DrawArc(r/2,-30,-120);
	MovePen(x+len/2+r*sqrt(3)/4,y+len/2+r/4);
	StartFilledRegion(1);
	DrawArc(0.1*r,0,360);
	EndFilledRegion();
	MovePen(x+len/2-r*sqrt(3)/4+0.2*r,y+len/2+r/4);
	StartFilledRegion(1);
	DrawArc(0.1*r,0,360);
	EndFilledRegion();
}

void MJKDrawNumber(double x,double y,int n){
	int ge=n%10;
	int shi=(n/10)%10;
	int bai=(n/100)%10;
	SetPenSize(2);
	MovePen(x+0.02,y+0.02);
	switch(bai){
		case 0:
			DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth-0.06));
	        DrawLine(-(length/3-0.04),0);
	        DrawLine(0,-(breadth-0.06));
	        break;
	    case 1:
	    	MovePen(x+length/3-0.02,y+0.02);
	    	DrawLine(0,(breadth-0.06));
	    	break;
	    case 2:
	    	MovePen(x+length/3-0.02,y+0.02);
	    	DrawLine(-(length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine(-(length/3-0.04),0);
	        break;
	    case 3:
	    	DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine(-(length/3-0.04),0);
	        DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine(-(length/3-0.04),0);
	        break;
	    case 4:
	    	MovePen(x+length/3-0.02,y+0.02);
	    	DrawLine(0,(breadth-0.06));
	    	DrawLine(0,-(breadth/2-0.03));
	    	DrawLine(-(length/3-0.04),0);
	    	DrawLine(0,(breadth/2-0.03));
	    	break;
	    case 5:
	    	DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine(-(length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine((length/3-0.04),0);
	        break;
	    case 6:
	    	DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine(-(length/3-0.04),0);
	        DrawLine(0,-(breadth/2-0.03));
	        DrawLine(0,(breadth-0.06));
	        DrawLine((length/3-0.04),0);
	        break;
	    case 7:
	    	MovePen(x+length/3-0.02,y+0.02);
	    	DrawLine(0,(breadth-0.06));
	    	DrawLine(-(length/3-0.04),0);
	    	break;
	    case 8:
	    	DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine(-(length/3-0.04),0);
	        DrawLine(0,-(breadth/2-0.03));
	        DrawLine(0,(breadth-0.06));
	        DrawLine((length/3-0.04),0);
	        DrawLine(0,-(breadth/2-0.03));
            break;
        case 9:
        	DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth-0.06));
	        DrawLine(-(length/3-0.04),0);
	        DrawLine(0,-(breadth/2-0.03));
	        DrawLine((length/3-0.04),0);
	        break;
	}
	MovePen(x+length/3+0.02,y+0.02);
	switch(shi){
		case 0:
			DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth-0.06));
	        DrawLine(-(length/3-0.04),0);
	        DrawLine(0,-(breadth-0.06));
	        break;
	    case 1:
	    	MovePen(x+length/3*2-0.02,y+0.02);
	    	DrawLine(0,(breadth-0.06));
	    	break;
	    case 2:
	    	MovePen(x+length/3*2-0.02,y+0.02);
	    	DrawLine(-(length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine(-(length/3-0.04),0);
	        break;
	    case 3:
	    	DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine(-(length/3-0.04),0);
	        DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine(-(length/3-0.04),0);
	        break;
	    case 4:
	    	MovePen(x+length/3*2-0.02,y+0.02);
	    	DrawLine(0,(breadth-0.06));
	    	DrawLine(0,-(breadth/2-0.03));
	    	DrawLine(-(length/3-0.04),0);
	    	DrawLine(0,(breadth/2-0.03));
	    	break;
	    case 5:
	    	DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine(-(length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine((length/3-0.04),0);
	        break;
	    case 6:
	    	DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine(-(length/3-0.04),0);
	        DrawLine(0,-(breadth/2-0.03));
	        DrawLine(0,(breadth-0.06));
	        DrawLine((length/3-0.04),0);
	        break;
	    case 7:
	    	MovePen(x+length/3*2-0.02,y+0.02);
	    	DrawLine(0,(breadth-0.06));
	    	DrawLine(-(length/3-0.04),0);
	    	break;
	    case 8:
	    	DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine(-(length/3-0.04),0);
	        DrawLine(0,-(breadth/2-0.03));
	        DrawLine(0,(breadth-0.06));
	        DrawLine((length/3-0.04),0);
	        DrawLine(0,-(breadth/2-0.03));
            break;
        case 9:
        	DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth-0.06));
	        DrawLine(-(length/3-0.04),0);
	        DrawLine(0,-(breadth/2-0.03));
	        DrawLine((length/3-0.04),0);
	        break;
	}
	MovePen(x+length/3*2+0.02,y+0.02);
	switch(ge){
		case 0:
			DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth-0.06));
	        DrawLine(-(length/3-0.04),0);
	        DrawLine(0,-(breadth-0.06));
	        break;
	    case 1:
	    	MovePen(x+length-0.02,y+0.02);
	    	DrawLine(0,(breadth-0.06));
	    	break;
	    case 2:
	    	MovePen(x+length-0.02,y+0.02);
	    	DrawLine(-(length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine(-(length/3-0.04),0);
	        break;
	    case 3:
	    	DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine(-(length/3-0.04),0);
	        DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine(-(length/3-0.04),0);
	        break;
	    case 4:
	    	MovePen(x+length-0.02,y+0.02);
	    	DrawLine(0,(breadth-0.06));
	    	DrawLine(0,-(breadth/2-0.03));
	    	DrawLine(-(length/3-0.04),0);
	    	DrawLine(0,(breadth/2-0.03));
	    	break;
	    case 5:
	    	DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine(-(length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine((length/3-0.04),0);
	        break;
	    case 6:
	    	DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine(-(length/3-0.04),0);
	        DrawLine(0,-(breadth/2-0.03));
	        DrawLine(0,(breadth-0.06));
	        DrawLine((length/3-0.04),0);
	        break;
	    case 7:
	    	MovePen(x+length-0.02,y+0.02);
	    	DrawLine(0,(breadth-0.06));
	    	DrawLine(-(length/3-0.04),0);
	    	break;
	    case 8:
	    	DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth/2-0.03));
	        DrawLine(-(length/3-0.04),0);
	        DrawLine(0,-(breadth/2-0.03));
	        DrawLine(0,(breadth-0.06));
	        DrawLine((length/3-0.04),0);
	        DrawLine(0,-(breadth/2-0.03));
            break;
        case 9:
        	DrawLine((length/3-0.04),0);
	        DrawLine(0,(breadth-0.06));
	        DrawLine(-(length/3-0.04),0);
	        DrawLine(0,-(breadth/2-0.03));
	        DrawLine((length/3-0.04),0);
	        break;
	}
}

void MJKDrawTime(double x,double y,int n){
	MovePen(x,y);
	SetPenColor("black");
	StartFilledRegion(1);
	MJKDrawBox(0.6,0.4);	
	EndFilledRegion();
	MJKDrawNumber(x,y,n); 
}

void TimerEventProcess(int timerID){
	MJKDrawTime(thex,they,n);
	switch (timerID) {
	    case TIMER_BLINK1000:
	    	n++;
	    	if(n==999) stopGame(0); 
	    	SetPenColor("black");
	    	MJKDrawNumber(thex,they,n-1);
	    	SetPenColor("red");
	    	MJKDrawNumber(thex,they,n);
	    	SetPenColor("black");
	    	break;
	}
}

void die(double x,double y,double len,double t,double r){
	MovePen(x,y);
	DefineColor("firstcolor",102.0/256,102.0/256,102.0/256);
	DefineColor("secondcolor",234.0/256,234.0/256,234.0/256);
	DefineColor("thirdcolor",255.0/256,255.0/256,0.0/256);
	SetPenColor("secondcolor");
	StartFilledRegion(1);
	DrawLine(0,len);
	DrawLine(len,0);
	DrawLine(-len/t,-len/t);
	DrawLine(-len+(len/t*2),0);
	DrawLine(0,-len+(len/t*2));
	DrawLine(-len/t,-len/t);
	EndFilledRegion();
	
	MovePen(x,y);
	SetPenColor("firstcolor");
	StartFilledRegion(1);
	DrawLine(len,0);
	DrawLine(0,len);
	DrawLine(-len/t,-len/t);
	DrawLine(0,-len+(len/t*2));
	DrawLine(-len+(len/t*2),0);
	DrawLine(-len/t,-len/t);
	EndFilledRegion();
	
	MovePen(x+len/2+r,y+len/2);
	StartFilledRegion(1);
	DrawArc(r,0,360);
	SetPenColor("thirdcolor");
	EndFilledRegion();
	SetPenColor("firstcolor");
	DrawArc(r,0,360);
	
	MovePen(x+len/2+r*sqrt(3)/4,y+len/2-r/2);
	DrawArc(r/2,30,120);
	MovePen(x+len/2-r*sqrt(3)/4+0.2*r,y+len/2+r/4+0.1*r);
	DrawLine(-2*r/10,-2*r/10);
	MovePen(x+len/2-r*sqrt(3)/4,y+len/2+r/4+0.1*r);
	DrawLine(2*r/10,-2*r/10);
	MovePen(x+len/2+r*sqrt(3)/4,y+len/2+r/4+0.1*r);
	DrawLine(-2*r/10,-2*r/10);
	MovePen(x+len/2+r*sqrt(3)/4-0.2*r,y+len/2+r/4+0.1*r);
	DrawLine(2*r/10,-2*r/10);
}

void drawWinOrLoseBox(int wol){
	
	SetFont("Courier");
	if(wol==1){
		SetPenColor("red");
		MovePen(ww/4,wh/2+(double)gridy/2*bw+2*bw);
		DrawTextString("You Win It !");
		MovePen(ww/8*4.7,wh/2+(double)gridy/2*bw+2*bw);
		DrawTextString("You Win It !");
	}
	if(wol==0){
		die(ww/2-0.2,wh/2+(double)gridy/2*bw+1.5*bw,0.4,10,0.18);
		SetPenColor("red");
		MovePen(ww/4,wh/2+(double)gridy/2*bw+2*bw);
		DrawTextString("You Lose It !");
		MovePen(ww/8*4.7,wh/2+(double)gridy/2*bw+2*bw);
		DrawTextString("You Lose It !");
	}
	
	SetFont("Default");
}

int judgeWinOrLose(void){
	int thingunderit=thingunder[arrayx][arrayy];
	
	
	//判断是否获胜 
	int i,j,countflag=0,countgrid=0;
	for(i=0;i<gridx;i++){
		for(j=0;j<gridy;j++){
			if(ud[i][j]==1) countgrid++;
			
			if(thingunder[i][j]==-1&&thingup[i][j]!=1) break;
			else if(thingunder[i][j]!=-1&&thingup[i][j]==1) break;
			else if(thingunder[i][j]==-1&&thingup[i][j]==1) countflag++;
		}
	}
	if(countflag+countgrid==gridx*gridy) return(1);
	
	//还未决定 
	return(-1);
} 

void stopGame(int what){
	
	if(what==-1) return;
	
	gameOver=TRUE;
	cancelTimer(TIMER_BLINK1000);
	
	int i,j;
	for(i=0;i<gridx;i++){
		for(j=0;j<gridy;j++){
			clickBox(i,j,thingunder[i][j]); 
		}
	}
	for(i=0;i<gridx;i++){
		for(j=0;j<gridy;j++){
			if(thingunder[i][j]==-1){
				if(thingup[i][j]==1){
					SetPenSize(3);
					SetPenColor("red");
					MovePen(ww/2+(i-(double)gridx/2)*bw+bw/4,wh/2+(j-(double)gridy/2)*bw+bw/4);
					DrawLine(bw/2,bw/2);
					MovePen(ww/2+(i-(double)gridx/2)*bw+bw/4*3,wh/2+(j-(double)gridy/2)*bw+bw/4);
					DrawLine(-bw/2,bw/2);
				}
			}
		}
	}
	SetPenColor("black");
	SetPenSize(1);
	
	if(what==1) drawWinOrLoseBox(1);
	else drawWinOrLoseBox(0); 
}


void initArray(void){
	int i,j;
	for(i=0;i<Maxgridx;i++){
		for(j=0;j<Maxgridy;j++){
			ud[i][j]=0;
			thingup[i][j]=0;
			thingunder[i][j]=0;
		}
	} 
	int createMine=0;
	srand((unsigned int)time(NULL));
	int forx,fory;
	while(createMine!=mine){
		forx = rand()%gridx;
		fory = rand()%gridy; 
		if(thingunder[forx][fory]==0&&forx!=arrayx&&fory!=arrayy){
			thingunder[forx][fory]=-1;
			createMine++;
		} 
	}
	
	int m,n;
	for(m=0;m<gridx;m++){
		for(n=0;n<gridy;n++){
			if(thingunder[m][n]!=-1){
				int thenumber=0;
				if(wo(m-1,n-1)&&thingunder[m-1][n-1]==-1) thenumber++;
				if(wo(m-1,n)&&thingunder[m-1][n]==-1) thenumber++;
				if(wo(m-1,n+1)&&thingunder[m-1][n+1]==-1) thenumber++;
				if(wo(m,n-1)&&thingunder[m][n-1]==-1) thenumber++;
				if(wo(m,n+1)&&thingunder[m][n+1]==-1) thenumber++;
				if(wo(m+1,n-1)&&thingunder[m+1][n-1]==-1) thenumber++;
				if(wo(m+1,n)&&thingunder[m+1][n]==-1) thenumber++;
				if(wo(m+1,n+1)&&thingunder[m+1][n+1]==-1) thenumber++;
				thingunder[m][n]=thenumber;
			}
		}
	}
	

} 


int wo(int x,int y){
	if(x>=0&&x<gridx&&y>=0&&y<gridy) return 1;
	return 0;
} 


void changeNowArray(void){
	if(thingunder[arrayx][arrayy]==-1){
		ud[arrayx][arrayy]=1;
		oneBoxToClearWhite(arrayx,arrayy);
		clickBox(arrayx,arrayy,-1);
	}
	
	else if(thingunder[arrayx][arrayy]==0){
		open(arrayx,arrayy); 
	}
	
	else {
		ud[arrayx][arrayy]=1;
		oneBoxToClearWhite(arrayx,arrayy);
		clickBox(arrayx,arrayy,thingunder[arrayx][arrayy]);
	}
}

void open(int x,int y){

	if(wo(x,y)==0) return;
	if(thingup[x][y]!=0||ud[x][y]==1) return;
	
	if(thingunder[x][y]==0){
		ud[x][y]=1;
		oneBoxToClearWhite(x,y);
		clickBox(x,y,0);
		open(x-1,y-1);
		open(x-1,y);
		open(x-1,y+1);	
		open(x,y-1);
		open(x,y+1);
		open(x+1,y-1);
		open(x+1,y);
		open(x+1,y+1);
	}
	
	else{
		ud[x][y]=1;
		oneBoxToClearWhite(x,y);
		clickBox(x,y,thingunder[x][y]);
	}
} 









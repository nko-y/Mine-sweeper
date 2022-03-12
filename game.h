#ifndef game_h
#define game_h 

#define Maxgridx 35
#define Maxgridy 18

#define length 0.6
#define breadth 0.4
#define TIMER_BLINK1000 2

int mine;
int gridx;
int gridy;
double bw;
int ud[Maxgridx][Maxgridy];//0-代表还没有翻开  1-代表已经翻开 
int thingunder[Maxgridx][Maxgridy];//这是进入初始化函数以后就再也不会改变的东西；-1代表地雷 0代表没有 1-8代表数字 
int thingup[Maxgridx][Maxgridy];//0-没有 1-棋子 2-问号 一旦翻开那就是没有任何东西0 
int mseconds1000;
double thex,they;
int n;//用于表示计时器显示的读数。
int  arrayx,arrayy;
int firstClick;
int howMangFlag;
bool gameOver;

void clickBox(int x,int y,int number);

void unClickBox(int x,int y,int number); //0-没有  1-旗子  2-问号 

void oneBoxToWhite(int x,int y);//把一个格子擦掉 ,留下背景色 
void oneBoxToClearWhite(int x,int y);

void gameBackGround(void);

void initAllBox(void);

int changeToX(double mx);
int changeToY(double my);

void MJKNumber(double x,double y,int n);
void MJKDrawBox(double x,double y);

void restart(double x,double y,double len,double t,double r); 

void MJKDrawNumber(double x,double y,int n);
void MJKDrawTime(double x,double y,int n); 
void TimerEventProcess(int timerID);

void drawWinOrLoseBox(int wol);
int judgeWinOrLose(void);//-1代表未决定 0代表输 1代表赢 待使用---- //保证点击的坐标是有效点击以后再调用//只有左键点击才会调用该函数 ????
void stopGame(int what);//使用方式stopGame(judgeWinOrLose()); 

void die(double x,double y,double len,double t,double r);//表示输掉了 

void initArray(void); //初始化地雷数组,保证第一次点击的位置没有地雷 
void changeNowArray(void);//有效点击以后改变当前数组,一边翻开一边画

int wo(int x,int y);//判断有无越界的函数 

void open(int x,int y);//地雷展开函数 

#endif

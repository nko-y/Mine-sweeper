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
int ud[Maxgridx][Maxgridy];//0-����û�з���  1-�����Ѿ����� 
int thingunder[Maxgridx][Maxgridy];//���ǽ����ʼ�������Ժ����Ҳ����ı�Ķ�����-1������� 0����û�� 1-8�������� 
int thingup[Maxgridx][Maxgridy];//0-û�� 1-���� 2-�ʺ� һ�������Ǿ���û���κζ���0 
int mseconds1000;
double thex,they;
int n;//���ڱ�ʾ��ʱ����ʾ�Ķ�����
int  arrayx,arrayy;
int firstClick;
int howMangFlag;
bool gameOver;

void clickBox(int x,int y,int number);

void unClickBox(int x,int y,int number); //0-û��  1-����  2-�ʺ� 

void oneBoxToWhite(int x,int y);//��һ�����Ӳ��� ,���±���ɫ 
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
int judgeWinOrLose(void);//-1����δ���� 0������ 1����Ӯ ��ʹ��---- //��֤�������������Ч����Ժ��ٵ���//ֻ���������Ż���øú��� ????
void stopGame(int what);//ʹ�÷�ʽstopGame(judgeWinOrLose()); 

void die(double x,double y,double len,double t,double r);//��ʾ����� 

void initArray(void); //��ʼ����������,��֤��һ�ε����λ��û�е��� 
void changeNowArray(void);//��Ч����Ժ�ı䵱ǰ����,һ�߷���һ�߻�

int wo(int x,int y);//�ж�����Խ��ĺ��� 

void open(int x,int y);//����չ������ 

#endif

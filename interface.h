#ifndef interface_h
#define interface_h

//全局变量
char *username;
double ww;
double wh;
double box1x,box2x,box3x,box4x;
double box1y,box2y,box3y,box4y;
double boxw,boxh; 
int nowpage;
int inWhichApperance;
int inWhichTheOtherApperance;
bool isClickBox1;
double box5x,box6x,box7x,box8x;
double box5y,box6y,box7y,box8y;
double box5w,box5h,box6w,box6h;

void introduction(void);

void drawStartBox(double x,double y,double len,double height,double t);
void drawDownBox(double x,double y,double len,double height,double t);

void drawtitle(double x,double y);

void initInterface(void);

void initGlobalVariable(void); 

void MouseEventProcess(int x, int y, int button, int event);

bool isInBox(double x,double y,double len,double height,double cx,double cy);

void changeTheBox(double mx,double my);
void changeTheOtherBox(double mx,double my);

void doClickBox1(void);

void drawTheChoice(void);

void toWhite(void);//全部变白函数 

#endif

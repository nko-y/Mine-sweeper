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

void Main(){
	InitGraphics();
	
	
	initGlobalVariable();
	initInterface();
	
	introduction();
	
	registerMouseEvent(MouseEventProcess);
	registerTimerEvent(TimerEventProcess);
	
}














#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#define HIG 30
#define WID 80

char *ui[HIG];
WORD *uiColor[HIG];
void cls(){
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;                                      
    pos.X = 0;
    pos.Y = 0;//COORD pos = {x,y}; 
    SetConsoleCursorPosition(handle,pos);
}
void setColor(WORD color){//设置颜色 
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole,color);
}
void hideCursor(){
	CONSOLE_CURSOR_INFO cursor;    
	cursor.bVisible = FALSE;    
	cursor.dwSize = sizeof(cursor);    
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);    
	SetConsoleCursorInfo(handle, &cursor);
}
void setUi(int x,int y,char *s){//根据坐标设置显示内容
	int i;
	for(i=0;s[i];i++){
		ui[y][x+i]=s[i];
	}
}
void setUiWithColor(int x,int y,char *s,WORD color){//根据坐标设置显示内容以及颜色 
	int i;
	for(i=0;s[i];i++){
		ui[y][x+i]=s[i];
		uiColor[y][x+i]=color;
	}
}
void setBufferColor(int xStart,int yStart,int xEnd,int yEnd,WORD color){//根据坐标设置颜色 
	int i,j;
	for(i=yStart;i<=yEnd;i++){
		for(j=xStart;j<=xEnd;j++){
			uiColor[i][j]=color;
		}
	}
}
void draw(){//输出界面 
	cls();
	int i,j;
	for(i=0;i<HIG;i++){
		for(j=0;j<WID;j++){
			setColor(uiColor[i][j]);
			putchar(ui[i][j]);
		}
		puts("");
	}
}
void setUiBorder(char border){//设置边框 
	int i;
	for(i=0;i<WID;i++){
		ui[0][i]=border;
		ui[HIG-1][i]=border;
	}
	for(i=1;i<HIG-1;i++){
		ui[i][0]=border;
		ui[i][WID-1]=border;
	}
}
void initUi(){//初始化界面 
	int i,j;
	for(i=0;i<HIG;i++){
		for(j=0;j<WID;j++){
			ui[i][j]=' ';
		}
	}
	setUiBorder('/');
	setBufferColor(0,0,WID-1,HIG-1,0x7);
}
void clsBuffer(){//清空缓冲区 
	while(_kbhit()){
		getch();
	}
}
void init(){//初始化 
    srand((unsigned)time(NULL));
	hideCursor(); 
	int i;
	for(i=0;i<HIG;i++){
		ui[i]=(char *)malloc(sizeof(char)*WID);
		uiColor[i]=(WORD *)malloc(sizeof(WORD)*WID);
	}
	system("title ☆*: .. o(≧▽≦)o ..:*☆");
	char s[20];
	sprintf(s,"mode con cols=%d lines=%d",WID,HIG+1);
	system(s);
	initUi();
}
void openCartoon(){
	initUi();
	setUiWithColor(WID/2-11,HIG/2,"☆",0xe);
	setUiWithColor(WID/2+9,HIG/2,"☆",0xe);
	draw();
	int gate=1;
	Sleep(gate);
	setUiWithColor(WID/2-9,HIG/2,"*",0x6);
	setUiWithColor(WID/2+8,HIG/2,"*",0x6);
	draw();
	Sleep(gate);
	setUiWithColor(WID/2-8,HIG/2,":",0x7);
	setUiWithColor(WID/2+7,HIG/2,":",0x7);
	draw();
	Sleep(gate);
	setUiWithColor(WID/2-7,HIG/2,".",0x8);
	setUiWithColor(WID/2+6,HIG/2,".",0x8);
	draw();
	Sleep(gate);
	setUiWithColor(WID/2-6,HIG/2,".",0x9);
	setUiWithColor(WID/2+5,HIG/2,".",0x9);
	draw();
	Sleep(gate);
	setUiWithColor(WID/2-5,HIG/2,"o",0x1);
	setUiWithColor(WID/2+4,HIG/2,"o",0x1);
	draw();
	Sleep(gate);
	setUiWithColor(WID/2-4,HIG/2,"(",0x2);
	setUiWithColor(WID/2+3,HIG/2,")",0x2);
	draw();
	Sleep(gate);
	setUiWithColor(WID/2-3,HIG/2,"≧",0x1);
	setUiWithColor(WID/2+1,HIG/2,"≦",0x1);
	draw();
	Sleep(gate);
	setUiWithColor(WID/2-1,HIG/2,"▽",0x2);
	draw();
	Sleep(gate);
//	initUi();
	setUi(WID/2-8,HIG/2+3,"按任意键继续...");
	draw();
	getch();
	clsBuffer();
}
void emoji(){
	initUi();
	int gap=25;
	setUiWithColor(WID/2-6,HIG/2,"φ(*￣0￣)",0x1);
	draw();
	Sleep(gap);
	initUi();
	setUiWithColor(WID/2-6,HIG/2,"φ(*￣0￣)",0x2);
	draw();
	Sleep(gap);
	initUi();
	setUiWithColor(WID/2-6,HIG/2,"q(≧▽≦q)",0x3);
	draw();
	Sleep(gap);
	initUi();
	setUiWithColor(WID/2-6,HIG/2,"ψ(｀?′)ψ",0x4);
	draw();
	Sleep(gap);
	initUi();
	setUiWithColor(WID/2-6,HIG/2,"（￣︶￣）↗　",0x5);
	draw();
	Sleep(gap);
	initUi();
	setUiWithColor(WID/2-6,HIG/2,"*^____^*",0x6);
	draw();
	Sleep(gap);
	initUi();
	setUiWithColor(WID/2-6,HIG/2,"(～￣▽￣)～",0x7);
	draw();
	Sleep(gap);
	initUi();
	setUiWithColor(WID/2-6,HIG/2,"[]~(￣▽￣)~*",0x8);
	draw();
	Sleep(gap);
	initUi();
	setUiWithColor(WID/2-6,HIG/2,"O(∩_∩)O",0x9);
	draw();
	Sleep(gap);
	initUi();
	setUiWithColor(WID/2-6,HIG/2,"o((>ω< ))o",0xA);
	draw();
	Sleep(gap);
	initUi();
	setUiWithColor(WID/2-6,HIG/2,"ㄟ(≧◇≦)ㄏ",0xB);
	draw();
	Sleep(gap);
	initUi();
	setUiWithColor(WID/2-6,HIG/2,"§(*￣▽￣*)§",0xC);
	draw();
	Sleep(gap);
	initUi();
	setUiWithColor(WID/2-10,HIG/2,"(*≧︶≦))(￣▽￣* )ゞ",0xD);
	draw();
	Sleep(gap);
	initUi();
	setUiWithColor(WID/2-6,HIG/2,"（〃｀ 3′〃）",0xE);
	draw();
	Sleep(gap);
	initUi();
	setUiWithColor(WID/2-10,HIG/2,"(*≧︶≦))(￣▽￣* )ゞ",0xF);
	draw();
	Sleep(gap);
	setUiWithColor(WID/2-10,HIG/2,"(*≧︶≦))(￣▽￣* )ゞ",0xF1);
	draw(); 
	int i;
	for(i=0;HIG/2+i<HIG&&WID/2+10+i<WID;i++){
		setBufferColor(WID/2-10-2*i,HIG/2-i,WID/2+10+2*i,HIG/2+i,0xF1);
		draw();
	}
	setBufferColor(0,0,WID-1,HIG-1,0xF1);
	draw();
	setUiBorder(' ');
	draw();
	Sleep(gap);
}
void emojiCartoon(){
	int i;
	for(i=0;;i++){
		if(WID/2-10-i==1){
			setUi(0,HIG/2,"(*≧︶≦)O  ");
			draw();
			break;
		}
		initUi();
		setUiBorder(' ');
		setBufferColor(0,0,WID-1,HIG-1,0xF1);
		setUi(WID/2-10-i,HIG/2,"(*≧︶≦)O");
		setUi(WID/2+i,HIG/2,"(￣▽￣* )ゞ");
		draw();
	}
	//小人 
	WORD sunColor=0x04;
	setUi(WID/2-2,HIG-1,"(°o)");
	setBufferColor(WID/2-2,HIG-1,WID/2+2,HIG-1,sunColor);
	draw();
	setUi(WID/2-2,HIG-1,"     ");
	setUi(WID/2-2,HIG-2,"(°o)");
	setBufferColor(WID/2-2,HIG-2,WID/2+2,HIG-2,sunColor);
	draw();
	setUi(WID/2-2,HIG-1,"/   \\");
	draw();
	//夜晚
	WORD nightColor=0x04;
	for(i=0;;i++){
		if(WID/2+2+i==WID){
			setBufferColor(0,0,WID-1,HIG-1,nightColor);
			break;
		}
		if(HIG-2-i<0){
			setBufferColor(WID/2-2-i,0,WID/2+2+i,HIG-1,nightColor);
			draw(); 
		}else{
			setBufferColor(WID/2-2-i,HIG-2-i,WID/2+2+i,HIG-1,nightColor);
			draw();	
		}
	}
	setBufferColor(WID/2-2,HIG-2,WID/2+2,HIG-1,0x4F);
	draw();
	//星星
	WORD starColor=0x6;
	setUiWithColor(0,HIG/2,"☆☆☆☆☆",starColor);
	setUiWithColor(WID-12,HIG/2,"☆☆☆☆☆☆",starColor);
	draw(); 
	int gap=500;
	Sleep(gap);
	//移动星星
	setUiWithColor(5,3,"☆",starColor);
	setUi(0,HIG/2,"  ");
	draw();
	Sleep(gap);
	setUiWithColor(18,7,"☆",starColor);
	setUi(0,HIG/2,"    ");
	draw();
	Sleep(gap);
	setUiWithColor(15,2,"☆",starColor);
	setUi(0,HIG/2,"      ");
	draw();
	Sleep(gap);
	setUiWithColor(4,8,"☆",starColor);
	setUi(0,HIG/2,"        ");
	draw();
	Sleep(gap);
	setUiWithColor(25,3,"☆",starColor);
	setUi(0,HIG/2,"          ");
	draw();
	Sleep(gap);
	
	setUiWithColor(33,1,"☆",starColor);
	setUi(WID-12,HIG/2,"  ");
	draw();
	Sleep(gap);
	setUiWithColor(50,3,"☆",starColor);
	setUi(WID-12,HIG/2,"    ");
	draw();
	Sleep(gap);
	setUiWithColor(60,1,"☆",starColor);
	setUi(WID-12,HIG/2,"      ");
	draw();
	Sleep(gap);
	setUiWithColor(70,3,"☆",starColor);
	setUi(WID-12,HIG/2,"        ");
	draw();
	Sleep(gap);
	setUiWithColor(78,1,"☆",starColor);
	setUi(WID-12,HIG/2,"          ");
	draw();
	Sleep(gap);
	setUiWithColor(60,7,"☆",starColor);
	setUi(WID-12,HIG/2,"            ");
	draw();
	Sleep(gap);
	WORD moonColor=0xEE;
	setBufferColor(69,11,71,11,moonColor);
	Sleep(gap);
	draw();
	setBufferColor(71,10,72,10,moonColor);
	Sleep(gap);
	draw();
	setBufferColor(72,9,73,9,moonColor);
	Sleep(gap);
	draw();
	setBufferColor(73,8,73,8,moonColor);
	Sleep(gap);
	draw();
	setBufferColor(66,12,69,12,moonColor);
	Sleep(gap);
	draw();
	setUiWithColor(67,13,"↗",0xE); 
	Sleep(gap);
	draw();
	setUiWithColor(54,14,"假装这是一个月亮",0xE);
	draw();
	setUi(WID/2-7,HIG/2,"按任意键继续..."); 
	draw();
	getch();
	clsBuffer();
	setUiWithColor(67,13,"   ",0xE);
}
int getRandomY(){
	return rand()%(HIG/4)+HIG/4;
}
WORD getBoomColor(){
	static state=0;
	state++;
	if(state==0){
		return 0xC4;
	}else if(state==1){
		return 0x91;
	}else if(state==2){
		return 0x19;
	}else if(state==3){
		return 0x4D;
	}else if(state==4){
		return 0x4C;
	}else if(state==5){
		return 0x4C; 
	}else{
		state=0;
		return 0xFF;
	}
}
void fire(){
	setUiWithColor(54,14,"                ",0xE);
	setUi(WID/2-7,HIG/2,"               ");
	draw(); 
	WORD moveColor=0xC4;
	WORD boomColor=0xC4;
	WORD t;
	int i=0;
	int y=getRandomY();
	while(1){
		t=uiColor[HIG-3-i][WID/2];
		uiColor[HIG-3-i][WID/2]=moveColor;
		draw();
		uiColor[HIG-3-i][WID/2]=t;
		i++;
		if(HIG-3-i<y){
			break;
		}
	}
	//boom;
	WORD temp[40];
	int x=WID/2;
	//第一层 3个 (x+1,y+1) (x-1,y) (x,y-1);
	boomColor=getBoomColor(); 
	temp[0]=uiColor[y+1][x+1];
	temp[1]=uiColor[y+1][x-1];
	temp[2]=uiColor[y-1][x];
	uiColor[y+1][x+1]=boomColor;
	uiColor[y+1][x-1]=boomColor;
	uiColor[y-1][x]=boomColor;
	draw();
	uiColor[y+1][x+1]=temp[0];
	uiColor[y+1][x-1]=temp[1];
	uiColor[y-1][x]=temp[2];
	//第二层 9个
	boomColor=getBoomColor(); 
	temp[0]=uiColor[y-2][x-1]; 
	temp[1]=uiColor[y-2][x+1]; 
	temp[2]=uiColor[y][x-2];
	temp[3]=uiColor[y] [x+2];
	temp[4]=uiColor[y+2][x-2];
	temp[5]=uiColor[y+2][x+2];
	temp[6]=uiColor[y+2][x];
	temp[7]=uiColor[y+3][x+1];
	temp[8]=uiColor[y+3][x-1];
	uiColor[y-2][x-1]=boomColor; 
	uiColor[y-2][x+1]=boomColor; 
	uiColor[y][x-2]=boomColor;
	uiColor[y] [x+2]=boomColor;
	uiColor[y+2][x-2]=boomColor;
	uiColor[y+2][x+2]=boomColor;
	uiColor[y+2][x]=boomColor;
	uiColor[y+3][x+1]=boomColor;
	uiColor[y+3][x-1]=boomColor;
	draw();
	uiColor[y-2][x-1]=temp[0]; 
	uiColor[y-2][x+1]=temp[1]; 
	uiColor[y][x-2]=temp[2];
	uiColor[y] [x+2]=temp[3];
	uiColor[y+2][x-2]=temp[4];
	uiColor[y+2][x+2]=temp[5];
	uiColor[y+2][x]=temp[6];
	uiColor[y+3][x+1]=temp[7];
	uiColor[y+3][x-1]=temp[8];
	//第三层 13个
	boomColor=getBoomColor();
	temp[0]=uiColor[y-2][x-2];
	temp[1]=uiColor[y-2][x+2];
	temp[2]=uiColor[y-1][x-3];
	temp[3]=uiColor[y-1][x+3];
	temp[4]=uiColor[y][x-4];
	temp[5]=uiColor[y][x+4];
	temp[6]=uiColor[y+2][x-4];
	temp[7]=uiColor[y+2][x+4];
	temp[8]=uiColor[y+3][x-3];
	temp[9]=uiColor[y+3][x+3];
	temp[10]=uiColor[y+4][x-2];
	temp[11]=uiColor[y+4][x+2];
	temp[12]=uiColor[y+4][x];
	uiColor[y-2][x-2]=boomColor;
	uiColor[y-2][x+2]=boomColor;
	uiColor[y-1][x-3]=boomColor;
	uiColor[y-1][x+3]=boomColor;
	uiColor[y][x-4]=boomColor;
	uiColor[y][x+4]=boomColor;
	uiColor[y+2][x-4]=boomColor;
	uiColor[y+2][x+4]=boomColor;
	uiColor[y+3][x-3]=boomColor;
	uiColor[y+3][x+3]=boomColor;
	uiColor[y+4][x-2]=boomColor;
	uiColor[y+4][x+2]=boomColor;
	uiColor[y+4][x]=boomColor;
	draw();
	uiColor[y-2][x-2]=temp[0];
	uiColor[y-2][x+2]=temp[1];
	uiColor[y-1][x-3]=temp[2];
	uiColor[y-1][x+3]=temp[3];
	uiColor[y][x-4]=temp[4];
	uiColor[y][x+4]=temp[5];
	uiColor[y+2][x-4]=temp[6];
	uiColor[y+2][x+4]=temp[7];
	uiColor[y+3][x-3]=temp[8];
	uiColor[y+3][x+3]=temp[9];
	uiColor[y+4][x-2]=temp[10];
	uiColor[y+4][x+2]=temp[11];
	uiColor[y+4][x]=temp[12];
	//第四层 17个
	temp[0]=uiColor[y-1][x-3];
	temp[1]=uiColor[y-1][x-1];
	temp[2]=uiColor[y-1][x+3];
	temp[3]=uiColor[y-1][x+1];
	temp[4]=uiColor[y+1][x-5];
	temp[5]=uiColor[y+1][x+5];  
  	temp[6]=uiColor[y+3][x-5];
  	temp[7]=uiColor[y+3][x+5];
  	temp[8]=uiColor[y+4][x+4];
  	temp[9]=uiColor[y+4][x-4];
  	temp[10]=uiColor[y+5][x-3];
  	temp[11]=uiColor[y+5][x-1];
  	temp[12]=uiColor[y+5][x+3];
  	temp[13]=uiColor[y+5][x+1];
  	temp[14]=uiColor[y+6][x-2]; 
  	temp[15]=uiColor[y+6][x+2];
	temp[16]=uiColor[y+6][x]; 
	boomColor=getBoomColor(); 
	uiColor[y-1][x-3]=boomColor;
	uiColor[y-1][x-1]=boomColor;
	uiColor[y-1][x+3]=boomColor;
	uiColor[y-1][x+1]=boomColor;
	uiColor[y+1][x-5]=boomColor;
	uiColor[y+1][x+5]=boomColor;  
  	uiColor[y+3][x-5]=boomColor;
  	uiColor[y+3][x+5]=boomColor;
  	uiColor[y+4][x+4]=boomColor;
  	uiColor[y+4][x-4]=boomColor;
  	uiColor[y+5][x-3]=boomColor;
  	uiColor[y+5][x-1]=boomColor;
  	uiColor[y+5][x+3]=boomColor;
  	uiColor[y+5][x+1]=boomColor;
  	uiColor[y+6][x-2]=boomColor; 
  	uiColor[y+6][x+2]=boomColor;
	uiColor[y+6][x]=boomColor; 
	draw();
	//最后一层
	 
	 uiColor[y+5][x-1]=temp[11];
	 uiColor[y+5][x+1]=temp[13];
	 uiColor[y+6][x]=temp[16];
//	 uiColor
	 temp[16]=uiColor[y][x]; 
	 temp[17]=uiColor[y+7][x+1];
	 temp[18]=uiColor[y+7][x-1];
	 temp[19]=uiColor[y+8][x];
	 boomColor=getBoomColor();//红色 
	 uiColor[y][x]=boomColor;
	 uiColor[y+7][x+1]=boomColor;
	 uiColor[y+7][x-1]=boomColor;
	 uiColor[y+8][x]=boomColor;
	 draw();
	 Sleep(500);
	setUi(x-8,y-3,"假装这是一颗爱心");
	setUi(x-1,y-2,"QAQ");
	draw();
	Sleep(1000);
	 boomColor=getBoomColor();//白色 
	 uiColor[y][x]=boomColor;
	 uiColor[y+7][x+1]=boomColor;
	 uiColor[y+7][x-1]=boomColor;
	 uiColor[y+8][x]=boomColor;
	uiColor[y-1][x-3]=boomColor;
	uiColor[y-1][x-1]=boomColor;
	uiColor[y-1][x+3]=boomColor;
	uiColor[y-1][x+1]=boomColor;
	uiColor[y+1][x-5]=boomColor;
	uiColor[y+1][x+5]=boomColor;  
  	uiColor[y+3][x-5]=boomColor;
  	uiColor[y+3][x+5]=boomColor;
  	uiColor[y+4][x+4]=boomColor;
  	uiColor[y+4][x-4]=boomColor;
  	uiColor[y+5][x-3]=boomColor;
  	uiColor[y+5][x+3]=boomColor;
  	uiColor[y+6][x-2]=boomColor; 
  	uiColor[y+6][x+2]=boomColor;
	draw();
	uiColor[y-1][x-3]=temp[0];
	uiColor[y-1][x-1]=temp[1];
	uiColor[y-1][x+3]=temp[2];
	uiColor[y-1][x+1]=temp[3];
	uiColor[y+1][x-5]=temp[4];
	uiColor[y+1][x+5]=temp[5];  
  	uiColor[y+3][x-5]=temp[6];
  	uiColor[y+3][x+5]=temp[7];
  	uiColor[y+4][x+4]=temp[8];
  	uiColor[y+4][x-4]=temp[9];
  	uiColor[y+5][x-3]=temp[10];
  	uiColor[y+5][x+3]=temp[12];
  	uiColor[y+6][x-2]=temp[14]; 
  	uiColor[y+6][x+2]=temp[15];
	uiColor[y][x]=temp[16]; 
	uiColor[y+7][x+1]=temp[17];
	uiColor[y+7][x-1]=temp[18];
	uiColor[y+8][x]=temp[19];
	setUi(x-8,y-3,"                ");
	setUi(x-1,y-2,"   ");
	setUi(x-7,HIG/2,"按任意键发射...");
	draw();
	getch();
	clsBuffer();
	setUi(x,y,"               "); 
}
int main(){
	init();//init
	openCartoon();//开屏动画 
	emoji();//emoji
	emojiCartoon();
	while(1){
		fire();//发射烟花 
	}
	//释放内存 
	int i;
	for(i=0;i<HIG;i++){
		free(ui[i]);
		free(uiColor[i]);
		ui[i]=NULL;
		uiColor[i]=NULL;
	}
	getch();
	return 0;
} 

#include<bits/stdc++.h>
#include<graphics.h>
#include<windows.h>
using namespace std;
音乐加载 
MUSIC music;
const char* music1="第一.mp3";
music.OpenFile(music1);

#define random(a,b) (rand()%(b-a)+a)
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
int time_;
struct z{
	double tipe,up,left,x,y,attack,tan=1,xuan;
	int time;
}zidan[999999];
int muchzidan;
对话窗口 
void text(){//MessageBox
	if(textid!=0){
		if(KEY_DOWN('Q'))textA=1;
		if(KEY_DOWN('P')&&textC==0)if((textid==13&&textB<4)||((textid==14||textid==15)&&textB<2)||(textid==84&&textB<9)||(textid==101&&textB<2))textB++,textC=1;
		if(textC==1&&!KEY_DOWN('P'))textC=0;
		if(textA==1&&!KEY_DOWN('Q')){
			if(textid==101){
				while(1){
					play_tower();
					if(endgame==1)break;
				}
				textid=102;
			}
			textid=0,textA=0,textB=1;
			return;
		}
		setfont(25,0,"宋体");
		if((textid==13&&textB<4)||((textid==14||textid==15)&&textB<2)||(textid==84&&textB<9)||(textid==101&&textB<2))setfillcolor(EGEARGB(160,255,255,0));
		else setfillcolor(EGEARGB(160,255,255,255));
		ege_fillrect(10,SCR_HEIGHT-210,SCR_WIDTH-20,200);
		setfillcolor(EGEARGB(160,0,0,0));
		ege_fillrect(30,SCR_HEIGHT-190,SCR_WIDTH-60,160);
		setcolor(EGEARGB(160,255,255,255));
		if(textid==1){
			outtextxy(35,SCR_HEIGHT-185,"wsad移动，E来阅读/存档等，Q关闭对话");
			outtextxy(35,SCR_HEIGHT-155,"边框为黄色的对话可以按P来继续阅读");
			outtextxy(35,SCR_HEIGHT-125,"Zhoumy:向右开始你的探索吧");
		}
子弹 
void shoot(int x,int y/*本身的*/,int x1,int y1/*点出的*/,int r,double pian,double much,int tipes,int tipe,int attack,double speed,int tan){
	double q,qwq;
	if(much-1!=0)qwq=(2*-pian)/(much-1);
	else qwq=0;
	int qx,qy;
	qx=x1,qy=y1; 
	for(double i=pian;i<=-pian;i+=qwq){
		muchzidan++;
		zidan[muchzidan].tipe=tipes;
		if(tipe==0){
			x1=cos(i)*(qx-x)-sin(i)*(qy-y)+x;
			y1=cos(i)*(qy-y)+sin(i)*(qx-x)+y;	
		}
		q=sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1));
		zidan[muchzidan].up=-((y1-y)/q*speed);
		zidan[muchzidan].left=-((x1-x)/q*speed);
		zidan[muchzidan].x=x+15+r*zidan[muchzidan].left/2;
		zidan[muchzidan].y=y+20+r*zidan[muchzidan].up/2;
		zidan[muchzidan].tan=1+tan;
		zidan[muchzidan].attack=attack;
		zidan[muchzidan].time=0;
		if(qwq==0)break;
	}
}  

void getZoomImage(PIMAGE pimg, const char* fileName, int width, int height){
	PIMAGE temp = newimage();
	getimage(temp, fileName);
	if (getwidth(pimg) != width || getheight(pimg) != height)
		resize(pimg, width, height);
	putimage(pimg, 0, 0, width, height, temp, 0, 0, getwidth(temp), getheight(temp));
	delimage(temp);
}
int main(){
	最小化窗口 
	HWND hwndaa;
	hwndaa=FindWindow("ConsoleWindowClass",NULL);
	//if(hwndaa)ShowWindow(hwndaa,SW_HIDE);
	initgraph(480,480);
	setcaption("传说之下之大战Zhoumy");	
		导入内容 
	freopen("新手村可走.txt","r",stdin);
	for(int i=0;i<60;i++)for(int j=0;j<60;j++)for(int k=0;k<=4;k++)cin>>moveRPG[0][i][j][k];
	fclose(stdin);
		显示图像 
		PIMAGE chuan=newimage(); 
		putimage_withalpha(NULL,ditu,0,0);
				putimage_withalpha(NULL,map2d_word[4],SCR_WIDTH/2-player.x,SCR_HEIGHT/2-player.y+24);
				
	getZoomImage(tower,"lib/炮塔.png",52,32);
	getZoomImage(ditu,"lib/地图.png",630,480);
	
	for(int i=0;i<=3;i++){
		for(int j=0;j<=2;j++){
			player_RPG[i][j]=newimage();
			getimage(player_RPG[i][j],PLAYER,49*j,49*i,49,49);
		}
	}
		显示数字 
		char s[5];//显示时间 
		sprintf(s,"%d  ",time_);
		~~~~~~~~~~~~~
		player.time++;
		setcolor(EGERGB(125,255,125)); 
		setfont(30, 0,"宋体");
		char s[5];
		sprintf(s,"%d$",player.money);
		outtextxy(1,1, s);
		setcolor(EGERGB(255,0,125)); 
		sprintf(s,"%dblood",int(player.blood));
		outtextxy(1,41, s);
		setfont(40, 0,"宋体");
		outtextxy(1,1,s);
		透明绘画 
		setfillcolor(EGEARGB(200,256,80,80));
		ege_fillrect(450,0,480,30);	
		鼠标 
		int x,y;
    	mousepos(&x, &y);
		透明椭圆 
		setfillcolor(EGEARGB(200,255,0,0));
		ege_fillellipse(x-10,y-10,20,20);	
		左右键 
    	KEY_DOWN(VK_RBUTTON)&&KEY_DOWN(VK_LBUTTON)
		存档 
			if(MessageBox(NULL,"确认存储？","Zhoumy", MB_ICONINFORMATION|MB_OKCANCEL)==1){
				freopen("game.txt","w",stdout);
				cout<<setbullet<<endl;
				for(int i=1;i<=setbullet;i++){
					cout<<make_bullet[i].time<<" "<<make_bullet[i].tipe<<" "<<make_bullet[i].x1<<" "<<make_bullet[i].x2<<" "<<make_bullet[i].y1<<" "<<make_bullet[i].y2<<endl;
				}
				MessageBox(NULL,"存储完毕","Zhoumy", MB_ICONINFORMATION|MB_OK);
				fclose(stdout);	
			}
			if(MessageBox(NULL,"确认导入？","Zhoumy", MB_ICONINFORMATION|MB_OKCANCEL)==1){
				freopen("game.txt","r",stdin);
				cin>>setbullet;
				for(int i=1;i<=setbullet;i++){
					cin>>make_bullet[i].time>>make_bullet[i].tipe>>make_bullet[i].x1>>make_bullet[i].x2>>make_bullet[i].y1>>make_bullet[i].y2;	
				}
				MessageBox(NULL,"导入成功","Zhoumy", MB_ICONINFORMATION|MB_OK);
				fclose(stdin);
				cout<<setbullet; 
			}
		字体+字符 
		setfont(60, 0,"宋体");
		outtextxy(120,100,"纪元战争-前传0.4");
		跳跃
		if(KEY_DOWN('W')&&player.can_jump>0&&player.jump_key==1){
				player.y_speed=23,player.can_jump--,player.jump_key=0;
				if(player.can_jump==0&&rate[2]==0){
					rate[2]=1;
					//MessageBox(NULL,"新技能？    已达成","进度", MB_ICONINFORMATION|MB_OK);
				}
			}
			if(!KEY_DOWN('W'))player.jump_key=1;
			player.y_speed+=G;
			for(int i=1;i<=(abs(player.y_speed)+4)/5;i++){
				if(player.y_speed<0)player.y+=5;
				if(player.y_speed>0)player.y-=5;
				if(player.map_>=0){
					if((play_map[player.map_][int(player.y)/bar_size][int(player.x)/bar_size]==1||play_map[player.map_][int(player.y)/bar_size][int(player.x-2)/bar_size]==1)&&player.y_speed<0){
						player.y_speed=0;
						player.can_jump=2;
						while(play_map[player.map_][int(player.y)/bar_size][int(player.x)/bar_size]==1||play_map[player.map_][int(player.y)/bar_size][int(player.x-2)/bar_size]==1)player.y--;
					}
					if((play_map[player.map_][int(player.y)/bar_size][int(player.x)/bar_size]==1||play_map[player.map_][int(player.y)/bar_size][int(player.x-2)/bar_size]==1)&&player.y_speed>0){
						player.y_speed=0;
						while(play_map[player.map_][int(player.y)/bar_size][int(player.x)/bar_size]==1||play_map[player.map_][int(player.y)/bar_size][int(player.x-2)/bar_size]==1)player.y++;
					}
				}
				if(player.map_<0){
					if((move2d[-1-player.map_][int(player.x)/24][int(player.y+3)/24]==1||move2d[-1-player.map_][int(player.x)/24][int(player.y+3)/24]==2)&&player.y_speed<0){
						player.can_jump=2;
						player.y_speed=0;
						while(move2d[-1-player.map_][int(player.x)/24][int(player.y)/24]==1)player.y--;
					}
					if((move2d[-1-player.map_][int(player.x)/24][int(player.y+3)/24]==1||move2d[-1-player.map_][int(player.x)/24][int(player.y+3)/24]==2)&&player.y_speed>0){
						player.y_speed=0;
						while(move2d[-1-player.map_][int(player.x)/24][int(player.y)/24]==1)player.y++;
					}
				}
			}
		}
		else{
			if(move2d[-1-player.map_][int(player.x)/24][int(player.y)/24]==4)hurt(0.8,2);
			player.can_jump=1;
			player.y_speed=0;
			if(KEY_DOWN('W')&&move2d[-1-player.map_][int(player.x)/24][int(player.y)/24]==2&&move2d[-1-player.map_][int(player.x)/24][int(player.y-8)/24]!=1)player.y-=8;
			else if(KEY_DOWN('W')&&(move2d[-1-player.map_][int(player.x)/24][int(player.y)/24]==3||move2d[-1-player.map_][int(player.x)/24][int(player.y)/24]==4)&&move2d[-1-player.map_][int(player.x)/24][int(player.y-8)/24]!=1)player.y-=6.5;
			if(KEY_DOWN('S')&&move2d[-1-player.map_][int(player.x)/24][int(player.y)/24]==2&&move2d[-1-player.map_][int(player.x)/24][int(player.y+8)/24]!=1)player.y+=8;
			else if(KEY_DOWN('S')&&(move2d[-1-player.map_][int(player.x)/24][int(player.y)/24]==3||move2d[-1-player.map_][int(player.x)/24][int(player.y)/24]==4)&&move2d[-1-player.map_][int(player.x)/24][int(player.y+8)/24]!=1)player.y+=6.5;
		} 
	}
	return 0;
}

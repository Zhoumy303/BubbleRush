#include<bits/stdc++.h>
#include<graphics.h>
#include<windows.h>
using namespace std;
#define random(a,b) (rand()%(b-a)+a)
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
void getZoomImage(PIMAGE pimg, const char* fileName, int width, int height){
	PIMAGE temp = newimage();
	getimage(temp, fileName);
	if (getwidth(pimg) != width || getheight(pimg) != height)
		resize(pimg, width, height);
	putimage(pimg, 0, 0, width, height, temp, 0, 0, getwidth(temp), getheight(temp));
	delimage(temp);
}
struct Player{
	double x,y,angle,speed=20,ang=0.2/*角度偏移量*/,dashCD,die,dash_angle;
	int bubble=0,bubble_max=2,orient=2,spawn=1,secret,blood=2,max_blood=2,save_max_blood=2,save_max_bubble=2,save_bubble=2,dash_tipe;
}player;
int touch[9999][9999],unit=45/*每个格子占几个像素*/;
/*void text(){//MessageBox
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
}*/
struct Item{
	double x,y,x1,y1;
	int tipe/*1-bubble 2-漩涡 3-门 4-瓶子*/;
}item[999];

struct Fish{
	double x,y,angle,speed=20,ang=0.2/*角度偏移量*/;
	int tipe/*1-绕圈*/,orient=2;
}fish[999];
int much_item,item_use[999],item_use_save[999],much_fish;
//52/63
void door_set(int x,int y,int x1,int y1,int tipe){
	for(int i=int(-x/unit)+22;i<=int(-x1/unit)+22;i++){
		for(int j=int(-y/unit)+12;j<=int(-y1/unit)+14;j++){
			touch[i][j]=tipe;
		}
	}
}
void storage(int level){
	if(level==0){
		player.save_max_blood=2,player.save_bubble=0,player.save_max_bubble=2;
	}
	if(level==1){
		player.save_max_blood=player.max_blood,player.save_bubble=player.bubble,player.save_max_bubble=player.bubble_max;
	}
	for(int i=1;i<=much_item;i++){
		item_use_save[i]=item_use[i];
	}
}
void spawn(){
	player.bubble=player.save_bubble;
	player.bubble_max=player.save_max_bubble;
	player.max_blood=player.save_max_blood;
	player.blood=player.max_blood;
	if(player.spawn==1){
		player.x=429.316;
		player.y=-954.456;
		player.angle=3.14;
	}
	if(player.spawn==2){
		player.x=-4103.64;
		player.y=-2048.74;
		player.angle=3.14;
	}
	for(int i=1;i<=100;i++)item_use[i]=item_use_save[i];
}

void seting(){
		item[1].x=-1463;
		item[1].y=-2271;
		item[1].tipe=1;
		item[2].x=59;
		item[2].y=-2020;
		item[2].tipe=2;
		item[3].x=-2286.3;
		item[3].y=-1000;//-2286.12 -999.418->-2437.71 -1335.34
		item[3].x1=-2437.71;
		item[3].y1=-1335.34;
		door_set(item[3].x,item[3].y,item[3].x1,item[3].y1,1);
		item[3].tipe=3;
		item[7].x=-80.1982;//第一个隐藏瓶子 
		item[7].y=-172.027;
		item[7].tipe=4;
		
		item[4].x=-2945.74;
		item[4].y=-2179.22;
		item[4].tipe=1;
		item[5].x=-2651.93;
		item[5].y=-1933.7;
		item[5].tipe=1;
		//item[6].x=-3804.96;
		//item[6].y=-1810.93;//-2286.12 -999.418->-2437.71 -1335.34
		//item[6].x1=-3906.94;
		//item[6].y1=-2187.13;
		//door_set(item[6].x,item[6].y,item[6].x1,item[6].y1,1);
		item[6].tipe=3;
		item[9].x=-5923;
		item[9].y=-957;
		item[9].tipe=1;
		item[8].x=-6499.06;
		item[8].y=-1999.85;
		item[8].tipe=2;
		much_item=9;
		
		fish[1].x=-4983.49;
		fish[1].y=-1719.79;
		fish[1].tipe=1;
		fish[1].ang=0.2;
		fish[1].speed=20;
		fish[2].x=-4546.49;
		fish[2].y=-1892.79;
		fish[2].tipe=1;
		fish[2].ang=0.3;
		fish[2].speed=20;
		fish[3].x=-5514.81;
		fish[3].y=-1061.32;
		fish[3].tipe=1;
		fish[3].ang=-0.2;
		fish[3].speed=15;
		fish[4].x=-5484.81;
		fish[4].y=-1061.32;
		fish[4].tipe=1;
		fish[4].ang=-0.17;
		fish[4].speed=25;
		much_fish=4;
		//-4546.82 -1792.78
}
int midx,midy;
int main(){
	HWND hwndaa;
	hwndaa=FindWindow("ConsoleWindowClass",NULL);
	//if(hwndaa)ShowWindow(hwndaa,SW_HIDE);
	initgraph(1920,1080);
	setcaption("嘤");	
	PIMAGE player1=newimage(); 
	PIMAGE player2=newimage();
	PIMAGE player1back=newimage(); 
	PIMAGE player2back=newimage();
	PIMAGE fish1=newimage(); 
	PIMAGE fish2=newimage();
	PIMAGE fish1back=newimage(); 
	PIMAGE fish2back=newimage();
	PIMAGE map1=newimage(); 
	PIMAGE map1hide=newimage(); 
	PIMAGE map2=newimage(); 
	PIMAGE UI=newimage(); 
	PIMAGE button=newimage(); 
	PIMAGE bubble3=newimage(); 
	PIMAGE vortex[8];
	PIMAGE door=newimage(); 
	PIMAGE gone=newimage(); 
	PIMAGE bottle=newimage(); 
	PIMAGE bottle_UI=newimage(); 
	PIMAGE bottle_bubble=newimage(); 
	for(int i=1;i<=7;i++)vortex[i]=newimage();
	getZoomImage(vortex[1],"assets/vortex1.png",800,800);
	getZoomImage(vortex[2],"assets/vortex2.png",800,800);
	getZoomImage(vortex[3],"assets/vortex3.png",800,800);
	getZoomImage(vortex[4],"assets/vortex4.png",800,800);
	getZoomImage(vortex[5],"assets/vortex5.png",800,800);
	getZoomImage(vortex[6],"assets/vortex6.png",800,800);
	getZoomImage(vortex[7],"assets/vortex7.png",800,800);
	getZoomImage(bottle,"assets/bottle.png",512,512);
	getZoomImage(bottle_UI,"assets/bottle.png",236,236);
	getZoomImage(bottle_bubble,"assets/bottle_bubble.png",236,236); 
	getZoomImage(map1,"assets/map1.png",1920*3,1080*3);
	getZoomImage(map1hide,"assets/map1hide.png",1920*3,1080*3);
	getZoomImage(map2,"assets/map2.png",1920*3,1080*3);
	getZoomImage(player1,"assets/player1.png",500,500);
	getZoomImage(player2,"assets/player2.png",500,500);
	getZoomImage(player1back,"assets/player1back.png",500,500);
	getZoomImage(player2back,"assets/player2back.png",500,500);
	getZoomImage(fish1,"assets/fish1.png",500,500);
	getZoomImage(fish2,"assets/fish2.png",500,500);
	getZoomImage(fish1back,"assets/fish1back.png",500,500);
	getZoomImage(fish2back,"assets/fish2back.png",500,500);
	getZoomImage(button,"assets/button.png",500,500);
	getZoomImage(door,"assets/door.png",2100,2100);
	getZoomImage(UI,"assets/ui.png",1920,1080);
	getZoomImage(gone,"assets/gone.png",1920,1080);
	getZoomImage(bubble3,"assets/bubble3.png",1000,1000);
				freopen("data/map1.save","r",stdin);
				for(int i=1;i<=128;i++){
					for(int j=1;j<=72;j++){
						cin>>touch[i][j];	
					}
				}
				int play=1;
				freopen("data/game.txt","r",stdin);
				for(int i=1;i<=128;i++){
					for(int j=1;j<=72;j++){
						cin>>touch[i+128][j];	
					}
				}
	seting();
	storage(0);
		player.spawn=2;
		storage(1);
	spawn();
	while(1){
		player.bubble=2;
		play++;
		if(player.y>-730&&player.x>-580&&player.x<345){
			player.secret=1;
			putimage_withalpha(NULL,map1hide,player.x,player.y);
		}
		else{
			player.secret=0;	
			putimage_withalpha(NULL,map1,player.x,player.y);
		}
			putimage_withalpha(NULL,map2,player.x+1920*3,player.y);
		//物品交互 
		for(int i=1;i<=much_item;i++){
			if(item_use[i]==0&&(i!=7||player.secret==1)){
				if(item[i].tipe==1){
					if(KEY_DOWN('Q')&&abs(player.x-item[i].x)<120&&abs(player.y-item[i].y)<120&&player.bubble<player.bubble_max){
						item_use[i]=1;
						player.bubble++;
					}
					putimage_withalpha(NULL,bubble3,player.x-item[i].x+510,player.y-item[i].y-30);
				}	
				if(item[i].tipe==2){
					if(abs(player.x-item[i].x)<120&&abs(player.y-item[i].y)<120&&player.die==0){
						player.die=35;
						midx=item[i].x,midy=item[i].y;
					}
					putimage_withalpha(NULL,vortex[play%7+1],player.x-item[i].x+540,player.y-item[i].y+150);
				}	
				if(item[i].tipe==3){
					putimage_withalpha(NULL,door,player.x-item[i].x-40,player.y-item[i].y-400);
				}	
				if(item[i].tipe==4){
					putimage_withalpha(NULL,bottle,player.x-item[i].x+610,player.y-item[i].y+310);
					if(KEY_DOWN('Q')&&abs(player.x-item[i].x)<120&&abs(player.y-item[i].y)<120){
						item_use[i]=1;
						player.bubble_max++;
					}
				}	
			}	
		}
		//鱼类显示
		for(int i=1;i<=much_fish;i++){
			if(fish[i].tipe==1){
				
				if(abs(player.x-fish[i].x)<60&&abs(player.y-fish[i].y)<60&&player.dashCD==0){
					player.blood--;
					player.dashCD=10; 
					player.dash_tipe=2;
					player.dash_angle=-fish[i].angle;
				}
				
				if(fish[i].angle/6.2831852<0.75&&fish[i].angle/6.2831852>0.25)fish[i].orient=2;
				else fish[i].orient=1;
				fish[i].angle+=fish[i].ang;
				fish[i].x+=fish[i].speed*cos(fish[i].angle);
				fish[i].y+=fish[i].speed*sin(fish[i].angle);
					
				if(fish[i].angle<0)fish[i].angle+=6.2831852;
				if(fish[i].angle>6.2831852)fish[i].angle-=6.2831852;
				if(fish[i].orient==1){
					if(play%4<2)putimage_rotate(NULL,fish1,player.x-fish[i].x+950,player.y-fish[i].y+540,0.5,0.5,-fish[i].angle,1,-1,0);
					else putimage_rotate(NULL,fish2,player.x-fish[i].x+950,player.y-fish[i].y+540,0.5,0.5,-fish[i].angle,1,-1,0);
				}
				if(fish[i].orient==2){
					if(play%4<2)putimage_rotate(NULL,fish1back,player.x-fish[i].x+950,player.y-fish[i].y+540,0.5,0.5,-fish[i].angle,1,-1,0);
					else putimage_rotate(NULL,fish2back,player.x-fish[i].x+950,player.y-fish[i].y+540,0.5,0.5,-fish[i].angle,1,-1,0);
				}
			}
		} 
		//玩家显示 
		if(player.angle/6.2831852<0.75&&player.angle/6.2831852>0.25)player.orient=2;
		else player.orient=1;
		if(player.orient==1){
			if(play%4<2)putimage_rotate(NULL,player1,1920/2-25,1080/2-5,0.5,0.5,-player.angle,1,-1,0);
			else putimage_rotate(NULL,player2,1920/2-25,1080/2-5,0.5,0.5,-player.angle,1,-1,0);
		}
		if(player.orient==2){
			if(play%4<2)putimage_rotate(NULL,player1back,1920/2-25,1080/2-5,0.5,0.5,-player.angle,1,-1,0);
			else putimage_rotate(NULL,player2back,1920/2-25,1080/2-5,0.5,0.5,-player.angle,1,-1,0);	
		}
		//UI显示 
		putimage_withalpha(NULL,UI,0,0);
		if(player.bubble<=0)putimage_withalpha(NULL,gone,117,-5);
		if(player.bubble<=1)putimage_withalpha(NULL,gone,160,-5);
		if(player.bubble_max>=3){
			if(player.bubble<=2)putimage_withalpha(NULL,bottle_UI,235,10);
			else putimage_withalpha(NULL,bottle_bubble,235,10);
		}
		if(player.blood<=1)putimage_withalpha(NULL,gone,-48,-3);
		//移动 
		if(player.die>0){
			player.die--;
			player.angle-=player.ang;
			if(player.die>30){
				player.x=midx+player.speed*1.5*cos(player.angle);
				player.y=midy+player.speed*1.5*sin(player.angle);	
			}
			else{
				player.x=midx+player.speed*1.5*cos(player.angle);
				player.y=midy+player.speed*1.5*sin(player.angle);
			}
			if(player.angle<0)player.angle+=6.2831852;
			if(player.die==0)spawn();
		}
		if(player.dashCD>0)player.dashCD--;
		if(KEY_DOWN('E')&&player.dashCD==0&&player.bubble>0){
			player.dash_tipe=1;
			player.dashCD=10,player.bubble--;
			if(player.die>0)player.die=-1;
		}
		if(player.dashCD>=7){
			int much;
			if(player.dash_tipe==1)much=7;
			else much=3;
			for(int i=1;i<=much;i++){
				//if(touch[int((player.x+player.speed*cos(player.angle))/unit)][int((player.y+player.speed*sin(player.angle))/unit)]==0){
				if(player.dash_tipe==2){
					if(touch[int(-(player.x-player.speed*cos(player.dash_angle))/unit+21)][int(-(player.y-player.speed*sin(player.dash_angle))/unit+13)]==0){
						player.x-=player.speed*cos(player.dash_angle);
						player.y-=player.speed*sin(player.dash_angle);	
					}
				}
				if(player.dash_tipe==1){
					if(touch[int(-(player.x-player.speed*cos(player.angle))/unit+21)][int(-(player.y-player.speed*sin(player.angle))/unit+13)]==0){
						player.x-=player.speed*cos(player.angle);
						player.y-=player.speed*sin(player.angle);	
					}
					for(int j=1;j<=much_item;j++){
						if(item_use[j]==0){
							if(item[j].tipe==3){
								if(player.y<item[j].y&&player.y>item[j].y1&&(abs(item[j].x-player.x)<40||abs(item[j].x1-player.x)<40)){	
									item_use[j]=1;
									door_set(item[j].x,item[j].y,item[j].x1,item[j].y1,0);
									if(j==6){
										player.spawn=2;
										storage(1);
									}
								}
							}	
						}
					}
				}
					
			}
			if(player.dashCD==7)player.die=0; 
		}
		if(player.dashCD<7&&player.die==0){
			int m=1;
			if(KEY_DOWN(VK_SHIFT))m=3;
			for(int i=1;i<=m;i++){
				if(KEY_DOWN(VK_SPACE)){
					if(touch[int(-(player.x+player.speed*cos(player.angle))/unit+21)][int(-(player.y+player.speed*sin(player.angle))/unit+13)]==0){
						player.x+=player.speed*cos(player.angle);
						player.y+=player.speed*sin(player.angle);	
					}
					cout<<player.x<<" "<<player.y<<endl; 
				}
			}
			if(KEY_DOWN('F')){
				player.angle-=player.ang;
				if(player.angle<0)player.angle+=6.2831852;
			}
			if(KEY_DOWN('J')){
				player.angle+=player.ang;
				if(player.angle>6.2831852)player.angle-=6.2831852;
			}		
		}
		
		if(KEY_DOWN('R')||player.blood==0){
			spawn();
		}
		Sleep(25);
		cleardevice();
	}
	return 0;
}

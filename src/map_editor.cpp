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
int touch[999][999];
int main(){
	HWND hwndaa;
	hwndaa=FindWindow("ConsoleWindowClass",NULL);
	int length,width,unit=15,mode=0,x1,y1,k=0,awa=0;
	cout<<"长：";
	cin>>length;
	cout<<"宽：";
	cin>>width;
	//if(hwndaa)ShowWindow(hwndaa,SW_HIDE);
	initgraph(length*unit,width*unit);
	PIMAGE map=newimage(); 
	getZoomImage(map,"assets/map2.png",length*unit,width*unit);
	while(1){
		int x,y;
    	mousepos(&x, &y);
		putimage_withalpha(NULL,map,0,0);
		for(int i=1;i<=length;i++){
			for(int j=1;j<=width;j++){
				if(touch[i][j]==2)setfillcolor(EGEARGB(100,255,0,0));
				if(touch[i][j]==1)setfillcolor(EGEARGB(100,100,100,100));
				else if(touch[i][j]==0)setfillcolor(EGEARGB(100,255,255,80));
				ege_fillrect(i*unit-unit+1,j*unit-unit+1,unit-2,unit-2);	
			}
		}
		if(KEY_DOWN(VK_RBUTTON)){
			if(k==0){
				k=1;
				MessageBox(NULL,"已切换为不可走","Zhoumy", MB_ICONINFORMATION|MB_OK);
			}
			else if(k==1){
				k=2;
				MessageBox(NULL,"已切换为陷阱","Zhoumy", MB_ICONINFORMATION|MB_OK);
			}
			else if(k==2){
				k=0;
				MessageBox(NULL,"已切换为可走","Zhoumy", MB_ICONINFORMATION|MB_OK);
			}
		}		
		if(mode==0){
			if(KEY_DOWN(VK_LBUTTON)){
				if(awa==0){
					x1=x/unit+1,y1=y/unit+1;
					awa=1;
				}
				if(awa==2){
					for(int i=min(x1,x/unit+1);i<=max(x1,x/unit+1);i++){
						for(int j=min(y1,y/unit+1);j<=max(y1,y/unit+1);j++){
							touch[i][j]=k;
						}
					}
					cout<<min(x1,x/unit+1)<<" "<<max(x1,x/unit+1)<<","<<min(y1,y/unit+1)<<" "<<max(y1,y/unit+1);
					awa=3;
				}
			}
			if(!KEY_DOWN(VK_LBUTTON)&&awa==1){
				awa=2;
			}
			if(!KEY_DOWN(VK_LBUTTON)&&awa==3){
				awa=0;
			}
		}
		if(mode==1){
			if(KEY_DOWN(VK_LBUTTON)){
				touch[x/unit+1][y/unit+1]=k;
			}
		}
		if(KEY_DOWN('P')){
			MessageBox(NULL,"已切换为单格模式","Zhoumy", MB_ICONINFORMATION|MB_OK);
			mode=1;
		}
		if(KEY_DOWN('O')){
			MessageBox(NULL,"已切换为范围模式","Zhoumy", MB_ICONINFORMATION|MB_OK);
			mode=0;
		}
		if(KEY_DOWN('U')){
			if(MessageBox(NULL,"确认存储？","Zhoumy", MB_ICONINFORMATION|MB_OKCANCEL)==1){
				freopen("data/game.txt","w",stdout);
				for(int i=1;i<=length;i++){
					for(int j=1;j<=width;j++){
						cout<<touch[i][j]<<" ";	
					}
					cout<<endl;
				}
				MessageBox(NULL,"存储完毕","Zhoumy", MB_ICONINFORMATION|MB_OK);
				//fclose(stdout);	
			}
		}
		if(KEY_DOWN('I')){
			if(MessageBox(NULL,"确认导入？","Zhoumy", MB_ICONINFORMATION|MB_OKCANCEL)==1){
				freopen("data/game.txt","r",stdin);
				for(int i=1;i<=length;i++){
					for(int j=1;j<=width;j++){
						cin>>touch[i][j];	
					}
				}
				MessageBox(NULL,"导入成功","Zhoumy", MB_ICONINFORMATION|MB_OK);
				//fclose(stdin);
			}
		}
		Sleep(200);
	}
	/*
	setcaption("地图编辑器");	
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
				freopen("data/game.txt","w",stdout);
				cout<<setbullet<<endl;
				for(int i=1;i<=setbullet;i++){
					cout<<make_bullet[i].time<<" "<<make_bullet[i].tipe<<" "<<make_bullet[i].x1<<" "<<make_bullet[i].x2<<" "<<make_bullet[i].y1<<" "<<make_bullet[i].y2<<endl;
				}
				MessageBox(NULL,"存储完毕","Zhoumy", MB_ICONINFORMATION|MB_OK);
				fclose(stdout);	
			}
			if(MessageBox(NULL,"确认导入？","Zhoumy", MB_ICONINFORMATION|MB_OKCANCEL)==1){
				freopen("data/game.txt","r",stdin);
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
	}*/
	return 0;
}

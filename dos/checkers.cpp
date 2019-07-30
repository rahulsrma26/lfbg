#include <fstream.h>
#include <dos.h>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
void waitretrace()
{asm mov dx,3DAh
l1:
 asm in al,dx
 asm and al,08h
 asm jnz l1
l2:
 asm in al,dx
 asm and al,08h
 asm jz  l2
}
void PORTPal(unsigned char ColorNo,unsigned char R,unsigned char G,unsigned char B)
{  if(ColorNo>7)ColorNo+=48; else if(ColorNo==6)ColorNo=20;
   outp(0x3c8,ColorNo);
   outp(0x3c9,R);   outp(0x3c9,G);   outp(0x3c9,B);
}
union REGS im,om;
int pal[16][3];
int menu_app=0,gam=0,p1_c=11,p2_c=11;
void credit()
{ im.x.ax=2;
  int86(0x33,&im,&om);
  cleardevice();
 struct palettetype pal;
 for (int i=1; i<10; i++)
  PORTPal(i, 0,0 ,0 );
  PORTPal(10,54,20,43 );
  PORTPal(0,0,0,0);
 settextstyle(3,0,6);
 setcolor(1);
 outtextxy(100,50,"P");
 setcolor(2);
 outtextxy(150,50,"R");
 setcolor(3);
 outtextxy(200,50,"O");
 setcolor(4);
 outtextxy(250,50,"G");
 setcolor(5);
 outtextxy(300,50,"R");
 setcolor(6);
 outtextxy(350,50,"A");
 setcolor(7);
 outtextxy(400,50,"M");
 setcolor(8);
 outtextxy(450,50,"E");
 setcolor(9);
 outtextxy(500,50,"R");
 setcolor(10);
 outtextxy(100,200,"PRASHANT VERMA");
 outtextxy(100,300,"RAHUL SHARMA");
 while(!kbhit())
 {
 for(i=1;i<18;i+=4)
 {waitretrace();
  for(int j=63;j<64;j++)
  {
    PORTPal(1,j/(2*abs(i-2)),j/(abs(i-2)),j/(2*abs(i-2)));
    PORTPal(2,j/(2*abs(i-4)),j/(abs(i-4)),j/(2*abs(i-4)));
    PORTPal(3,j/(2*abs(i-6)),j/(abs(i-6)),j/(2*abs(i-6)));
    PORTPal(4,j/(2*abs(i-8)),j/(abs(i-8)),j/(2*abs(i-8)));
    PORTPal(5,j/(2*abs(i-10)),j/(abs(i-10)),j/(2*abs(i-10)));
    PORTPal(6,j/(2*abs(i-12)),j/(abs(i-12)),j/(2*abs(i-12)));
    PORTPal(7,j/(2*abs(i-14) ),j/(abs(i-14)),j/(2*abs(i-14)));
    PORTPal(8,j/(2*abs(i-16)),j/(abs(i-16)),j/(2*abs(i-16)));
    PORTPal(9,j/(2*abs(i-18)),j/(abs(i-18)),j/(2*abs(i-18)));
  }
  delay(100);
 }
  for(i=17;i>0;i-=4)
 {waitretrace();
  for(int j=63;j<64;j++)
  {
    PORTPal(1,j/(2*abs(i-2)),j/(abs(i-2)),j/(2*abs(i-2)));
    PORTPal(2,j/(2*abs(i-4)),j/(abs(i-4)),j/(2*abs(i-4)));
    PORTPal(3,j/(2*abs(i-6)),j/(abs(i-6)),j/(2*abs(i-6)));
    PORTPal(4,j/(2*abs(i-8)),j/(abs(i-8)),j/(2*abs(i-8)));
    PORTPal(5,j/(2*abs(i-10)),j/(abs(i-10)),j/(2*abs(i-10)));
    PORTPal(6,j/(2*abs(i-12)),j/(abs(i-12)),j/(2*abs(i-12)));
    PORTPal(7,j/(2*abs(i-14)),j/(abs(i-14)),j/(2*abs(i-14)));
    PORTPal(8,j/(2*abs(i-16)),j/(abs(i-16)),j/(2*abs(i-16)));
    PORTPal(9,j/(2*abs(i-18)),j/(abs(i-18)),j/(2*abs(i-18)));
  }
  delay(100);
 }
 }
 getch();
}
char pos[7][7];
void savegame()
{
 fstream fgame("game.dll",ios::in|ios::out|ios::binary);
 fgame.write((char*)&pos,sizeof(pos));
 fgame.close();
}
void loadgame()
{
 fstream fgame("game.dll",ios::in|ios::out|ios::binary);
 fgame.read((char*)&pos,sizeof(pos));
 fgame.close();
}
void newgame()
{
 for(int i=0;i<22;i+=2)
  pos[(i/7)][(i%7)]=1;
 for(i=28;i<49;i+=2)
  pos[(i/7)][(i%7)]=2;
 for(i=1;i<49;i+=2)
  pos[(i/7)][(i%7)]=0;
 p1_c=p2_c=11;
}
void score()
{if(p1_c!=0&&p2_c!=0){
 char str[10];
 setcolor(7);
 rectangle(50,40,500,80);
 setcolor(13);
 outtextxy(60,50,"Player 1 -");
 outtextxy(270,50,"Player 2 -");
 setfillstyle(1,0);
 bar(200,50,240,70);
 bar(400,50,440,70);
 itoa(p1_c,str,10);
 outtextxy(200,50,str);
 itoa(p2_c,str,10);
 outtextxy(400,50,str);}
}
void board()
{
im.x.ax=2;
int86(0x33,&im,&om);
setcolor(6);
line(5,25,5,475);
line(5,475,635,475);
line(635,475,635,25);
line(635,25,5,25);

line(0,15,0,480);
line(0,479,640,479 );
line(639,480,639,7);
line(15,0,625,0);

arc(15,15,90,180,15);
arc(625,15,0,90,15);
setfillstyle(1,6);
floodfill(240,5,6);

setcolor(1);
for(int i=0;i<8;i++)                    //1-line
{line(50,100+i*50,400,100+i*50);
 line(50+i*50 ,100,50+i*50,450);
}
for(i=0;i<49;i+=2)
{
setfillstyle(1,2);                       //2-non user
floodfill((i/7)*50+75,(i%7)*50+125,1);
}
setfillstyle(1,3);
for(i=1;i<49;i+=2)
{
floodfill((i/7)*50+75,(i%7)*50+125,1);
}
for(i=0;i<7;i++)
{for(int j=0;j<7;j++)
 {if(pos[i][j]!=0)
  {setfillstyle(1,3+pos[i][j]);fillellipse(i*50+75,j*50+125,10,10);}
  if(pos[i][j]==0)
  {setfillstyle(1,3);fillellipse(i*50+75,j*50+125,10,10);
   setcolor(3);circle(i*50+75,j*50+125,10 );
   if((i*7+j)%2==0)
    {setfillstyle(1,2);fillellipse(i*50+75,j*50+125,10,10);
     setcolor(2 );circle(i*50+75,j*50+125,10 );
    }
   }
 }
}
  setcolor(14);
  rectangle(570, 7,586,21);
  rectangle(589, 7,606,21);
  rectangle(609, 7,626,21);
  setfillstyle(1,2);
   bar(610, 8,625,20);
  line(613,10,621,17);
  line(613,17,621,10);
  line(614,10,622,17);
  line(614,17,622,10);
  setcolor(1);
  line(573,18,582,18);
  line(573,17,582,17);
  rectangle(593, 9,602,18);
  line(593,10,602,10);
setfillstyle(1,2);
im.x.ax=1;
int86(0x33,&im,&om);
}
int count1()
{ int g=0;
 for(int i=0;i<7;i++)
 for(int j=0;j<7;j++)
if(pos[j][i]==1)g++;
 return g;
}
int count2()
{ int g=0;
for(int i=0;i<7;i++)
for(int j=0;j<7;j++)
if(pos[j][i]==2)g++;
return g;
}
void win1()
{setfillstyle(1,0);
 bar(50,40,500,80);
 setcolor(7);
 rectangle(50,40,500,80);
 setcolor(13);
 outtextxy(60,50,"PLAYER 1 is winner");
}
void win2()
{ setfillstyle(1,0);
 bar(50,40,500,80);
 setcolor(7);
 rectangle(50,40,500,80);
 setcolor(13);
 outtextxy(60,50,"PLAYER 2 is winner");
}
int checkx()
{
im.x.ax=3;
int86(0x33,&im,&om);
return((om.x.cx-50)/50);
}
int checky()
{
im.x.ax=3;
int86(0x33,&im,&om);
return((om.x.dx-100)/50);
}
int mousex()
{
im.x.ax=3;
int86(0x33,&im,&om);
return om.x.cx;
}
int mousey()
{
im.x.ax=3;
int86(0x33,&im,&om);
return om.x.dx;
}
int mousex2()
{
im.x.ax=3;
int86(0x33,&im,&om);
return om.x.cx;
}
int mousey2()
{
im.x.ax=3;
int86(0x33,&im,&om);
return om.x.dx;
}
void mademenu()
{PORTPal(7,20,20,20);
 PORTPal(8,20,20,20);
 PORTPal(9,20,20,20);
 PORTPal(10,20,20,20);
 PORTPal(11,20,20,20);
 PORTPal(12,20,20,20);
 PORTPal(13,20,50,50);
 setfillstyle(1,7);
 /*setcolor(7);
 bar(450,100,600,400);*/
 setcolor(6);
  arc(460,110, 90,180,10);
  arc(460,390,180,270,10);
  arc(590,110,  0, 90,10);
  arc(590,390,270,  0,10);
 line(460,100,590,100);
 line(460,400,590,400);
 line(450,110,450,390);
 line(600,110,600,390);
 floodfill(500,200,6);
 setcolor(7);
  arc(460,110, 90,180,10);
  arc(460,390,180,270,10);
  arc(590,110,  0, 90,10);
  arc(590,390,270,  0,10);
 line(460,100,590,100);
 line(460,400,590,400);
 line(450,110,450,390);
 line(600,110,600,390);

 settextstyle(1,0,3);
 outtextxy(500,420,"Menu");
 settextstyle(3,0,3);
 setcolor (8);
 outtextxy(460,130,"NEW  Game");
 setcolor (9);
 outtextxy(460,180,"SAVE Game");
 setcolor(10);
 outtextxy(460,230,"LOAD Game");
 setcolor(11);
 outtextxy(460,280,"  ABOUT  ");
 setcolor(12);
 outtextxy(460,330,"EXIT Game");
 settextstyle(2,0,7);
}
void menu()
{int b; int mousex=mousex2(),mousey=mousey2();
 im.x.ax=3;
 int86(0x33,&im,&om);
 b=om.x.bx;

 PORTPal(2,42-menu_app/2,20,20);
 PORTPal(3,42-menu_app/2,42-menu_app/2,menu_app/2);
 PORTPal(5,menu_app/2,menu_app/2,menu_app/2);
 PORTPal(4,40-menu_app/2,40-menu_app/2,40-menu_app/2);
 PORTPal(7,20,20+menu_app,20);

 if(mousex>450&&mousex<600&&mousey>100&&mousey<160)
 {PORTPal(8,20+menu_app,20+menu_app,20+menu_app);
  PORTPal(9,20-menu_app/2,20-menu_app/2,20+menu_app);
  PORTPal(10,20-menu_app/2,20-menu_app/2,20+menu_app);
  PORTPal(11,20-menu_app/2,20-menu_app/2,20+menu_app);
  PORTPal(12,20-menu_app/2,20-menu_app/2,20+menu_app);
  if(b==1)gam=1;
  delay(33);
  }
 else  if(mousex>450&&mousex<600&&mousey>160&&mousey<220)
 {PORTPal(9,20+menu_app,20+menu_app,20+menu_app);
  PORTPal(8,20-menu_app/2,20-menu_app/2,20+menu_app);
  PORTPal(10,20-menu_app/2,20-menu_app/2,20+menu_app);
  PORTPal(11,20-menu_app/2,20-menu_app/2,20+menu_app);
  PORTPal(12,20-menu_app/2,20-menu_app/2,20+menu_app);
  if(b==1)gam=2;
  delay(33);
  }
  else  if(mousex>450&&mousex<600&&mousey>220&&mousey<280)
 {PORTPal(10,20+menu_app,20+menu_app,20+menu_app);
  PORTPal(9,20-menu_app/2,20-menu_app/2,20+menu_app);
  PORTPal(8,20-menu_app/2,20-menu_app/2,20+menu_app);
  PORTPal(11,20-menu_app/2,20-menu_app/2,20+menu_app);
  PORTPal(12,20-menu_app/2,20-menu_app/2,20+menu_app);
  if(b==1)gam=3;
  delay(33);
  }
  else  if(mousex>450&&mousex<600&&mousey>280&&mousey<340)
 {PORTPal(11,20+menu_app,20+menu_app,20+menu_app);
  PORTPal(9,20-menu_app/2,20-menu_app/2,20+menu_app);
  PORTPal(10,20-menu_app/2,20-menu_app/2,20+menu_app);
  PORTPal(8,20-menu_app/2,20-menu_app/2,20+menu_app);
  PORTPal(12,20-menu_app/2,20-menu_app/2,20+menu_app);
  if(b==1)gam=4;
  delay(33);
  }
  else  if(mousex>450&&mousex<600&&mousey>340&&mousey<400)
 {PORTPal(12,20+menu_app,20+menu_app,20+menu_app);
  PORTPal(9,20-menu_app/2,20-menu_app/2,20+menu_app);
  PORTPal(10,20-menu_app/2,20-menu_app/2,20+menu_app);
  PORTPal(11,20-menu_app/2,20-menu_app/2,20+menu_app);
  PORTPal(8,20-menu_app/2,20-menu_app/2,20+menu_app);
  if(b==1)gam=5;
  delay(33);
  }
 else
 {PORTPal(8,20-menu_app/2,20-menu_app/2,20+menu_app);
  PORTPal(9,20-menu_app/2,20-menu_app/2,20+menu_app);
  PORTPal(10,20-menu_app/2,20-menu_app/2,20+menu_app);
  PORTPal(11,20-menu_app/2,20-menu_app/2,20+menu_app);
  PORTPal(12,20-menu_app/2,20-menu_app/2,20+menu_app);
  delay(33);}
}
void game()
{
gam=0;
im.x.ax=0;
int86(0x33,&im,&om);
PORTPal(1,20,20,20);
PORTPal(2,42,20,20);
PORTPal(3,42,42,0);
PORTPal(4,40,40,40);
PORTPal(5,0,0,0);
PORTPal(15,0,60,0);
PORTPal(14,50,50,60);
PORTPal(6,30,30,50);
PORTPal(0,20,20,20);
mademenu();
board();
im.x.ax=1;
int86(0x33,&im,&om);
int b,xp,yp,xs1,ys1,xs2,ys2,flag=0,lag,chance=1;       //xp-x present xs1-x selected I
while(gam==0)
{
im.x.ax=3;
int86(0x33,&im,&om);
b=om.x.bx;
if(mousex()>450&&mousex()<600&&mousey()>100&&mousey()<400&&menu_app<41)menu_app++;
else if(menu_app>0)menu_app--;
menu();
score();
if(mousex()>50&&mousex()<400&&mousey()>100&&mousey()<450)
{
 if(b==1)
    {  PORTPal(15,60,0,60);
	  if(checkx()>8&&checkx()>8)
	    { flag=0;}
	  else
	    { xs1=checkx();
	      ys1=checky();
	      flag=1;
	    }
    }
  if(b==2)
    {  PORTPal(15,0,60,0);
       xs2=checkx();
       ys2=checky();
       if((checkx()<7)&&(checkx()<7)&&(flag!=0))
	  {
	   if(
	    (pos[xs1][ys1]==1)
	     &&(abs(xs2-xs1)==1)
	     &&(abs(ys2-ys1)==1)
	     &&(pos[xs2][ys2]!=1)
	     &&(chance==1))
	   {pos[xs1][ys1]=0;
	    if(pos[xs2][ys2]==2)p2_c--;
	    pos[xs2][ys2]=1;
	    chance=2;
	   }

	   if(
	   (pos[xs1][ys1]==2)
	    &&(abs(xs1-xs2)==1)
	    &&(abs(ys2-ys1)==1)
	    &&(pos[xs2][ys2]!=2)
	    &&(chance==2))
	   {pos[xs1][ys1]=0;
	    if(pos[xs2][ys2]==1)p1_c--;
	    pos[xs2][ys2]=2;
	   chance=1;
	   }
	   flag=0;
	   board();
	   if(count1()==0){win2();}
	   if(count2()==0){win1();}
	  }
    }
}
xp=checkx();
yp=checky();
if(!(mousex()>50&&mousex()<400&&mousey()>100&&mousey()<450)){PORTPal(15,0,0,60);}
else if((xp*7+yp)%2==0)PORTPal(15,60,0,0);
else if((xp*7+yp)%2==1)PORTPal(15,0,60,0);
if(gam>0)return;
}
PORTPal(0,0,0,0);
cleardevice();
}
void main()
{
   int gdriver = VGA, gmode = VGAHI;
   struct palettetype pal;
   int i, ht, y, xmax;
   initgraph(&gdriver, &gmode, "");
   getpalette(&pal);

   for(i=0;i<16;i++)
     PORTPal(i,0,0,0);

   for(i=0;i<640;i++)putpixel(i,45,(320-abs(320-i))/32);
   setcolor(13);
   line(320,45,320,435);
   for(i=0;i<640;i++)putpixel(i,436,(320-abs(320-i))/32);
   settextstyle(1,0,6);
   setcolor(14);
   outtextxy(20,201,"WELCOME");
   outtextxy(20,199,"WELCOME");
   outtextxy(21,200,"WELCOME");
   outtextxy(19,200,"WELCOME");
   setcolor(15);
   outtextxy(22,202,"WELCOME");
   for(float j=5;j>=1;j-=0.5)
   {PORTPal(0, 20/j,30/j,50/j );
    PORTPal(14,30/j,40/j,55/j );
    PORTPal(15, 63/j,63/j,63/j);
    for(i=0;i<13;i++)
     PORTPal(i+1, 63/j,31/j+2*i/j,0+4*i/j );
    delay(33);
   }
if(getch()==27)goto onscren;
 cleardevice();
 PORTPal(0, 0,0,0 );PORTPal(2, 0,0,0 );
 PORTPal(1, 0,0,0 );PORTPal(3, 0,0,0 );PORTPal(4, 0,0,0 );
   setcolor(3);
   outtextxy(50,105,"Prashant Verma");
   outtextxy(50,355," Rahul Sharma ");
   setcolor(4);
   outtextxy(300,230,"And");
   setcolor(1);
   outtextxy(50,100,"Prashant Verma");
   outtextxy(50,350," Rahul Sharma ");
   setcolor(2);
   outtextxy(300,225,"And");
 for (i=0; i<64; i++)
 { PORTPal(1,i,i,0 );
   PORTPal(2,i,i,i );
   PORTPal(3,i/2,i/2,0 );
   PORTPal(4,i/2,i/2,i/2 );
   delay(20);  }
 delay(1000);
 for (i=63; i>=0; i--)
 { PORTPal(1,i,i,0 );
   PORTPal(2,i,i,i );
   PORTPal(3,i/2,i/2,0 );
   PORTPal(4,i/2,i/2,i/2 );
   delay(20);  }
 delay(500);
 if(kbhit())goto onscren;
 cleardevice();
 for (i=0; i<16; i++)
 { PORTPal(i,0,0,0 ); }

 settextstyle(1,0,6);
 for (i=0; i<16; i++)
 { setcolor(i);
   outtextxy(150,220-i/2,"PRESENTS");  }
 for (i=0; i<64; i++)
 { for (int k=1; k<16; k++)
   { PORTPal(k,0,k*i/16,0 ); }
   delay(33);
 }
 delay(500);
 for (i=63; i>=0; i--)
 { for (int k=1; k<16; k++)
   { PORTPal(k,0,k*i/16,0 ); }
   delay(23);
 }
 delay(500);
 if(kbhit())goto onscren;
 cleardevice();
   setcolor(2);
   outtextxy(150,125,"CHECKERS");
   setcolor(3);
   outtextxy(150,200,"2005");
   setcolor(4);
   outtextxy(150,275,"Dedicated to");
   settextstyle(2,0,5);
   setcolor(9);
   outtextxy(150,350,"our respected parents");
   setcolor(6);
   outtextxy(150,370,"by virtue of whome");
   setcolor(7);
   outtextxy(150,390,"we have became able to ");
   setcolor(8);
   outtextxy(150,410,"See the world");
   setcolor(5);
   outtextxy(150,430,"Brighter and Brighter every day");
   for (i=1;i<64;i++)
   {PORTPal(1, i/2,i,i/2 );
   delay(13);}
   for (i=1; i<64; i++)
   {PORTPal(2, i/2,i,i/2 );
   delay(13);}
   for (i=1; i<64; i++)
   {PORTPal(3, i/2,i,i/2 );
   delay(13);}
   for (i=1; i<64; i++)
   {PORTPal(4, i/2,i,i/2 );
   delay(13);}
   for (i=1; i<64; i++)
   {PORTPal(9, i,i,i/2 );
   delay(13);}
   for (i=1; i<64; i++)
   {PORTPal(6, i/2,i,i/2 );
   delay(13);}
   for (i=1; i<64; i++)
   {PORTPal(7, i/2,i,i/2 );
   delay(13);}
   for (i=1; i<64; i++)
   {PORTPal(8, i/2,i,i/2 );
   delay(13);}
   for (i=1; i<64; i++)
   {PORTPal(5, i/2,i,i/2 );
   delay(13);}
   for (i=64; i>0; i--)
   {PORTPal(1, i/2,i,i/2 );
    PORTPal(2, i/2,i,i/2 );
    PORTPal(3, i/2,i,i/2 );
    PORTPal(4, i/2,i,i/2 );
    PORTPal(5, i/2,i,i/2 );
    PORTPal(6, i/2,i,i/2 );
    PORTPal(7, i/2,i,i/2 );
    PORTPal(8, i/2,i,i/2 );
    PORTPal(9, i,i,i/2 );
   delay(15);}
onscren:
   cleardevice();
   newgame();
bigin :
   game();
   if(gam==1){cleardevice();newgame();goto bigin;}
   else if(gam==2){savegame();goto bigin;}
   else if(gam==3){cleardevice();loadgame();goto bigin;}
   else if(gam==4){cleardevice();credit();cleardevice();goto bigin;}
   PORTPal(0,0,0,0);
}
#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<conio.h>
#include<stdio.h>

struct poison
{
    int x;
    int y;
    char value;

}p;
using namespace std;
struct fruit
{
    int x;
    int y;
    char value;

}f;
struct snake
{

    int x;
    int y;
    char value;
     struct snake *next;
};
struct snake *start=NULL,*tail=NULL;
char a[10][10]={' '};
void snakes(int,int);
void field();



void savegame()

{
 FILE *fp,*fp1,*fp2;
    fp=fopen("snake.txt","w");
    fp1=fopen("food.txt","w");
fp2=fopen("poison.txt","w");
    struct snake *ptr=start;
    while(ptr!=NULL)
    {
        putc(ptr->x+'0',fp);
         putc(ptr->y+'0',fp);

           putc('\n',fp);
        ptr=ptr->next;
    }
     putc(f.x+'0',fp1);
      putc(f.y+'0',fp1);
      putc(p.x+'0',fp2);
      putc(p.y+'0',fp2);




fclose(fp);
fclose(fp1);
fclose(fp2);


}
void resumegame()
{
    FILE *fp,*fp1,*fp2;
fp=fopen("snake.txt","r");

fp1=fopen("food.txt","r");
fp2=fopen("poison.txt","r");
char ch;
int a,b;
ch=getc(fp);
while(ch!=EOF)
    {
        if(ch!='\n')
        {
    a=ch-'0';
   ch=getc(fp);
   b=ch-'0';

    snakes(a,b);
        }
        ch=getc(fp);
    }
    char ch1;
ch1=getc(fp1);
while(ch1!=EOF)
{
f.x=ch1-'0';
   ch1=getc(fp1);
   f.y=ch1-'0';
   ch1=getc(fp1);
}
tail->value='Y';
char ch2;
ch2=getc(fp2);
while(ch2!=EOF)
{
p.x=ch2-'0';
   ch2=getc(fp2);
   p.y=ch2-'0';
   ch2=getc(fp2);
}

fclose(fp);
fclose(fp1);
fclose(fp2);
}
void deletenode()
{

    struct snake *current=start;
    struct snake *p=current->next;
    struct snake *q=p->next;
    while(q->next!=NULL)
    {

        current=current->next;
        p=p->next;
        q=q->next;
    }
    a[q->x][q->y]=' ';
    q->x=p->x;
    q->y=p->y;
    current->next=q;
    delete p;


}
 void snakes(int i,int j)
{
    struct snake *n;
    n=new snake;
    n->x=i;
    n->y=j;
    if(start==NULL)
    {

        n->value='X';
        n->next=NULL;
        start=n;
        tail=n;
    }
    else
    {
        n->value='#';
        n->next=NULL;
        tail->next=n;
        tail=n;

    }

}


void change()
{
    struct snake *ptr,*nptr;
    int a,b,c,d;
    ptr=start;
    nptr=start->next;
    while(nptr!=NULL)
    {
        if(ptr==start)

        {
            a=nptr->x;
            b=nptr->y;
            nptr->x=ptr->x;
            nptr->y=ptr->y;
            nptr=nptr->next;
            ptr=ptr->next;

        }
        else{
            c=nptr->x;
            d=nptr->y;
            nptr->x=a;
            nptr->y=b;
            a=c;
            b=d;
            nptr=nptr->next;
        }
    }

}
void food()
{


int t1,t2;


    f.value='F';
    p.value='P';
    if(start->x==f.x && start->y==f.y)
    {
      t1=tail->x;
      t2=tail->y;
      tail->value='#';
      snakes(t1,t2);
      tail->value='Y';
 f.x=rand()%(10-3)+1;
	f.y=rand()%(10-3)+1;

      }
      else if(start->x==p.x && start->y==p.y)
      {
          deletenode();
          p.x=rand()%(10-5)+1;
	p.y=rand()%(10-5)+1;
      }


}
void field()
{

food();
    a[f.x][f.y]=f.value;
    a[p.x][p.y]=p.value;
     struct snake *ptr;
    ptr=start;
    for(int i=0;i<10;i++)
    {

        a[0][i]='*';
        a[i][0]='*';
        a[9][i]='*';
        a[i][9]='*';
    }

    while(ptr!=NULL)
    {
a[ptr->x][ptr->y]=ptr->value;

ptr=ptr->next;
}

}
int check()
{
    int flag=0;
    struct snake *ptr,*nptr;
    ptr=start;
    nptr=start->next;
    while(nptr!=NULL)
    {
        if(nptr->x==ptr->x && nptr->y==ptr->y)
        {

            flag=1;
            break;
        }
nptr=nptr->next;
    }
    if(flag==1)
    {
        return 1;



    }
    return 0;
}
int movesnake(char c)
{


int flag=0;
a[tail->x][tail->y]=' ';
    if(c=='w')
    {
        if(start->x==1)
        {
            change();
            start->x=8;
            field();
        }
        else
        {
            change();
            start->x=start->x-1;
             field();
        }
    }
    else if(c=='s')
    {
      if(start->x==8)
        {
            change();
            start->x=1;
             field();
        }
        else
        {
            change();
            start->x=start->x+1;
             field();
        }

    }
    else if(c=='a')
    {
        if(start->y==1)
        {
            change();
            start->y=8;
             field();
        }
        else
        {
            change();
            start->y=start->y-1;
             field();
        }

    }
    else if(c=='d')
    {
        if(start->y==8)
        {
            change();
            start->y=1;
             field();
        }
        else
        {
            change();
            start->y=start->y+1;
             field();
        }

    }

flag=check();
if(flag==1)
{
    cout<<endl<<"*****************GAME OVER***********************"<<endl;
    return 1;
}
system("CLS");
    for(int i=0;i<10;i++)
    {

        for(int j=0;j<10;j++)
        {
            cout<<a[i][j];
            cout<<" ";
        }
        cout<<endl;
    }
return 0;
    }

void create()
{
    int r=5;
    int c=5;
int    z=3;
    while(z--)
    {
        snakes(r,c);
        r++;

    }
     tail->value='Y';
}

int main()
{
    char choice;
    cout<<"Do you want to resume the game Y/N";
    cin>>choice;
    if(choice=='y')
    {
      resumegame();
    }
    else
    {
      f.x=2;f.y=2;
p.x=7;p.y=7;
        create();
    }

    char c;

field();



    for(int i=0;i<10;i++)
    {

        for(int j=0;j<10;j++)
        {
            cout<<a[i][j];
            cout<<" ";
        }
        cout<<endl;
    }
cout<<endl<<"Enter W,A,S,D to move and enter Q to QUIT";

int flag=0;
char ch;
cin>>c;
while(c!='q')
{
   flag=movesnake(c);
   if(flag==1)
    break;
    cin>>c;
    if(c=='q')
    {

        cout<<"DO YOU WANT TO SAVE THE GAME ? Y/N";
        cin>>ch;
        if(ch=='y')
        {
          savegame();
          break;
        }
        else if(ch=='n')
        {
            break;
        }
    }

}
}

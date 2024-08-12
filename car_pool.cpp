#include<fstream>
#include<stdio.h>
#include<string.h>
#include<iomanip>
#include<stdlib.h>
#include <iostream>
#include <unistd.h>

using namespace std;

class user
{
public:
 char username[25],password[25],email[25],phone[25];
 char type,junc[1000],status;
user()
{
status='n';
}
};

class ride
{
public:
 user driver,rider;
 char status;
};

user x;
int search(char ch, char tag[9])
{
int k,flag=0;
for(k=0;k<strlen(tag);k++)
{
  if (ch==tag[k])
  flag++;
}
return flag;
}

void check()
{
int y,pos,flag=0,i,j;
cout<<"Checking for rides";
for(y=0;y<4;y++)
{
//delay(2000);
sleep(2);
cout<<".";
}
cout<<endl;
fstream rides("rides.dat",ios::in|ios::binary); //
ride buff;
rides.seekg(0);
if(x.type=='r')
 {   while(rides.read((char*)&buff,sizeof(buff))&&flag==0)
   {
     if(buff.status=='d')
     {
 for(int l=0;l<strlen(buff.driver.junc)&&flag==0;l++)
      {
	if(x.junc[0]==buff.driver.junc[l])
	 {
	  for(j=l+1;j<strlen(buff.driver.junc)&&flag==0;j++)
	  {
	   if(x.junc[1]==buff.driver.junc[j])
	   flag++;
	  }
	  }
      }
     }
   }
   pos=rides.tellg();
   rides.close();
   if (flag!=0)
   {  rides.open("rides.dat",ios::out|ios::binary); //
   rides.seekp(pos-sizeof(buff));
   buff.status='p';
   buff.rider=x;
   rides.write((char*)&buff,sizeof(buff));
   cout<<"We have found you a ride.\n"<<endl;
   cout<<"Driver Details\n"<<endl;
   cout<<"User Name:"<<buff.driver.username<<endl;
   cout<<"Phone    :"<<buff.driver.phone<<endl;
   cout<<"Email    :"<<buff.driver.email<<endl;
   cout<<"Press any key to logout"<<endl;
   getchar();
   rides.close();
   }
   else
   {
   rides.open("rides.dat",ios::app|ios::binary);
   ride gear;
   gear.rider=x;
   gear.status='r';
   rides.write((char*)&gear,sizeof(gear));
   rides.close();
   cout<<"Details saved. Come back to check again later";
   getchar();
   }
   }

 
   if(x.type=='d')
     {
      int l,j;      while(rides.read((char*)&buff,sizeof(buff))&&flag==0)
   {
     if(buff.status=='r')
     {
      for(l=0;l<strlen(x.junc)&&flag==0;l++)
      {
	if(x.junc[l]==buff.rider.junc[0])
	 {
	  for(j=l+1;j<strlen(x.junc)&&flag==0;j++)
	  {
	   if(x.junc[j]==buff.rider.junc[1])
	   flag++;
	  }
	  }
      }
     }
   }
   pos=rides.tellg();
   rides.close();
   if (flag!=0)
   {               rides.open("rides.dat",ios::out|ios::binary); //
   rides.seekp(pos-sizeof(buff));
   buff.status='p';
   buff.driver=x;
   rides.write((char*)&buff,sizeof(buff));
   cout<<"We have found your rider.\n"<<endl;
   cout<<"Rider Details\n"<<endl;
   cout<<"User Name:"<<buff.rider.username<<endl;
   cout<<"Phone    :"<<buff.rider.phone<<endl;
   cout<<"Email    :"<<buff.rider.email<<endl;
   cout<<"Press any key to logout"<<endl;
   rides.close();
   getchar();
   }
   else
   {
   rides.open("rides.dat",ios::app|ios::binary);
   ride gear;
   gear.driver=x;
   gear.status='d';
   rides.write((char*)&gear,sizeof(gear));
   rides.close();
   cout<<"Details saved. Come back to check again later";
   getchar();
   }
   }
   }

 void run()
 {
 int i,emer=0;
 char ch='a';
 char def[10]="abcdefghi",tag[10]="abcdefghi"; //
 cout<<"What are you doing today?\n";
 cout<<"Enter 'd' for driving and 'r' for riding:";
 cin>>x.type;
 if(x.type=='d')
 {
 cout<<"Enter 'z' to stop"<<endl;
 for(i=0;i<100&&search(ch,def)&&emer==0;i++)
   {
    if(i==0)
    {
    strcpy(x.junc,"");
    cout<<"Let us begin:";
    }
    else
    {
    cout<<"Next Junction?";
    }
    cin>>ch;
    while(!search(ch,tag)&&emer==0)
    {
    if(!search(ch,"abcdefghi"))
    {
    ch='z';
    emer++;
    }
    else
    {
    cout<<"Choose wisely";
    cin>>ch;
    }
    }
    if(ch!='z')
    x.junc[i]=ch;
    switch(ch)
    {
      case 'a':strcpy(tag,"bd");
	       break;
      case 'b':strcpy(tag,"ace");
	       break;
      case 'c':strcpy(tag,"bf");
	       break;
      case 'd':strcpy(tag,"aeg");
	       break;
      case 'e':strcpy(tag,"bdfh");
	       break;
      case 'f':strcpy(tag,"cei");
	       break;
      case 'g':strcpy(tag,"dh");
	       break;
      case 'h':strcpy(tag,"egi");
	       break;
      case 'i':strcpy(tag,"fh");
		break;
      case 'z':break;
      default :break;
      }
      }
      cout<<"Your route has been saved\n";
      cout<<"Route at a glance:";
      cout<<x.junc<<endl;
      getchar();
      check();
      }
      else
      {
      strcpy(x.junc,"");
      cout<<"Where to pickup?";
      cin>>x.junc[0];
      cout<<"\nWhere do you want to go?";
      cin>>x.junc[1];
      cout<<"\nDetails have been updated\n";
      cout<<"You are getting on at "<<x.junc[0];
      cout<<" and getting down at "<<x.junc[1]<<endl;
      check();
      }
      }


void login()
{
fstream users("users.dat",ios::in|ios::binary); //
int i=0;
user buff;
do
{
cout<<"Logging in"<<endl;
cout<<"Username:";
//gets(x.username);
cin>>x.username;
cout<<"Password:";
//gets(x.password);
cin>>x.password;
while(users.read((char*)&buff,sizeof(buff)))
{
if(!strcmp(x.username,buff.username)) //

{
if(!strcmp(x.password,buff.password))
{
cout<<"Welcome Back !"<<endl;
i++;
run();
}
}
}
retry:
if(i==0)
{
cout<<"Invalid Username/Password";
getchar();
i++;
}
}while(i==0);
}




void create()
{
int dup,flag=0;
fstream users("users.dat",ios::in|ios::binary); //
user buff;
cout<<"Creating..."<<endl;
do
{
dup=0;
cout<<"Enter Username:";
cin>>x.username;
//fgets(x.username, sizeof(x.username), stdin);
users.seekg(0);
while(users.read((char*)&buff,sizeof(buff))&&dup==0 && flag==0)
{
if(!strcmp(x.username,buff.username)) //
{
cout<<"\n This username is not available"<<endl;
dup++;
}
}
if(dup==0)
 flag++;
 }while(flag==0);
 cout<<"\nUsername Accepted";
 cout<<"\nPassword:";
 //gets(x.password);
 cin>>x.password;
 cout<<"Email: ";
 //gets(x.email);
 cin>>x.email;
 cout<<"Phone: ";
 //gets(x.phone);
 cin>>x.phone;
 users.close();
users.open("users.dat",ios::ate|ios::out|ios::binary);
 users.seekp(0,ios::end);
 users.write((char*)&x,sizeof(x));
 users.close();
 cout<<"Account created"<<endl;
 getchar();
 }


int main()
{
system("cls");
char choice;
do
{
cout<<"\nEnter choice\n1.Create\n2.Login\n3.Exit\n";
cin>>choice;
switch(choice)
{
case '1':create();break;
case '2':login();break;
case '3':exit(0);
};
}
while(choice=='1'||choice=='2');
getchar();
return 0;
}

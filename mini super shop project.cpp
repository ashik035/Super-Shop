#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<fstream>
#include<windows.h>

using namespace std;

COORD coord={0,0};

void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

class product
{
int pno;
char name[50];
float price,dis;
public:
void create_product()
{
cout<<"\n\nPlease Enter The Product No. of The Product : ";
cin>>pno;
cout<<"\nPlease Enter The Name of The Product :";
cin>>name;
cout<<"\nPlease Enter The Price of The Product : ";
cin>>price;
cout<<"\nPlease Enter The Discount (%) : ";
cin>>dis;
}

void show_product()
{
cout<<"\nThe Product No. of The Product : "<<pno;
cout<<"\nThe Name of The Product : "<<name;
cout<<"\nThe Price of The Product : "<<price;
cout<<"\nDiscount : "<<dis;
}

int retpno()
{return pno;}

float retprice()
{return price;}

char* retname()
{return name;}

float retdis()
{return dis;}

};

fstream fp;
product pr;

/** function to write in file**/

void write_product()
{
fp.open("Shop.dat",ios::out|ios::app);
pr.create_product();
fp.write((char*)&pr,sizeof(product));
fp.close();
cout<<"\n\nThe Product Has Been Created. ";
getch();
}

/** function to read all records from file**/

void display_all()
{
cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";

fp.open("Shop.dat",ios::in);

while(fp.read((char*)&pr,sizeof(product)))
{
pr.show_product();

cout<<"\n\n====================================\n";
getch();
}
fp.close();
getch();
}

/** function to read specific record from file while search by coustomer**/

void display_sp(int n)
{
int flag=0;
fp.open("Shop.txt",ios::in);
while(fp.read((char*)&pr,sizeof(product)))
{
if(pr.retpno()==n)
{
pr.show_product();
flag=1;
}
}
fp.close();
if(flag==0)
cout<<"\n\nrecord not exist";
getch();
}

/** function to modify record of file **/

void modify_product()
{
int no,found=0;
cout<<"\n\n\tTo Modify ";
cout<<"\n\n\tPlease Enter The Product No. of The Product : ";
cin>>no;

fp.open("Shop.dat",ios::in|ios::out);

while(fp.read((char*)&pr,sizeof(product)) && found==0)
{
if(pr.retpno()==no)
{
pr.show_product();

cout<<"\nPlease Enter The New Details of Product : "<<endl;

pr.create_product();

int pos=-1*sizeof(pr);

fp.seekp(pos,ios::cur);

fp.write((char*)&pr,sizeof(product));

cout<<"\n\n\t Record Updated";

found=1;
}
}
fp.close();

if(found==0)

cout<<"\n\n Record Not Found ";

getch();
}

/** function to delete record of file **/

void delete_product()
{
int no;
cout<<"\n\n\n\tDelete Record";
cout<<"\n\nPlease Enter The product no. of The Product You Want To Delete : ";
cin>>no;

fp.open("Shop.dat",ios::in|ios::out);
fstream fp2;

fp2.open("Temp.dat",ios::out);

fp.seekg(0,ios::beg);

while(fp.read((char*)&pr,sizeof(product)))
{
if(pr.retpno()!=no)
{
fp2.write((char*)&pr,sizeof(product));
}
}
fp2.close();
fp.close();

remove("Shop.dat");
rename("Temp.dat","Shop.dat");
cout<<"\n\n\tRecord Deleted ..";

getch();
}

/** function to display all products price list **/

void menu()
{
fp.open("Shop.dat",ios::in);
if(!fp)
{
cout<<"ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To ASHIK Menu to create File";
cout<<"\n\n\n Program is closing ...";
getch();
exit(0);
}

cout<<"\n\n\t\tProduct MENU\n\n";
cout<<"====================================================\n";
cout<<"P.NO.\t\tNAME\t\tPRICE\n";
cout<<"====================================================\n";

while(fp.read((char*)&pr,sizeof(product)))
{
cout<<pr.retpno()<<"\t\t"<<pr.retname()<<"\t\t"<<pr.retprice()<<endl;
}
fp.close();
}

/**function of buing product**/
void place_order()
{
int order_arr[50],quan[50],c=0;

float amt,damt,total=0;

char ch='Y';
menu();

cout<<"\n============================";
cout<<"\n PLACE YOUR ORDER";
cout<<"\n============================\n";

do{
cout<<"\n\nEnter The Product No. Of The Product : ";
cin>>order_arr[c];
cout<<"\nQuantity in number (kg) : ";
cin>>quan[c];
c++;

cout<<"\nDo You Want To Buy Another Product ? (y/n)";
cin>>ch;
}
while(ch=='y' ||ch=='Y');
cout<<"\n\nThank You For Placing The Order";
getch();
cout<<"\n\n===========TOTAL===========\n";
cout<<"\nPr No.\tPr Name\tQuantity \tPrice \tAmount \tAmount after discount\n";

for(int x=0;x<=c;x++)
{
fp.open("Shop.dat",ios::in);
fp.read((char*)&pr,sizeof(product));
while(!fp.eof())
{
if(pr.retpno()==order_arr[x])
{
amt=pr.retprice()*quan[x];

damt=amt-(amt*pr.retdis()/100);

cout<<"\n"<<order_arr[x]<<"\t"<<pr.retname()<<"\t"<<quan[x]<<"\t\t"<<pr.retprice()<<"\t"<<amt<<"\t\t"<<damt;

total+=damt;
}
fp.read((char*)&pr,sizeof(product));
}

fp.close();
}
cout<<"\n\n\t\t\t\t\tTOTAL = "<<total;
getch();
}

/** ~~~INTRODUCTION FUNCTION~~~ **/
void load(){
    int r,c,q;
    gotoxy(36,14);
    printf("loading...");
    gotoxy(30,15);
    for(r=1;r<=20;r++){
    for(q=0;q<=100000000;q++);/**to display the character slowly**/
    printf("%c",176);}
    getch();
}

void intro()
{
load();
system("cls");
gotoxy(25,02);
cout<<"MINI SUPER SHOP BILLING MANAGEMENT SYSTEM";
gotoxy(38,04);
cout<<"PROJECT";
cout<<"\n\n\t\t\t      MADE BY :  MD. ASHIKUZZAMAN";
cout<<"\n\n\t\t\t\t EAST WEST UNVERSITY";
getch();

}

/** ~~~ADMINSTRATOR MENU FUNCTION~~~ **/

void ASHIK_menu()
{
char ch2;
cout<<"\n\n\n\tASHIK MENU";

cout<<"\n\n\t1.CREATE PRODUCT";

cout<<"\n\n\t2.DISPLAY ALL PRODUCTS";

cout<<"\n\n\t3.DETAILS";

cout<<"\n\n\t4.MODIFY PRODUCT";

cout<<"\n\n\t5.DELETE PRODUCT";

cout<<"\n\n\t6.VIEW PRODUCT MENU";

cout<<"\n\n\t7.BACK TO MAIN MENU";

cout<<"\n\n\tPlease Enter Your Choice (1-7) : ";

ch2=getch();

switch(ch2)
{
case '1':
write_product();
break;
case '2': display_all();
break;
case '3': int num;
cout<<"\n\n\tPlease Enter The Product No. ";
cin>>num;
display_sp(num);
break;
case '4': modify_product();
break;
case '5': delete_product();
break;
case '6': menu();
getch();
case '7': break;
default:cout<<"\a";
ASHIK_menu();
}
}

/** ~~~THE MAIN FUNCTION OF PROGRAM~~~ **/

int main()
{
char ch;
intro();
do
{
cout<<"\n\n\tMAIN MENU";
cout<<"\n\t01. CUSTOMER";
cout<<"\n\t02. SHOPKEEPER";
cout<<"\n\t03. EXIT";
cout<<"\n\tPlease Select Your Option (1-3) ";
ch=getche();
switch(ch)
{
case '1': place_order();
getch();
break;
case '2':ASHIK_menu();
break;
case '3':exit(0);

default :cout<<"\a";
}
}while(ch!='3');
return 0;
}

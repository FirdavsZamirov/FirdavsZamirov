#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include<windows.h>
#include<stdlib.h>

struct subscriber
{
char phonenumber[20];
char name[50];
float amount;
}s;

void addrecords();
void listrecords();
void modifyrecords();
void deleterecords();
void searchrecords();
void payment();
char get;

int main()
{	
	int password;
	int phonenumber;
	char choice;



	system("cls");

	printf("\n\n\n\n\n\n\n\n\n\t\t****************************************************");
	printf("\n\t\t\t----WELCOME TO BILLING APP----");
	printf("\n\t\t****************************************************");
	printf("\n\t\t\t\tPRESS ANY KEY..");
	Sleep(2000);
	getch();
    system("cls");
	while (1)
	{
		system("cls");
		printf("\n\t\t\t***CHOOSE THE OPTIONS BELOW*** \n\t\t\t A : for Adding new Records.\n\t\t\t L : for List of Records.");
		printf("\n\t\t\t M : for Modifying Records.\n\t\t\t P : for Payment.");
		printf("\n\t\t\t S : for Searching Records.");
		printf("\n\t\t\t D : for Deleting Records.\n\n\n\n\t\t\t E : for Exit!!\n");
		choice=getche();
		choice=toupper(choice);
		switch(choice)
		{
			case 'P':
				payment();break;
			case 'A':
				addrecords();break;
			case 'L':
				listrecords();break;
			case 'M':
				modifyrecords();break;
			case 'S':
				searchrecords();break;
			case 'D':
				deleterecords();break;
			case 'E':
				system("cls");
				printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tTHANK YOU!!\n\n\n\n\n\n\n\n\n");
				Sleep(2000);
				exit(0);
				break;
			default:
				system("cls");
				printf("Incorrect Input!! Choose from THE FIRST COLUMN.");
				printf("\nBack to MAIN ---> Press ANY KEY..");
				getch();
		}
	}
}

void addrecords()
{
	FILE *f;
	char test;
	f=fopen("subsList.txt","ab+");
	if(f==0)
	{   f=fopen("subsList.txt","wb+");
		system("cls");
		printf("Please wait while we configure your computer");
		printf("/nPress any key to continue");
		getch();
	}
	while(1)
	{
		system("cls");
		printf("\n Enter Phone Number:");
		scanf("%s",&s.phonenumber);
		printf("\n Enter Name:");
		fflush(stdin);
		scanf("%[^\n]",&s.name);
		printf("\n Enter Amount:");
		scanf("%f",&s.amount);
		fwrite(&s,sizeof(s),1,f);
		fflush(stdin);
		system("cls");
		printf("Record successfully added");
		printf("\n Press ESC key to exit. Any other key to add another record:");
		test=getche();
		if(test==27)
			break;
	}
	fclose(f);
}

void listrecords()
{
	FILE *f;
	int i;
	if((f=fopen("subsList.txt","rb"))==NULL)
		exit(0);
	system("cls");
	printf("PHONE NUMBER\t\tUSER NAME\t\t\tAMOUNT IN FORINTS\n");
	for(i=0;i<79;i++)
		printf("-");
	while(fread(&s,sizeof(s),1,f)==1)
	{
		printf("\n%-10s\t\t%-20s\t\tHUF. %.2f /-",s.phonenumber,s.name,s.amount);
	}
	printf("\n");
	for(i=0;i<79;i++)
		printf("-");

fclose(f);
getch();
}

void deleterecords()
{
	FILE *f,*t;
	int i=1;
	char phonenumber[20];
	if((t=fopen("tempList.txt","w+"))==NULL)
	exit(0);
	if((f=fopen("subsList.txt","rb"))==NULL)
	exit(0);
	system("cls");
	printf("Enter the phone number to be deleted from the LIST.");
	fflush(stdin);
	scanf("%[^\n]",phonenumber);
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.phonenumber,phonenumber)==0)
		{       i=0;
			continue;

		}
		else
			fwrite(&s,sizeof(s),1,t);
	}
	if(i==1)
	{       system("cls");
		printf("Phone number \"%s\" not found!!",phonenumber);
		remove("subsList.txt");
		rename("tempList.txt","subsList.txt");
		getch();
		fclose(f);
		fclose(t);
		main();
	}
	remove("subsList.txt");
	rename("tempList.txt","subsList.txt");
	system("cls");
	printf("The number %s successfully deleted!!",phonenumber);
	fclose(f);
	fclose(t);
	getch();
}

void searchrecords()
{
	FILE *f;
	char phonenumber[20];
	int flag=1;
	f=fopen("subsList.txt","rb+");
	if(f==0)
		exit(0);
	fflush(stdin);
	system("cls");
	printf("Enter the phone number ->");
	scanf("\t%s", phonenumber);
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.phonenumber,phonenumber)==0)
		{	system("cls");
			printf(" Record Found ");
			printf("\n\nPhone Number: %s\nName: %s\nAmount: HUF.%0.2f\n",s.phonenumber,s.name,s.amount);
			flag=0;
			break;
		}
		else if(flag==1)
		{	system("cls");
			printf("Entered phone number is not in the LIST!!");
		}
	}
	getch();
	fclose(f);
}
void modifyrecords()
{
	FILE *f;
	char phonenumber[20];
	long int size=sizeof(s);
	if((f=fopen("subsList.txt","rb+"))==NULL)
		exit(0);
	system("cls");
	printf("Enter phone number of the user to modify:\t");
	scanf("%[^\n]",phonenumber);
	fflush(stdin);
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.phonenumber,phonenumber)==0)
		{
			system("cls");
			printf("\n Enter phone number:");
			scanf("%s",&s.phonenumber);
			printf("\n Enter Name: ");
			fflush(stdin);
			scanf("%[^\n]",&s.name);
			printf("\n Enter Amount: ");
			scanf("%f",&s.amount);
			fseek(f,-size,SEEK_CUR);
			fwrite(&s,sizeof(s),1,f);
			break;
		}
	}
	fclose(f);
}
void payment()
{
	FILE *f;
	char phonenumber[20];
	long int size=sizeof(s);
	float amt;
	int i;
	if((f=fopen("subsList.txt","rb+"))==NULL)
		exit(0);
	system("cls");
	printf("Enter phone number of the user for payment.\t");
	scanf("%[^\n]",phonenumber);
	fflush(stdin);
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.phonenumber,phonenumber)==0)
		{
			system("cls");
			printf("\n Phone Number.: %s",s.phonenumber);
			printf("\n User Name: %s",s.name);
			printf("\n Current Amount: %f",s.amount);
			printf("\n");
			for(i=0;i<79;i++)
				printf("-");
			printf("\n\nEnter amount of Payment :");
			fflush(stdin);
			scanf(" %f",&amt);
			s.amount=s.amount-amt;
			fseek(f,-size,SEEK_CUR);
			fwrite(&s,sizeof(s),1,f);
			break;
		}
	}
	system("cls");
	printf("THANK YOU %s FOR YOUR PAYMENT",s.name);
	getch();
	fclose(f);
}

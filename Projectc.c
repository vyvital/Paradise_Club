#include <stdio.h>
#include <string.h>
#include <stdlib.h>  
#include <conio.h>
#include <windows.h>
#include <time.h>

typedef struct 
{
	char id[100];
	char name[100];
	char password[100];
	char permission[100];
	char position[100];
	char salary[100];
}Staff;
typedef struct 
{
	char name[100];
	char quantity[100];
	char price[100];
}Drink;
typedef struct
{
	char name[100];
	char start[100];
	char finish[100];
	char day[100];
}Schedule;
typedef struct
{
		char name[100];
		char spend[100];
}VIP;

void Print_VIP(VIP *vip,int counter){
	int i;
	system("cls");
	flushall();
	for(i=0;i<counter;i++){
		printf("name: %s\n",vip[i].name);
		printf("spend: %s\n",vip[i].spend);
		printf("\n");
	}
	printf("\nPress any key to return to VIP Menu..\n");
	getchar();
}

void Final_Remove_VIP(VIP *vip,int counter,char buf[100]){
	int i=0,indexf=0,flag=0,index=0;
	int indexbuf1=0,indexbuf2=0,countputs=0;
	char newbuf[100];
	char temp[100];
	FILE *ptr4;
	ptr4=fopen("vip.txt","r");
	if(ptr4==NULL){
    printf("Unable to open the file. Program will now exit.");
    exit(0);
  }
	flushall();
	while(fgets(newbuf,100,ptr4)!=NULL)
	{
		while(newbuf[indexbuf1]!='\n')
				indexbuf1++;
			newbuf[indexbuf1]='\0';
		if(strcmp(newbuf,buf)==0)	
		{
			for(i=0;i<counter;i++){
				strcpy(temp,vip[i].name);
				while(temp[indexbuf2]!='\n')
					indexbuf2++;
				temp[indexbuf2]='\0';
				if(strcmp(buf,temp)==0)
				{
					indexf=i;
					break;
				}
				indexbuf2=0;
			}
			break;
		
		}
		indexbuf1=0;
		
	}

	fclose(ptr4);
	ptr4=fopen("vip.txt","w");

	for(i=0;i<counter;i++){
		if(i==indexf)
			i++;
		fputs(vip[i].name,ptr4);
		if(i==(counter-2))
		{
			while(vip[i].spend[index]!='\n')
			{
				fputc(vip[i].spend[index],ptr4);
				index++;
			}
			index=0;
		}
		if(i<(counter-1))
		{
			fputs(vip[i].spend,ptr4);
			fputs("\n",ptr4);
		}
	}
	fclose(ptr4);

}
int Add_VIP(VIP *vip,int counter){
	FILE *ptr4;
	char buf[100];
	int i,flag=1,countbacks=0;
	int index=0,index2=0;
	char temp[100];
	char temp2[100];
	system("cls");
	ptr4=fopen("vip.txt","r");
	if(ptr4==NULL){
    printf("Unable to open the file. Program will now exit.");
    exit(0);
  }
	printf("Add_VIP\n");
	flushall();
	do
	{
		if(countbacks>0)
		printf("The VIP: '%s' exist please try again!Press any key\n",temp2);
		flag=1;
	printf("name: ");
	gets(buf);
	for(i=0;i<counter;i++){
		strcpy(temp,vip[i].name);
		while(temp[index]!='\n')
				index++;
			temp[index]='\0';
		if(strcmp(buf,temp)==0)
		{
			flag=0;
			strcpy(temp2,vip[i].name);
			while(temp2[index2]!='\n')
				index2++;
			temp2[index2]='\0';
		}
		index=0;
		index2=0;
	}
	if(flag==0)
	{
		system("cls");
	}
	countbacks++;
	}while(flag==0);
	fclose(ptr4);
	ptr4=fopen("vip.txt","a");
		if(ptr4==NULL){
    printf("Unable to open the file. Program will now exit.");
    exit(0);
  }
	fseek(ptr4,+100, SEEK_END);
	fputc('\n',ptr4);
	fputc('\n',ptr4);
	fputs(buf,ptr4);
	fputc('\n',ptr4);

	printf("\nspend: ");
	gets(buf);
	fputs(buf,ptr4);
	printf("The new VIP person was succesfully added. Press any key to return to the Inventory Menu...\n");
	getchar();
	fclose(ptr4);
	counter=Update_VIP(vip,ptr4);
	return counter;
}
int Remove_VIP(VIP *vip,int counter){
	FILE *ptr4;
	char buf[100];
	char choose[5];
	int newcounter=0,i,index=0,index2=0;
	char temp[100],temp2[100];
	int flag=1;
	ptr4=fopen("vip.txt","r");
		if(ptr4==NULL){
    printf("Unable to open the file. Program will now exit.");
    exit(0);
  }
	system("cls");
	if(ptr4==NULL){
    printf("Unable to open the file. Program will now exit.");
    exit(0);
  }
	flushall();
	printf("Enter the name of the VIP person you want  to remove:\n");
	printf("name: ");
	gets(buf);
	for(i=0;i<counter;i++){
		flushall();
		strcpy(temp,vip[i].name);
		while(temp[index]!='\n')
				index++;
			temp[index]='\0';
		if(strcmp(buf,temp)==0)
		{
			flag=0;
			strcpy(temp2,vip[i].name);
			while(temp2[index2]!='\n')
				index2++;
			temp2[index2]='\0';
		}
		index=0;
		index2=0;
	}
	if(flag==0)
	{
		printf("\nAre you sure that you want remove this VIP Member? press 1 to confirm or 0 to return to the Managment Menu\n");
		gets(choose);
		if(strcmp(choose,"1")==0)
		{

			fclose(ptr4);
			counter=Update_VIP(vip,ptr4);
			Final_Remove_VIP(vip,counter,buf);
			counter=Update_VIP(vip,ptr4);
			printf("The VIP member was succesfully removed!press any key to return to the Managment Menu\n");
			getchar();
		}
	}
	if(flag==1){
		printf("The VIP name don't exit press any key to back Inventory menu\n");
		getchar();
	}


	counter=Update_VIP(vip,ptr4);
	return counter;
}
//int Remove_VIP(VIP *vip,int counter)
//{
//	FILE *ptr4;
//	int i,j,index=0;
//	for(i=0;i<counter;i++)
//	{
//		printf("%d-%s\n",i,vip[i].name);
//	}
//	do{
//	printf("Choose person\n");
//	scanf("%d",&j);
//	}while(j<0||j>(counter-1));
//	ptr4=fopen("vip.txt","w");
//	//strcpy(vip[j].name,"0");
//	//strcpy(vip[j].spend,"0");
//	//for (i=0;i<counter;i++)
//	//{
//	//	if (vip[i].name==0)
//	//		i=i++;
//	//	fputs(vip[i].name,ptr4);
//	//	fputs(vip[i].spend,ptr4);
//	//	fputs("/n",ptr4);
//
//	//}
//	//
//
//	for(i=0;i<counter;i++){
//		if(i==j)
//			i++;
//		fputs(vip[i].name,ptr4);
//		if(i==(counter-2))
//		{
//			while(vip[i].spend[index]!='\n')
//			{
//			fputc(vip[i].spend[index],ptr4);
//			index++;
//			}
//			index=0;
//			break;
//		}
//		if(i<(counter-1))
//		{
//			fputs(vip[i].spend,ptr4);
//			fputs("\n",ptr4);
//		}
//	}
//	fclose(ptr4);
//	counter=Update_VIP(vip,ptr4);
//	printf("The Remove\n");
//	getchar();
//	return counter;
//}
int Update_VIP(VIP *vip,FILE *ptr4){
int i;
char buf[100];
int counter=0;
flushall();
ptr4=fopen("vip.txt","r");
		for(i=0;fgets(buf,100,ptr4)!=NULL;i++)
		{
		strcpy(vip[i].name,buf);
		fgets(buf,100,ptr4);
		strcpy(vip[i].spend,buf);
		fgets(buf,100,ptr4);
		counter++;
		}
		fclose(ptr4);
		return counter;
}
int Remove_Schedule(Staff *staff,Schedule *worker,int countWorkers,int countStaff){
	FILE *ptr3;
	char buf[100],buf2[100];
	char temp[100],temp2[100],starttemp[100],finaltemp[100];
	int counter=0,i,flag=0,index=0,j,index2=0,index3=0,flagofnames=0,flagday=0,finalindex=0,startindex=0;
	int removecounter=0,fin=0;
	flushall();
	system("cls");
	ptr3=fopen("schedule.txt","r");
	printf("This are the workers:\n");
	for(i=0;i<countStaff;i++)
	{
		flagofnames=0;
		printf("---------------------------\n");
		puts(staff[i].name);
		printf("The days of work is:\n");
		strcpy(starttemp,staff[i].name);
			while(starttemp[index3]!='\n')
			index3++;
			starttemp[index3]='\0';
			index3=0;
		for(j=0;j<countWorkers;j++)
		{
			strcpy(temp2,worker[j].name);
			while(temp2[index2]!='\n')
			index2++;
			temp2[index2]='\0';
			index2=0;
			if(strcmp(starttemp,temp2)==0)
			{
				printf("%d\n",atoi(worker[j].day));
				flagofnames=1;
			}
		}
		if(flagofnames==1)
		printf("--------------------------\n");
	}
	printf("name:");
	gets(buf);
	for(i=0;i<countStaff;i++){
		strcpy(starttemp,staff[i].name);
		while(starttemp[startindex]!='\n')
			startindex++;
		starttemp[startindex]='\0';
		startindex=0;
		if(strcmp(starttemp,buf)==0)
		{
			flag=1;
			break;
		}
	}
	if(flag==0)
	{
		printf("The worker are not exist,press any key to back menu\n");
		getchar();
	}
	if(flag==1)
	{
	printf("\nDay:");
	gets(buf2);
	for(i=0;i<countWorkers;i++)
	{
		strcpy(finaltemp,worker[i].name);
		while(finaltemp[finalindex]!='\n')
			finalindex++;
		finaltemp[finalindex]='\0';
		finalindex=0;
		if(atoi(buf2)==atoi(worker[i].day)&&(strcmp(finaltemp,buf)==0))
		{
			removecounter=i;
			break;
		}
		if(atoi(buf2)==atoi(worker[i].day)&&(strcmp(finaltemp,buf)!=0))
		{
			flagday=1;
			break;
		}
	}
	if(flag==1&&flagday==1)
	{
		printf("The day that worker %s not exist,press any key to back menu\n",buf);
		getchar();
	}
	}
	fclose(ptr3);
	if(flag==1&&flagday==0)
	{
	ptr3=fopen("schedule.txt","w");
	for(j=0;j<10;j++)
	{
	for(i=0;i<countWorkers;i++)
	{
		if(i==removecounter)
			i++;
	fputs(worker[i].name,ptr3);
	fputs(worker[i].start,ptr3);
	fputs(worker[i].finish,ptr3);
	fputs(worker[i].name,ptr3);
	if(i<(countWorkers-1))
			fputs("\n",ptr3);
	}
	}
	printf("The worker is succesefully deleted!Press any key\n");
	getchar();
	}
	fclose(ptr3);
	counter=Update_Schedule(staff,worker,ptr3,countWorkers);
	return counter;
}
int Add_Schedule(Staff *staff,Schedule *worker,int countWorkers,int countStaff){
	FILE *ptr3;
	char buf[100];
	char temp[100];
	int counter=0,i,flag=0,index=0;
	flushall();
	system("cls");
	ptr3=fopen("schedule.txt","a");
	printf("This are the workers:\n");
	for(i=0;i<countStaff;i++)
		puts(staff[i].name);
	printf("name:");
	gets(buf);
	for(i=0;i<countStaff;i++){
		strcpy(temp,staff[i].name);
		while(temp[index]!='\n')
			index++;
		temp[index]='\0';
		index=0;
		if(strcmp(temp,buf)==0)
		{
			flag=1;
			break;
		}
	}

	if(flag==1)
	{
		printf("\n");
		fseek(ptr3,+100, SEEK_END);
		fputc('\n',ptr3);
		fputc('\n',ptr3);
		fputs(buf,ptr3);
		fputc('\n',ptr3);

		printf("\nStart at:");
		gets(buf);
		fputs(buf,ptr3);
		fputc('\n',ptr3);

		printf("\nFinish at:");
		gets(buf);
		fputs(buf,ptr3);
		fputc('\n',ptr3);

		printf("\nDay:");
		gets(buf);
		fputs(buf,ptr3);
		printf("The Schedule of worker succesfully added:press any key to back Schedule menu");
		getchar();
	}
	fclose(ptr3);
	if(flag==0)
	{
		printf("The worker are not exist,press any key to back menu\n");
		getchar();
	}
	counter=Update_Schedule(staff,worker,ptr3,countWorkers);
	return counter;


}
void Print_Schedule(Schedule *worker,FILE *ptr3,int counter){
	int i,index=0,j;
	char temp[100];
	system("cls");
	ptr3=fopen("schedule.txt","r");
				if(ptr3==NULL){
    printf("Unable to open the file. Program will now exit.");
    exit(0);
  }			printf("Day:\t\tName:\t\t    Start at:\t\t Finish at:\n");
				for(i=0;i<counter;i++){
					index=0;
					strcpy(temp,worker[i].day);
					printf("%d",atoi(temp));
					strcpy(temp,worker[i].name);
					while(temp[index]!='\n')
						index++;
					for(j=index;j<20;j++)
					{
						temp[index]=' ';
						index++;
					}
					temp[index]='\0';
					index=0;
					printf("\t\t%s",temp);
					strcpy(temp,worker[i].start);
					while(temp[index]!='\n')
						index++;
					temp[index]='\0';
					index=0;
					printf("%s",temp);
					strcpy(temp,worker[i].finish);
					while(temp[index]!='\n')
						index++;
					temp[index]='\0';
					index=0;
					printf("\t\t\t %s",temp);
					printf("\n");
				}
				printf("\n\nPress Any key to back Menu Schedule...\n");

				fclose(ptr3);
				getchar();
				getchar();
}
int Update_Schedule(Staff *staff,Schedule *worker,FILE *ptr3,int countWorkers){
	int i,j,counter=0;
	char buf[100];
	char temp[100];
	flushall();
		ptr3=fopen("schedule.txt","r");
				if(ptr3==NULL){
    printf("Unable to open the file. Program will now exit.");
    exit(0);
  }
	for(i=0;fgets(buf,100,ptr3)!=NULL;i++){
			strcpy(temp,buf);
		for(j=0;j<countWorkers;j++)
		{
		if(strcmp(temp,staff[j].name)==0)
		{
			strcpy(worker[counter].name,temp);
			//printf("%s",worker[i].name);
			fgets(buf,100,ptr3);
			strcpy(worker[counter].start,buf);
			//printf("%s",worker[i].start);
			fgets(buf,100,ptr3);
			strcpy(worker[counter].finish,buf);
			///printf("%s",worker[i].finish);
			fgets(buf,100,ptr3);
			strcpy(worker[counter].day,buf);
			//printf("%s",worker[i].day);
			fgets(buf,100,ptr3);
			counter++;
		}
		}
	}
	fclose(ptr3);
	return counter;
}
void Loading()
{
	int i,counter=0;
	system("cls");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t Loading...\n\t\t\t");
	//printf("Loading...\t");
	for(i=0;i<100000000000;i++){
		if(i%90000599==0)
		{
			counter++;
			printf("*\t");
		}
		if(counter==4)
		{
			system("cls");
			break;
		}

	}

}
void Final_Remove_Inventory(Drink *drinks,int counter,char buf[100],FILE *ptr2){
	int i=0,index=0,flag=0;
	int indexbuf1=0,indexbuf2=0,countputs=0;
	char newbuf[100];
	char temp[100];
	ptr2=fopen("inventory.txt","r");
	if(ptr2==NULL){
    printf("Unable to open the file. Program will now exit.");
    exit(0);
  }
	flushall();
	while(fgets(newbuf,100,ptr2)!=NULL)
	{
		while(newbuf[indexbuf1]!='\n')
				indexbuf1++;
			newbuf[indexbuf1]='\0';
		if(strcmp(newbuf,buf)==0)	
		{
			for(i=0;i<counter;i++){
				strcpy(temp,drinks[i].name);
				while(temp[indexbuf2]!='\n')
					indexbuf2++;
				temp[indexbuf2]='\0';
				if(strcmp(newbuf,temp)==0)
				{
					index=i;
					break;
				}
				indexbuf2=0;
			}
			break;
		
		}
		indexbuf1=0;
	}

			fclose(ptr2);
			ptr2=fopen("inventory.txt","w");
			
			for(i=0;i<counter;i++){
				if(i==index)
					i++;
				fputs(drinks[i].name,ptr2);
				fputs(drinks[i].price,ptr2);
				fputs(drinks[i].quantity,ptr2);
				if(i<(counter-1))
				fputc('\n',ptr2);
				countputs++;
			}
	fclose(ptr2);

}
int Update_Product(Drink *drinks,char buf[100],FILE *ptr2){
int i;
char buf2[100];
int countInverntory=0,countlines=0,index=0;
flushall();
ptr2=fopen("inventory.txt","r");
		for(i=0;fgets(buf,100,ptr2)!=NULL;i++)
		{
		strcpy(drinks[i].name,buf);
		fgets(buf2,100,ptr2);
		strcpy(drinks[i].price,buf2);
		fgets(buf2,100,ptr2);
		strcpy(drinks[i].quantity,buf2);
		fgets(buf2,100,ptr2);
		countInverntory++;
		}
		fclose(ptr2);
		return countInverntory;
}
void Print_Inventory_In_Inventory(Drink *drinks,int counter){
	int i;
	system("cls");
	flushall();
	for(i=0;i<counter;i++){
		printf("name: %s\n",drinks[i].name);
		printf("price: %s\n",drinks[i].price);
		printf("quantity: %s\n",drinks[i].quantity);
		printf("\n");
	}
	printf("\nPress any key to return to Inventory Menu..\n");
	getchar();

}
int Remove_Product(Drink *drinks,int counter){
	FILE *ptr2;
	char buf[100];
	char choose[5];
	int newcounter=0,i,index=0,index2=0;
	char temp[100],temp2[100];
	int flag=1;
	ptr2=fopen("inventory.txt","r");
		if(ptr2==NULL){
    printf("Unable to open the file. Program will now exit.");
    exit(0);
  }
	system("cls");
	if(ptr2==NULL){
    printf("Unable to open the file. Program will now exit.");
    exit(0);
  }
	flushall();
	printf("Enter the name of the Product item you want remove:\n");
	printf("name: ");
	gets(buf);
	for(i=0;i<counter;i++){
		flushall();
		strcpy(temp,drinks[i].name);
		while(temp[index]!='\n')
				index++;
			temp[index]='\0';
		if(strcmp(buf,temp)==0)
		{
			flag=0;
			strcpy(temp2,drinks[i].name);
			while(temp2[index2]!='\n')
				index2++;
			temp2[index2]='\0';
		}
		index=0;
		index2=0;
	}
	if(flag==0)
	{
		printf("\nAre you sure that you want remove this Staff Member? press 1 to confirm or 0 to return to the Managment Menu\n");
		gets(choose);
		if(strcmp(choose,"1")==0)
		{
			fclose(ptr2);
			Final_Remove_Inventory(drinks,counter,buf,ptr2);
			printf("The user was succesfully removed!press any key to return to the Managment Menu\n");
			getchar();
		}
	}
	if(flag==1){
		printf("The Product name don't exit press any key to back Inventory menu\n");
		getchar();
	}
	counter=Update_Product(drinks,buf,ptr2);
	return counter;
}
int Add_Product(Drink *drinks,int counter){
	FILE *ptr2;
	char buf[100];
	int i,flag=1,countbacks=0;
	int index=0,index2=0;
	char temp[100];
	char temp2[100];
	system("cls");
	ptr2=fopen("inventory.txt","r");
	if(ptr2==NULL){
    printf("Unable to open the file. Program will now exit.");
    exit(0);
  }
	printf("Add_Inventory\n");
	flushall();
	do
	{
		if(countbacks>0)
		printf("The Product: '%s' exist please try again!Press any key\n",temp2);
		flag=1;
	printf("name: ");
	gets(buf);
	for(i=0;i<counter;i++){
		strcpy(temp,drinks[i].name);
		while(temp[index]!='\n')
				index++;
			temp[index]='\0';
		if(strcmp(buf,temp)==0)
		{
			flag=0;
			strcpy(temp2,drinks[i].name);
			while(temp2[index2]!='\n')
				index2++;
			temp2[index2]='\0';
		}
		index=0;
		index2=0;
	}
	if(flag==0)
	{
		system("cls");
	}
	countbacks++;
	}while(flag==0);
	fclose(ptr2);
	ptr2=fopen("inventory.txt","a");
		if(ptr2==NULL){
    printf("Unable to open the file. Program will now exit.");
    exit(0);
  }
	fseek(ptr2,+100, SEEK_END);
	fputc('\n',ptr2);
	fputc('\n',ptr2);
	fputs(buf,ptr2);
	fputc('\n',ptr2);

	printf("\nprice: ");
	gets(buf);
	fputs(buf,ptr2);
	fputc('\n',ptr2);

	printf("\nquantity: ");
	gets(buf);
	fputs(buf,ptr2);
	printf("The new Inventory Item was succesfully added. Press any key to return to the Inventory Menu...\n");
	getchar();
	fclose(ptr2);
	counter=Update_Product(drinks,buf,ptr2);
	return counter;
}
int Update_Staff(Staff *staff,char buf[100],FILE *ptr){
	int i,counter=0;
	ptr=fopen("oved.txt","r");
	for(i=0;fgets(buf,100,ptr)!=NULL;i++)
	{
		strcpy(staff[i].id,buf);
		fgets(buf,100,ptr);
		strcpy(staff[i].name,buf);
		fgets(buf,100,ptr);
		strcpy(staff[i].password,buf);
		fgets(buf,100,ptr);
		strcpy(staff[i].permission,buf);
		fgets(buf,100,ptr);
		strcpy(staff[i].position,buf);
		fgets(buf,100,ptr);
		strcpy(staff[i].salary,buf);
		fgets(buf,100,ptr);
		counter++;
	}
	fclose(ptr);
	return counter;
	
}
void Print_Inventory_In_Management(int counter2,FILE *ptr2,Drink *drinks){
	int i;
	system("cls");
	for(i=0;i<counter2;i++){
		printf("name: %s\n",drinks[i].name);
		printf("price: %s\n",drinks[i].price);
		printf("quantity: %s\n",drinks[i].quantity);
		printf("\n");
	}
	printf("\nPress any key to return to Managment Menu..\n");
	getchar();
	getchar();
}
void Print_Staff(Staff *staff,int counter){
	int i;
	system("cls");
	for(i=0;i<counter;i++){
		printf("Id: %s\n",staff[i].id);
		printf("Name: %s\n",staff[i].name);
		printf("Password: %s\n",staff[i].password);
		printf("Permission: %s\n",staff[i].permission);
		printf("Position: %s\n",staff[i].position);
		printf("Salary: %s\n",staff[i].salary);
		printf("\n");
	}
	printf("\nPress any key to return to Managment Menu..\n");
	getchar();
	getchar();
}
char Identifier(Staff *staff,int counter)
{
	int i,j;
	char user[100];
	char dont_permissed='0',permissed='0';
	char password[100];
	int flag=0;
	char temp[100],temp2[100];
	char permiss[5];
	flushall();
	//printf("User:");
	printf("\n\n\n\n\n\n\n\n\n\t\t\tPARADISE CLUB-->User:");
	gets(user);
	//printf("Password:");
	printf("\n\n\t\t\tPARADISE CLUB-->Password:");
	gets(password);
	for(i=0;i<counter;i++)
	{
		strcpy(temp,staff[i].id);
		temp[4]='\0';
		strcpy(temp2,staff[i].password);
		temp2[4]='\0';
		if(strcmp(temp2,password)==0 &&strcmp(temp,user)==0)
		{
			strcpy(permiss,staff[i].permission);
			permissed=permiss[0];
			flag=1;
		}
	}
		if(flag==1)
		{
			return permissed;
		}
	
	return dont_permissed ;
}
int Add_Staff(Staff *staff,int counter){
	FILE *ptr;
	char buf[100];
	int flag=1,countbacks=0,i;
	char temp[100],temp2[100];
	int index=0,index2=0;
	system("cls");
	ptr=fopen("oved.txt","r");
	if(ptr==NULL){
    printf("Unable to open the file. Program will now exit.");
    exit(0);
  }
	flushall();
	printf("Add_Staff\n");
	do
	{
		if(countbacks>0)
			printf("The Staff: '%s' exist please try again!Press any key\n",temp2);
		flag=1;
		printf("id-4 chars: ");
		gets(buf);
		for(i=0;i<counter;i++){
			strcpy(temp,staff[i].id);
			while(temp[index]!='\n')
				index++;
			temp[index]='\0';
			if(strcmp(buf,temp)==0)
			{
				flag=0;
				strcpy(temp2,staff[i].id);
				while(temp2[index2]!='\n')
					index2++;
				temp2[index2]='\0';
			}
			index=0;
			index2=0;
		}
		if(flag==0)
		{
			system("cls");
		}
		countbacks++;
	}while(flag==0);
	fclose(ptr);
	ptr=fopen("oved.txt","a");
	fseek(ptr,+100, SEEK_END);
	fputc('\n',ptr);
	fputc('\n',ptr);
	fputs(buf,ptr);
	fputc('\n',ptr);

	printf("\nname: ");
	gets(buf);
	fputs(buf,ptr);
	fputc('\n',ptr);

	printf("\npassword: ");
	gets(buf);
	fputs(buf,ptr);
	fputc('\n',ptr);

	printf("\npermission: ");
	gets(buf);
	fputs(buf,ptr);
	fputc('\n',ptr);

	printf("\nposition: ");
	gets(buf);
	fputs(buf,ptr);
	fputc('\n',ptr);

	printf("\nsalary: ");
	gets(buf);
	fputs(buf,ptr);
	printf("The new Staff Member was succesfully added. Press any key to return to the Managment Menu...\n");
	getchar();
	fclose(ptr);
	counter=Update_Staff(staff,buf,ptr);
	return counter;
}
int check_if_Staff_exist(Staff *staff,char buf[100],int counter){
	int flag=0,i;
	char temp[100];
	flushall();
	for(i=0;i<counter;i++){
		strcpy(temp,staff[i].id);
		temp[4]='\0';
		if(strcmp(buf,temp)==0)
		{
			printf("That Staff is already in the system: %s\n",staff[i].name);
			flag=1;
		}
	}

	return flag;
}
void Final_Remove(Staff *staff,int counter,char buf[100],FILE *ptr){
	int i=0,index;
	char newbuf[100];
	char temp[100];
	ptr=fopen("oved.txt","r");
	if(ptr==NULL){
    printf("Unable to open the file. Program will now exit.");
    exit(0);
  }
	while(fgets(newbuf,100,ptr)!=NULL)
	{
		newbuf[4]='\0';
		if(strcmp(newbuf,buf)==0)	
		{
			for(i=0;i<counter;i++){
				strcpy(temp,staff[i].id);
				temp[4]='\0';
				if(strcmp(newbuf,temp)==0)
				{
					index=i;
					break;
				}
			}
			break;
		}
	}

			fclose(ptr);
			ptr=fopen("oved.txt","w");
			for(i=0;i<counter;i++){
				if(i==index)
					i++;
				fputs(staff[i].id,ptr);
				fputs(staff[i].name,ptr);
				fputs(staff[i].password,ptr);
				fputs(staff[i].permission,ptr);
				fputs(staff[i].position,ptr);
				fputs(staff[i].salary,ptr);
				if(i<(counter-1))
					fputc('\n',ptr);
			}
	fclose(ptr);
}
int Remove_Staff(Staff *staff,int counter){
	FILE *ptr;
	char buf[100];
	char choose[5];
	int newcounter=0;
	int flag=0;
	ptr=fopen("oved.txt","r");
	system("cls");
	if(ptr==NULL){
    printf("Unable to open the file. Program will now exit.");
    exit(0);
  }
	flushall();
	printf("Enter the ID of the Staff Member you want remove:\n");
	gets(buf);
	flag=check_if_Staff_exist(staff,buf,counter);
	if(flag==1)
	{
		printf("\nAre you sure that you want remove this Staff Member? press 1 to confirm or 0 to return to the Managment Menu\n");
		gets(choose);
		if(strcmp(choose,"1")==0)
		{
			Final_Remove(staff,counter,buf,ptr);
			printf("The user was succesfully removed!press any key to return to the Managment Menu\n");
			getchar();
		}
	}
	if(flag==0)
	{
	printf("This Staff doesn't exists, press any key to return to the Managment Menu...\n");
	getchar();
	}
	fclose(ptr);
	newcounter=Update_Staff(staff,buf,ptr);
	return newcounter;
}
int Management(Staff *staff,int counter,char buf[100],FILE *ptr,int counter2,FILE *ptr2,Drink *drinks,Schedule *worker,FILE *ptr3,int countWork,VIP *vip,int counterVIP)
{
	
	int x;
	
	do
	{
		system("cls");
		system("COLOR F0");
		printf("\n\n\n\n\n\n\n\t\t\tChoose your wanted option: \n\t\t\t1-Add staff \n\t\t\t2-Remove staff \n\t\t\t3-Print VIP \n\t\t\t4-Print Staff info \n\t\t\t5-Print Inventory \n\t\t\t6-Print finance record \n\t\t\t7-Schedule\n\t\t\t8-Exit to the user \n\t\t\t9-exit programme\n\n\n\n\n\n\n");
		scanf("%d",&x);
		if(x==1)
			counter=Add_Staff(staff,counter);
		if(x==2)
			counter=Remove_Staff(staff,counter);
		if(x==3)
		{
			Print_VIP(vip,counterVIP);
		}
		if(x==4)
			Print_Staff(staff,counter);
		if(x==5)
			Print_Inventory_In_Management(counter2,ptr2,drinks);
//		if(x==6)
//			Print_Finance_Record();
		if(x==7)
			Print_Schedule(worker,ptr3,countWork);
		if(x==8)
			return 0;
		if (x==9)
		{
			printf("Thank You and have a nice day!!!press any key...\n");
			getchar();
			getchar();
			exit(1);
		}
		countWork=Update_Schedule(staff,worker,ptr3,counter);
	}while(x!=10);
}
int Inventory(Drink *drinks,char buf2[100],FILE *ptr2,int counter)
{
	int x,i;
	system("cls");

	do
	{
		system("cls");
		printf("Inventory menu \n Choose your wanted option: \n1-Add Product \n2-Remove Product \n3-Update Product \n4-Print Inventory\n5-Exit to the user \n6-exit programme\n");
		scanf("%d",&x);
		if(x==1)
			counter=Add_Product(drinks,counter);
		if(x==2)
			counter=Remove_Product(drinks,counter);
		if(x==3)
			counter=Update_Product(drinks,buf2,ptr2);
		if(x==4)
			Print_Inventory_In_Inventory(drinks,counter);
		if(x==5)
			return 0;
		if (x==6)
		{
			printf("Thank You and have a nice day!!!press any key...\n");
			getchar();
			getchar();
			exit(1);
		}
	}while(x!=6);

}
int Vip(VIP *vip,FILE *ptr4,int counter)
{
		int x;
	
	do
	{

		system("cls");
		printf("Choose your wanted option: \n1-Add VIP  \n2-Remove VIP \n3-Print VIP list\n4-Exit to the User \n5-Exit\n");
		scanf("%d",&x);
		if(x==1)
			counter=Add_VIP(vip,counter);
		if(x==2)
			counter=Remove_VIP(vip,counter);
		if(x==3)
			Print_VIP(vip,counter);
		if(x==4)
			return 0;
		if (x==5)
		{
			printf("Thank You and have a nice day!!!press any key...\n");
			getchar();
			getchar();
			exit(1);
		}
		
	}while(x!=5);
}
int schedule(Schedule *worker,FILE *ptr3,int counter,Staff *staff,int countstaff)
{
	int x;
	
	do
	{
		
		system("cls");
		printf("Choose your wanted option: \n1-Add Staff's Schedule   \n2-Remove Staff's Schedule \n3-Print Staff's Schedule \n4-Exit to the user\n5-Exit programme\n");
		scanf("%d",&x);
		if(x==1)
			counter=Add_Schedule(staff,worker,counter,countstaff);
		if(x==2)
			Remove_Schedule(staff,worker,counter,countstaff);
		if(x==3)
			Print_Schedule(worker,ptr3,counter);
		if(x==4)
			return 0;
		if(x==5)
		{
			printf("Thank You and have a nice day!!!press any key...\n");
			getchar();
			getchar();
			exit(1);
	    }
		
	}while(x!=5);
}
void main()
{
	Staff staff[50]={NULL};
	Drink drinks[100]={NULL};
	Schedule worker[100]={NULL};
	VIP vip[100]={NULL};
	FILE *ptr;
	FILE *ptr2;
	FILE *ptr3;
	FILE *ptr4;
	int control;
	int check,sche;
	char insidesche[100];
	int countStaff=0;
	int countInverntory=0;
	int countVIP=0;
	int countSchedule=0;
	char buf[100];
	char buf2[100];
	char p;
	system("COLOR F0");
	ptr=fopen("oved.txt","r");
	if(ptr==NULL){
		printf("Unable to open the file. Program will now exit.");
		exit(0);
	}
	countStaff=Update_Staff(staff,buf,ptr);
	ptr2=fopen("inventory.txt","r");
	if(ptr2==NULL){
		printf("Unable to open the file. Program will now exit.");
		exit(0);
	}
	countInverntory=Update_Product(drinks,buf2,ptr2);
	ptr3=fopen("schedule.txt","r");
	if(ptr3==NULL){
		printf("Unable to open the file. Program will now exit.");
		exit(0);
	}
	countSchedule=Update_Schedule(staff,worker,ptr3,countStaff);
	ptr4=fopen("vip.txt","r");
	if(ptr4==NULL){
		printf("Unable to open the file. Program will now exit.");
		exit(0);
	}
	countVIP=Update_VIP(vip,ptr4);

	do{
		do{
			p=Identifier(staff,countStaff);
			control=(p-'0');
			if(control==0)
			{
				printf("\n\n\n\nYour user or password invalid try again!Press any key...\n");
				getchar();
				system("cls");
			}
		}while(control==0);
		//Loading();
		if(control==1)
		{
			printf("\nThe permission is: %d\n,press any key\n",control);
			getchar();
			system("cls");
			system("COLOR FC");
			printf("\n\n\n\n\n\n\n\n\n\t\t\t\tMANAGEMENT MENU:\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
			getchar();
			system("cls");
			system("COLOR F0");
			countStaff=Update_Staff(staff,buf,ptr);
			countSchedule=Update_Schedule(staff,worker,ptr3,countStaff);
			check=Management(staff,countStaff,buf,ptr,countInverntory,ptr2,drinks,worker,ptr3,countSchedule,vip,countVIP);
			ptr=fopen("oved.txt","r");
			if(ptr==NULL){
				printf("Unable to open the file. Program will now exit.");
				exit(0);
			}
			countStaff=Update_Staff(staff,buf,ptr);
		}
		if(control==2)
		{
			printf("\nThe permission is: %d\n,press any key\n",control);
			getchar();
			countInverntory=Update_Product(drinks,buf2,ptr2);
			check=Inventory(drinks,buf2,ptr2,countInverntory);
			ptr2=fopen("inventory.txt","r");
			if(ptr2==NULL){
				printf("Unable to open the file. Program will now exit.");
				exit(0);
			}
			countInverntory=Update_Product(drinks,buf2,ptr2);
			fclose(ptr2);
		}
		if(control==3)
		{
			printf("\nThe permission is: %d\n,press any key\n",control);
			getchar();
			ptr3=fopen("schedule.txt","r");
			if(ptr3==NULL){
				printf("Unable to open the file. Program will now exit.");
				exit(0);
			}
			check=schedule(worker,ptr3,countSchedule,staff,countStaff);
			countSchedule=Update_Schedule(staff,worker,ptr3,countStaff);
			fclose(ptr3);
		}
		if(control==4)
		{
			printf("\nThe permission is: %d\n,press any key\n",control);
			getchar();
			ptr4=fopen("vip.txt","r");
			if(ptr4==NULL){
				printf("Unable to open the file. Program will now exit.");
				exit(0);
			}
			check=Vip(vip,ptr4,countVIP);
			countVIP=Update_VIP(vip,ptr4);
			fclose(ptr4);
		}
		system("cls");
		countSchedule=Update_Schedule(staff,worker,ptr3,countStaff);
		countVIP=Update_VIP(vip,ptr4);
	}while(check!=1);

	//C:\Users\Gregory\Documents\Visual Studio 2012\Projects\Projectc
	fclose(ptr);
	fclose(ptr2);
	fclose(ptr3);

}
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

struct STUDENT
{
  int admission_no;
  char sname[40];
  int age;





}s,s1;

struct book
{  int bno;
  char bname[30];
  char authorname[30];
  int quantity;


}b,b1;


struct node
{
  int bkno;
  int fine;
  int studadmission_no;
  int d,m,y;

  struct node *next;

};
struct node *head=NULL, *current=NULL;

FILE *file1,*file2,*file3;


void update_book(int r)
 {


 int  quant;



  file1 = fopen("book.dat", "rb");

  file3 = fopen("temp.dat", "wb");

  while (fread(&b, sizeof(b), 1, file1))

   {

     if(b.bno==r)

   {   printf("enter quantity to add");
        scanf("%d",&quant);
        b.quantity=b.quantity+quant;
   }

   fwrite(&b, sizeof(b), 1, file3);
  }
   fclose(file1);

  fclose(file3);
  remove("book.dat");
	rename("temp.dat", "book.dat");
}




  void enternewbookrecord()
{ int flag3=0; char bookname[40];
        printf("enter bookname");
		scanf("%s",&bookname);
		printf("\n");

	while(fread(&b,sizeof(b),1,file1))
	{
		if(strcmpi(b.bname,bookname)==0)
		{
			update_book(b.bno);
			flag3=1;
			break;
		}


	}
	fclose(file1);

    if(flag3==0)
    {

       file1=fopen("book.dat","ab");

		printf("enter book no.");
		scanf("%d",&b.bno);
		printf("\n");
		strcpy(b.bname,bookname);
		printf("enter authorname");
		scanf("%s",&b.authorname);
		printf("\n");
		printf("enter quantity");
		scanf("%d",&b.quantity);
		printf("\n");
		fwrite(&b,sizeof(b),1,file1);

   fclose(file1);
    }




}



void bookissue()
{ int num; int admino; int flag=0;
int day,month,year;
   struct node *newnode= (struct node*)malloc(sizeof(struct node));
   newnode->next=NULL;
   printf("enter admission number");
   scanf("%d",&admino);

  printf("enter bookno. to be issued");
  scanf("%d",&num);
  file2=fopen("student.dat","rb");



  while(fread(&s,sizeof(s),1,file2))
  {   int date,month,year;
    if(s.admission_no==admino)
      {
        newnode->studadmission_no=s.admission_no;
        printf("enter date of issue dd-mm-yy");
        scanf("%d %d %d",&date,&month,&year);
        newnode->d=date;
        newnode->m=month;
        newnode->y=year;
        break;

	  }


  }
   fclose(file2);






 file1=fopen("book.dat","rb");
 while(fread(&b,sizeof(b),1,file1))
 {
   if(num==b.bno)
   {
   if(b.quantity!=0)
      {
           flag=1;
		   b.quantity=b.quantity-1;
          newnode->bkno=b.bno;
          break;
      }
   }

 }
 fclose(file1);
 if(flag==1)
 {

 if(!newnode)
{
	printf("memory allocation error");
	return;
}

if(head==NULL)
{
  head=newnode;
  current=newnode;

}

else
{
current->next=newnode;
current=newnode;
}


}
//fclose(file2);
//fclose(file1);
}


void displaylinklist()
{
  struct node *p;
  p=head;
  while(p!=NULL)
  { printf("Book No. :%d",p->bkno);
    printf("\n");
    printf("Student Admission No. :%d",p->studadmission_no);
    printf("\n");
    printf("The date of issue : %d-%d-%d",p->d,p->m,p->y);
    printf("\n");
    p=p->next;

	  }

}
int fine(struct node *a)
    {
      int d1,m1,y1;	int days;int fines;
    printf("enter date of deposit dd mm yy");

    scanf("%d %d %d",&d1,&m1,&y1);
      days=(d1-(a->d))+((m1-(a->m))*30)+((y1-(a->y))*365);
      if(days>10)
        fines=(days-10)*10;
      else
	  fines=0;

	return fines;


	}


void bookdeposit()
{ int admino;int num;
   printf("enter admission number");
   scanf("%d",&admino);

  printf("enter bookno. to be deposited");
  scanf("%d",&num);
  file2=fopen("student.dat","rb");


  file1=fopen("book.dat","rb");
 while(fread(&b,sizeof(b),1,file1))
 {
   if(num==b.bno)


		   b.quantity=b.quantity+1;;



 }

 struct node *p,*q;
  p=head;

  while(p->studadmission_no!=admino && p!=NULL)
     {
        q=p;
        p=p->next;


	 }





       printf("details of record now being deleted");
        printf("Book No. :%d",p->bkno);
        printf("\n");
        printf("Student Admission no. :%d",p->studadmission_no);
        printf("\n");
        printf("The date of issue %d-%d-%d",p->d,p->m,p->y);
        printf("\n");
    int a1= fine(p);
    printf("the fine is %d",a1);

    if(p==head)
    {
        head=head->next;
    }
    else
    q->next=p->next;
    free(p);
    }







void insert_book()
{
	int ch;
	file1=fopen("book.dat","wb");
	do
	{
		//clrscr();
		printf("enter book no.");
		scanf("%d",&b.bno);
		printf("\n");
		printf("enter bookname");
		scanf("%s",b.bname);
		printf("\n");
		printf("enter authorname");
		scanf("%s",b.authorname);
		printf("\n");
		printf("enter quantity");
		scanf("%d",&b.quantity);
		printf("\n");


		fwrite(&b,sizeof(b),1,file1);
		printf("\n\nDo you want to add more record..(1/0)");
		scanf("%d",&ch);
	}while(ch==1);
	fclose(file1);
}



void display_studentrecord()
{
	file2=fopen("student.dat","rb");
	while(fread(&s,sizeof(s),1,file2))
	{
		//	clrscr();
		printf("the admission no. is :");
		printf("%d",s.admission_no);
		printf("\n");
		printf(" student name is :");
		printf("%s",s.sname);
		printf("\n");
		printf("age is:");
		printf("%d",s.age);
		printf("\n");
	}
	fclose(file2);
}




void display_bookrecord()
{
	file1=fopen("book.dat","rb");
	while(fread(&b,sizeof(b),1,file1))
	{
			//clrscr();clrscr();
		printf(" book no. is: ");
		printf("%d",b.bno);
		printf("\n");
		printf("bookname is : ");
		printf("%s",b.bname);
		printf("\n");
		printf("authorname is : ");
		printf("%s",b.authorname);
		printf("\n");
		printf(" quantity:  ");
		printf("%d",b.quantity);
		printf("\n");

}
fclose(file1);
}



void insert_student()
{
	int ch1;
	file2=fopen("student.dat","wb");
	do
	{
		//clrscr();
		printf("enter admission no.");
		scanf("%d",&s.admission_no);
		printf("\n");
		printf("enter student name");
		scanf("%s",&s.sname);
		printf("\n");
		printf("enter age");
		scanf("%d",&s.age);
		printf("\n");


	    fwrite(&s,sizeof(s),1,file2);
		printf("\n\nDo you want to add more record..(1/0)");
		scanf("%d",&ch1);
	}while(ch1==1);
	fclose(file2);
}




void search_book()
{

    int Found=0;char bkname[40];
    printf("Enter the name of the book :");
                                            //We are searching the book by its name
     scanf("%s",&bkname);
    file1=fopen("book.dat","rb");

        while(fread(&b,sizeof(b),1,file1))
        {
           // fscan(librecord,"%d %s %s %d",&book.bno,book.bname,book.authorname,&book.quantity);
            if(strcmpi(bkname,b.bname)==0)
                {
				Found=1;
                break;
            }
        }
        if(Found)
        {

		printf("available");
		printf("\n");
        printf(" book no. is:");
		printf("%d\t",b.bno);
		printf("\n");
		printf("bookname is :");
		printf("%s",b.bname);
		printf("\n");
		printf(" authorname is");
		printf("%s",b.authorname);
		printf("\n");
		printf(" quantity:");
		printf("%d",b.quantity);
		printf("\n");
        }
        else if(!Found)
        printf("There is no such entry");
        fclose(file1);
    }



void delete_book()
{
    int booksno;
    file1=fopen("book.dat","rb");
    file3=fopen("temp.dat","wb");
        printf("Enter the book no to be deleted");

        scanf("%d",&booksno);
        while(fread(&b,sizeof(b),1,file1))
        {
            if(b.bno!=booksno)
            {
            	fwrite(&b,sizeof(b),1,file3);
			}

        }

        fclose(file1);
        fclose(file3);
        remove("book.dat");
	rename("temp.dat","book.dat");




}

//file1 for book anf file2 for student

void delete_student()
{
    char studentname[40];
    file2=fopen("student.dat","rb");
    file3=fopen("temp.dat","wb");
        printf("Enter the student name to be deleted");

        scanf("%s",&studentname);
        while(fread(&s,sizeof(s),1,file2))
        {
            if(strcmpi(s.sname,studentname)!=0)
            {
            	fwrite(&s,sizeof(s),1,file3);
			}

        }

        fclose(file2);
        fclose(file3);
        remove("student.dat");
	rename("temp.dat","student.dat");



}


void update_student()

{


 int  r, ch;

 printf("Enter admission number of student  to update:");
scanf("%d", &r);


  file2 = fopen("student.dat", "rb");

  file3 = fopen("temp.dat", "wb");

  while (fread(&s, sizeof(s), 1, file2))

  {

if (s.admission_no==r)

   {

    printf("\n\t1. Update Name of student");

    printf("\n\t2. Update age of student");

    printf("\n\t3. Update both name  and age of student");

    printf("\nEnter your choice to be updated:");

    scanf("%d", &ch);
 switch (ch)

    {

    case 1:

     printf("Enter Name: ");

     scanf("%s", &s.sname);

     break;

    case 2:
 printf("Enter age: ");

     scanf("%d", &s.age);

     break;

    case 3:

     printf("Enter Name: ");

     scanf("%s", &s.sname);

      printf("Enter age: ");

     scanf("%d", &s.age);

     break;

    default:

     printf("Invalid Selection");

     break;

    }
}

    fwrite(&s, sizeof(s), 1, file3);

   }



  fclose(file2);

  fclose(file3);
  remove("student.dat");
	rename("temp.dat", "student.dat");




 }















 //counting number of books

 void count()
 { int quant=0;
  file1=fopen("book.dat","rb");
  while(fread(&b,sizeof(b),1,file1))
  {
		   quant+=b.quantity;


   }

   printf(" total number of books are: %d",quant);

 }













void admin_menu()
{
//clrscr();
	int ch2;
	printf("\n\n\n\tADMINISTRATOR MENU");
	printf("\n\n\t1.CREATE STUDENT RECORD");
	printf("\n\n\t2.DISPLAY ALL STUDENTS RECORD");
	printf("\n\n\t3.DISPLAY SPECIFIC STUDENT RECORD ");
	printf("\n\n\t4.MODIFY STUDENT RECORD");
	printf("\n\n\t5.DELETE STUDENT RECORD");
	printf("\n\n\t6.INSERT BOOK ");
	printf("\n\n\t7.DISPLAY ALL BOOKS ");
	printf("\n\n\t8.SEARCH AND DISPLAY SPECIFIC BOOK BY NAME");
	printf("\n\n\t9.ADD BOOK RECORD");
	printf("\n\n\t10.DISPLAY ISSUED RECORDS ");
    printf("\n\n\t11.COUNT THE NUMBER OF BOOKS");
    printf("\n\n\t12.DELETE BOOK");
    printf("\n\n\t13.UPDATE BOOK");
	printf("\n\n\t14.RETURN TO THE MAIN MENU");
	printf("\n\n\tPlease Enter Your Choice (1-13) ");
	scanf("%d",&ch2);
	switch(ch2)
	{
    		case 1: //clrscr();
	    		    insert_student();
				     break;

    		case 2: display_studentrecord();
			        break;
    		case 3:
	       	      int num;
	       		//clrscr();
	       		printf("\n\n\tPlease Enter The Admission No. ");
	       		scanf("%d",num);
	       		//display_sps(num);
	       		break;


      		case 4: update_student();
			         break;

      		case 5:delete_student();
			        break;
		    case 6: //clrscr();
			        insert_book();
					break;
		    case 7: display_bookrecord();
			         break;
		    case 8:
	       			 search_book();
	       			  break;


      		case 9: enternewbookrecord();
			        break;


      		case 10: displaylinklist();
			         break;



     		case 11: count();
     		          break;
     		case 12: delete_book();
     		          break;
     	    case 13: int booksno;
			          printf("enter bookno to  update");

     	              scanf("%d",&booksno);
 			          update_book(booksno);
     	              break;
     	    case 14: return;
      		default:	printf("\a");
   	}
   }




int main()
{
	int  ch;
	//intro();
	do
	{
		//clrscr();
			printf("\n\n\n\tMAIN MENU");
			printf("\n\n\t01. BOOK ISSUE");
			printf("\n\n\t02. BOOK DEPOSIT");
	  		printf("\n\n\t03. ADMINISTRATOR MENU");
	  		printf("\n\n\t04. EXIT");
	  		printf("\n\n\tPlease Select Your Option (1-4) ");
	  	    scanf("%d",&ch);
	  	switch(ch)
	  	{
			case 1://clrscr();
				     bookissue();
			   	      break;
		  	case 2:bookdeposit();
			    	  break;
		  	case 3:admin_menu();
				      break;
		  	case 4:exit(0);
		  	default :printf("\a");
		}
    	}while(ch!='4');
    	return 0 ;
}

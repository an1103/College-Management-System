#include<fstream.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>


struct scholar
{
	   char det[50];
	   float per;
};

class College
{

    int college_id, rank, course_dur;
    char name[50], state[30], country[30], web[30], date[20];
    char course[20], select_crit[50], type[20];
    scholar scholar_crit;
    float fee;


    public:

    void getd()
    {
	cout<<"\n Enter college id, name and rank:";
	cin>>college_id; gets(name); cin>>rank;
	cout<<"Enter state, country and college type:";
	gets(state); gets(country); gets(type);
	cout<<"Enter course, duration and selection criteria: ";
	gets(course); cin>>course_dur; gets(select_crit);
	cout<<"Enter scholarship details and minimum percentage:";
	gets(scholar_crit.det); cin>>scholar_crit.per;
	cout<<"Application deadline, fee and website:";
	gets(date); cin>>fee; gets(web);
     }

    void show()
    {

       cout<<"College id, name and world rank:";
       cout<<'\n'<<college_id<<'\t'<<name<<'\t'<<rank;
       cout<<"\n State, country, type and website:";
       cout<<'\n'<<state<<'\t'<<country<<'\t'<<type<<'\t'<<web;
       cout<<"\n Courses, duration(in yrs) and selection criteria:";
       cout<<'\n'<<course<<'\t'<<course_dur<<'\t'<<select_crit;
    }

    void app_show()
    {
		cout<<"College name:";
		cout<<name;
		cout<<"\n Application deadline:";
		puts(date);
		cout<<"\n Application fees:";
		cout<<fee;
		cout<<"\n Website:";
		puts(web);
    }

    char * ret_nm()
     {
       return name;
     }

    int ret_id()
   {
     return college_id;
   }

    int ret_rank()
   {
    return rank;
   }
   float ret_per()
   {
      return scholar_crit.per;
   }
   float ret_fee()
   {
	return fee;
   }
   char * ret_det()
   {
	return scholar_crit.det;
   }
   char * ret_tp()
   {
	return type;
   }
   char * ret_cs()
   {
	return course;
   }
   void schol(float);
   char * ret_ctry()
   {
	return country;
   }
};

     fstream f1, temp;
     College c,cnew;


int check_pass(char n[] )
{
	if( strcmp(n,"admin123")==0 ) //Password is admin123
	return 0;
	else
	return 1;
}

void create()
{
	char a;
	f1.open("college.dat", ios::out|ios::binary);
	 do
	 {
	       cout<<"Enter the details of the record:";
	       c.getd();
	       f1.write((char *)&c, sizeof(c));
	       cout<<"Do you want to enter another record?";
	       cin>>a;
	 }while(a=='y'||a=='Y');
	 f1.close();
}

void src_name()
{
	    char cname[20]; int fl=0;
	    cout<<"Enter the name of college:"; gets(cname);
	    f1.open("college.dat", ios::in | ios::binary);

	    while(f1.read((char*)&c, sizeof(c)))
	    {
	      if(strcmpi(c.ret_nm(),cname)==0)
	      {
		     c.show();
		     fl++;
		     break;
	      }
	      if(fl==0)
	      cout<<"NO SUCH RECORD";
	    }
	    f1.close();
}

void scholar()
{
	    int id; float p;
	    cout<<"Enter college id:"; cin>>id;
	    cout<<"Enter grade 12 percentage:";
	    cin>>p;
	    f1.open("college.dat", ios::in | ios::binary);
	    while(f1.read((char *)&c, sizeof(c)))
	    {
	      if(c.ret_id()==id)
	      {
		   cout<<"Scholarship criteria:";
		   puts(c.ret_det());
		   c.schol(p);
		   break;
	      }
	    }
	    f1.close();

}

void College :: schol(float p)
{
	  if( (c.ret_per())<=p)
	  cout<<"Eligible!";
	  else
	  cout<<"Not eligible!";
}

void app()
{
	int id, fl=0; float p;
	cout<<"Enter college id:"; cin>>id;

	f1.open("college.dat", ios::in | ios::binary);
	while(f1.read((char *)&c, sizeof(c)))
	{
	    if(c.ret_id()==id)
	    {
		fl++;
		c.app_show();
		break;
	    }
	}
        if(fl==0)
	cout<<"Enter a valid college id!!";
	f1.close();

}

void fread()
{
	 f1.open("college.dat", ios::in | ios::binary);
	 while(f1.read((char *)&c, sizeof(c)))
	 {
	      c.show();
	 }
	 f1.close();

}

void add()
{
	 char a;
	 f1.open("college.dat", ios::app|ios::binary);
	 do
	 {
	       cout<<"Enter the details of the new record:";
	       c.getd();
	       f1.write((char *)&c, sizeof(c));
	       cout<<"Do you want to enter another record?";
	       cin>>a;
	 }while(a=='y'||a=='Y');
	 f1.close();
}

void add_n()
{
	 f1.open("college.dat", ios::in|ios::binary);
	 temp.open("new.dat", ios::out | ios::binary);
	 int r=0, rno;

	 cout<<"Enter the record no. after which you wish to insert:";
	 cin>>rno;

	 while(f1.read((char *)&c, sizeof(c)))
	 {
	       r++;
	       temp.write((char *)&c, sizeof(c));
	       if(r==rno)
	       {
		  cout<<"Enter the new details:";
		  cnew.getd();
		  temp.write((char *)&cnew, sizeof(cnew));

	       }

	 }
	 temp.close();
	 f1.close();
	 remove("college.dat");
	 rename("new.dat","college.dat");

}

void add_c()
{
	 char cname[20];
	 f1.open("college.dat", ios::in|ios::binary);
	 temp.open("new.dat", ios::out | ios::binary);
	 int r=0, rno;

	 cout<<"Enter the college name after which you wish to insert:";
	 gets(cname);

	 while(f1.read((char *)&c, sizeof(c)))
	 {
	       r++;
	       temp.write((char *)&c, sizeof(c));
	       if(strcmpi(c.ret_nm(),cname)==0)
	       {
		  cout<<"Enter the new details:";
		  cnew.getd();
		  temp.write((char *)&cnew, sizeof(cnew));

	       }

	 }
	 temp.close();
	 f1.close();
	 remove("college.dat");
	 rename("new.dat", "college.dat");

}

void add_f()
{
	 f1.open("college.dat", ios::in | ios::binary);
	 temp.open("new.dat", ios::out | ios::binary);

	 cout<<"Enter the new details:";
	 cnew.getd();
	 temp.write((char *)&cnew, sizeof(cnew));

	 while(f1.read((char *)&c, sizeof(c)))
	 {
	       temp.write((char *)&c, sizeof(c));
	 }
	 temp.close();
	 f1.close();
	 remove("college.dat");
	 rename("new.dat","college.dat");
}



void edit_n()
{
	 f1.open("college.dat", ios::in|ios::binary);
	 temp.open("new.dat", ios::out | ios::binary);
	 int r=0, rno;

	 cout<<"Enter the record no. to edit:";
	 cin>>rno;

	 while(f1.read((char *)&c, sizeof(c)))
	 {
	       r++;

	       if(r==rno)
	       {
		  cout<<"Enter the new details:";
		  c.getd();

	       }
	       temp.write((char *)&c, sizeof(c));

	 }
	 temp.close();
	 f1.close();
	 remove("college.dat");
	 rename("new.dat", "college.dat");
}

void edit_id()
{
     int id, fl=0;
     cout<<"Enter collge id:"; cin>>id;

     f1.open("college.dat", ios::in | ios::binary);
     temp.open("new.dat", ios::out | ios::binary);

     while(f1.read((char *)&c, sizeof(c)))
     {
	   if(c.ret_id()==id)
	   {
		   fl++;
		   cout<<"\n Enter the new details:";
		   c.getd();
	   }
	   temp.write((char *)&c, sizeof(c));

	   if(fl==0)
	   cout<<"NO SUCH RECORD!";
     }
     temp.close();
     f1.close();
     remove("college.dat");
     rename("new.dat", "college.dat");
}

void edit_nm()
{
     char cname[20], fl=0;
     cout<<"Enter collge name:"; gets(cname);

     f1.open("college.dat", ios::in | ios::binary);
     temp.open("new.dat", ios::out | ios::binary);

     while(f1.read((char *)&c, sizeof(c)))
     {
	   if(strcmpi(c.ret_nm(),cname)==0)
	   {
		   fl++;
		   cout<<"Enter the new details:";
		   c.getd();
	   }
	   temp.write((char *)&c, sizeof(c));
     }

	   if(fl==0)
	   cout<<"NO SUCH RECORD!";

     temp.close();
     f1.close();
     remove("college.dat");
     rename("new.dat", "college.dat");
}

void del_nm()
{
      char cname[20]; int fl=0;
      cout<<"Enter the name of college:"; gets(cname);
      f1.open("college.dat", ios::in | ios::binary);
      temp.open("new.dat", ios::out | ios::binary);

      while(f1.read((char *)&c, sizeof(c)))
      {
	  if(strcmpi(c.ret_nm(),cname)!=0)
	  {
		     temp.write((char *)&c, sizeof(c));
		     fl++;
	  }
      }
     if(fl==0)
     cout<<"NO SUCH RECORD"; 
     temp.close();
     f1.close();
     remove("college.dat");
     rename("new.dat", "college.dat");
}

void del_id()
{
      int id, fl=0;
      cout<<"Enter the college id:"; cin>>id;
      f1.open("college.dat", ios::in | ios::binary);
      temp.open("new.dat", ios::out | ios::binary);

      while(f1.read((char *)&c, sizeof(c)))
      {
	  if(c.ret_id()!=id)
	  {
		     temp.write((char *)&c, sizeof(c));
		     fl++;
	  }  
      }
     if(fl==0)
     cout<<"NO SUCH RECORD";
     temp.close();
     f1.close();
     remove("college.dat");
     rename("new.dat", "college.dat");
}

void del_n()
{
	 f1.open("college.dat", ios::in|ios::binary);
	 temp.open("new.dat", ios::out | ios::binary);
	 int r=0, rno;

	 cout<<"Enter the record no. which you wish to delete:";
	 cin>>rno;

	 f1.seekg(0);

	 while(f1.read((char *)&c, sizeof(c)))
	 {
	       r++;

	       if(r!=rno)
	       temp.write((char *)&c, sizeof(c));
	 }
	 temp.close();
	 f1.close();
	 remove("college.dat");
	 rename("new.dat", "college.dat");
}

void del_l()
{
	 f1.open("college.dat", ios::in|ios::binary);
	 temp.open("new.dat", ios::out | ios::binary);
	 int r=0,l,n;

	 f1.seekg(0, ios::end);
	 l=f1.tellg();
	 n=l/sizeof(c);

	 f1.seekg(0);

	 while(f1.read((char *)&c, sizeof(c)))
	 {
	       r++;

	       if(r!=n)
	       temp.write((char *)&c, sizeof(c));
	 }
	 temp.close();
	 f1.close();
	 remove("college.dat");
	 rename("new.dat", "college.dat");

}

void del_f()
{
	 f1.open("college.dat", ios::in|ios::binary);
	 temp.open("new.dat", ios::out | ios::binary);

	 f1.read((char *)&c, sizeof(c));

	 while(f1.read((char *)&c, sizeof(c)))
	 {
	       temp.write((char *)&c, sizeof(c));
	 }
	 temp.close();
	 f1.close();
	 remove("college.dat");
	 rename("new.dat", "college.dat");

}

void src_id()
{
     int id, fl=0;
     cout<<"Enter id:";
     cin>>id;

     f1.open("college.dat", ios::in | ios::binary);
     temp.open("new.dat", ios::out | ios::binary);

     while(f1.read((char *)&c, sizeof(c)))
     {
	   if(c.ret_id()==id)
	   {         c.show();
		     fl++;
		     break;
	   }

      }
      if(fl==0)
      cout<<"\n NO SUCH RECORD";
	    f1.close();
}

void src_rank()
{
     int rk, fl=0;
     cout<<"Enter rank:";
     cin>>rk;

     f1.open("college.dat", ios::in | ios::binary);
     temp.open("new.dat", ios::out | ios::binary);

     while(f1.read((char *)&c, sizeof(c)))
     {
	   if(c.ret_rank()==rk)
	   {         c.show();
		     fl++;
		     break;
	   }

      }
      if(fl==0)
      cout<<"No such record!";
      f1.close();
}

void src_ctry()
{
	    char ctry[20]; int fl=0;
	    cout<<"Enter the name of country:"; gets(ctry);
	    f1.open("college.dat", ios::in | ios::binary);

	    while(f1.read((char *)&c, sizeof(c)))
	    {
	      if(strcmpi(c.ret_ctry(),ctry)==0)
	      {
		     c.show();
		     fl++;
		     break;
	      }
	    }
	    if(fl==0)
	    cout<<"NO SUCH RECORD";
	    f1.close();
}

void src_cs()
{
	    char cs[20]; int fl=0;
	    cout<<"Enter the name of course:"; gets(cs);
	    f1.open("college.dat", ios::in | ios::binary);

	    while(f1.read((char *)&c, sizeof(c)))
	    {
	      if(strcmpi(c.ret_cs(),cs)==0)
	      {
		     c.show();
		     fl++;
		     break;
	      }
	    }
	    if(fl==0)
	    cout<<"NO SUCH RECORD";
	    f1.close();
}

void count_ctry()
{
	    char ctry[20]; int cnt=0;
	    cout<<"Enter the name of country:"; gets(ctry);
	    f1.open("college.dat", ios::in | ios::binary);

	    while(f1.read((char *)&c, sizeof(c)))
	    {
	      if(strcmpi(c.ret_ctry(),ctry)==0)
	      {
		     c.show();
		     cnt++;
		     break;
	      }
	    }
	    cout<<"\n No. of colleges in"<<ctry<<"="<<cnt;
	    f1.close();
}

void count_fee()
{
	    float f; int cnt=0;
	    cout<<"Enter application fee:";
	    cin>>f;

	    f1.open("college.dat", ios::in | ios::binary);

	    while(f1.read((char*)&c, sizeof(c)))
	    {
		if(c.ret_fee()==f)
		{    c.show();
		     cnt++;
		     break;
		}
	    }
	    cout<<"\n No. of colleges having"<<f<<"application fee is:"<<cnt;
	    f1.close();
}


void count_tp()
{
	    char tp[20]; int cnt=0;
	    cout<<"Enter the name of university (college type):"; gets(tp);
	    f1.open("college.dat", ios::in | ios::binary);

	    while(f1.read((char *)&c, sizeof(c)))
	    {
	      if(strcmpi(c.ret_tp(),tp)==0)
	      {
		     c.show();
		     cnt++;
		     break;
	      }
	    }
	    cout<<"\n No. of colleges in"<<tp<<"="<<cnt;
	    f1.close();
}

void count_cs()
{
	    char cs[20]; int cnt=0;
	    cout<<"Enter the name of the course:"; gets(cs);
	    f1.open("college.dat", ios::in | ios::binary);

	    while(f1.read((char *)&c, sizeof(c)))
	    {
	      if(strcmpi(c.ret_cs(),cs)==0)
	      {
		     c.show();
		     cnt++;
		     break;
	      }
	    }
	    cout<<"\n No. of colleges offering"<<cs<<"="<<cnt;
	    f1.close();
}


void main()
{
     clrscr();
     int ct, x; char ch, ans='y', pass[20];


     while(ans=='y'||ans=='Y')
     {
	   cout<<"You are admin(a) or student(s) : ";
	   cin>>ch;
	   if(ch=='a' || ch=='A')
	    {
		cout<<"Enter password:";
		gets(pass);
		if (check_pass(pass)==0)
		{
		    cout<<"Enter your choice:";
		    cout<<"\n 1. Create:"
			<<"\n 2. Insert:"
			<<"\n 3. Edit:"
			<<"\n 4. Delete:"
			<<"\n 5. Read:";

		    cin>>ct;
		    switch(ct)
		    {
		     case 1:   create();  break;

		     case 2:   cout<<"Enter your choice:";
			       cout<<"\n Add:";
			       cout<<"\n 1. As first record:"
				   <<"\n 2. After nth record:"
				   <<"\n 3. After a particular college:"
				   <<"\n 4. In the last:";

			       cin>>x;

			       switch(x)
			       {
				    case 1:   add_f(); break;
				    case 2:   add_n(); break;
				    case 3:   add_c(); break;
				    case 4:   add(); break;
			       }
			       break;

		    case 3:    cout<<"Enter your choice:";
			       cout<<"\n Edit according to:";
			       cout<<"\n 1. College id:"
				   <<"\n 2. College name:"
				   <<"\n 3. Record no.:";

			       cin>>x;

			       switch(x)
			       {
				   case 1:   edit_id(); break;
				   case 2:   edit_nm(); break;
				   case 3:   edit_n(); break;
			       }
			       break;

		    case 4:    cout<<"Enter your choice:";
			       cout<<"\n Delete:";
			       cout<<"\n 1. According to college name:"
				   <<"\n 2. According to college id:"
				   <<"\n 3. First record:"
				   <<"\n 4. Last record:"
				   <<"\n 5. nth record:";

			       cin>>x;

			       switch(x)
			       {
				   case 1:  del_nm(); break;
				   case 2:  del_id(); break;
				   case 3:  del_f(); break;
				   case 4:  del_l(); break;
				   case 5:  del_n(); break;
			       }
			       break;

		    case 5:    fread(); break;

		    }
	     }
	     else
	     cout<<"\n Access Denied!";
	   }

	   else if (ch=='s' || ch=='S')
	   {
	       cout<<"Enter your choice:";
	       cout<<"\n 1. Search:"
		   <<"\n 2. Count:"
		   <<"\n 3. Scholarship Details:"
		   <<"\n 4. Application Details:";


	       cin>>ct;

	       switch(ct)
	       {
		      case 1: cout<<"Enter your choice:";
			      cout<<"\n Search on the basis of:";
			      cout<<"\n 1. College name:"
				  <<"\n 2. College id:"
				  <<"\n 3. Country:"
				  <<"\n 4. Rank:"
				  <<"\n 5. Course:";

			      cin>>x;

			      switch(x)
			      {
				  case 1: src_name(); break;
				  case 2: src_id(); break;
				  case 3: src_ctry(); break;
				  case 4: src_rank(); break;
				  case 5: src_cs(); break;
			      }
			      break;

		      case 2: cout<<"Enter your choice:";
			      cout<<"\n Count no. of colleges as per:";
			      cout<<"\n 1. Country:"
				  <<"\n 2. Course:"
				  <<"\n 3. University:"
				  <<"\n 4. Application fee:";

			      cin>>x;

			      switch(x)
			      {
				  case 1: count_ctry(); break;
				  case 2: count_cs(); break;
				  case 3: count_tp(); break;
				  case 4: count_fee(); break;
			      }
			      break;



		      case 3: scholar(); break;
		      case 4: app(); break;
	       }
	   }
       cout<<"\n Do you want to continue ?";
       cin>>ans;
     }

}

/* OUTPUT:

You are admin(a) or student(s) : a

 Enter password:admin123
Enter your choice:
 1. Create:
 2. Insert:
 3. Edit:
 4. Delete:
 5. Read:1

Enter the details of the record:
 Enter college id, name and rank: 2
Alberta College
99

 Enter state, country and college type:Ontario
Canada
Alberta University

 Enter course, duration and selection criteria: Data Analytics
3
SAT Scores

 Enter scholarship details and minimum percentage Class 12 marks, proficiency awards in applied math
90.00
Application deadline, fee and website:31 Oct
3000.00
www.alberta.com
Do you want to enter another record?y
Enter the details of the record:
 Enter college id, name and rank:4
National College of Singapore
10
Enter state, country and college type:Singapore
Singapore
University of Singapore
Enter course, duration and selection criteria: Artificial Intelligence
4
JEE Rank
Enter scholarship details and minimum percentage:Class 12 marks, projects undertaken
96.00
Application deadline, fee and website:15 Oct
2500.00
www.ncs.edu
Do you want to enter another record?n

 Do you want to continue ?y

 You are admin(a) or student(s) : a

 Enter password:admin123
Enter your choice:
 1. Create:
 2. Insert:
 3. Edit:
 4. Delete:
 5. Read: 2

 Enter your choice:
 Add:
 1. As first record:
 2. After nth record:
 3. After a particular college:
 4. In the last:1

Enter the new details:
 Enter college id, name and rank:1
Princeton College of Engineering
25
Enter state, country and college type:New Jersey
USA
Princeton University
Enter course, duration and selection criteria: Computer Science
4
SAT Scores
Enter scholarship details and minimum percentage:Class 12 marks, extra curriculars
95.00
Application deadline, fee and website:15 Sept
2500.00
www.princeton.com

 Do you want to continue ?y

 You are admin(a) or student(s) : a
Enter password:admin123
Enter your choice:
 1. Create:
 2. Insert:
 3. Edit:
 4. Delete:
 5. Read:2

 Enter your choice:
 Add:
 1. As first record:
 2. After nth record:
 3. After a particular college:
 4. In the last:2

Enter the record no. after which you wish to insert:2
Enter the new details:
 Enter college id, name and rank:3
Griffith College
70
Enter state, country and college type:Brisbane
Australia
Community College
Enter course, duration and selection criteria: Environmental Science
3
Grade 12 GPA
Enter scholarship details and minimum percentage:Class 12 marks, need based
85.00
Application deadline, fee and website:31 Oct
4600.00
www.griffith.com

 Do you want to continue ? y

 You are admin(a) or student(s) : a
Enter password:admin123
Enter your choice:
 1. Create:
 2. Insert:
 3. Edit:
 4. Delete:
 5. Read:5

 College id, name and world rank:
 1       Princeton School of Engineering 25
 State, country, type and website:
New Jersey      USA     Princeton University        www.princeton.com
 Courses, duration(in yrs) and selection criteria:
Computer Science        4       SAT Scores
 College id, name and world rank:
2       Alberta College 99
 State, country, type and website:
Ontario Canada  Alberta University      www.alberta.com
 Courses, duration(in yrs) and selection criteria:
Data Analytics  3       SAT Scores
 College id, name and world rank:
3       Griffith College        70
 State, country, type and website:
Brisbane        Australia       Community College       www.griffith.com
 Courses, duration(in yrs) and selection criteria:
Environmental Science       Grade 12 GPA        3
 College id, name and world rank:
4       National College of Singapore   10
 State, country, type and website:
Singapore       Singapore       University of Singapore      www.ncs.edu
 Courses, duration(in yrs) and selection criteria:
Artificial Intelligence  4    JEE Rank
 Do you want to continue ?y

 You are admin(a) or student(s) : a
Enter password:admin123
Enter your choice:
 1. Create:
 2. Insert:
 3. Edit:
 4. Delete:
 5. Read:2

  Add:
 1. As first record:
 2. After nth record:
 3. After a particular college:
 4. In the last:4
Enter the details of the new record:
 Enter college id, name and rank:5
Imperial College of London
12
Enter state, country and college type:London
UK
College
Enter course, duration and selection criteria: English Literature
3
Grade 12 marks, IELTS
Enter scholarship details and minimum percentage:Class 12 marks, IELTS band abov
e 8
90.00
Application deadline, fee and website:15 Sept
5000.00
www.icl.org
Do you want to enter another record?n

 Do you want to continue ?y

You are admin(a) or student(s) : a
Enter password:admin123
Enter your choice:
 1. Create:
 2. Insert:
 3. Edit:
 4. Delete:
 5. Read:2

  Add:
 1. As first record:
 2. After nth record:
 3. After a particular college:
 4. In the last:3

Enter the college name after which you wish to insert:Imperial College of London
Enter the details of the new record:
 Enter college id, name and rank:6
IIT Delhi
100
Enter state, country and college type:New Delhi
India
IIT
Enter course, duration and selection criteria: BTech
4
JEE Rank
Enter scholarship details and minimum percentage:JEE Rank
98.00
Application deadline, fee and website:31 May
500.00
www.iit.in
Do you want to enter another record?n

 Do you want to continue ?y

 You are admin(a) or student(s) : a
Enter password:admin123
Enter your choice:
 1. Create:
 2. Insert:
 3. Edit:
 4. Delete:
 5. Read:3

 Edit according to:
 1. College id:
 2. College name:
 3. Record no.:1
Enter collge id:4

 Enter the new details:
 Enter college id, name and rank:4
National College of Singapore
15
Enter state, country and college type:Singapore
Singapore
University of Singapore
Enter course, duration and selection criteria: Artificial Intelligence
4
JEE Rank
Enter scholarship details and minimum percentage:Class 12 marks, projects undert
aken
96.00
Application deadline, fee and website:30 Oct
2500
www.ncs.edu

 Do you want to continue ?y

 You are admin(a) or student(s) : a
Enter password:admin123
Enter your choice:
 1. Create:
 2. Insert:
 3. Edit:
 4. Delete:
 5. Read:3

Enter your choice:
 Edit according to:
 1. College id:
 2. College name:
 3. Record no.:2

Enter collge name:Alberta College
Enter the new details:
 Enter college id, name and rank:7
Alberta College
99
Enter state, country and college type:Ontario
Canada
Alberta University
Enter course, duration and selection criteria: Data Analytics
2
SAT Scores
Enter scholarship details and minimum percentage:SAT Scores
85.00
Application deadline, fee and website:31 Oct
3000.00
www.alberta.com

 Do you want to continue ?y

You are admin(a) or student(s) : a
Enter password:admin123
Enter your choice:
 1. Create:
 2. Insert:
 3. Edit:
 4. Delete:
 5. Read:3
Enter your choice:
 Edit according to:
 1. College id:
 2. College name:
 3. Record no.:3

Enter the record no. to edit:2
Enter the new details:
 Enter college id, name and rank:2
Alberta College
99
Enter state, country and college type:Ontario
Canada
Alberta University
Enter course, duration and selection criteria: Data Science
3
SAT Scores
Enter scholarship details and minimum percentage:SAT Scores
85.00
Application deadline, fee and website:31 Oct
3000.00
www.alberta.com

 Do you want to continue ?y

 You are admin(a) or student(s) : s
Enter your choice:
 1. Search:
 2. Count:
 3. Scholarship Details:
 4. Application Details:1

Enter your choice:
 Search on the basis of:
 1. College name:
 2. College id:
 3. Country:
 4. Rank:
 5. Course:1

Enter the name of college:Alberta College
College id, name and world rank:
2       Alberta College 99
 State, country, type and website:
Ontario Canada  Alberta University      www.alberta.com
 Courses, duration(in yrs) and selection criteria:
Data Science    3       SAT Scores
 Do you want to continue ?y

 You are admin(a) or student(s) : s
Enter your choice:                                                              
 1. Search:                                                                     
 2. Count:                                                                      
 3. Scholarship Details:                                                        
 4. Application Details:1
                                                       
Enter your choice:                                                              
 Search on the basis of:                                                        
 1. College name:                                                               
 2. College id:                                                                 
 3. Country:                                                                    
 4. Rank:                                                                       
 5. Course:2
                                                                    
Enter id:3                                                                      
College id, name and world rank:                                                
3       Griffith College        70                                              
 State, country, type and website:                                              
Brisbane        Australia       Community College       www.griffith.com        
 Courses, duration(in yrs) and selection criteria:                              
Environmental Science     Grade 12 GPA        3       Grade 12 GPA                    
 Do you want to continue ?y

 You are admin(a) or student(s) : s
Enter your choice:
 1. Search:
 2. Count:
 3. Scholarship Details:
 4. Application Details:1

Enter your choice:
 Search on the basis of:
 1. College name:
 2. College id:
 3. Country:
 4. Rank:
 5. Course:3

Enter the name of country:USA
College id, name and world rank:
1       Princeton School of Engineering 25
 State, country, type and website:
New Jersey      USA     Princeton University    www.princeton.com
 Courses, duration(in yrs) and selection criteria:
Computer Science        4       SAT Scores
 Do you want to continue ?y

You are admin(a) or student(s) : s
Enter your choice:
 1. Search:
 2. Count:
 3. Scholarship Details:
 4. Application Details:1

Enter your choice:
 Search on the basis of:
 1. College name:
 2. College id:
 3. Country:
 4. Rank:
 5. Course:4

Enter rank:15
College id, name and world rank:
4       National College of Singapore   15
 State, country, type and website:
Singapore       Singapore       University of Singapore     www.ncs.edu
 Courses, duration(in yrs) and selection criteria:
Artificial Intelligence    4     JEE Rank    
 Do you want to continue ?y

You are admin(a) or student(s) : s
Enter your choice:
 1. Search:
 2. Count:
 3. Scholarship Details:
 4. Application Details:1

Enter your choice:
 Search on the basis of:
 1. College name:
 2. College id:
 3. Country:
 4. Rank:
 5. Course:5

Enter the name of course:Computer Science
College id, name and world rank:
1       Princeton School of Engineering 25
 State, country, type and website:
New Jersey      USA     Princeton University      www.princeton.com
 Courses, duration(in yrs) and selection criteria:
Computer Science        4       SAT Scores
 Do you want to continue ?y

You are admin(a) or student(s) : s
Enter your choice:
 1. Search:
 2. Count:
 3. Scholarship Details:
 4. Application Details:2

Enter your choice:
 Count no. of colleges as per:
 1. Country:
 2. Course:
 3. University:
 4. Application fee:1

Enter the name of country:Australia
College id, name and world rank:
3       Griffith College        70
 State, country, type and website:
Brisbane        Australia       Community College       www.griffith.com
 Courses, duration(in yrs) and selection criteria:
Environmental Science Grade 12 GPA        3
No. of colleges in Australia=1
 Do you want to continue ?y

You are admin(a) or student(s) : s
Enter your choice:                                                              
 1. Search:                                                                     
 2. Count:                                                                      
 3. Scholarship Details:                                                        
 4. Application Details:2
                                                       
Enter your choice:                                                              
 Count no. of colleges as per:                                                  
 1. Country:                                                                    
 2. Course:                                                                     
 3. University:                                                                 
 4. Application fee:2 
                                                          
Enter the name of the course:BTECH                                              
College id, name and world rank:                                                
6       IIT Delhi       100                                                     
 State, country, type and website:                                              
New Delhi       India   IIT     www.iit.in                                      
 Courses, duration(in yrs) and selection criteria:                              
BTech   4       JEE Rank                                                        
 No. of colleges offering BTECH=1
 Do you want to continue ?Y

You are admin(a) or student(s) : s
Enter your choice:                                                              
 1. Search:                                                                     
 2. Count:                                                                      
 3. Scholarship Details:                                                        
 4. Application Details:2
                                                       
Enter your choice:                                                              
 Count no. of colleges as per:                                                  
 1. Country:                                                                    
 2. Course:                                                                     
 3. University:                                                                 
 4. Application fee:3
                                                           
Enter the name of university (college type):community college                   
College id, name and world rank:                                                
3       Griffith College        70                                              
 State, country, type and website:                                              
Brisbane        Australia       Community College       www.griffith.com        
 Courses, duration(in yrs) and selection criteria:                              
Environmental Science  Grade 12 GPA        3
 No. of colleges in community college=1
 Do you want to continue ?y
                                                                                
You are admin(a) or student(s) : s
Enter your choice:                                                              
 1. Search:                                                                     
 2. Count:                                                                      
 3. Scholarship Details:                                                        
 4. Application Details:2
                                                       
Enter your choice:                                                              
 Count no. of colleges as per:                                                  
 1. Country:                                                                    
 2. Course:                                                                     
 3. University:                                                                 
 4. Application fee:4                                                           
Enter application fee:1000                                                      
                                                                                
 No. of colleges having 1000 application fee is:0                                 
 Do you want to continue ?y

You are admin(a) or student(s) : s
Enter your choice:                                                              
 1. Search:                                                                     
 2. Count:                                                                      
 3. Scholarship Details:                                                        
 4. Application Details:3
                                                       
Enter college id:1                                                              
Enter grade 12 percentage:90                                                    
Scholarship criteria:Class 12 marks, extra curriculars                          
Not eligible!                                                                   
 Do you want to continue ?y

You are admin(a) or student(s) : s
Enter your choice:                                                              
 1. Search:
 2. Count:
 3. Scholarship Details:
 4. Application Details:4

Enter college id:1
College name:Princeton School of Engineering
 Application deadline:15 Sept

 Application fees:2500
 Website:www.princeton.com

 Do you want to continue ?y

You are admin(a) or student(s) : a
Enter password:admin123
Enter your choice:
 1. Create:
 2. Insert:
 3. Edit:
 4. Delete:
 5. Read:4

Enter your choice:
 Delete:
 1. According to college name:
 2. According to college id:
 3. First record:
 4. Last record:
 5. nth record:1

Enter the name of college:Alberta College

 Do you want to continue ?y

You are admin(a) or student(s) : a
Enter password:admin123
Enter your choice:
 1. Create:
 2. Insert:
 3. Edit:
 4. Delete:
 5. Read:5

College id, name and world rank:
 1       Princeton School of Engineering 25
 State, country, type and website:
New Jersey      USA     Princeton University        www.princeton.com
 Courses, duration(in yrs) and selection criteria:
Computer Science        4       SAT Scores
 College id, name and world rank:
3       Griffith College        70
 State, country, type and website:
Brisbane        Australia       Community College       www.griffith.com
 Courses, duration(in yrs) and selection criteria:
Environmental Science       Grade 12 GPA        3
 College id, name and world rank:
4       National College of Singapore   10
 State, country, type and website:
Singapore       Singapore       University of Singapore      Class 12 marks, projects undertaken     www.ncs.edu
 Courses, duration(in yrs) and selection criteria:
Artificial Intelligence  JEE Rank    4
 College id, name and world rank:
5       Imperial College of London      12
 State, country, type and website:
London  UK      College www.icl.org
 Courses, duration(in yrs) and selection criteria:
English Literature      3       Grade 12 marks, IELTS
 College id, name and world rank:                                                
6       IIT Delhi       100                                                     
 State, country, type and website:                                              
New Delhi       India   IIT     www.iit.in                                      
 Courses, duration(in yrs) and selection criteria:                              
BTech   4       JEE Rank         
 Do you want to continue ?y

You are admin(a) or student(s) : a
Enter password:admin123                                                         
Enter your choice:                                                              
 1. Create:                                                                     
 2. Insert:                                                                     
 3. Edit:                                                                       
 4. Delete:                                                                     
 5. Read:4

Enter your choice:
 Delete:
 1. According to college name:
 2. According to college id:
 3. First record:
 4. Last record:
 5. nth record:2

Enter the college id:3

 Do you want to continue ?y

You are admin(a) or student(s) : a
Enter password:admin123
Enter your choice:
 1. Create:
 2. Insert:
 3. Edit:
 4. Delete:
 5. Read:5

College id, name and world rank:
 1       Princeton School of Engineering 25
 State, country, type and website:
New Jersey      USA     Princeton University        www.princeton.com
 Courses, duration(in yrs) and selection criteria:
Computer Science        4       SAT Scores
 College id, name and world rank:
4       National College of Singapore   10
 State, country, type and website:
Singapore       Singapore       University of Singapore      Class 12 marks, projects undertaken     www.ncs.edu
 Courses, duration(in yrs) and selection criteria:
Artificial Intelligence  JEE Rank    4
 College id, name and world rank:
5       Imperial College of London      12
 State, country, type and website:
London  UK      College www.icl.org
 Courses, duration(in yrs) and selection criteria:
English Literature      3       Grade 12 marks, IELTS
 College id, name and world rank:                                                
6       IIT Delhi       100                                                     
 State, country, type and website:                                              
New Delhi       India   IIT     www.iit.in                                      
 Courses, duration(in yrs) and selection criteria:                              
BTech   4       JEE Rank         
 Do you want to continue ?y

You are admin(a) or student(s) : a
Enter password:admin123                                                         
Enter your choice:                                                              
 1. Create:                                                                     
 2. Insert:                                                                     
 3. Edit:                                                                       
 4. Delete:                                                                     
 5. Read:4
                                                                      
Enter your choice:                                                              
 Delete:                                                                        
 1. According to college name:                                                  
 2. According to college id:                                                    
 3. First record:                                                               
 4. Last record:
 5. nth record:3                                                                
                                                                                
 Do you want to continue ?y

You are admin(a) or student(s) : a
Enter password:admin123
Enter your choice:
 1. Create:
 2. Insert:
 3. Edit:
 4. Delete:
 5. Read:5

 College id, name and world rank:
4       National College of Singapore   10
 State, country, type and website:
Singapore       Singapore       University of Singapore      Class 12 marks, projects undertaken     www.ncs.edu
 Courses, duration(in yrs) and selection criteria:
Artificial Intelligence  JEE Rank    4
 College id, name and world rank:
5       Imperial College of London      12
 State, country, type and website:
London  UK      College www.icl.org
 Courses, duration(in yrs) and selection criteria:
English Literature      3       Grade 12 marks, IELTS
 College id, name and world rank:                                                
6       IIT Delhi       100                                                     
 State, country, type and website:                                              
New Delhi       India   IIT     www.iit.in                                      
 Courses, duration(in yrs) and selection criteria:                              
BTech   4       JEE Rank         
 Do you want to continue ?y

You are admin(a) or student(s) : a
Enter password:admin123                                                         
Enter your choice:                                                              
 1. Create:                                                                     
 2. Insert:                                                                     
 3. Edit:                                                                       
 4. Delete:                                                                     
 5. Read:4 
                                                                     
Enter your choice:                                                              
 Delete:                                                                        
 1. According to college name:                                                  
 2. According to college id:                                                    
 3. First record:                                                               
 4. Last record:                                                                
 5. nth record:4                                                                
                                                                                
 Do you want to continue ?y

You are admin(a) or student(s) : a
Enter password:admin123
Enter your choice:
 1. Create:
 2. Insert:
 3. Edit:
 4. Delete:
 5. Read:5

 College id, name and world rank:
4       National College of Singapore   10
 State, country, type and website:
Singapore       Singapore       University of Singapore      Class 12 marks, projects undertaken     www.ncs.edu
 Courses, duration(in yrs) and selection criteria:
Artificial Intelligence  JEE Rank    4
 College id, name and world rank:
5       Imperial College of London      12
 State, country, type and website:
London  UK      College www.icl.org
 Courses, duration(in yrs) and selection criteria:
English Literature      3       Grade 12 marks, IELTS
 Do you want to continue ?y

You are admin(a) or student(s) : a
Enter password:admin123
Enter your choice:
 1. Create:
 2. Insert:
 3. Edit:
 4. Delete:
 5. Read:4

Enter your choice:
 Delete:
 1. According to college name:
 2. According to college id:
 3. First record:
 4. Last record:
 5. nth record:5

Enter the record no. which you wish to delete:4

 Do you want to continue ?Y

You are admin(a) or student(s) : a
Enter password:admin123
Enter your choice:
 1. Create:
 2. Insert:
 3. Edit:
 4. Delete:
 5. Read:5

 College id, name and world rank:
5       Imperial College of London      12
 State, country, type and website:
London  UK      College www.icl.org
 Courses, duration(in yrs) and selection criteria:
English Literature      3       Grade 12 marks, IELTS
 
  Do you want to continue ?n

*/














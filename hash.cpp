#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<time.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

using namespace std;

struct train{
	string no,seq,dist;
	string name, scode,sname,at,dt,ss,ssname,ds,dsname;
	train* next=NULL;
	bool empty;
train(){
empty=true;
    }	
};

train* a=new train[40000];

int hashf(string st){                                           //hash function to return index from station code
	int t,w=0,p=512; 	
	for(int i=0;i<st.size();i++){	
	t=(int)(st[i])-64;	
	w=w+p*t; p=p/2;  
  	}
	
	return w;
	} 

void find(string r,string t, int i){
	int tt,t1,t2; bool match=false; string ta,td;
	train* temp=&a[i];
	tt=atoi(t.c_str());
	
	while(temp!=NULL){
		ta=temp->at;
		td=temp->dt;
		ta=ta.substr(0,2)+ta.substr(3,2);
		td=td.substr(0,2)+td.substr(3,2);
		t1=atoi(ta.c_str());                                                                  //integer value of arrival time
		t2=atoi(td.c_str());                                                                  //integer value of departure time
		
		if(( (t1>(tt-30) && t1<(tt+30)) || (t2>(tt-30) && t2<(tt-30)) )&&(temp->scode==r)) {

		if(!match) cout<<"Number  Name  Src  Dest  Arrival  Departure"<<endl;                 //prints for one time when intially match was false 
		match=true;
		cout<<temp->no<<" "<<temp->name<<" "<<temp->ss<<" "<<temp->ds<<" "<<temp->at<<" "<<temp->dt<<" "<<endl;
			}
		temp=temp->next;
		}

	if(!match) cout<<"no such train found"<<endl;
}	


int main(int argc, char* argv[]){
	int i,j; 
	string g,code,time;
        train p;
	ifstream infile;
	infile.open("railtime.csv");
	getline(infile,g);
	while(infile.good()){
	getline(infile,p.no,',');
	getline(infile,p.name,',');
	getline(infile,p.seq,',');
	getline(infile,p.scode,',');
	getline(infile,p.sname,',');
	getline(infile,p.at,',');
	getline(infile,p.dt,',');
	getline(infile,p.dist,',');
	getline(infile,p.ss,',');
	getline(infile,p.ssname,',');
	getline(infile,p.ds,',');
	getline(infile,p.dsname);

	g=p.no;	                               
	if(atoi(g.c_str())==0) continue;	//checks if the input is valid
		
	i=hashf(p.scode);
	if(a[i].empty) {
	a[i]=p; 
	a[i].empty=false;     	
	
	} 
	else
	{
		train* t=new train;
		t->no=p.no;
		t->name=p.name;
		t->seq=p.seq;
		t->scode=p.scode;
		t->sname=p.sname;
		t->at=p.at;
		t->dt=p.dt;
		t->dist=p.dist;
		t->ss=p.ss;
		t->sname=p.sname;		
		t->ds=p.ds;	
		t->dsname=p.dsname;		
		t->empty=false;		

		train* temp=&a[i];
		while(temp->next!=NULL) temp=temp->next;
		temp->next=t;     
		}

	} 
	
	code=argv[1];
	time=argv[2];
	train* temp;	
	int y=hashf(code);	

	struct timespec start, stop;
  i=clock_gettime(CLOCK_REALTIME, &start);                    //start of time
  
	find(code,time,y);
	
  j=clock_gettime(CLOCK_REALTIME, &stop);                     //end of time
	cout<<"Time taken";
  printf(" %ld", stop.tv_nsec - start.tv_nsec );
	cout<<" ns"<<endl;
}


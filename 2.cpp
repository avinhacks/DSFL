#include<iostream>							//header files
#include<stdlib.h>
#include<string.h>

using namespace std;

int count = 0;

typedef struct node
{						//structure for a node of queue
	int srno;
	string name;
	int age;
	string disease;
	int severity;
	struct node *next;
}node;

class queue							//Queue class
{
public:
	node *R,*F;

	queue()						//Default constructor
	{
		R=NULL;
		F=NULL;
	}

	void enque(node );
	void display();
	node deque();

	int empty()
	{
		if(F==NULL)
		{
			return 1;
		}
		else
			return 0;
	}

};
void queue::enque(node x)			//Function to insert in queue
{
	if(F==NULL)
	{
		R=F=new node(x);
	}
	else
	{
		R->next=new node(x);
		R=R->next;
	}
	R->next=NULL;
}
node queue::deque()				//Function to delete in queue
{
	node *temp;
	node t;
	if(F==NULL)
	{
		cout<<"Queue is empty ...Underflow condition"<<endl;
		//return;
	}
	else
	{
		temp=F;
		t.name = temp -> name;
		t.disease = temp -> disease;
		t.age = temp -> age;
		t.srno = temp -> srno;
		t.next = NULL;
		t.severity = temp -> severity;
		F=F->next;
		delete temp;
		return t;

	}
}
void queue::display()
{
	node *temp=F;
	if(temp==NULL)
	{
		return;
	}
	while(temp!=NULL)
	{
		cout<<"Sr_No"<<temp->srno<<"\tName :"<<temp->name<<endl;
		temp=temp->next;
	}
}
class pq{							//Class for priority queue
	queue q[3];					//Array for 3 queues
public:
	void arrival();				//Member functions
	void service();
	void display();

};
void pq::arrival()
{
	node temp;
//	cout<<"Enter Sr No of patient"<<endl;
//	cin>>temp.srno;
	temp.srno = count;
	cout<<"Enter name of patient"<<endl;
	cin>>temp.name;
	cout<<"Enter age of patient"<<endl;
	cin>>temp.age;
	cout<<"Enter disease of patient or priority (L,M,H)"<<endl;
	cin>>temp.disease;

	if(temp.disease == "heartattack" || temp.disease == "cancer" || temp.disease == "brainhamarage" || temp.disease == "kidneyfailure" || temp.disease == "severeinjury" ||temp.disease == "H"||temp.disease == "h")
	{
		temp.severity=0;
	}
	else if(temp.disease == "eyeinfection" || temp.disease == "jaundice" || temp.disease == "diabetes" || temp.disease == "ulcer" || temp.disease == "paralysis"||temp.disease == "M"||temp.disease == "m")
	{
		temp.severity=1;
	}
	else if(temp.disease == "fever" || temp.disease == "allergy" || temp.disease == "deficiency" || temp.disease == "thyroid" || temp.disease == "chickenpox"||temp.disease == "L"||temp.disease == "l")
	{
		temp.severity=2;
	}

	switch(temp.severity)					//Insert according to severity
	{
	case 0:
		q[0].enque(temp);
		count++;
		break;
	case 1:
		q[1].enque(temp);
		count++;
		break;
	case 2:
		q[2].enque(temp);
		count++;
		break;
	default: cout<<"Wrong patient type"<<endl;
	}
}
void pq::service()				//Service of patient in order of their severity
{
	int i=0;
	node temp;
	while(i<3 && q[i].empty())
	{
		i++;
	}
	if(i==3)
	{
		cout<<"No patient to be serviced"<<endl;
	}
	else
	{
		temp=q[i].deque();
		cout<<"Patient serviced"<<endl<<"Sr No"<<temp.srno<<"\tName-"<<temp.name;

	}
}
void pq::display()
{
	cout<<endl;
	cout<<"Serious patient"<<endl;
	q[0].display();
	cout<<endl<<"Medium Illness"<<endl;
	q[1].display();
	cout<<endl<<"General"<<endl;
	q[2].display();
	cout<<endl;

}
int main()						//main function
{
	int ch;
	pq q;
	do
	{
		cout<<endl<<"1.Arrival of a patient"<<endl<<"2.Service of a patient"<<endl;
		cout<<"3.Display List of patients"<<endl<<"4.Quit"<<endl;
		cin>>ch;
		switch(ch)
		{
		case 1:q.arrival();
		break;
		case 2:q.service();
		break;
		case 3:q.display();
		break;
		case 4:exit(0);
		break;
		default:cout<<"Invalid choice"<<endl;
		}
	}
	while(ch<=4);
	return 0;
}







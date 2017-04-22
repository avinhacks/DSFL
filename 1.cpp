#include<iostream>
#include<string>
#include<cmath>

using namespace std;

template<class T>
class stack {
	struct node
	{
		T data;
		node *next;
	};

	node *top;
	public:
		stack()
		{
			top = NULL;
		}
		~stack()
		{
			node *temp;
			while(top != NULL)
			{
				temp = top;
				top = top->next;
				delete temp;
			}
		}
		void push(T x);
		void display();
		T pop();
		bool isempty();
		T stacktop();
		bool isfull();
		string intopost(string);
		string intopre(string);
		int posteval(string);
		int evaluate(int, int, int);
		int preeval(string);
};
template<class T>
bool stack<T> :: isempty()
{
	if(top == NULL)
		return true;
	return false;
}
template<class T>
bool stack<T> :: isfull()
{
	node *temp = new node;
	if(temp != NULL)
	{
		delete temp;
		return false;
	}
	return true;
}

template<class T>
void stack<T>:: push(T x)
{
	if(isfull())
		cout<<"\n Stack is full";
	else
	{
		node *newptr;
		newptr = new node;
		newptr->data = x;
		newptr->next = top;
		top = newptr;
	}
}

template<class T>
void stack<T> :: display()
{
	node *p = top;
	do
	{
		cout << p->data << " <- ";
		p = p->next;
	}while(p !=  NULL);
}

template<class T>
T stack<T> :: pop()
{
	T val;
	node *popptr;
	popptr = top;
	top = top->next;
	val = popptr->data;
	delete popptr;
	return val;
}

template<class T>
T stack<T> :: stacktop()
{
	T val = top->data;
	return val;
}

template<class T>
int precedence(T ch)
{
	if(ch=='(')
       return 0;
	if(ch=='+' || ch=='-')
		return 1;
	if(ch=='*' || ch=='/' || ch=='%')
       return 2;
    return 3;
}

template<class T>
string stack<T> :: intopost(string instr)
{
	string postr("");
	stack <char> st;
	int i;
	T ch, op;
	for(i=0; i<instr.length(); i++)
	{
		ch = instr.at(i);
		if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		{
			postr.append(1,ch);
		}
		else
		{
			if(ch=='(')
				st.push(ch);
			else if(ch==')')
			{
				while((op=st.pop())!='(')
			    {
					postr.append(1,op);
			    }
			}
			else if((st.isempty()!= true) && precedence(ch)<=precedence(st.stacktop()))
			{
				op=st.pop();
			    postr.append(1,op);
			}
			if(ch!='('&&ch!=')')
				st.push(ch);
		}
	}
	while(st.isempty()!=true)
	{
		op=st.pop();
		postr.append(1,op);
	}
	return postr;
}

template<class T>
int stack<T> :: posteval(string postr)
{
	stack <char> st;
	int poval, i, val, op1, op2;
	char ch;
	for(i=0; i<postr.length(); i++)
	{
		ch = postr.at(i);
		if(isalnum(ch))
		{
			cout<<"\n Enter Value for ( "<<ch<<" ) ";
		    cin>>val;
		    st.push(val);
		}
		else
		{
			op1=st.pop();
		    op2=st.pop();
		    poval=evaluate(ch,op1,op2);
		    st.push(poval);
		}
	}
	poval=st.pop();
	return poval;
}

template<class T>
int stack<T> :: evaluate(int ch, int op1, int op2)
{
	if(ch == '+')
		return op1+op2;
	if(ch == '-')
		return op1-op2;
	if(ch == '*')
		return op1*op2;
	if(ch == '/')
		return op1/op2;
	if(ch == '%')
		return op1%op2;
	if(ch == '^')
		return pow(op1, op2);
}

template<class T>
string stack<T> :: intopre(string instr)
{
	string prestr, revstr, postr;
	char ch;
	stack <char> st;
	int i;
	for(i=0; i<instr.length(); i++)
		st.push(instr.at(i));
	while(st.isempty() != true)
	{
		ch = st.pop();
		if(ch == '(')
			revstr.append(1, ')');
		else if(ch == ')')
			revstr.append(1, '(');
		else
			revstr.append(1, ch);
	}
	postr = st.intopost(revstr);

	for(i=0; i<postr.length(); i++)
		st.push(postr.at(i));
	while(st.isempty() != true)
		prestr.append(1, st.pop());
	return prestr;
}

template<class T>
int stack<T> :: preeval(string prestr)
{
	int i, preval;
	string postr;
	stack <char> st;
	for(i=0; i<prestr.length(); i++)
		st.push(prestr.at(i));
	while(st.isempty() != true)
	{
		postr.append(1, st.pop());
	}
	preval = st.posteval(postr);
	return preval;
}

int main()
{
 	stack <int> s1;
	stack <char> s2;

	int n,i,ch,x, ival, postval, preval;
	char c,st,cval,op;
	string instr, postr, prestr;

	do
	{
		cout<<"\n\n1.Push elements on stack \n2.Display stack \n3.Pop element from stack";
		cout<< "\n4.Stack top \n5.Infix to Postfix Conversion \n6.Postfix Evaluation";
		cout << "\n7.Infix to Prefix Conversion\n8.Prefix Evalution\n9.Exit \n>>";
		cin >> ch;
		switch(ch)
		{
			case 1:
				cout<< "\n Create stack \n a.integer stack \n b.character stack:";
				cin >> st;
				switch(st)
				{
					case 'a':
						cout<<"\n How many elements you want to push onto the stack";
						cin >> n;
						cout<< "\n Enter the elements";
						for(i=0; i<n; i++)
						{
							cin >> x;
							s1.push(x);
						}
						break;
					case 'b':
						cout<<"\n How many elements you want to push onto the stack";
						cin >> n;
						cout<< "\n Enter the elements";
						for(i=0; i<n; i++)
						{
							cin >> c;
							s2.push(c);
						}
				}
				break;
			case 2:
				if(s1.isempty() != true)
				{
					cout<<"\n Displaying integer stack: \n";
					s1.display();
				}
				if(s2.isempty() != true)
				{
					cout<<"\n Displaying character stack: \n";
					s2.display();
				}
				break;
			case 3:
				cout<< "\n Pop element from \n a. interger stack \n b. character stack";
				cin >> st;
				switch(st)
				{
					case 'a':
						do
						{
							if(s1.isempty() != true)
							{
								ival = s1.pop();
								cout << "\n Popped element:" << ival;
								cout << "\n Do you want to continue: (Y/N)";
								cin >> op;
							}
							else
							{
								cout << "\n Integer stack is empty !!";
								break;
							}
						}while(op != 'N' || op != 'n');
						break;
					case 'b':
						do
						{

							if(s2.isempty() != true)
							{
								cval = s2.pop();
								cout << "\n Popped element:" << cval;
								cout << "\n Do you want to continue: (Y/N)";
								cin >> op;
							}
							else
							{
								cout << "\n Character stack is empty ";
								break;
							}
						}while(op != 'N' || op != 'n');
						break;
				}
				break;
			case 4:
				if(s1.isempty() != true)
				{
					ival = s1.stacktop();
					cout << "\n Integer Stack Top element:" << ival;
				}
				else
					cout << "\n Integer Stack is Empty !!";
				if(s2.isempty() != true)
				{
					cval = s2.stacktop();
					cout << "\n Character Stack Top element:" << cval;
				}
				else
						cout << "\n Character Stack is Empty !!";
				break;
			case 5:
				cout << "\n Enter an Infix Expression: ";
				cin >> instr;
				postr = s1.intopost(instr);
				cout << "\n Postfix Expression: " << postr << endl;
				break;
			case 6:
				cout << "\n Enter an Infix Expression: ";
				cin >> instr;
				postr = s1.intopost(instr);
				cout << "\n Postfix Expression: " << postr << endl;
				postval = s1.posteval(postr);
				cout << "\n Result of Postfix Evaluation: " << postval;
				break;
			case 7:
				cout << "\n Enter an Infix Expression: ";
				cin >> instr;
				prestr = s1.intopre(instr);
				cout << "\n Prefix Expression: " << prestr << endl;
				break;
			case 8:
				cout << "\n Enter an Infix Expression: ";
				cin >> instr;
				prestr = s1.intopre(instr);
				cout << "\n Prefix Expression: " << prestr << endl;
				preval = s1.preeval(prestr);
				cout << "\n Result of Prefix Evaluation: "<<  preval <<endl;
				break;
		}
		}while(ch!=10);
	return 0;
}








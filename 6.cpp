
#include<iostream>
#include<string>
#include<stack>
#include<queue>
using namespace std;

class node
{
public:
	string name;
	int DOBd, DOBm, DOBy, indegree, outdegree, processed;
	node *next;
	class friends *first;
};

class friends
{
public:
	string fname;
	int comments;
	friends *nextfriend;
	node *dest;
};

class facebook
{

public:
	node *first;
	int count = 0;
	stack<node *> s;
	queue<node *> q;

	facebook()
	{
		first = NULL;
	}
	void create();
	void insertuser(string);
	void insertfriend(string, string);
	void display();
	void maxfriends();
	void countbday(int);
	void minmaxcomments();
	void dfs();
	void bfs();
};


void facebook :: create()
{
	int comment;
	char ch;
	string username, user, friends;
	do
	{
	cout<< "\n Enter the user name:";
	cin >> username;
	insertuser(username);
	count ++;
	cout << "\n Do you want to insert new user?";
	cin >> ch;
	}while(ch == 'y' || ch == 'Y');
	do
	{
		cout << "\n Enter Friends relationship data: Enter user's and friends's name";
		cin >> user >> friends;
		insertfriend(user, friends);
		insertfriend(friends, user);
		cout << "\n Enter more edges:";
		cin >> ch;
	}while(ch == 'y' || ch == 'Y');


}

void facebook :: insertuser(string x)
{
	node *newuser, *p, *locptr;
	newuser = new node;
	newuser->next = NULL;
	newuser->name = x;
	cout << "\n Enter user's Birth date : Enter date, Month and year";
	cin >> newuser->DOBd >> newuser->DOBm >> newuser->DOBy;
	newuser->indegree = newuser->outdegree = 0;
	newuser-> processed = 0;
	newuser->first = NULL;
	if(first == NULL)
	{
		first = newuser;
	}
	else
	{
		p = NULL;
		locptr = first;
		while(locptr != NULL && x.compare(locptr->name)>0)
		{
			p = locptr;
			locptr = locptr->next;
		}
		if(p == NULL)
			first = newuser;
		else
		{
			p->next = newuser;
			newuser->next = locptr;
		}
	}
}

void facebook :: insertfriend(string user, string userf)
{
	friends *newfriend, *p ,*locptr;
	node *from, *to;

	newfriend = new friends;
	from = first;
	while(from != NULL && user.compare(from->name)>0)
	{
		from = from->next;
	}
	to = first;
	while(to != NULL && userf.compare(to->name)>0)
	{
		to = to->next;
	}
	from->outdegree = from->outdegree + 1;
	to->indegree = to->indegree + 1;
	newfriend->fname = to->name;
	newfriend->dest = to;

	cout << "Enter no. of comments posted by " << userf << " on " << user;
	cin >> newfriend->comments;

	if(from->first == NULL)
	{
		from->first = newfriend;
		newfriend->nextfriend = NULL;
	}
	else
	{
		p = NULL;
		locptr = from->first;
		while(locptr != NULL && newfriend->comments <= locptr->comments)
		{
			p = locptr;
			locptr= locptr->nextfriend;
		}
		if(p == NULL)
			from->first = newfriend;
		else
			p->nextfriend = newfriend;
		newfriend->nextfriend = locptr;
	}

}

void facebook :: display()
{
	node *sp = first;
	friends *sa;
	cout << "\n Displaying Facebook friend's network:";
	while(sp != NULL)
	{
		cout << "\n" << sp->name << "|" << sp->DOBd << "/" << sp->DOBm << "/" << sp->DOBy << "-> ";
		sa = sp->first;
		while(sa != NULL)
		{
			cout << sa->fname << "|"<< sa->comments << "-> ";
			sa = sa->nextfriend;
		}
		sp = sp->next;
	}
}

void facebook :: maxfriends()
{
	node *user = first;
	string fbuser;
	int max,maxfriends = 0;
	friends *next;
	while(user != NULL)
	{
		max = 0;
		next = user->first;
		if(next == NULL)
			max = 0;
		else
		{
			while(next != NULL)
			{
				max++;
				next = next->nextfriend;
			}
		}
		if(max > maxfriends)
		{
			maxfriends = max;
			fbuser = user->name;
		}
		user = user->next;
	}
	cout << "\n User with maximum friends(" << maxfriends <<") is -> " << fbuser;

}

void facebook :: countbday(int month)
{
	node *user;
	user = first;
	while(user != NULL)
	{
		if(user->DOBm == month)
			cout << "\n " << user->name << "|" << user->DOBd << "/" << user->DOBm << "/"  << user->DOBy;
		user = user->next;
	}
}

void facebook :: minmaxcomments()
{
	struct user
	{
		string uname;
		int c;
	}u[count];

	node *user, *loc;
	user = first;

	string maxuser, minuser;
	int i = 0, n, max = 0, min = 999;
	friends *next;
	do
	{
		u[i].uname = user->name;
		n = 0;
		loc = first;
		while(loc != NULL)
		{
			next = loc->first;
			while(next != NULL)
			{
				if(next->fname == u[i].uname)
				{
					n = n + next->comments;
				}
				next = next->nextfriend;
			}
			loc = loc->next;
		}
		u[i].c = n;
		i++;
		user = user->next;
	}while(i < count && user != NULL);

	cout << "\n Total no. of comments given by each user:";
	for(i=0;i<count;i++)
	{
		cout << "\n" << u[i].uname << "\t" << u[i].c;
	}

	for(i=0; i < count; i++)
	{
		if(u[i].c > max)
		{
			max = u[i].c;
			maxuser = u[i].uname;
		}
		if(u[i].c < min)
		{
			min = u[i].c;
			minuser = u[i].uname;
		}
	}
	cout << "\n user who has post maximum comments" << max << ":" << maxuser;
	cout << "\n user who has post minimum comments" << min << ":" << minuser;
}

void facebook :: dfs()
{
	node *user = first;
	node *fbuser, *to;
	friends *next;
	if(user == NULL)
		cout << "\n Nothing to display !!";
	while(user != NULL)
	{
		user->processed = 0;
		user = user->next;
	}

	user = first;
	while(user != NULL)
	{
		if(user->processed < 2)
		{
			if(user->processed < 1)
			{
				s.push(user);
				user->processed = 1;
			}
			while(!s.empty())
			{
				fbuser = s.top();
				s.pop();
				cout << fbuser->name;
				fbuser->processed = 2;
				next = fbuser->first;
				while(next != NULL)
				{
					to = next->dest;
					if(to->processed == 0)
					{
						s.push(to);
						to->processed = 1;
					}
					next = next->nextfriend;
				}
			}
		}
		user = user->next;
	}
}

void facebook :: bfs()
{
	node *user = first;
	node *fbuser, *to;
	friends *next;
	if(user == NULL)
		cout << "\n Nothing to display !!";
	while(user != NULL)
	{
		user->processed = 0;
		user = user->next;
	}

	user = first;
	while(user != NULL)
	{
		if(user->processed < 2)
		{
			if(user->processed < 1)
			{
				q.push(user);
				user->processed = 1;
			}
			while(!q.empty())
			{
				fbuser = q.front();
				q.pop();
				cout << fbuser->name;
				fbuser->processed = 2;
				next = fbuser->first;
				while(next != NULL)
				{
					to = next->dest;
					if(to->processed == 0)
					{
						q.push(to);
						to->processed = 1;
					}
					next = next->nextfriend;
				}
			}
		}
		user = user->next;
	}
}

int main()
{
	int ch, month;

	facebook fb;
	do
	{
		cout << "\n MENU \n 1.Insert user and friend's relationship \n 2. Display facebook friend's network \n 3. get the user with maximum friends";
		cout << "\n 4. Who has post minimum and maximum post \n 5. users having birthday in this month \n 6. DFS BFS Traversal \n 7. Exit \n Enter your choice:";
		cin >> ch;
		switch(ch)
		{
			case 1:
				fb.create();
				break;
			case 2:
				fb.display();
				break;
			case 3:
				fb.maxfriends();
				break;
			case 4:
				fb.minmaxcomments();
				break;
			case 5:
				cout << "\n Enter month to find birthdays in a month:";
				cin >> month;
				fb.countbday(month);
				break;
			case 6:
				cout << "\n DFS traversal:";
				fb.dfs();
				cout << "\n BFS Traversal:";
				fb.bfs();
				break;
		}
	}while(ch<=7);
}





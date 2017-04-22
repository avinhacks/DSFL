#include <iostream>
using namespace std;
#define MAX 20

typedef struct TreeNode
{
	    char data;
	    TreeNode *leftChild,  *rightChild;
}TreeNode;

typedef struct StackNode
{
	TreeNode *data;
	StackNode *next;
}StackNode;

class Tree
{
public :

	TreeNode *head;
    StackNode *stackTop;

    Tree()
    {
        head = NULL;
        stackTop = NULL;
    }

    // Stack Operations
    void push(TreeNode *);
    TreeNode* pop();
    int isEmpty();
    int isFull();

    // Validate input Postfix expression
    int validate(char[]);

    // Expression Tree Creation
    int isOp(char);
    int createTree(char[]);

    // Traversal with recursion
    void inOrder(TreeNode *);
    void preOrder(TreeNode *);
    void postOrder(TreeNode *);

    // Traversal without recursion
    void inOredeWO();
    void preOredeWO();
    void postOredeWO();
};

void Tree::push(TreeNode *data)
{
     if(stackTop == NULL)
     {
         stackTop = new StackNode;
         stackTop -> data = data;
         stackTop -> next = NULL;
     }
     else
     {
        StackNode *temp = new StackNode;
        temp -> data = data;
        temp -> next = stackTop;
        stackTop = temp;
    }
}

TreeNode* Tree :: pop()
{
	TreeNode *data;
	if(stackTop == NULL)
	{
		cout<<"\nCant delete stack underflow...";
	}
	else
	{
		data = stackTop -> data;
		stackTop = stackTop -> next;
	}
	return data;
}

int Tree::isOp(char ch)
{
    if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch== '$' || ch=='^')
        return 1;
    else
        return 0;
}

int Tree::createTree(char post[])
{
    int i=0;
    if(validate(post) == 1)
    {
		while(post[i]!='\0')
		{
			TreeNode *node = new TreeNode();
			node->data = post[i];
			if(isalnum(post[i]))		// character is alphbet or number
			{
				push(node);
			}
			else									//  character is operator
			{
				node->rightChild = pop();
				node->leftChild = pop();
				push(node);
			}
			i++;
		}
		head = pop();
	}
    else
    {
    	return 0;
    }
}

void Tree::inOrder(TreeNode *temp)
{
    if(temp!=NULL)
    {
        inOrder(temp->leftChild);
        cout<<"\t"<<temp->data;
        inOrder(temp->rightChild);
    }
}

void Tree::preOrder(TreeNode *temp)
{
    if(temp!=NULL)
    {
        cout<<"\t"<<temp->data;
        preOrder(temp->leftChild);
        preOrder(temp->rightChild);
    }
}

void Tree::postOrder(TreeNode *temp)
{
    if(temp!=NULL)
    {
        postOrder(temp->leftChild);
        postOrder(temp->rightChild);
        cout<<"\t"<<temp->data;
    }
}

void Tree::inOredeWO()
{
    stackTop = NULL;
    TreeNode *p = head;
    while(p!=NULL || stackTop != NULL)
    {
        while(p!=NULL)
        {
            push(p);
            p = p -> leftChild;
        }
        p = pop();
        cout<<"\t"<<p->data;
        p = p -> rightChild;
    }
}

void Tree::preOredeWO()
{
    stackTop = NULL;
    TreeNode *p = head;
    while(p!=NULL || stackTop != NULL)
    {
        while(p!=NULL)
        {
            cout<<"\t"<<p->data;
            push(p);
            p = p -> leftChild;
        }
        p = pop();
        p = p -> rightChild;
    }
}

void Tree::postOredeWO()
{
	int i=0;
	char str[50];
	TreeNode *p = head;
	while(stackTop!=NULL||p!=NULL)
	{
		while(p!=NULL)
		{
			str[i++]=p->data;
			push(p);
			p=p->rightChild;
		}
		p=pop();
		p=p->leftChild;
	}
	while(--i>=0)
	   cout<<"\t"<<str[i];
}
int Tree :: validate(char p[50])
{

	int i=0,cnt=0;
	while(p[i]!='\0')
	{
		if(isalpha(p[i]))
		{
			cnt++;
			i++;
		}
		else
		{
			cnt--;
			i++;
		}
	}
	if(cnt==1)
	return 1;
	else
	{
		if(cnt==0)
		cout<<"\nInvalid : Operators & Operands are EQUAL";
		cout<<"\n";

		if(cnt<0)
		cout<<"\nInvalid : Operators are MORE than Operands";
		cout<<"\n";

		if(cnt>0)
		cout<<"\nInvalid : Operands are MORE than Operators";
		cout<<"\n";

		return 0;
	}
}

int main() {

    int ch;
    char post[20];
    Tree T;

    cout<<"\nEnter postfix expression:";
    cin>>post;
    if(T.createTree(post))
    do
    {
        cout<<"\n1.Inorder \n2.Preorder \n3.Postorder \n4.Inorder Non Recursive \n5.Preorder Non Recursive \n6.Postorder Non Recursive \n7.Exit\n";
        cin>>ch;
        switch(ch) {

            case  1:
                T.inOrder(T.head);
                break;
            case  2:
                T.preOrder(T.head);
                break;
            case  3:
                T.postOrder(T.head);
                break;
            case 4:
                T.inOredeWO();
                break;
            case 5:
                T.preOredeWO();
                break;
            case 6:
                T.postOredeWO();
                break;
            case 7:
                goto exit;
            default :
                cout<<"\nWrong choice please try again...";
        }

    } while(1);

    exit:
    return 0;
}

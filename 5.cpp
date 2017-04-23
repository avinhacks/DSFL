#include <iostream>
using namespace std;

class BSTnode {

	public :
		int data;
		BSTnode *left, *right;

		BSTnode(int x) {
			data = x;
			left = right = NULL;
		}
};

class BST {

	public :

	BSTnode *root ;

	BST() {
		root = NULL;
	}

	void create();
	void insert(int x);
	void disp(BSTnode *p);
	void search(BSTnode *p, int x);
	BSTnode* deleteNode(BSTnode *p, int key);
	void minmax();
	void dispMirror(BSTnode *p);

};

void BST :: create() {
	int i, n, x;
	cout<<"\nEnter no. of BSTnodes to be inserted:\t";
	cin>>n;
	for(i=0;i<n;i++) {
		cout<<"\nEnter data";
		cin>>x;
		insert(x);
	}
}

void BST::insert(int x) {

	BSTnode *p, *q, *r;
	r = new BSTnode(x);

	if(root==NULL) {
		root = r;
	} else {
		p = root ;

		while(p!= NULL) {
			q = p;
			if(x > p->data) {
				p = p->right;
			} else {
				p = p -> left;
			}
		}

		if(x>q->data)
			q -> right = r;
		else
			q -> left = r;
	}
}

void BST::disp(BSTnode *p) {
	if(p!=NULL) {
		disp(p->left);
		cout<<"\t "<<p->data;
		disp(p->right);
	}
}

void BST::dispMirror(BSTnode *p) {
	if(p!=NULL) {
		dispMirror(p->right);
		cout<<"\t "<<p->data;
		dispMirror(p->left);
	}
}

void BST::search(BSTnode *p, int x) {

	if(p == NULL) {
		cout<<"\nNot found...\n";
	} else	if(p->data == x) {
		cout<<"\nFound ";
	} else if(x > p->data ) {
		search(p->right, x);
	} else {
		search(p->left, x);
	}

}
void BST::minmax(){
	BSTnode *p;
	p = root;
	if(p==NULL)
		cout<<"\nEmpty Tree...";
	while(p->left != NULL) {
		p = p->left;
	}
	cout<<"\nLowest element is : "<<p->data;

	p = root;
	while(p->right != NULL) {
		p = p->right;
	}
	cout<<"\nGreatest element is : "<<p->data;

}

BSTnode* BST::deleteNode(BSTnode *t, int x) {

    BSTnode *temp;
    if(t==NULL){
        cout<<"Cannot delete ,element not found ";
        return t;
    }
    if(x<t->data)
    {
    	t->left=deleteNode(t->left,x);
    	return t;
	}
	if(x>t->data)
	{
		t->right=deleteNode(t->right,x);
		return t;
	}

	if(t->left==NULL && t->right==NULL)
	{
		temp=t;
		delete temp;
		return NULL;
	}

	if(t->left==NULL)
	{
		temp=t;
		t=t->right;
		delete temp;
		return t;
	}
	if(t->right==NULL)
	{
		temp=t;
		t=t->left;
		delete temp;
		return t;
	}

	temp=t->right;
	while(temp->left!=NULL)
	temp=temp->left;
	t->data=temp->data;
	t->right=deleteNode(t->right,temp->data);
	return t;

}

int main() {

	int ch, x;
	BST B;

	do {
		cout<<"\n1. Create Tree\n2. Display\n3. Search for lowest and greatest\n4. Search an element\n5. Insert new BSTnode\n6. Display mirror image of Tree\n7. Delete a BSTnode from Tree\n8.Exit";
		cin>>ch;
		switch(ch) {
		case 1:
		 	B.create();
			break;
		case 2:
			B.disp(B.root);
			break;
		case 3:
			B.minmax();
			break;
		case 4:
			cout<<"\nEnter a value to search:\t";
			cin>>x;
			B.search(B.root, x);
			break;
		case 5:
			cout<<"\nEnter data to insert :\t";
			cin>>x;
			B.insert(x);
			break;
		case 6:
			B.dispMirror(B.root);
			break;
		case 7:
		int key;
			cout<<"\nEnter what to delete :";
			cin>>key;
			B.deleteNode(B.root, key);
			break;
		default:
			cout<<"\nWrong choice, please try again...";
		}
	} while(ch!=8);
	return  0;

}



#include"BST.h"
#include<iostream>
#include <cstring>
using namespace std;

Node::Node(){
	// cout<<"in const of node"<<endl;
	count = 0;
	key = NULL;
	leftnode = NULL;
	rightnode = NULL;
	parent = NULL;

}

BST::BST(){
	// cout<<"default cnst"<<endl;
	root = NULL;
	x_sq_sum = 0;
	x_sum = 0;
	// cout<<"const done"<<endl;
}

void BST::external(TraversalType_e tt,struct Node* node){
	// cout<<node->key<<" ";
	// cout<<"in external"<<endl;
}

void BST::left(TraversalType_e tt,struct Node* node){
	// if(tt == PRE_ORDER){cout<<node->key<<" ";}
}
void BST::below(TraversalType_e tt,struct Node* node){
	// cout<<"in below"<<endl;
	// cout<<tt<<endl;
	double x_i = (node->key[0]-'0')*10 + node->key[1] - '0';
	if(tt == IN_ORDER){x_sum += node->count * x_i; x_sq_sum += node->count * x_i * x_i;}; 
	// cout<<node->key;
	// cout<<endl;
}

void BST::right(TraversalType_e tt,struct Node* node){
	if(tt == POST_ORDER){cout<<node->key<<" ";}
}


void BST::traverse(TraversalType_e tt,struct Node* node){
	// cout<<"traversing"<<endl;
	// cout<<node->?
	if(node->leftnode==NULL && node->rightnode==NULL){
		// cout<<node->key<<endl;
		external(tt,node);
	}
	else{
		left(tt,node); 
		if(node->leftnode!=NULL){
			// cout<<"in left"<<endl;
			traverse(tt,node->leftnode->root);
		}
		below(tt,node);
		if(node->rightnode!=NULL){
			// cout<<"in right"<<endl;
			traverse(tt,node->rightnode->root);
		}
		right(tt,node);
	}
}


struct Node* BST::min(){
	if(this->root->leftnode!=NULL)return this->root->leftnode->min();
	return this->root;
}

struct Node* BST::max(){
	if(this->root->rightnode!=NULL)return this->root->rightnode->max();
	return this->root;	
}

struct Node* BST::search(char* s){
	// cout<<"searching "<<s<<endl;
	if(this->root==NULL){
		// cout<<"search k andar root null"<<endl;
		return NULL;
	}
	// cout<<"matching "<<s<<" with "<<this->root->key<<endl;
	// struct Node* x = new Node();
	// x = this->root;
	if(strcmp(s,this->root->key)==0){
		// cout<<"found "<<root->key<<endl;
		return this->root;
	}
	if(strcmp(s,this->root->key)<0){
		if(this->root->leftnode!=NULL)return this->root->leftnode->search(s);
		else return NULL;
	}
	else {
		if(this->root->rightnode!=NULL)return this->root->rightnode->search(s);
		else return NULL;	
	}

}

bool BST::insert(struct Node *n){
	// cout<<"inserting "<<n->key<<endl;
	if(this->root==NULL){
		// cout<<"insert k andar root null"<<endl;
		// BST* temp = new BST();
		// temp->root = n;
		root = new Node();
		// root = n;
		// this->root = new node
		int len=0;
		for (int i = 0; n->key[i]!='\0' ; ++i)
		{
			// cout<<n->key[i];
			len++;
		}
		// cout<<len<<endl;
		this->root->key = new char[len];
		this->root->count = 1;
		for (int i = 0; i < len; ++i)
		{
			this->root->key[i] = n->key[i];	
		}
		// cout<<"(in insert)inserted "<<this->root->key<<endl;
		this->root->height++;
		return true;
	}

	// cout<<"(insert)Current node has "<<this->root->key<<endl;
	if(this->search(n->key)!=NULL){
		// cout<<"already there"<<endl;
		this->root->count++;
		return false;
	}
	
	this->root->height++;
	if(strcmp(n->key,this->root->key)<0){
		// cout<<n->key<<" less than "<<this->root->key<<"\n";
		if(this->root->leftnode!=NULL)return this->root->leftnode->insert(n);
		else {
			BST* temp = new BST();
			//root = new Node();
			// root = n;
			// this->root = new node
			int len=0;
			for (int i = 0; n->key[i]!='\0' ; ++i)
			{	

				len++;
			}
			temp->root = new Node();
			temp->root->key = new char[len];
			temp->root->count = 1;
			for (int i = 0; i < len; ++i)
			{
				temp->root->key[i] = n->key[i];	
				// cout<<"coping "<<n->key[i];
			}
			temp->root->height = 1;
			temp->root->parent = this->root;
			this->root->leftnode = temp;
			return true;
		}
	}
	else {
		// cout<<n->key<<" greater than "<<this->root->key<<"\n";
		if(this->root->rightnode!=NULL)return this->root->rightnode->insert(n);
		else {
			BST* temp = new BST();
			// root = new Node();
			// root = n;
			// this->root = new node
			int len=0;
			for (int i = 0; n->key[i]!='\0' ; ++i)
			{	
				// cout<<n->key[i]<<endl;
				len++;
				// cout<<"hereeee"<<endl;
			}
			// cout<<n->key<<" "<<len<<endl;
			temp->root = new Node();
			temp->root->count = 1;
			temp->root->key = new char[len];
			// cout<<"here"<<endl;
			for (int i = 0; i < len; ++i)
			{
				temp->root->key[i] = n->key[i];	
			}
			// cout<<"here"<<endl;
			temp->root->height = 1;
			temp->root->parent = this->root;
			this->root->rightnode = temp;
			// cout<<"here"<<endl;
			return true;
		}
	}

}



struct Node* BST::successor(struct Node *n){
	struct Node*x,*y;
	x = new Node;
	y = new Node;
	n = search(n->key);
	if(n->rightnode!=NULL){
	return n->rightnode->min();
	}
	x = n;
	y = x->parent;
	if(y==NULL)return NULL;
	else {
		while(y!=NULL && y->rightnode->root==x){x=y;y=y->parent;}
		return y;
	}
}

struct Node* BST::predecessor(struct Node *n){
	struct Node*x,*y;
	n = search(n->key);
	if(n->leftnode!=NULL){
	return n->leftnode->max();
	}
	x = n;
	y = x->parent;
	if(y==NULL)return NULL;
	else {
		while(y!=NULL && y->leftnode->root==x){x=y;y=y->parent;}
		return y;
	}
}

bool BST::remove(char *s){
	if(this->search(s)==NULL)return false;
	struct Node *apna = search(s);
	if(apna->leftnode==NULL && apna->rightnode==NULL){
		if(apna->parent->leftnode->root==apna)apna->parent->leftnode=NULL;
		else apna->parent->rightnode=NULL;
		return true;
	}
	if(apna->leftnode!=NULL){
		if(apna->parent->leftnode->root==apna)apna->parent->leftnode = apna->leftnode;
		else apna->parent->rightnode = apna->rightnode;
	}
	this->successor(apna)->leftnode = apna->leftnode;
	return true;
}

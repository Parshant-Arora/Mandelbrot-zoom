#include<iostream>
#include<bits/stdc++.h>
#include <fstream>
#include"BST.cpp"
using namespace std;
using namespace std::chrono;
ofstream file("insertion.txt");                /* Choose file appropriately*/


char *int2charstar (int v) { //Convert int to char* label
 char *s = new char[sizeof(int)];
 sprintf(s,"%d",v);
 return s;
};


std::vector<int> v(10010,0);

void input(int num){
	int n = num;
	BST T;
	auto tick = high_resolution_clock::now();	 //time starts
	while(num--){
		srand(time(0));
		int temp = rand()%1000000;
		Node* input = new Node();
		
		input->key = int2charstar(temp);//&c;
		T.insert(input);
		
	}
	auto tock = high_resolution_clock::now(); //time stops
	auto time = duration_cast<microseconds>(tock-tick);
	v[n]+=time.count();
}


int main(){
	int num = 2000;
	// for (int i = 0; i < 5; ++i)
	// {
	// 	for (int i = 1; i <= num; ++i)
	// 	{	
	// 	//cout<<i<<endl;
	// 	input(i);
	// 	}
	// }
	// for (int i = 1; i <2000; ++i)
	// {
	// 	file<<i<<" "<<v[i]/5<<"\n";
	// }
	BST T;
	int times = 3,temp;
	srand(time(0));
	while(times--){

		temp = rand()%10;
		cout<<"Inserting "<<temp<<"\n";
		Node* input = new Node();
		input->key = int2charstar(temp);//&c;
		T.insert(input);
		cout<<"Inserted "<<temp<<"\n";
	}
	int n;
	cout<<"How many numbers you want to search: ";
	cin>>n;
	cout<<"Enter the number to search: ";
	while(n--){
		cin>>temp; 	
		if(T.search(int2charstar(temp))!=NULL)cout<<"Yes its there\n";
		else cout<<"Not here\n";
	}
	cout<<"Inorder traversal\n";
	TraversalType_e order = IN_ORDER;
	T.traverse(order,T.root);
	cout<<"\nEnter Number , whose successor you want: ";
	cin>>temp;
	Node* input = new Node();
	input->key = int2charstar(temp);//&c;
	if(T.successor(input)!=NULL){
		cout<<"Its successor is:"<<T.successor(input)->key<<"\n";
	}
	else "Not found\n";

	cout<<"\nEnter Number , whose predecessor you want: ";
	cin>>temp;
	input = new Node();
	input->key = int2charstar(temp);//&c;
	if(T.predecessor(input)!=NULL){
		cout<<"Its predecessor is:"<<T.predecessor(input)->key<<"\n";
	}
	else "Not found\n";
	cout<<"\nEnter Number , which you want to remove";
	cin>>temp;
	if(T.remove(int2charstar(temp)))cout<<"Removed \n";
	else "Not here\n";
	cout<<"Inorder traversal\n";
	order = IN_ORDER;
	T.traverse(order,T.root);
	// cout<<"Root "<<T.root->key<<endl;
	// cout<<"left "<<T.->leftnode->key<<endl;

	
	// cout<<endl;

}
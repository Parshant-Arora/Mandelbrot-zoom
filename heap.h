#include<bits/stdc++.h>
// #ifndef HEAP_H
// #define HEAP_H

#include"packet.h"
using namespace std;
#define MAX_SIZE (1<<21)



class Packet;

class Heap {
    class Packet *arr;
    int l;
    int swaps;
    public:
    Heap();
    // Heap(int);
    void insert(class Packet elem);
    Packet delete_min_and_return();
    void delete_min();
    void heapify(int node);
    void print(int,int);
    void reset_swaps(){swaps=0;}
    int getSwaps(){return swaps;}
    Packet top();
    void push(Packet);
    void pop();
    int size();
    int top_num();
};

Packet Heap::top(){
    return arr[0];
} 
void Heap::pop(){
    delete_min();
}

int Heap::top_num(){
    int cnt=0;
    for (int i = 0; i < l; i++)
    {
        if(arr[i].entropy==arr[0].entropy)cnt++;
    }
    return cnt;
}

Heap::Heap(){
    arr = new Packet[MAX_SIZE];
    l = 0;
    swaps=0;
}


int Heap::size(){
    return l;
}

void Heap::push(Packet e){
    insert(e);
}

void Heap::insert(Packet elem){
    // cout<<"inserting "<<elem<<endl;
    
    arr[l] = elem; //put at last
    int p = (l+1)/2-1, ch = l; //initialize parent and child
    while(p>=0){ //traverse to the top
        if(arr[p].entropy<arr[ch].entropy){  
            Packet temp = arr[p];
            arr[p] = arr[ch];
            arr[ch] = temp;
            swaps++;
            ch = p;
            p = (p-1)/2;
        }
        else break;
    }
    l++; //update length
}

void Heap::delete_min(){
    if(l==0){
        cout<<"Nothing to delete\n";
    }
    Packet temp = arr[0]; //swap it with last elem
    arr[0] = arr[l-1];
    arr[l-1] = temp;
    swaps++;
    l--; //decrease length
    heapify(0);
}

Packet Heap::delete_min_and_return(){
    Packet temp = arr[0]; //swap it with last elem
    arr[0] = arr[l-1];
    arr[l-1] = temp;
    swaps++;
    l--; //decrease length
    heapify(0);
    return temp;
}

void Heap::heapify(int node){
    int p = node;
    int ch1 = 2*node+1, ch2 = 2*node+2;
    if(ch1>=l)return;
    if(ch1==l-1){
        if(arr[ch1].entropy>arr[p].entropy){
            Packet temp = arr[p];
            arr[p] = arr[ch1];
            arr[ch1] = temp;
            swaps++;
            heapify(ch1);
        }
        else return;
    }
    else {
        int max_index;
        if(max(arr[ch1].entropy,arr[ch2].entropy)==arr[ch1].entropy)max_index=ch1;
        else max_index=ch2;
        Packet temp = arr[max_index];
        if(temp.entropy>arr[p].entropy){
            arr[max_index]=arr[p];
            arr[p] = temp;
            swaps++;
            heapify(max_index);
        }
        else return;
    }
}

// #endif
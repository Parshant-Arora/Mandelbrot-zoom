#include<bits/stdc++.h>
#include"heap.h"
#include <chrono>
using namespace std;
using namespace std::chrono;
int main(){
    srand(time(0));
    Heap* h = new Heap();

    for (int i = 0; i < 5; i++)
    {   
        int temp = rand()%100;
        cout<<"\nInsert "<<temp<<"\n";
        h->insert(temp);
        h->print(1,0);
    }
    cout<<"\n";
    for (int i = 0; i < 5; i++)
    {
        cout<<"Deleted "<<h->delete_min_and_return()<<"\n";
        h->print(1,0);
        cout<<"\n";
    }


    // int M = 1e6;
    // ofstream file_time("time.txt");                /* Choose file appropriately*/
    // ofstream file_swaps("swaps.txt");                /* Choose file appropriately*/
    // for (int N = 1000; N <= M ; N*=10){
    //     cout<<N<<endl;
    //     delete h;
    //     h = new Heap();
    //     double insert_time = 0,del_time = 0;
    //     int insert_num =0, del_num = 0;
    //     int insert_swaps=0, del_swaps=0;
        
    //     for (int j = 0; j < N; j++) {
            
    //         auto tick = high_resolution_clock::now();	 //time starts    
    //         h->insert(rand()%1000000);	 
    //         auto tock = high_resolution_clock::now(); //time stops
    //         auto time = duration_cast<nanoseconds>(tock-tick);
    //         insert_time += time.count();    
    //         insert_num++;
    //         insert_swaps+=h->getSwaps();
    //         h->reset_swaps();
    //     }
        

    //     // insert_swaps+=h->getSwaps();
    //     // h->reset_swaps();
    //     for (int j = 0; j < N/5; j++) {
            
    //         if(rand()%2){
    //             auto tick = high_resolution_clock::now();	 //time starts
    //             h->delete_min();	 
    //             auto tock = high_resolution_clock::now(); //time stops
    //             auto time = duration_cast<nanoseconds>(tock-tick);
    //             del_time += time.count();
    //             // cout<<"Adding in deltime "<<time.count()<<"\n";
    //             del_num++;
    //             del_swaps+=h->getSwaps();
    //             h->reset_swaps();
    //         }
    //         else {
    //             auto tick = high_resolution_clock::now();	 //time starts
    //             h->insert(rand()%1000000);	 
    //             auto tock = high_resolution_clock::now(); //time stops
    //             auto time = duration_cast<nanoseconds>(tock-tick);
    //             insert_time += time.count();
    //             insert_num++;
    //             insert_swaps+=h->getSwaps();
    //             h->reset_swaps();
    //         }
    //     }
    //     // file<<"N= "<<N<<endl<<" total insert_time="<<insert_time<<"                total del_time="<<del_time*1.0<<endl;
    //     file_time<<insert_time*1.0/insert_num/1000<<" "<<del_time*1.0/del_num/1000<<endl;
    //     file_swaps<<insert_swaps*1.0/insert_num<<" "<<del_swaps*1.0/del_num<<endl;
    //     // file<<"  insert swaps="<<insert_swaps<<"                    del swaps="<<del_swaps<<endl;
    //     // file<<"  insert num="<<insert_num<<"                    del num="<<del_num<<endl;

    // }//end of loop over N
    // // h->print(1,0);

}
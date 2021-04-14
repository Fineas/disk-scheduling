#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <thread>
#include <time.h>
#include "schedule.h"
#include "algo_sstf.h"
#include "algo_fcfs.h"
#include "algo_scan.h"
#include "algo_cscan.h"
#include "algo_clook.h"
#include "algo_look.h"

std :: vector<int> initial_queue;
std :: vector<int> extra_queue;
int new_que_len = 0;
int start = 0;
int newd_flg[] = {0,0,0,0,0,0};

// === Print queue === 
void debugQueue(std :: vector<int> queue){
    for (std :: vector<int> :: iterator it = initial_queue.begin(); it != initial_queue.end(); ++it){
        std :: cout << *it << ' ';
    }
    std :: cout << '\n';
}

//  === Read New Queue === 
void read_data(std::string file_name){
    std :: ifstream data_in;
    data_in.open(file_name.c_str());
    int tmp = 0;

    // Read data into queue
    data_in >> start;
    extra_queue.push_back(start);
    for(int i = 0; !data_in.eof(); i++) {
        data_in >> tmp;
        extra_queue.push_back(tmp);
    }

    new_que_len = extra_queue.size();
    
    for (std :: vector<int>::iterator it = extra_queue.begin(); it != extra_queue.end(); ++it) {
        initial_queue.push_back(*it);
        memset(newd_flg,1,6*sizeof(int));
        while(newd_flg[0] != 0 ||
              newd_flg[1] != 0 ||
              newd_flg[2] != 0 ||
              newd_flg[3] != 0 ||
              newd_flg[4] != 0 ||
              newd_flg[5] != 0){
            continue;
        }
        std::cout<<"A fost citit nr "<<*it<<" , citesc urmatorul\n";
        initial_queue.clear();
    }
    
    new_que_len = 0;
    extra_queue.clear();
    data_in.close();
}

//  === Main Execution Flow === 
int main(int argc, char** argv){
    std :: cout << "[*] Disk Scheduling Simulator" << std :: endl;

    int tmp;
    bool flag = true;
    int has_read[] = {0,0,0,0,0,0};
    int sk, r, rw, blk, start; sk = r = rw = blk = start = 0;
    std :: thread* schedule_threads[6];


    // Read Scheduler Params
    std :: ifstream fin;
    fin.open("data1.in");
    fin >> sk;
    fin >> r;
    fin >> rw;
    fin >> blk;
    fin >> start;
    fin.close();

    // Create Instances of Sch Algorithms
    std :: vector<ScheduleAlgoritm *> algorithms;
    algorithms.push_back(new Fcfs(sk, r, rw, blk, start, initial_queue, flag, newd_flg[0], new_que_len));
    algorithms.push_back(new Sstf(sk, r, rw, blk, start, initial_queue, flag, newd_flg[1], new_que_len));
    algorithms.push_back(new Scan(sk, r, rw, blk, start, initial_queue, flag, newd_flg[2], new_que_len));
    algorithms.push_back(new Cscan(sk, r, rw, blk, start, initial_queue, flag, newd_flg[3], new_que_len));
    algorithms.push_back(new Look(sk, r, rw, blk, start, initial_queue, flag, newd_flg[4], new_que_len));
    algorithms.push_back(new Clook(sk, r, rw, blk, start, initial_queue, flag, newd_flg[5], new_que_len));

    // Create Threads
    for (int i = 0; i < 6; ++i) {
        schedule_threads[i] = new std :: thread(std::ref(*algorithms[i]));
    }

    // READ FIRST QUEUE
    std::cout<<"Citim set1 \n";
    read_data("data2.in");
    new_que_len = 0;
    usleep(100000);

    // READ SECOND QUEUE
    std::cout<<"Citim set2 \n";
    read_data("data3.in");
    new_que_len = 0;
    usleep(1000000);

    // STOP THREADS
    flag = false;

    // Join Threds
    for (auto& th : schedule_threads) th->join();


    return 0;
}
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <thread>
#include <time.h>
#include "algo_sstf.h"
#include "algo_fcfs.h"

std :: vector<int> initial_queue;
std :: vector<int> extra_queue;

// === Print queue === 
void debugQueue(std :: vector<int> queue){
    for (std :: vector<int> :: iterator it = initial_queue.begin(); it != initial_queue.end(); ++it){
        std :: cout << *it << ' ';
    }
    std :: cout << '\n';
}

//  === Main Execution Flow === 
int main(int argc, char** argv){
    std :: cout << "[*] Disk Scheduling Simulator" << std :: endl;

    int tmp;
    bool flag = true;
    int sk, r, rw, blk, start; sk = r = rw = blk = start = 0;
    std :: thread schedule_threads[6];


    // Read Scheduler Params
    std :: ifstream fin;
    fin.open("data1.in");
    fin >> sk;
    fin >> r;
    fin >> rw;
    fin >> blk;
    fin >> start;

    // Create Instances of Sch Algorithms
    std :: vector<ScheduleAlgoritm> toatie;
    // toatie.push_back(Fcfs(sk, r, rw, blk, start, initial_queue, flag));
    toatie.push_back(Sstf(sk, r, rw, blk, start, initial_queue, flag));

    // Create Threads
    for (int i = 0; i < 1; ++i) {
        schedule_threads[i] = std :: thread(toatie[i]);
    }

    std :: cout << "[*] Threads Started" << std :: endl;

    // Read Initial queue
    for(int i = 0; fin; i++) {
        fin >> tmp;
        initial_queue.push_back(tmp);
    }

    std :: cout << "[*] First Queue" << std :: endl;

    // Experimental Extra data
    initial_queue.clear();
    // // usleep(500000);
    // initial_queue.push_back(1337);
    // initial_queue.push_back(1336);
    // initial_queue.push_back(1338);
    // initial_queue.push_back(1335);
    // initial_queue.push_back(1339);
    // initial_queue.push_back(1334);
    // std :: cout << "[*] Second Queue" << std :: endl;
    // usleep(500000);
    // initial_queue.clear();

    flag = false;

    // Join Threds
    for (auto& th : schedule_threads) th.join();

    return 0;
}
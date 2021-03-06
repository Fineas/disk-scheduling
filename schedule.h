#pragma once

#include <mutex>
#include <vector>
#include <iostream>
#include <fstream>
#include <condition_variable>


class ScheduleAlgoritm {

    public:

        void operator()() {
            this -> run();
        }


        virtual void run() = 0;


        ScheduleAlgoritm(int sk, int r, int rw, int blk, int start, std::vector<int> &queue_data, bool &flag, int &newd, int &newd_len) : queue_data{queue_data}, status{flag}, newd{newd}, newd_len{newd_len} {
            /*
                Constructor
            */
            this -> seek = sk;
            this -> rotation = r;
            this -> read_write = rw;
            this -> blocks = blk;
            this -> head = start;
            this -> cost_count = 0;
            this -> direction = 0;
        }


        ~ScheduleAlgoritm() {
            /*
                Deconstructor
            */
            this -> queue.clear();
            this -> fout.close();
        };


        ScheduleAlgoritm(const ScheduleAlgoritm& obj) : queue_data{obj.queue_data}, status{obj.status}, newd{obj.newd}, newd_len{obj.newd_len} {
            /*
                Copy Constructor
            */
            this -> seek = obj.seek;
            this -> rotation = obj.rotation;
            this -> read_write = obj.read_write;
            this -> blocks = obj.blocks;
            this -> head = obj.head;
            this -> cost_count = obj.cost_count;
            this -> queue = obj.queue;
            this -> queue_data = obj.queue_data;
            this -> direction = obj.direction;
            this -> file_name = obj.file_name;
            this -> fout.open(this->file_name);
            this -> alg_name = obj.alg_name;
        }


        void setQueue() { 
            /* 
                Routine to update the Queue
            */
            if(this->newd){
                this->fout << "[*] ====== Reading new data in Queue\n";
                int count = 0;
                while(count != this->newd_len && this->newd_len != 0){
                    // this->fout << "Sunt aiiici " << count << " " << this->newd_len << "\n";
                    if(this->newd){
                        this->fout << "New element available, total= " << this->newd_len << "\n";
                        this->queue.insert(this->queue.end(), this->queue_data.begin(), this->queue_data.end());
                        this->writeToFile(this->strQueue());
                        this->newd = 0;
                        count++;
                    }
                }
                count = 0;
            }
        }


        void displayQueue(){ 
            /* 
                Routine to print the current Queue
            */
            std :: cout << "Queue = [ ";
            for (std :: vector<int>::iterator it = this -> queue.begin(); it != this -> queue.end(); ++it) {
                std :: cout << *it << ", ";
            }
            std :: cout << "]" << std :: endl;
        }


        void displayTrace(){
            /* 
                Routine to print the final Trace
            */
            std :: cout << "Trace = [ ";
            for (std :: vector<int>::iterator it = this -> trace.begin(); it != this -> trace.end(); ++it) {
                std :: cout << *it << ", ";
            }
            std :: cout << "]" << std :: endl;            
        }


        void formatOutputToFile() {
            /* 
                Write final output to file
            */
            try{

                std :: string border = "======================================";
                this->fout << border << std :: endl;
            
                this->fout << "Schedule = [ ";
                for (std :: vector<int>::iterator it = this -> trace.begin(); it != this -> trace.end(); ++it) {
                    this->fout << *it << ", ";
                }

                this->fout << "]" << std :: endl << std :: endl;  
                this->fout << "Total Cost = " << this -> cost_count << std :: endl << std :: endl;

            }
            catch (const std::exception &exc){
                std::cerr << exc.what();
            }

        }


        std::string strQueue(){
            /* 
                Return a string representation of the current queue
            */            
            std::string ret = "";
            ret.append("Queue = [ ");
            for (std :: vector<int>::iterator it = this -> queue.begin(); it != this -> queue.end(); ++it) {
                ret.append(std::to_string(*it));
                ret.append(", ");
            }
            ret.append("]\n");
            return ret;
        }


        void writeToFile(std::string data) {
            /* 
                Write String to file
            */
            this->fout << data << std :: endl;
        }

    private:

        std :: vector<int> &queue_data;  // Incoming data to be added to the Queue
           
    protected:

        bool &status;              // Scheduler running (1) not running (0)
        int &newd;                 // New queue flag
        int &newd_len;             // New queue len
        int seek;                  // Cost of seeking from i to i+1
        int rotation;              // Cost of switching direction (L -> R) or (R -> L)
        int read_write;            // Cost of performing Read or Write
        int blocks;                // Total Number of blocks
        int head;                  // Current Position
        int cost_count;            // Total Cost of the schedule
        int direction;             // Moving to left (1) moving to right (2) starting point (0)
        std :: string alg_name;    // Name of the scheduling algorithm
        std :: string file_name;   // Name of the output file
        // std :: mutex mtx;
        std :: vector<int> queue;  // Work Queue
        std :: vector<int> trace;  // Store the order
        std :: ofstream fout;

};
#include <mutex>
#include <vector>
#include <iostream>
#include <condition_variable>

#pragma

class ScheduleAlgoritm {

    public:

        void operator()() {
            this -> run();
        }

        virtual int run() {
            /*
                Virtual Routine to perform the scheduling algorithm
            */
            return 0;
        }

        ScheduleAlgoritm(int sk, int r, int rw, int blk, int start, std::vector<int> &queue_data, bool &flag) : queue_data{queue_data}, status{flag} {
            /*
                Constructor
            */
            std :: cout << "Constructor" << std :: endl;
            this -> seek = sk;
            this -> rotation = r;
            this -> read_write = rw;
            this -> blocks = blk;
            this -> head = start;
            this -> status = flag;
            this -> cost_count = 0;
            this -> direction = 0;
        }

        ~ScheduleAlgoritm() {
            /*
                Deconstructor
            */
            this -> queue.clear();
        };

        ScheduleAlgoritm(const ScheduleAlgoritm& obj) : queue_data{obj.queue_data}, status{obj.status} {
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
        }

        void setQueue() { 
            /* 
                Routine to update the Queue
            */
            this -> queue.insert(this->queue.end(), this->queue_data.begin(), this->queue_data.end());
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

    private:

        std :: vector<int> &queue_data;  // Incoming data to be added to the Queue
           
    protected:

        bool &status;              // Scheduler running (1) not running (0)
        int seek;                  // Cost of seeking from i to i+1
        int rotation;              // Cost of switching direction (L -> R) or (R -> L)
        int read_write;            // Cost of performing Read or Write
        int blocks;                // Total Number of blocks
        int head;                  // Current Position
        int cost_count;            // Total Cost of the schedule
        int direction;             // Moving to left (1) moving to right (2) starting point (0)
        std :: string alg_name;    // Name of the scheduling algorithm
        std :: mutex mtx;
        std :: vector<int> queue;  // Work Queue
        std :: vector<int> trace;  // Store the order

};
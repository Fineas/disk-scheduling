#include <mutex>
#include <unistd.h>
#include "schedule.h"

class Fcfs : public virtual ScheduleAlgoritm {

    public:

        void run() {

            std::cout<<"Running inside "<<this->alg_name<<std::endl;
            //this->displayQueue();

            if(this->queue.size() != 0){
                this -> trace.push_back(this->head);
            }

            while(this -> status) {
                
                int current_track = 0;
                int distance = 0;

                this->setQueue();

                while(!this->queue.empty()) {
                    this->setQueue();

                    std :: vector<int>::iterator it = this -> queue.begin(); 
                    current_track = *it;
                    distance = abs(current_track - this->head);

                    this -> cost_count += distance * this->seek;
                    this -> cost_count += this->read_write;

                    // check if direction is changed
                    if(this->direction != 0) {
                        if(this->direction == 1 && this->head < current_track) {
                            this -> cost_count += rotation;
                            this->direction = 2;
                        }
                        if(this->direction == 2 && this->head > current_track) {
                            this -> cost_count += rotation;
                            this->direction = 1;
                        }
                    }
                    else{ // set direction according to the first move direction
                        if(this->head < current_track) {
                            this->direction = 2;
                        }
                        else{
                            this->direction = 1;
                        }
                    }

                    this -> head = current_track; // update head
                    this -> trace.push_back(current_track); // update trace
                    this -> queue.erase(this->queue.begin()); // remove the already served process

                    usleep(100000);
                }
            }
            //this->displayTrace();
            this->formatOutputToFile();
            
        }

        Fcfs(int sk, int r, int rw, int blk, int start, std::vector<int> &queue_data, bool &flag, int &newd, int &newd_len) : ScheduleAlgoritm(sk, r, rw, blk, start, queue_data, flag, newd, newd_len) {
            this -> alg_name = "First Come First Serve (FCFS)";
            this -> file_name = "output/fcfs_output.txt";
            this -> fout.open(this -> file_name);
        }
                

    private:

    protected:
        

};
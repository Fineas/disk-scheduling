#include <mutex>
#include <unistd.h>
#include <algorithm>
#include "schedule.h"

class Sstf : public ScheduleAlgoritm {

    public:

        void run() {

            std::cout<<"Running inside "<<this->alg_name<<std::endl;
            std :: string border = "======================================";
            this->fout << border << std :: endl;
            this->fout << this -> alg_name << std :: endl;
            this->fout << border << std :: endl;

            if(this->queue.size() != 0){
                this -> trace.push_back(this->head);
            }

            while(this -> status) {

                this->setQueue();
                int current_track = 0;
                int distance = 0;

                if(this->queue.size() >= 1){
                    this->fout << "Current Cost: [ "<<this->cost_count<<"];\n";
                    
                    int que_idx = this->getMinDiff(this->head); // get the closest elemnt
                    current_track = this->queue[que_idx];
                    distance = abs(current_track - this->head);

                    this->fout << "Current Head at: [ "<<this->head<<"];\n";
                    this->fout << "Next block to be scheduled: [ "<<current_track<<"], distance= "<<distance<<";\n";

                    this -> cost_count += distance * this->seek;
                    this -> cost_count += this->read_write;

                    // check if direction is changed
                    if(this->direction != 0) {
                        if(this->direction == 1 && this->head < current_track) {
                            this -> cost_count += rotation;

                            this->fout << "Changing Direction to Right;\n";
                            this->direction = 2;
                        }
                        if(this->direction == 2 && this->head > current_track) {
                            this -> cost_count += rotation;

                            this->fout << "Changing Direction to Left;\n";
                            this->direction = 1;
                        }
                    }
                    else{ // set direction according to the first move direction
                        if(this->head < current_track) {
                            this->fout << "Changing Direction to Right;\n";
                            this->direction = 2;
                        }
                        else{
                            this->fout << "Changing Direction to Left;\n";
                            this->direction = 1;
                        }
                    }

                    this -> head = current_track; // update head
                    this -> trace.push_back(current_track); // update trace
                    this -> queue.erase(std::remove(this->queue.begin(), this->queue.end(), this->queue[que_idx]), this->queue.end()); // remove the already served process

                    usleep(100000);
                }

            }

            this->formatOutputToFile();
        }

        Sstf(int sk, int r, int rw, int blk, int start, std::vector<int> &queue_data, bool &flag, int &newd, int &newd_len) : ScheduleAlgoritm(sk, r, rw, blk, start, queue_data, flag, newd, newd_len) {
            
            this -> trace.push_back(this->head);
            this -> alg_name = "Shortest Seek Time First (SSTF)";
            this -> file_name = "output/sstf_output.txt";
            this -> fout.open(this -> file_name);

        }
    

    private:

        int getMinDiff(int head) {
                unsigned int diff = 0xffffffff;
                int queue_idx = 0, counter = 0;
                for (std :: vector<int>::iterator it = this->queue.begin(); it != this->queue.end(); ++it) {
                    if(abs(head - *it) < diff){
                        diff = abs(head - *it);
                        queue_idx = counter;
                    }
                    counter++;
                }
                return queue_idx;
            }

    protected:
        

};
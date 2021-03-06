#include <mutex>
#include <unistd.h>
#include <algorithm>
#include "schedule.h"

class Cscan : public ScheduleAlgoritm {

    public:

        void run() { // go right

            std::cout<<"Running inside "<<this->alg_name<<std::endl;
            std :: string border = "======================================";
            this->fout << border << std :: endl;
            this->fout << this -> alg_name << std :: endl;
            this->fout << border << std :: endl;

            this->direction = 2;
            this->setQueue();

            if(this->queue.size() != 0){
                this -> trace.push_back(this->head);
            }

            while(this -> status) {
                
                this->setQueue();
                int current_track = 0;
                int distance = 0;

                if(this->queue.size() >= 1){
                    this->fout << "Current Cost: [ "<<this->cost_count<<"];\n";

                    // determin next move position
                    if(this->head != this->blocks && this->direction == 2) { // go to next left elem
                        current_track =  nextLarger(this->head);
                    }
                    else if(this->direction == 2 && this->head == this->blocks) { // reached the last right elem
                        current_track =  0;
                    }
                    else if(this->head != this->blocks && this->direction ==1 ) {
                        current_track =  nextLarger(this->head);
                    }
                    
                    distance = abs(current_track - this->head);

                    this->fout << "Current Head at: [ "<<this->head<<"];\n";
                    this->fout << "Next block to be scheduled: [ "<<current_track<<"], distance= "<<distance<<";\n";

                    this -> cost_count += distance * this->seek;
                    this -> cost_count += this->read_write;

                    // check if direction is changed
                    if(this->head < current_track) {
                        this->fout << "Changing Direction to Right;\n";
                        this->direction = 2;
                        this -> cost_count += rotation;
                    }
                    else{
                        this->fout << "Changing Direction to Left;\n";
                        this->direction = 1;
                        this -> cost_count += rotation;
                    }

                    this -> head = current_track; // update head
                    this -> trace.push_back(current_track); // update trace
                    if(this->head != 0 || this->head != this->blocks)    
                        this -> queue.erase(std::remove(this->queue.begin(), this->queue.end(), current_track), this->queue.end()); // remove the already served process
                    usleep(100000);
                }

            }

            this->formatOutputToFile();
        }

        Cscan(int sk, int r, int rw, int blk, int start, std::vector<int> &queue_data, bool &flag, int &newd, int&newd_len) : ScheduleAlgoritm(sk, r, rw, blk, start, queue_data, flag, newd, newd_len) {
            
            this -> trace.push_back(this->head);
            this -> alg_name = "Cscan (Circular Elevator)";
            this -> file_name = "output/cscan_output.txt";
            this -> fout.open(this -> file_name);

        }


    private:

        int nextLarger(int head) {
            int high = this->blocks; 
            // locate value
            for(int it : this->queue) {
                if(it < high && it > head) {
                    high = it;
                }
            }
            if(high != this->blocks)
                return *(std :: find(this->queue.begin(), this->queue.end(), high)); // return index
            else
                return high;
        }

    protected:
        

};
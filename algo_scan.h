#include <mutex>
#include <unistd.h>
#include <algorithm>
#include "schedule.h"

class Scan : public ScheduleAlgoritm {

    public:

        void run() { // go left first

            std::cout<<"Running inside "<<this->alg_name<<std::endl;

            this->direction = 1;
            //this->displayQueue();

            if(this->queue.size() != 0){
                this -> trace.push_back(this->head);
            }

            while(this -> status) {
                
                this->setQueue();
                int current_track = 0;
                int distance = 0;

                if(this->queue.size() >= 1){
                    
                    //this->displayQueue();

                    // determin next move position
                    if(this->head != 0 && this->direction == 1) { // go to next left elem
                        current_track =  nextSmaller(this->head);
                    }
                    else if(this->direction == 1 && this->head == 0) { // reached the last left elem
                        current_track =  nextLarger(this->head);
                    }
                    else if(this->head != this->blocks && this->direction == 2) { // go to next right elem
                        current_track =  nextLarger(this->head);
                    }
                    else if(this->direction == 2 && this->head == this->blocks) { // reached the last right elem
                        current_track =  nextSmaller(this->head);
                    }
                    
                    distance = abs(current_track - this->head);

                    this -> cost_count += distance * this->seek;
                    this -> cost_count += this->read_write;

                    // check if direction is changed
                    if(this->head < current_track) {
                        this->direction = 2;
                    }
                    else{
                        this->direction = 1;
                    }

                    this -> head = current_track; // update head
                    this -> trace.push_back(current_track); // update trace
                    if(this->head != 0 || this->head != this->blocks)    
                        this -> queue.erase(std::remove(this->queue.begin(), this->queue.end(), current_track), this->queue.end()); // remove the already served process
                    usleep(100000);
                }

            }
            //this->displayTrace();
            this->formatOutputToFile();
        }

        Scan(int sk, int r, int rw, int blk, int start, std::vector<int> &queue_data, bool &flag, int &newd, int &newd_len) : ScheduleAlgoritm(sk, r, rw, blk, start, queue_data, flag, newd, newd_len) {
            this -> alg_name = "SCAN (Elevator)";
            this -> file_name = "output/scan_output.txt";
            this -> fout.open(this -> file_name);
        }

        
                

    private:

        int nextSmaller(int head) {
            int low = 0; 
            // locate value
            for(int it : this->queue) {
                if(it > low && it < head) {
                    low = it;
                }
            }
            if (low != 0)
                return *(std :: find(this->queue.begin(), this->queue.end(), low)); // return index
            else
                return low;
        }

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
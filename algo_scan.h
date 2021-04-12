#include <mutex>
#include <unistd.h>
#include <algorithm>
#include "schedule.h"

class Scan : public virtual ScheduleAlgoritm {

    public:

        int run() {

            this->setQueue();
            while(this -> status) {
                
                int current_track = 0;
                int distance = 0;

                if(this->queue.size() >= 1){
                    int que_idx = this->getMinDiff(this->head); // get the closest elemnt
                    current_track = this->queue[que_idx];
                    distance = abs(current_track - this->head);

                    this -> cost_count += distance * this->seek;
                    this -> cost_count += this->read_write;

                    // check if direction is changed
                    if(this->direction != 0) {
                        if(this->direction == 1 && this->head < current_track) {
                            this -> cost_count += rotation;
                        }
                        if(this->direction == 2 && this->head > current_track) {
                            this -> cost_count += rotation;
                        }
                    }

                    this -> head = current_track; // update head
                    this -> trace.push_back(current_track); // update trace
                    this -> queue.erase(std::remove(this->queue.begin(), this->queue.end(), this->queue[que_idx]), this->queue.end()); // remove the already served process

                    usleep(100000);
                }

            }
            this->displayTrace();
            return this -> cost_count;
        }

        Scan(int sk, int r, int rw, int blk, int start, std::vector<int> &queue_data, bool &flag) : ScheduleAlgoritm(sk, r, rw, blk, start, queue_data, flag) {
            this -> alg_name = " SCAN (Elevator)";
        }

        
                

    private:

        int getMinDiff(int head) {
                unsigned int diff = 0xffffffff;
                int queue_idx = 0;
                for (std :: vector<int>::iterator it = this->queue.begin(); it != this->queue.end(); ++it) {
                    if(diff < abs(head - *it)){
                        diff = abs(head = *it);
                    }
                    queue_idx++;
                }
                return queue_idx;
            }

    protected:
        

};
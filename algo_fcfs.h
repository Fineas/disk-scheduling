#include <mutex>
#include <unistd.h>
#include "schedule.h"

class Fcfs : public virtual ScheduleAlgoritm {

    public:

        int run() {


            this->setQueue();
            while(this -> status) {
                
                int current_track = 0;
                int distance = 0;

                while(!this->queue.empty()) {
                    this -> displayQueue();

                    std :: vector<int>::iterator it = this -> queue.begin(); 
                    current_track = *it;
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
                    this -> queue.erase(this->queue.begin()); // remove the already served process

                    usleep(100000);
                }
            }
            this->displayTrace();
            return this -> cost_count;
        }

        Fcfs(int sk, int r, int rw, int blk, int start, std::vector<int> &queue_data, bool &flag) : ScheduleAlgoritm(sk, r, rw, blk, start, queue_data, flag) {
            this -> alg_name = "First Come First Serve (FCFS)";
        }
                

    private:

    protected:
        

};
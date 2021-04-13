#include <mutex>
#include <unistd.h>
#include <algorithm>
#include "schedule.h"

class Look : public ScheduleAlgoritm {

    public:

        void run() { // go right

            std::cout<<"Running inside "<<this->alg_name<<std::endl;

            this->direction = 2;
            //this->displayQueue();

            if(this->queue.size() != 0){
                this -> trace.push_back(this->head);
            }

            while(this -> status) {

                this->setQueue();
                int current_track = 0;
                int distance = 0;

                

                if(this->queue.size() >= 1){
                    
                    int que_max = *std::max_element(this->queue.begin(), this->queue.end());
                    int que_min = *std::min_element(this->queue.begin(), this->queue.end());
                    // look over blocks from head to end
                    for(int i = this->head; i <= que_max; i++){
                        // check if block is in queue
                        if ( std :: count(this->queue.begin(), this->queue.end(), i)) { 
                            //this->displayQueue();
                            current_track =  i;
                            this -> cost_count += this->read_write;
                            this -> trace.push_back(current_track); // update trace
                            this -> queue.erase(std::remove(this->queue.begin(), this->queue.end(), current_track), this->queue.end()); // remove the already served process
                        }

                        // update head and increment cost
                        this -> cost_count += this->seek;
                        this -> head = i;
                    }

                    // move all the way to block 0
                    this->direction = 1;
                    this -> cost_count += this->rotation;
                    this -> cost_count += this->seek * this->head;

                    usleep(100000);

                    // look over blocks from head to end
                    for(int i = this->head; i >= que_min; i--){
                        // check if block is in queue
                        if ( std :: count(this->queue.begin(), this->queue.end(), i)) { 
                            //this->displayQueue();
                            current_track =  i;
                            this -> cost_count += this->read_write;
                            this -> trace.push_back(current_track); // update trace
                            this -> queue.erase(std::remove(this->queue.begin(), this->queue.end(), current_track), this->queue.end()); // remove the already served process
                        }

                        // update head and increment cost
                        this -> cost_count += this->seek;
                        this -> head = i;
                    }

                    // move all the way to block 0
                    this->direction = 2;
                    this -> cost_count += this->rotation;
                    this -> cost_count += this->seek * this->head;

                    usleep(100000);
                }
            }
            //this->displayTrace();
            this->formatOutputToFile();
        }

        Look(int sk, int r, int rw, int blk, int start, std::vector<int> &queue_data, bool &flag, int &newd) : ScheduleAlgoritm(sk, r, rw, blk, start, queue_data, flag, newd) {
            this -> alg_name = "Look";
            this -> file_name = "output/look_output.txt";
            this -> fout.open(this -> file_name);
        }
      

    private:

    protected:
        

};
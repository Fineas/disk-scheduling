#include <mutex>
#include <unistd.h>
#include <algorithm>
#include <fstream>
#include "schedule.h"

class Clook : public ScheduleAlgoritm {

    public:

        void run() { // go right

            std::cout<<"Running inside "<<this->alg_name<<std::endl;

            this->direction = 2;
            this->setQueue();
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
                    this -> head = que_min;

                    usleep(100000);
                }

            }
            //this->displayTrace();
            this->formatOutputToFile();
        }

        Clook(int sk, int r, int rw, int blk, int start, std::vector<int> &queue_data, bool &flag, int &newd) : ScheduleAlgoritm(sk, r, rw, blk, start, queue_data, flag, newd) {
            this -> alg_name = "Clook (Circular LOOK)";
            this -> file_name = "output/clook_output.txt";
            this -> fout.open(this -> file_name);
        }

        
                

    private:

    protected:
        

};
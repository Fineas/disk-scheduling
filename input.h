#include <iostream>

class Input {

    public:

        static Input& getInstance() {
            static Input input;
            return input;
        }
        void set_input();
        void get_input();        

    private:
        
        Input() {}
        Input(Input const&);
        void operator=(Input const&);
        int *queue;
        FILE* f;

    public:
        
        Input(Input const&) = delete;
        void operator=(Input const&) = delete;

};
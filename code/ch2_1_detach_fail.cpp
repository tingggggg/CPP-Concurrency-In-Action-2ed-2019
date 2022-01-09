#include <thread>
#include <iostream>

void do_something(int &i) {
    ++i;
}

struct func {
    int &i;

    func(int &i_) : i(i_) {}

    void operator()() {
        for (int j = 0; j < 1000000; ++j) {
            do_something(i);
        }
    }
};

void oops() {
    int local_state = 1;
    func my_func(local_state);
    std::thread my_thread(my_func);
    my_thread.detach();
}

int main() {

    oops();

    return 0;
}
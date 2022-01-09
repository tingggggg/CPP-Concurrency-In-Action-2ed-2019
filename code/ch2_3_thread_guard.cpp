#include <thread>
#include <iostream>

class thread_guard
{
private:
    std::thread &t;
public:
    explicit thread_guard(std::thread &t_) : t(t_){}
    ~thread_guard() {
        if (t.joinable())
            t.join();
    }

    thread_guard (thread_guard const&) = delete;
    thread_guard& operator=(thread_guard const&) = delete;
};

void do_something(int &i) {
    ++i;
}

struct func
{
    int i;

    func(int &i_) : i(i_){}

    void operator()() {
        for (int j = 0; j < 500000; ++j) {
            do_something(i);
        }
    }
};

void do_something_in_current_thread()
{}

void f() {
    int local_state_status = 5;

    struct func my_func(local_state_status);

    std::thread t(my_func);
    thread_guard tg(t);

    do_something_in_current_thread();
}

int main() {
    f();
}
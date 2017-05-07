#include<iostream>
#include<thread>

// why ordinay function doesnt work at thread_safe?
struct func 
{
    int &i;
    func(int &i_): i(i_) {}
    void operator() () {
        std::cout << i << std::endl;
    }
};

class thread_safe
{
    std::thread& t;

    public:
    explicit thread_safe(std::thread& t_) : t(t_) {}

    ~thread_safe()
    {
        if ( t.joinable() )
            t.join();
    }
    thread_safe(thread_safe const&)=delete;
    thread_safe& operator= (thread_safe const&)=delete;
} ;

int main(void)
{
    int i = 1;
    func f(i);
    std::thread t(f);
    thread_safe s(t);
}



#include<iostream>
#include<thread>

struct func
{
    int &i;
    func(int& i_): i(i_) {}
    void operator() ()
    {
        std::cout << i << std::endl;
    }
};

int main(void)
{
    int i = 1;
    func f(i);
    std::thread t(f);
    t.detatch();
    return 0;
}

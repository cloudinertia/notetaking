#include <iostream>
#include <thread>

using namespace std;

void kernel(void)
{
    cout << "Hello,Cocurrnet!\n";
}

int main(void)
{
    thread t(kernel);
    t.join();
    return 0;
}

// Examples about Thread local
// cpp+20 
#include <iostream>
#include <thread>
#include <mutex>


std::mutex mtx;

void func(int id ,int& thread_alternative) {
  
    int x = 0;
    static int y = 0;
    thread_local int z = 0;

    ++x;
    ++z;
    std::lock_guard guard(mtx);
    ++y;
    thread_alternative=1+thread_alternative;
    std::cout << "Thread id: " << id << " TA (automatic storage) =" << thread_alternative << "\n";
    std::cout << "Thread id: " << id << " x (automatic storage) =" << x <<"\n";
    std::cout << "Thread id: " << id << " y (automatic storage) =" << y <<"\n";
    std::cout << "Thread id: " << id << " z (automatic storage) =" << z <<"\n------------------------------------------------------------------------\n";
                                                                        

}

void foo(int id)
{   
    int thread_alternative = 0;
    func(id,thread_alternative);
    func(id,thread_alternative);
    func(id,thread_alternative);

}
int main()
{
    std::thread threads[3];

    for (int i = 0; auto & thread: threads)
    {
        thread = std::thread(foo, i++);

    }
    for (int i = 0; auto & thread: threads)
    {
        thread.join();
    }

    std::cout << "Hello World!\n";
}


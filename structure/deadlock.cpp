#include <iostream>
#include <thread>
#include <mutex>

void work1(std::mutex& mylock1, std::mutex& mylock2) {
    for (int i = 0; i < 100000; i++) {
        mylock1.lock();
        mylock2.lock();
        std::cout << "work1 : " << i << std::endl;
        mylock2.unlock();
        mylock1.unlock();
    }
}

void work2(std::mutex& mylock1, std::mutex& mylock2) {
    for (int i = 0; i < 100000; i++) {
        //想解锁，就把锁的顺序调换过来
        mylock2.lock();
        mylock1.lock();
        std::cout << "work2 : " << i << std::endl;
        mylock1.unlock();
        mylock2.unlock();
    }
}

int main()
{
    //A，B互相争夺资源的死锁
    std::mutex mylock1, mylock2;
    int ans = 0;
    std::thread t1(work1, std::ref(mylock1), std::ref(mylock2));
    std::thread t2(work2, std::ref(mylock1), std::ref(mylock2));
    t1.join();
    t2.join();
    return 0;
}
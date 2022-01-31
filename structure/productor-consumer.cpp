#include <iostream>
#include <mutex>
#include <stdio.h>
#include <queue>
#include <Thread>
using namespace std;

template<class T>
class Queue
{
public:
    void put(T val){
        // lock_guard<mutex> lock(mtx);
        unique_lock<mutex> lck(mtx);
        while(!que.empty()) {
            // que不为空，生产者应该通知消费之去消费，
            // 使用条件变量，当不为空，就将锁释放掉，
            cv.wait(lck);
        }
        que.push(val);
        cv.notify_all(); // 通知所有的消费线程去消费
        // cv.notify_one(); // 通知一个线程
        // 其他线程得到该通知，就从等待状态，编程
        // 阻塞状态，然后在获取互斥锁继续执行。
    }

    int get(){
        T val = 0;
        {
            unique_lock<mutex> lck(mtx);
            while (que.empty())
            {
                // 通知生产者生产，
                // 进入等待状态，释放互斥锁

                cv.wait(lck);
            }
            val = que.front();
            que.pop();
            cv.notify_all(); // 通知消费线程，我消费完了，赶紧生产吧
        }
        return val;
    }

    const int MAX_PRODUCER = 10;
private:
    queue<T> que;
    mutex mtx; // 全局的锁,互斥线程访问队列
    condition_variable cv; // 定义全局的条件变量，同步线程
};

void producer(Queue<int> *que){
    for (int i = 1; i <= que->MAX_PRODUCER; ++i){
        que->put(i);
        cout << this_thread::get_id() << "生产 : " << i << "商品" << endl;
        //printf("%d 生产：%d商品\n",this_thread::get_id(), i);
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

void consumer(Queue<int> *que) {
    for (int i = 0; i < que->MAX_PRODUCER; ++i) {
        int data = que->get();
        cout << this_thread::get_id() << "消费 : " << data << "商品" << endl;
        //printf("%d 消费：%d商品\n",this_thread::get_id(), data);
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

int main() {
    Queue<int> que;
    thread t1(producer,&que);
    thread t2(consumer,&que);

    t1.join();
    t2.join();

    return 0;
}
//单生产者-多消费者模型
//Queue<int> que;
//int main()
//{
//    thread t1(producer, &que);
//    list<thread> lst;
//    for (int i = 0; i < 3; ++i)
//        lst.push_back(thread(consumer, &que));
//
//    t1.join();
//    for (auto &it : lst) // 注意这里只能使用引用&it，因为thread是没有左值的提供拷贝构造和赋值
//        it.join();
//
//    return 0;
//}
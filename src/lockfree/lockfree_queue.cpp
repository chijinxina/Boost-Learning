//
// Created by chijinxin on 18-8-23.
//
#include <iostream>
#include <atomic>
//boost无锁队列
#include <boost/lockfree/queue.hpp>
#include <boost/thread/thread.hpp>

using namespace std;


const int producer_thread_count = 4;    //生产线程数
const int consumer_thread_count = 2;    //消费线程数


atomic_long p_count(0);  //生产者数量
atomic_long c_count(0);  //消费者数量
atomic_bool done(false); //是否生产完毕标志

boost::lockfree::queue<int> queue(512);  //无锁队列

const long iterations = 10;    //迭代次数

void producer(void)
{
    for(int i=0; i < iterations; ++i)
    {
        //原子计数---多线程不存在计数不上的情况
        int value = ++p_count;
        cout<<"+"<<endl;   //观察生产类型： 纯生产还是同时有消费者的情况
        while(!queue.push(value));
    }
}

void consumer(void)
{
    int value;
    //当没有生产完毕，则边消费边生产
    while(!done)
    {
        while(queue.pop(value))
        {
            cout<<"-"<<endl;
            ++c_count;
        }
    }
    //如果生产完毕则消费
    while(queue.pop(value))
    {
        ++c_count;
    }
}


int main()
{

    cout << "boost::lockfree::queue is ";
    if (!queue.is_lock_free())
        cout << "not ";
    cout << "lockfree" << endl;
    //boost::thread 线程群管理器
    boost::thread_group producer_group, consumer_group;
    //创建生产者
    for(int i=0; i<producer_thread_count; i++)
    {
        producer_group.create_thread(producer);
    }
    //创建消费者
    for(int i=0; i<consumer_thread_count; i++)
    {
        consumer_group.create_thread(consumer);
    }

    //等待生产者生产完毕
    producer_group.join_all();

    done = true;
    cout<<"done"<<endl;

    //等待消费者消费结束
    consumer_group.join_all();

    //输出生产和消费数量
    cout<<endl;
    cout << "produced " << p_count << " objects." << endl;
    cout << "consumed " << c_count << " objects." << endl;

    return 0;
}
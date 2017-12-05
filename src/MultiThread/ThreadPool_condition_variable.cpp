//
// Created by chijinxin on 17-12-5.
//
#include <iostream>
#include <queue>
#include <boost/threadpool.hpp>
#include <boost/pool/pool.hpp>
#include <boost/thread/thread.hpp>
#include <boost/make_shared.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/mutex.hpp>

using namespace std;
using namespace boost::threadpool;


boost

/*
 * Boost多线程——条件变量 和 线程池 的结合应用
 */
class ProCon{   //  生产者-消费者模型 with 线程池
public:
    ProCon(int N)
    {
        Capacity_ = N;  //队列容量
        std::cout<<"调用ProCon构造函数！"<<std::endl;
        ProducerThread = boost::make_shared<boost::thread>(boost::bind(&ProCon::Producer,this));
        ConsumerThread = boost::make_shared<boost::thread>(boost::bind(&ProCon::Consumer,this));
    }
    ProCon(int N,int P,int C)
    {
        Capacity_ = N;  //队列容量
        std::cout<<"调用ProCon构造函数！"<<std::endl;
        for(int i=0;i<P;i++){
            ProducerThread = boost::make_shared<boost::thread>(boost::bind(&ProCon::Producer,this));
        }

        ConsumerThread = boost::make_shared<boost::thread>(boost::bind(&ProCon::Consumer,this));
    }
    ~ProCon(){std::cout<<"调用ProCon析构函数！"<<std::endl;}

    void start()
    {
        std::cout<<"ProCon系统启动！"<<std::endl;
    }


protected:
    std::queue<int> production; //“商品”
    int Capacity_;  //“商品”队列容量



    void Producer()
    {
        std::cout<<"生产者初始化成功！"<<std::endl;

        while(1)
        {
            {
                boost::mutex::scoped_lock lock(Middle_mu);

                std::cout<<"生产者准备好数据！"<<std::endl;
            }
            Middle_cv.notify_one();
            boost::this_thread::sleep(boost::posix_time::seconds(1));
        }
    }
    void Consumer()
    {
        std::cout<<"消费者初始化成功！"<<std::endl;
        while(1)
        {
            boost::mutex::scoped_lock lock(Middle_mu);
            Middle_cv.wait(lock);
            std::cout<<"Consumer打印Middle_var="<<Middle_var<<std::endl;
        }
    }
};


int main(){
    ProCon procon(10);
    procon.start();
    return 0;
}
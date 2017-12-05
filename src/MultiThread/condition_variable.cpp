//
// Created by chijinxin on 17-12-2.
//
#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/make_shared.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/mutex.hpp>


class ProCon{
public:
    ProCon(int var)
    {
        Middle_var=var;
        std::cout<<"调用ProCon构造函数！"<<std::endl;
        ProducerThread1 = boost::make_shared<boost::thread>(boost::bind(&ProCon::Producer,this,1));
        ProducerThread2 = boost::make_shared<boost::thread>(boost::bind(&ProCon::Producer,this,2));
        ConsumerThread = boost::make_shared<boost::thread>(boost::bind(&ProCon::Consumer,this));
    }
    ~ProCon(){std::cout<<"调用ProCon析构函数！"<<std::endl;}

    void start()
    {
        ProducerThread1->join();
        ProducerThread2->join();
        ConsumerThread->join();
        std::cout<<"ProCon系统启动！"<<std::endl;
    }


protected:
    boost::mutex Middle_mu;
    boost::condition_variable Middle_cv;
    boost::shared_ptr<boost::thread> ProducerThread1;
    boost::shared_ptr<boost::thread> ProducerThread2;
    boost::shared_ptr<boost::thread> ConsumerThread;
    int Middle_var;

    void Producer(int Num)
    {
        std::cout<<"生产者"<<Num<<"初始化成功！"<<std::endl;

        while(1)
        {
            {
                boost::mutex::scoped_lock lock(Middle_mu);
                Middle_var++;
                std::cout<<"生产者"<<Num<<"准备好数据！"<<std::endl;
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
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
        ProducerThread = boost::make_shared<boost::thread>(boost::bind(&ProCon::Producer,this));
        ConsumerThread = boost::make_shared<boost::thread>(boost::bind(&ProCon::Consumer,this));
    }
    ~ProCon(){std::cout<<"调用ProCon析构函数！"<<std::endl;}

    void start()
    {
        ProducerThread->join();
        ConsumerThread->join();
        std::cout<<"ProCon系统启动！"<<std::endl;
    }


protected:
    boost::mutex Middle_mu;
    boost::condition_variable Middle_cv;
    boost::shared_ptr<boost::thread> ProducerThread;
    boost::shared_ptr<boost::thread> ConsumerThread;
    int Middle_var;

    void Producer()
    {
        std::cout<<"生产者初始化成功！"<<std::endl;

        while(1)
        {
            {
                boost::mutex::scoped_lock lock(Middle_mu);
                Middle_var++;
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
//
// Created by chijinxin on 17-12-2.
//

#include <iostream>
#include <boost/make_shared.hpp>  //boost shared_ptr 工厂类
#include <boost/function/function0.hpp> //boost function
#include <boost/thread/thread.hpp> //boost thread

class demo{
public:
    demo(int i)
    {
        Sub_i = i;
        Sub1Thread = boost::make_shared<boost::thread>(boost::bind(&demo::Sub1,this)); //创建Sub1Thread线程
        Sub2Thread = boost::make_shared<boost::thread>(boost::bind(&demo::Sub2,this)); //创建Sub2Thread线程
        Sub1Thread->join(); //Sub1Thread线程开始运行
        Sub2Thread->join(); //Sub2Thread线程开始运行
    }

    void Sub1()  //子线程1
    {
        std::cout<<"Sub1线程初始化成功！"<<std::endl;
        while(1){
            //boost::mutex::scoped_lock lock(Subi_mu);
            try {
                Subi_mu.lock();
                Sub_i=Sub_i+1;
                std::cout<<"Sub1线程计算Sub_i="<<Sub_i<<std::endl;
                Subi_mu.unlock();
            }catch(...){
                Subi_mu.unlock();
            }
            usleep(1000000);
        }
    }

    void Sub2()//子线程1
    {
        //int Sub_i=0;
        std::cout<<"Sub2线程初始化成功！"<<std::endl;
        while(1){
            //boost::mutex::scoped_lock lock(Subi_mu);
            try {
                Subi_mu.lock();
                Sub_i=Sub_i+1;
                std::cout<<"Sub2线程计算Sub_i="<<Sub_i<<std::endl;
                Subi_mu.unlock();
            }catch(...){
                Subi_mu.unlock();
            }
            usleep(1000000);
        }
    }
protected:
    int Sub_i;
    boost::mutex Subi_mu;
    boost::shared_ptr<boost::thread> Sub1Thread;
    boost::shared_ptr<boost::thread> Sub2Thread;
};

int main(){
    demo d(10);

    return 0;
}
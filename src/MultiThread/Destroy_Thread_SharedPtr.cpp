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
        //Sub1Thread->join(); //Sub1Thread线程开始运行 （阻塞主线程！）
        //Sub2Thread->join(); //Sub2Thread线程开始运行 （阻塞主线程！）
        //Sub1Thread->detach(); //Sub1Thread线程开始运行 （不阻塞主线程！即主线程与子线程分离）
        //Sub2Thread->detach(); //Sub2Thread线程开始运行 （不阻塞主线程！即主线程与子线程分离）
    }

    ~demo()
    {
    }

    void Sub1()  //子线程函数1
    {
        std::cout<<"Sub1线程初始化成功！"<<std::endl;
        try
        {
            /** 手动在线程中加入中断点，中断点不影响其他语句执行 */
            boost::this_thread::interruption_point();

            while(1)
            {
                {
                    boost::mutex::scoped_lock lock(Subi_mu);
                    Sub_i=Sub_i+1;
                    //std::cout<<"Sub1线程计算Sub_i="<<Sub_i<<std::endl;
                }
                boost::this_thread::sleep(boost::posix_time::seconds(1));
            }
        }
        catch (...)
        {
            std::cout << "Interrupt exception was thrown." << std::endl;
        }
        /** 通过该语句可以判断线程先退出还是Destroy函数先退出 */
        std::cout << "Leave Thread. Function ID="<<1<< std::endl;
    }

    void Sub2()//子线程函数2
    {
        std::cout<<"Sub2线程初始化成功！"<<std::endl;
        try
        {
            /** 手动在线程中加入中断点，中断点不影响其他语句执行 */
            boost::this_thread::interruption_point();
            while(1)
            {
                {
                    boost::mutex::scoped_lock lock(Subi_mu);
                    Sub_i=Sub_i-1;
                    //std::cout<<"Sub2线程计算Sub_i="<<Sub_i<<std::endl;
                }
                boost::this_thread::sleep(boost::posix_time::seconds(1));
            }
        }
        catch (...)
        {
            std::cout << "Interrupt exception was thrown." << std::endl;
        }
        /** 通过该语句可以判断线程先退出还是Destroy函数先退出 */
        std::cout << "Leave Thread. Function ID="<<2<< std::endl;
    }


    void Destroy(boost::shared_ptr<boost::thread> AThread)
    {
        std::cout << "Interrupt thread with ID: " << AThread->get_id() << std::endl;

        /** 向线程发送中断请求 */
        AThread->interrupt();
        std::cout << "Joining thread..." << std::endl;

        /** join函数，作用是等待直到线程执行结束；可不加，但不能保证退出Destroy函数前线程被终结 */
        AThread->join();
        /** 通过该语句可以判断线程先退出还是Destroy函数先退出 */
        std::cout << "Leave Destroy Function." << std::endl;
    }


    boost::shared_ptr<boost::thread> Sub1Thread;
    boost::shared_ptr<boost::thread> Sub2Thread;
protected:
    int Sub_i;
    boost::mutex Subi_mu;
};




int main(){
    demo d(10);
    int event=0;
    while(std::cin>>event)
    {
        std::cout<<"Sub1Thread ID="<<d.Sub1Thread->get_id()<<std::endl;
        std::cout<<"Sub2Thread ID="<<d.Sub2Thread->get_id()<<std::endl;
        if(event==1)
        {
            d.Destroy(d.Sub1Thread);
            event=0;
        }
        else if(event==2)
        {
            d.Destroy(d.Sub2Thread);
            event=0;
        }
    }
    return 0;
}
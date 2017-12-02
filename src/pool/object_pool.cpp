#include <iostream>
#include <string>
#include <boost/pool/object_pool.hpp>

using namespace boost;

class demo{
public:
    int a,b,c;
    demo(int x=1,int y=2,int z=3):a(x),b(y),c(z){
        std::cout<<"调用demo构造函数！"<<std::endl;
    };
    ~demo(){
        std::cout<<"调用demo析构函数！"<<std::endl;
    }
};

int main(int argc,char **argv){
    object_pool<demo> pl;//对象内存池
    demo *p  = pl.malloc();//分配一个原始内存块
    assert(pl.is_from(p));

    //p指向的内存没有初始化
    std::cout<<"p->a:"<<p->a<<" p->b:"<<p->b<<" p->c:"<<p->c<<std::endl;

    demo *pp = pl.construct(7,8,9);//构造一个对象，可以传递参数
    std::cout<<"pp->a:"<<pp->a<<" pp->b:"<<pp->b<<" pp->c:"<<pp->c<<std::endl;

    pl.destroy(pp);


    object_pool<std::string> pls;
    for(int i=0;i<10;i++){
        std::stringstream temp;
        temp<<"hello object No:"<<i<<std::endl;
        //std::cout<<temp.str()<<std::endl;
        std::string *ps = pls.construct(temp.str());
        std::cout<<*ps;
    }

    return 0;
}

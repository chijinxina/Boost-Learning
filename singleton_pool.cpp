#include <iostream>
#include <boost/pool/singleton_pool.hpp>
using namespace boost;
using namespace std;

class pool_tag{
};

typedef singleton_pool<pool_tag,sizeof(int)> spl;   //内存池定义

int main(){
    int *p = (int *) spl::malloc();
    assert(spl::is_from(p));
    spl::release_memory(); //释放所有未分配的内存
    return 0;
}
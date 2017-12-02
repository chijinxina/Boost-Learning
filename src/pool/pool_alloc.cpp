#include <iostream>
#include <vector>
#include <boost/pool/pool_alloc.hpp>
using namespace std;
using namespace boost;


int main(){
    vector<int,pool_allocator<int>> v;  //使用pool_allocator代替标准容器默认的内存分配器
    v.push_back(10);
    cout<<v.size()<<endl;
    return 0;
}
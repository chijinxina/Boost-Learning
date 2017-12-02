#include <iostream>
#include <string>
#include <boost/smart_ptr.hpp>
#include <boost/pool/pool.hpp>

using namespace boost;



int main(){

    pool<> pl(sizeof(int));
    std::cout<<"get_requested_size: "<<pl.get_requested_size()<<std::endl;
   // assert(sizeof(int)==pl.get_requested_size());
    int *p = (int *)pl.malloc();
    assert(pl.is_from(p));
    pl.free(p);
    for (int i = 0; i < 100; ++i) {
        int *temp = (int *)pl.ordered_malloc(10);
        assert(pl.is_from(temp));
        //std::cout<<"remaining memory: "<<pl.<<std::endl;
    }
    int *t = new int(1);
    std::cout<<pl.is_from(t)<<std::endl;
    return 0;
}
//
// Created by chijinxin on 18-6-20.
//
#include <iostream>
#include <boost/coroutine2/all.hpp>
#include <boost/coroutine2/detail/push_coroutine.hpp>
#include <boost/coroutine2/detail/pull_coroutine.hpp>
using namespace std;

void foo(boost::coroutines2::coroutine<string>::pull_type &sink)
{
    std::cout << "a: "<<sink.get()<<endl;
    sink();
    std::cout << "b: "<<sink.get()<<endl;
    sink();
    std::cout << "c: "<<sink.get()<<endl;
}


/*
 * 使用协程迭代器
 */
void chi(boost::coroutines2::coroutine<int>::pull_type &sink)
{
    using coIter = boost::coroutines2::coroutine<int>::pull_type::iterator; //协程迭代器
    for(coIter start = begin(sink); start != end(sink); ++start)
    {
        std::cout << "retrieve "<<*start << "\n";
    }
}


int main()
{
//    std::string str1("HELLO");
//    std::string str2("WORLD");
//
//    boost::coroutines2::coroutine<string>::push_type source(foo);
//
//    std::cout << "1 "<<endl;
//    source(str1);
//    std::cout << "2 "<<endl;
//    source(str2);
//    std::cout << "3 "<<endl;
//    source(str1);

    /*
     * 协程迭代器
     */
    boost::coroutines2::coroutine<int>::push_type source(chi);

    for (int i = 0; i < 10000000; i++) {
        source(i);
    }

    getchar();
    return 0;
}

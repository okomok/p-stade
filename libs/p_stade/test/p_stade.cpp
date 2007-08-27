
#include <iostream>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <boost/progress.hpp>

int main()
{
    {
        boost::progress_timer t;
        for (int i = 0; i < 100000; ++i)
            new std::stringstream();
    }

    {
        boost::progress_timer t;
        for (int i = 0; i < 100000; ++i)
            boost::lexical_cast<std::string>(123456789);
    }

#if 0
    int i = 123456789;
    std::stringstream io;

    io << 123456789;

    char ch1;
    io >> ch1;

    char ch2;
    io >> ch2;

    char ch3;
    io >> ch3;

    std::cout << ch1 << std::endl;
    std::cout << ch2 << std::endl;
    std::cout << ch3 << std::endl;
#endif
}

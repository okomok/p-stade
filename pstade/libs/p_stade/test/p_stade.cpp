

#include <pstade/vodka/drink.hpp>

#include <boost/bind.hpp>


int foo(int x, int y)
{
    return x;
}

int bar(int x)
{
    return x;
}

int main()
{

    int j = 999;
    //boost::bind(&foo, 998, _1)(j);
    boost::bind(&bar, boost::bind(&bar, _1))(j);
}

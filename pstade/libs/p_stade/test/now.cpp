/*
#include <memory> // auto_ptr
#include <boost/interprocess/smart_ptr/unique_ptr_emulation.hpp>

using namespace boost;

std::auto_ptr<int> make_auto_ptr()
{
    // ok.
    return std::auto_ptr<int>(new int(10));
}

boost_ext::unique_ptr<int> make_unique_ptr1()
{
    boost_ext::unique_ptr<int> up(new int(10));
    // return up; // error
    return boost_ext::move(up);
}

boost_ext::unique_ptr<int> make_unique_ptr2()
{
    return boost_ext::unique_ptr<int>(new int(10));
}

int main()
{
    std::auto_ptr<int> ap1(new int(1));
    std::auto_ptr<int> ap2(ap1);

    boost_ext::unique_ptr<int> up1(new int(1));
    // boost_ext::unique_ptr<int> up2(up1); // error
    boost_ext::unique_ptr<int> up3(boost_ext::move(up1));
}
*/

#include "x.hpp"



X foo1()
{
    return X();
}

X foo2()
{
    X x;
    return x; // error
}


int main()
{
    X x1;
    X const cx1;

    X x2(x1);  // error
    X x3(cx1); // error

    X x4(boost::move(x1));
    X x5(boost::move(cx1));
}

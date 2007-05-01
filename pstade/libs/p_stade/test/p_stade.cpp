

#include <boost/optional.hpp>

#include <pstade/nonassignable.hpp>
#include <boost/noncopyable.hpp>


template<class X>
struct dummy_assignable
{
    X& operator=(X const&)
    {
        BOOST_ASSER(false);
        return *this;
    }

    X m_x;
}

struct my :
    pstade::nonassignable

int main()
{
    hello<my>::say();
    hello<std::string>::say();
    hello<int>::say();
}





// Deprecated code. Doesn't care of this.


#include <pstade/unit_test.hpp>
#include <boost/optional.hpp>
#include <string>


struct D
{
    virtual void bar() = 0;
    char data[5000];
};

struct E : D
{
    virtual void bar() {}
    std::string str;
};


typedef boost::optional<E> oE;
typedef boost::optional<oE> ooE;


ooE make_ooE_rvalue()
{
    E e;
    e.str = "hello";
    oE x(e);
    ooE y(x);
    return y;
}

ooE make_ooE_rvalue2()
{
    return make_ooE_rvalue();
}

void foo(int, ooE v)
{
    BOOST_CHECK( (**v).str == "hello" );
}


void pstade_unit_test()
{
    ::foo(3, make_ooE_rvalue2());
}

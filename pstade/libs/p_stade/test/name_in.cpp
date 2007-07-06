#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


namespace standard {

    template<class T>
    void zero(T x) { }

}


namespace my {

    using namespace ::standard;

    template<class T>
    struct X { };
}


namespace our {

    namespace your {

        struct zero_ { };
        zero_ const zero = { };


        template<class T0, class T1 = zero_>
        struct A
        {
            A(T0, T1 x = zero)
            { };
        };


        template<class T0, class T1>
        A<T0, T1> make_A(T0 _0, T1 _1)
        {
            return A<T0, T1>(_0, _1);
        }

        template<class T0>
        A<T0> make_A(T0 _0)
        {
            return A<T0>(_0);
        }
    }

}

//using namespace standard;
using standard::zero;

//int zero = 0;


void test()
{
    //our::your::make_A(1, zero);
    standard::zero(our::your::make_A(1));
    our::your::make_A(1);
}


int test_main(int, char *[])
{
    ::test();
    return 0; 
} 

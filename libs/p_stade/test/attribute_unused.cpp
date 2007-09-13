

#include <pstade/minimal_test.hpp>
//#include <pstade/egg/egg.hpp>


template<class X>
void ignore_unused(X const&){}


namespace my {

    template<class Baby>
    struct function
    {
        Baby baby;
    };


    struct A {};

}


#if 0
namespace {
    extern A const a;
}
namespace a_detail {
    inline void use_a() { ::ignore_unused(a); }
}
#endif


namespace my {
    function<A> const __attribute__ ((__unused__)) fa = {{}};
}

void pstade_minimal_test()
{}

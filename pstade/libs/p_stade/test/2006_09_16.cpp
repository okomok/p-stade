#if 1

#include <pstade/../libs/egg/test/disable_if_same.cpp>
//#include <pstade/../libs/oven/test/writer.cpp>
//#include <pstade/../libs/biscuit/test/capture.cpp>

#else


#include <iostream>
#include <string>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/range.hpp>
#include <boost/foreach.hpp>


struct klass
{
    klass()
    { }

    klass(klass const&) // (1)
    { }

    template< class T > // (2)
    explicit klass(T& x, typename boost::disable_if< boost::is_same<T, klass> >::type * = 0)
    { assert(false); }

#if 0
    klass(klass&) // (3)
    { }
#endif
};


int main()
{
    klass k;
    klass k_(k);
}


#endif



// In case BOOST_MPL_HAS_XXX_TRAIT_DEF, this doesn't compile.

#include <pstade/has_xxx.hpp>


namespace my1 {
    PSTADE_HAS_TYPE(ppp)
}

#include <boost/mpl/apply.hpp>
#include <boost/static_assert.hpp>

namespace my2 {
    PSTADE_HAS_TYPE(ppp)
}

struct foo
{
    typedef int ppp;
};

BOOST_STATIC_ASSERT( my1::has_ppp< foo >::value );
BOOST_STATIC_ASSERT( my2::has_ppp< foo >::value );


int main() {}

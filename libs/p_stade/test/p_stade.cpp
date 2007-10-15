
#include <boost/mpl/has_xxx.hpp>

namespace boost { namespace mpl { namespace aux {
template< typename T > struct msvc71_sfinae_helper;
}}}

namespace my1 {
    BOOST_MPL_HAS_XXX_TRAIT_DEF(ppp)
}

#include <boost/mpl/apply.hpp> // does something bad for msvc.
#include <boost/static_assert.hpp>

namespace my2 {
    BOOST_MPL_HAS_XXX_TRAIT_DEF(ppp)
}

struct foo
{
    typedef int ppp;
};

BOOST_STATIC_ASSERT( my1::has_ppp< foo >::value ); // pass
BOOST_STATIC_ASSERT( my2::has_ppp< foo >::value ); // failed


int main() {}

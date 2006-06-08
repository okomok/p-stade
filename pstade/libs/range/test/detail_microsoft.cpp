// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#include <boost/test/minimal.hpp>


#include <boost/detail/workaround.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
#  pragma warn -8091 // supress warning in Boost.Test
#  pragma warn -8057 // unused argument argc/argv in Boost.Test
#endif

#include <boost/range.hpp>
#include <vector>
#include <boost/range/detail/microsoft.hpp>

//
// Generic range algorithm
//
template< class Rng >
typename boost::range_result_iterator<Rng>::type foo_algo( Rng& r )
{
        //
        // This will only compile for Rng = UDT if the qualified calls
        // find boost_range_XXX via ADL.
        //
        return boost::size(r) == 0u ? boost::begin(r) : boost::end(r);
}

namespace Foo
{
        //
        // Our sample UDT
        //
        struct X
        {
                typedef std::vector<int>       data_t;
                typedef data_t::iterator       iterator;
                typedef data_t::const_iterator const_iterator;
                typedef data_t::size_type      size_type;

                data_t vec;

                void push_back( int i )
                { vec.push_back(i); }
        };
}


namespace boost { namespace range_detail_microsoft {


    template< >
    struct customization< Foo::X >
    {
        template< class X >
        struct meta
        {
            typedef typename X::iterator mutable_iterator;
            typedef typename X::const_iterator const_iterator;
        };

        template< class Iterator, class X >
        Iterator begin(X& x)
        {
            return x.vec.begin();
        }

        template< class Iterator, class X >
        Iterator end(X& x)
        {
            return x.vec.end();
        }
    };


} }


BOOST_RANGE_DETAIL_MICROSOFT_CUSTOMIZATION_TYPE(
    boost::range_detail_microsoft::using_type_as_tag,
    (Foo, BOOST_PP_NIL), X
)


void check_extension()
{
        Foo::X x;
        x.push_back(3);
        const Foo::X x2;

        foo_algo( x );
        foo_algo( x2 );
}

int test_main(int, char*[])
{
    ::check_extension();
    return 0;
}





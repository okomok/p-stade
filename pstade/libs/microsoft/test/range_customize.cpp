#include <boost/test/minimal.hpp>
#include <boost/range.hpp>
#include <boost/type.hpp>


// Boost.Microsoft
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/detail/range/customize.hpp>


struct MyRange
{ };


#define MACRO(T) \
    typedef boost::type< \
    T > xxx_t; \
/**/


template< class X >
struct XXXX;


typedef int int_def_t;

template< >
struct XXXX< int_def_t >
{ };

namespace boost { namespace microsoft { namespace range_customize {


    template< class MyRangeT >
    struct metafunctions< ::MyRange, MyRangeT>
    {
        typedef char *mutable_iterator;
        typedef const char *const_iterator;
        typedef int size_type;
    };


    // 'GetSize' missing
    template< >
    struct functions<MyRange>
    {
        template< class Result, class MyRangeT >
        typename overloaded<Result, MyRangeT>::type begin(MyRangeT& rng)
        {
            return 0;
        }

        template< class Result, class MyRangeT >
        Result begin(const MyRangeT& rng)
        {
            return 0;
        }

        template< class Result, class MyRangeT >
        Result end(MyRangeT& rng)
        {
            return 0;
        }

        template< class Result, class MyRangeT >
        Result size(MyRangeT& rng)
        {
            return 0;
        }
    };


} } } // namespace boost::microsoft::range_customize



BOOST_MICROSOFT_RANGE_CUSTOMIZE_TYPE(
    MyRange,
    BOOST_PP_NIL, MyRange
)


int test_main(int, char*[])
{
    MACRO(::boost::type<int>)

    {
        ::MyRange rng;
        boost::begin(rng);
        boost::end(rng);
    }

    {
        const ::MyRange rng = MyRange();
        boost::begin(rng);
        boost::end(rng);
    }

    return 0;
}

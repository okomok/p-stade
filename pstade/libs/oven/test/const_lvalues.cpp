#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/const_lvalues.hpp>


#include <vector>
#include <string>
#include <boost/range.hpp>
#include <pstade/oven/metafunctions.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/copy_range.hpp>
#include <pstade/oven/copied_out.hpp>
#include <pstade/oven/filtered.hpp>
#include <pstade/oven/transformed.hpp>

#include <iterator>
#include <boost/static_assert.hpp>
#include <boost/iterator/is_lvalue_iterator.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_same.hpp>


template <class It>
struct pure_traversal
  : boost::detail::pure_traversal_tag<
        typename boost::iterator_traversal<It>::type
    >
{ };


struct id
{
    typedef int& result_type;

    int& operator()(int& x) const
    {
        return x;
    }
};


struct inc
{
    typedef int result_type;

    int operator()(int x) const
    {
        return x + 1;
    }
};


typedef std::vector<int> rng_t;
typedef rng_t::iterator iter_t;


typedef boost::transform_iterator< ::id, iter_t > id_tr_iter_t;

    BOOST_MPL_ASSERT(( boost::is_same<
        ::pure_traversal<id_tr_iter_t>::type,
        boost::random_access_traversal_tag
    > ));

    BOOST_MPL_ASSERT(( boost::is_convertible<
        boost::iterator_category<id_tr_iter_t>::type,
        std::random_access_iterator_tag
    > ));


typedef boost::transform_iterator< ::inc, iter_t > inc_tr_iter_t;

    BOOST_MPL_ASSERT(( boost::is_same<
        ::pure_traversal<inc_tr_iter_t>::type,
        boost::random_access_traversal_tag
    > ));

    BOOST_MPL_ASSERT_NOT(( boost::is_convertible<
        boost::iterator_category<inc_tr_iter_t>::type,
        std::forward_iterator_tag
    > ));

    BOOST_MPL_ASSERT(( boost::is_convertible<
        boost::iterator_category<inc_tr_iter_t>::type,
        std::input_iterator_tag
    > ));


    typedef pstade::oven::const_lvalues_detail::const_lvalue_iterator< inc_tr_iter_t > lvalue_iter_t;

    BOOST_MPL_ASSERT(( boost::is_same<
        ::pure_traversal<lvalue_iter_t>::type,
        boost::random_access_traversal_tag
    > ));

    BOOST_MPL_ASSERT(( boost::is_convertible<
        boost::iterator_category<lvalue_iter_t>::type,
        std::random_access_iterator_tag
    > ));

    BOOST_MPL_ASSERT(( boost::is_lvalue_iterator<
        lvalue_iter_t
    > ));


template< class Range >
void check_random_access(Range& )
{
    BOOST_STATIC_ASSERT(( boost::is_convertible<
        typename pstade::oven::range_category<Range>::type,
        std::random_access_iterator_tag
    >::value ));
}


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;
    namespace bll = boost::lambda;

    {
        std::string rng("hello, const_lvalue_range!");
        std::vector<char> expected = rng|copied;
        BOOST_ASSERT(oven::test_RandomAccess_Readable(rng, expected));
    }
    {
        std::string src("axaxaxbxbxbx");
        std::string s1; // snapshot
        std::string s2;
        std::string answer("bbb");

        BOOST_CHECK((
            oven::equals(answer,
                src |
                    filtered(regular(bll::_1 != 'x'))  |
                    copied_out(std::back_inserter(s1)) |
                    filtered(regular(bll::_1 != 'a'))  |
                    copied_out(std::back_inserter(s2)) |
                    const_lvalues
            )
        ));

        BOOST_CHECK( s1 == "aaabbb" );
        BOOST_CHECK( s2 == answer );
    }

    {
        int const src[] = { 1,2,3 };

        ::check_random_access(
            src|transformed(::id())|const_lvalues
        );

        ::check_random_access(
            src|transformed(::inc())|const_lvalues
        );

        BOOST_CHECK( 3 == oven::distance(src|transformed(::inc())) );
        BOOST_CHECK( 3 == oven::distance(src|transformed(::inc())|const_lvalues) );
    }

#if 0 // impossible!
    {
        std::vector<int> vec;
        vec.push_back(3);
        lvalue_iter_t it1 = oven::make_const_lvalue_iterator(boost::make_transform_iterator(vec.begin(), ::inc()));
        lvalue_iter_t it2(it1);
        BOOST_CHECK( &*it1 == &*it2 );
        BOOST_CHECK( (it1 == it2) == (&*it1 == &*it2) );
    }
#endif

#if 0
    {
        std::string str;
        oven::make_const_lvalue_iterator(boost::begin(str));
    }
#endif
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}

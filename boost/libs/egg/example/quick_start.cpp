

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/poly.hpp>
#include <boost/egg/pipable.hpp>
#include <boost/egg/lazy.hpp>
#include <boost/egg/result_of.hpp>

#include BOOST_EGG_SUPPRESS_WARNING_BEGIN()
#include <boost/lambda/core.hpp> // _1
#include <iostream>
#include <string>
#include <boost/foreach.hpp>
#include <boost/iterator/filter_iterator.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include <locale> // islower
#include BOOST_EGG_SUPPRESS_WARNING_END()


//[code_quick_start_make_filtered_imperfect
#include <iostream>
#include <string>
#include <boost/foreach.hpp>
#include <boost/iterator/filter_iterator.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>

namespace imperfect {

    template<class Range, class Predicate>
    boost::iterator_range<
        boost::filter_iterator<
            Predicate,
            typename boost::range_result_iterator<Range>::type
        >
    >
    make_filtered(Range &rng, Predicate pred) /*< Take by reference, for Range isn't always __COPY_CONSTRUCTIBLE__. >*/
    {
        typedef
            boost::filter_iterator<
                Predicate,
                typename boost::range_result_iterator<Range>::type
            >
        iter_t;

        return boost::iterator_range<iter_t>(
            iter_t(pred, boost::begin(rng), boost::end(rng)),
            iter_t(pred, boost::end(rng), boost::end(rng))
        );
    }

    bool is_not_X(char ch) { return ch != 'X'; }

    void test_make_filtered()
    {
        std::string src("abXcdXefXgh");
        BOOST_FOREACH (char ch, make_filtered(src, &is_not_X))
            std::cout << ch; /*< Prints `abcdefgh`. >*/
    }

} // namespace imperfect
//]


//[code_quick_start_make_filtered
#include <boost/egg/poly.hpp>
#include <locale>

template<class Range, class Predicate>
struct mono_make_filtered
{
    typedef
        boost::filter_iterator<
            Predicate,
            typename boost::range_result_iterator<Range>::type
        >
    iter_t;

    typedef
        boost::iterator_range<iter_t>
    result_type;

    result_type operator()(Range &rng, Predicate &pred) const
    {
        return result_type(
            iter_t(pred, boost::begin(rng), boost::end(rng)),
            iter_t(pred, boost::end(rng), boost::end(rng))
        );
    }
};

typedef
    boost::egg::poly< mono_make_filtered<boost::mpl::_, boost::mpl::_> >::type
T_make_filtered;

T_make_filtered const make_filtered = BOOST_EGG_POLY();

bool is_not_X(char ch) { return ch != 'X'; }
bool is_not_Y(char ch) { return ch != 'Y'; }
bool is_lower(char ch) { return std::islower(ch, std::locale()); }

void test_make_filtered()
{
    std::string src("abXcYdXefXgYhY");

    boost::egg::result_of_< /*< __BOOST_RESULT_OF__ isn't used for now. See __EGG_RESULT_OF__. >*/
        T_make_filtered(std::string &, bool(*)(char))
    >::type lowers = make_filtered(src, &is_lower);

    BOOST_FOREACH (char ch, lowers)
        std::cout << ch; /*< Prints `abcdefgh`. >*/

    BOOST_FOREACH (char ch, make_filtered(make_filtered(src, &is_not_X), &is_not_Y)) /*< Notice outmost `make_filtered` takes rvalue. >*/
        std::cout << ch; /*< Prints `abcdefgh`. >*/
}
//]


//[code_quick_start_filtered
#include <boost/egg/pipable.hpp>

boost::egg::result_of_pipable<T_make_filtered>::type
    const filtered = BOOST_EGG_PIPABLE_L BOOST_EGG_POLY() BOOST_EGG_PIPABLE_R; /*< Recall the initializer of `T_make_filtered` is `BOOST_EGG_POLY()`. >*/

void test_filtered()
{
    std::string src("abXcYdXefXgYhY");
    BOOST_FOREACH (char ch, src|filtered(&is_not_X)|filtered(&is_not_Y))
        std::cout << ch; /*< Prints `abcdefgh`. >*/
}
//]


//[code_quick_start_lazy
#include <boost/egg/lazy.hpp>
#include <boost/lambda/core.hpp> // _1

template<class MakeRange>
void my_foreach(MakeRange make)
{
    std::string src("abXcYdXefXgYhY");
    BOOST_FOREACH (char ch, make(src))
        std::cout << ch;
}

void test_lazy()
{
    namespace bll = boost::lambda;
    boost::egg::result_of_lazy<T_make_filtered>::type make_Filtered; /*< The macro initializer is needed only in namespace scope. >*/
    ::my_foreach(make_Filtered(make_Filtered(bll::_1, &is_not_X), &is_not_Y)); /*< Prints `abcdefgh`. >*/
}
//]


int main()
{
    imperfect::test_make_filtered();
    test_make_filtered();
    test_filtered();
    test_lazy();
}



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
#define foreach BOOST_FOREACH

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
        foreach (char ch, make_filtered(src, &is_not_X)) {
            std::cout << ch; /*< Prints `abcdefgh`. >*/
        }
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

T_make_filtered const make_filtered = BOOST_EGG_POLY(); /*< This macro ensures __STATIC_INITIALIZATION__. >*/


bool is_not_X(char ch) { return ch != 'X'; }
bool is_not_Y(char ch) { return ch != 'Y'; }
bool is_lower(char ch) { return std::islower(ch, std::locale()); }

void test_make_filtered()
{
    std::string src("abXcYdXefXgYhY");

    boost::egg::result_of_< /*< `boost::result_of` isn't used for now. See __EGG_RESULT_OF__. >*/
        T_make_filtered(std::string &, bool(*)(char))
    >::type lowers = make_filtered(src, &is_lower);

    foreach (char ch, lowers) {
        std::cout << ch; /*< Prints `abcdefgh`. >*/
    }

    foreach (char ch, make_filtered(make_filtered(src, &is_not_X), &is_not_Y)) { /*< Notice outmost `make_filtered` takes rvalue. >*/
        std::cout << ch; /*< Prints `abcdefgh`. >*/
    }
}
//]


//[code_quick_start_pipable
#include <boost/egg/pipable.hpp>

boost::egg::result_of_pipable<T_make_filtered>::type
    const filtered = BOOST_EGG_PIPABLE_L BOOST_EGG_POLY() BOOST_EGG_PIPABLE_R; /*< Recall the initializer of `T_make_filtered` is `BOOST_EGG_POLY()`. >*/

void test_pipable()
{
    std::string src("abXcYdXefXgYhY");
    foreach (char ch, src|filtered(&is_not_X)|filtered(&is_not_Y)) {
        std::cout << ch;
    }
}
//]


//[code_quick_start_lazy
#include <boost/egg/lazy.hpp>
#include <boost/lambda/core.hpp> // _1

template<class MakeRange>
void my_foreach(MakeRange make)
{
    std::string src("abXcYdXefXgYhY");
    foreach (char ch, make(src)) {
        std::cout << ch;
    }
}

void test_lazy()
{
    namespace bll = boost::lambda;

    ::my_foreach(boost::egg::lazy(make_filtered)(bll::_1, &is_lower)); /*< Using __EGG_LAZY__ as higher-order function. >*/

    boost::egg::result_of_lazy<T_make_filtered>::type make_Filtered; /*< When you dislike to write `boost::egg::lazy` multiple times, the metafunction also is available. >*/
    ::my_foreach(make_Filtered(make_Filtered(bll::_1, &is_not_X), &is_not_Y));
}
//]


int main()
{
    imperfect::test_make_filtered();
    test_make_filtered();
    test_pipable();
    test_lazy();
}

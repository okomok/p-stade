

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/nest.hpp>
#include <boost/egg/poly.hpp>
#include <boost/egg/pipable.hpp>
#include <boost/egg/lazy.hpp>
#include <boost/egg/result_of.hpp>
#include <boost/egg/static.hpp>
#include <boost/egg/indirect.hpp>
#include <boost/egg/compose.hpp>
#include <boost/egg/curry.hpp>
#include <boost/egg/fuse.hpp>
#include <boost/egg/unfuse.hpp>
#include <boost/egg/mono.hpp>
#include <boost/egg/generator.hpp>
#include <boost/egg/function_facade.hpp>


#include BOOST_EGG_SUPPRESS_WARNING_BEGIN()
#include <functional>
#include <iostream>
#include <string>
#include <boost/mpl/always.hpp>
#include <boost/lambda/core.hpp> // _1
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
    make_filtered(Range &rng, Predicate pred) /*< Take by reference, for a Range isn't always __COPY_CONSTRUCTIBLE__. >*/
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

    void quick_start_make_filtered()
    {
        std::string src("abXcdXefXgh");
        foreach (char ch, make_filtered(src, &is_not_X)) {
            std::cout << ch;
        } /*< Prints `abcdefgh`. >*/
    }

} // namespace imperfect
//]


//[code_quick_start_make_filtered
#include <boost/egg/poly.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <locale>

namespace egg = boost::egg;

template<class Range, class Predicate>
struct mono_make_filtered
{
    typedef
        boost::filter_iterator<
            typename boost::remove_cv<Predicate>::type,
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
    egg::poly< mono_make_filtered<boost::mpl::_, boost::mpl::_> >::type
T_make_filtered;

T_make_filtered const make_filtered = {{}};


bool is_not_X(char ch) { return ch != 'X'; }
bool is_not_Y(char ch) { return ch != 'Y'; }
bool is_lower(char ch) { return std::islower(ch, std::locale()); }

void quick_start_make_filtered()
{
    std::string src("abXcYdXefXgYhY");

    egg::result_of_< /*< `boost::result_of` isn't used for now. See __EGG_RESULT_OF__. >*/
        T_make_filtered(std::string &, bool(*)(char))
    >::type lowers = make_filtered(src, &is_lower);

    foreach (char ch, lowers) {
        std::cout << ch;
    } /*< Prints `abcdefgh`. >*/

    foreach (char ch, make_filtered(make_filtered(src, &is_not_X), &is_not_Y)) { /*< Notice outmost `make_filtered` takes rvalue. >*/
        std::cout << ch;
    } /*< Prints `abcdefgh`. >*/
}
//]


//[code_quick_start_pipable
#include <boost/egg/pipable.hpp>

void quick_start_pipable()
{
    egg::result_of_<egg::T_pipable(T_make_filtered const &)>::type
        filtered = egg::pipable(make_filtered);

    std::string src("abXcYdXefXgYhY");
    foreach (char ch, src|filtered(&is_not_X)|filtered(&is_not_Y)) {
        std::cout << ch;
    }
}
//]


//[code_quick_start_static_pipable
#include <boost/egg/static.hpp>

egg::static_< egg::result_of_<egg::T_pipable(T_make_filtered)> >::type /*< __EGG_STATIC__ ensures __STATIC_INITIALIZATION__ of `filtered`. >*/
    const filtered = {{}};

void quick_start_static_pipable()
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

void quick_start_lazy()
{
    namespace bll = boost::lambda;

    egg::result_of_<egg::T_lazy(T_make_filtered const &)>::type
        make_Filtered = egg::lazy(make_filtered); /*< Using __EGG_LAZY__ as higher-order function. >*/

    ::my_foreach(make_Filtered(make_Filtered(bll::_1, &is_not_X), &is_not_Y));
}
//]


//[code_quick_start_indirect
#include <boost/egg/indirect.hpp>

egg::result_of_pipable< /*< Assume you don't know `T_make_filtered` can be initialized using `BOOST_EGG_POLY()`. >*/
    egg::result_of_indirect<T_make_filtered const *>::type
>::type
    const her_filtered = BOOST_EGG_PIPABLE_L BOOST_EGG_INDIRECT(&make_filtered) BOOST_EGG_PIPABLE_R;
//]


void quick_start_indirect()
{
    std::string src("abXcYdXefXgYhY");
    foreach (char ch, src|her_filtered(&is_lower)) {
        std::cout << ch;
    }
}


//[code_quick_start_object_generator
#include <boost/egg/generator.hpp>

template<class T>
struct always_result :
    egg::function_facade< always_result<T> > /*< __EGG_FUNCTION_FACADE__ might remind you of __BOOST_ITERATOR_FACADE__. >*/
{
    T m_t;
    explicit always_result(T const &t) : m_t(t) { }

    template<class Me, class A>
    struct apply
    {
        typedef T const &type;
    };

    template<class Re, class A>
    Re call(A &) const
    {
        return m_t;
    }
};

egg::generator<
    always_result< egg::deduce<boost::mpl::_1, egg::as_value> >
>::type const always = {{}};

void quick_start_object_generator()
{
    std::cout << always(10)(999); /*< Prints `10`. >*/
}
//]


//[code_quick_start_nest
#include <boost/egg/nest.hpp>
#include <boost/lambda/core.hpp> // _1, _2
#include <functional> // minus

using boost::lambda::_1;
using boost::lambda::_2;

// These represent nesting levels.
using egg::_0_;
using egg::_1_;
using egg::_2_;

void quick_start_nest()
{
    int i6 = 6, i7 = 7;
    std::plus<int> plus;
    std::minus<int> minus;

    int r =
    // Lv: 0     1          2
        // \x -> (\(y,z) -> plus(5, y(z, x)))
        egg::nest2(plus)(5, egg::nest2(_1_(_1))(_1_(_2), _0_(_1)))
            (i6)(minus, i7);

    std::cout << r; /*< Prints `6`.>*/
}
//]


//[code_quick_start_nest_family
#include <boost/egg/nest.hpp>
#include <boost/egg/compose.hpp>
#include <boost/egg/curry.hpp>
#include <boost/egg/lazy.hpp>
#include <functional> // plus, negate

void quick_start_nest_family()
{
    std::plus<int> plus;
    std::negate<int> negate;

    int i6 = 6, i7 = 7;

// Lv: 0         1
    // \(x,y) -> negate(plus(x, y))
    std::cout << egg::nest1(negate)(egg::nest1(plus)(_0_(_1), _0_(_2)))(i6, i7); /*< Prints `-13`. >*/
    std::cout << egg::compose(negate, plus)(i6, i7);

// Lv: 0     1      2
    // \x -> (\y -> plus(x, y))
    std::cout << egg::nest2(plus)(_0_(_1), _1_(_1))(i6)(i7); /*< Prints `13`. >*/
    std::cout << egg::curry2(plus)(i6)(i7);

// Lv: 0     1
    // \x -> negate(x)
    std::cout << egg::nest1(negate)(_0_(_1))(i7); /*< Prints `-7`. >*/
    std::cout << egg::lazy(negate)(_1)(i7);
}
//]


//[code_quick_start_fusing1
#include <functional> // plus
#include <boost/tuple/tuple.hpp>
#include <boost/egg/fuse.hpp>
#include <boost/egg/unfuse.hpp>

void quick_start_fusing1()
{
    std::plus<int> plus;

    std::cout << egg::fuse(plus)(boost::make_tuple(1, 2)); /*< Prints `3`. >*/
    std::cout << egg::unfuse(egg::fuse(plus))(1, 2);
}
//]


//[code_quick_start_fusing2
struct fused_plus
{
    typedef int result_type;

    template<class Tuple>
    int operator()(Tuple const &t) const
    {
        return t.get_head() + (*this)(t.get_tail());
    }

    int operator()(boost::tuples::null_type const &) const
    {
        return 0;
    }
};

typedef egg::static_< egg::result_of_<egg::T_unfuse(fused_plus)> >::type T_good_plus;
T_good_plus const good_plus = {{}};

void quick_start_fusing2()
{
    std::cout << good_plus(1); /*< Prints `1`. >*/
    std::cout << good_plus(1, 2); /*< Prints `3`. >*/
    std::cout << good_plus(1, 2, 3); /*< Prints `6`. >*/
}
//]


//[code_quick_start_mono
#include <boost/egg/mono.hpp>

egg::static_< egg::result_of_<egg::X_mono<int(int, int)>(T_good_plus)> >::type
    const int_plus = {{}};

void quick_start_mono()
{
#if 0
    std::cout << int_plus(std::string("a"), std::string("b")); /*< Would show an error with clear messages. >*/
#endif
    std::cout << int_plus(1, 2); /*< Prints `3`. >*/
}
//]


int main()
{
    imperfect::quick_start_make_filtered();
    std::cout << std::endl;
    quick_start_make_filtered();
    std::cout << std::endl;
    quick_start_pipable();
    std::cout << std::endl;
    quick_start_lazy();
    std::cout << std::endl;
    quick_start_indirect();
    std::cout << std::endl;
    quick_start_object_generator();
    std::cout << std::endl;
    quick_start_nest();
    std::cout << std::endl;
    quick_start_nest_family();
    std::cout << std::endl;
    quick_start_fusing1();
    std::cout << std::endl;
    quick_start_fusing2();
    std::cout << std::endl;
    quick_start_mono();
    std::cout << std::endl;
}

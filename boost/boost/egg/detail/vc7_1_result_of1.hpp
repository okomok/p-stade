#ifndef BOOST_EGG_DETAIL_VC7_1_RESULT_OF1_HPP
#define BOOST_EGG_DETAIL_VC7_1_RESULT_OF1_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Used in "../explict1.hpp" for msvc-7.1 bug workaround;
// msvc-7.1 complains about the "const A" syntax of:
//     template<class A> ...A const... foo(A &a) { }
// if A is deduced as array type, which "./deduced_const.hpp" using 'add_const' easily works around.
// But, only in namespace scope, msvc-7.1 (fairly infrequently) fails to const-qualify 'A'
// in 'boost::result_of' parameter types if a metafunction is used:
//     template<class A> // 'add_const' below is ignored.
//     typename boost::result_of<F(typename add_const<A>::type &)>::type foo(A &a, F) { }
// So, we must delay to write 'const' for array types, then instantiate 'result_of' using 'const'.
// In other words, this bug introduces "Metafunction Forwarding Problem".
// Fortunately, this bug doesn't occur in class scope.
// Notice EGG_ARRAY_RESURRECT is metafunction, so that it still doesn't work.


#include <boost/egg/result_of.hpp>
#include <boost/egg/detail/vc7_1_const_ref.hpp>


namespace boost { namespace egg { namespace detail_vc7_1 {


    template<class Fun, class A>
    struct result_of1;


    template<class Fun, class A>
    struct result_of1< Fun, A & > :
        result_of_<Fun(A &)>
    { };

    template<class Fun, class A>
    struct result_of1< Fun, const_ref<A> > :
        result_of_<Fun(A const &)> // Write `const` by hand.
    { };


} } } // namespace boost::egg::detail_vc7_1


#endif

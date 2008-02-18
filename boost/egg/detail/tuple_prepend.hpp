#ifndef BOOST_EGG_DETAIL_TUPLE_PREPEND_HPP
#define BOOST_EGG_DETAIL_TUPLE_PREPEND_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/tuple/tuple.hpp> // cons
#include <boost/type_traits/remove_cv.hpp>
#include <boost/egg/forward.hpp>
#include <boost/egg/detail/derived_from.hpp>
#include <boost/egg/detail/enable_if.hpp>
#include <boost/egg/detail/is_boost_tuple.hpp>


namespace boost { namespace egg { namespace details {


    // tuple_prepend
    //

    template<class ByTag, class Tuple, class A, class EnableIf = enabler>
    struct tuple_prepend_impl;

    template<class Bytag>
    struct little_tuple_prepend
    {
        template<class Me, class Tuple, class A>
        struct apply
        {
            // avoid `mpl::apply` around enable_if for gcc-3.4.
            typedef typename
                tuple_prepend_impl<Bytag, Tuple, A>::result_type
            type;
        };

        template<class Re, class Tuple, class A>
        Re call(Tuple &t, A &a) const
        {
            return tuple_prepend_impl<Bytag, Tuple, A>()(t, a);
        }
    };

    template<class Bytag>
    struct X_tuple_prepend : derived_from<
        function<little_tuple_prepend<Bytag>, Bytag> >
    { };


    // boost::tuple
    //

    template<class Bytag, class Tuple, class A>
    struct tuple_prepend_impl<Bytag, Tuple, A,
        typename enable_if< is_boost_tuple<Tuple> >::type>
    {
        typedef
            tuples::cons<
                typename result_of_forward<Bytag, A>::type,
                typename remove_cv<Tuple>::type
            >
        result_type;

        result_type operator()(Tuple &t, A &a) const
        {
            return result_type(a, t);
        }
    };


} } } // namespace boost::egg::details


#endif

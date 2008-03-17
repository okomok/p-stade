#ifndef BOOST_EGG_STATIC_HPP
#define BOOST_EGG_STATIC_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/always.hpp> // inclusion guaranteed
#include <boost/mpl/apply.hpp>
#include <boost/mpl/placeholders.hpp> // inclusion guaranteed
#include <boost/egg/by_perfect.hpp>
#include <boost/egg/detail/tuple_fuse.hpp>
#include <boost/egg/result_of.hpp>
#include <boost/egg/variadic.hpp>


namespace boost { namespace egg {


    namespace static_detail {


        template<class Fun>
        struct little
        {
            template<class Me, class Args>
            struct apply :
                result_of_<
                    typename result_of_<details::T_tuple_fuse(Fun)>::type(Args &)
                >
            { };

            template<class Re, class Args>
            Re call(Args &args) const
            {
                return details::tuple_fuse(Fun())(args);
            }
        };


    } // namespace static_detail


    template<class Expr, class Strategy = by_perfect>
    struct static_ :
        variadic<
            static_detail::little<typename mpl::apply1<Expr, Strategy>::type>,
            Strategy,
            use_default,
            use_nullary_result
        >
    { };

    #define BOOST_EGG_STATIC() BOOST_EGG_VARIADIC({})


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif

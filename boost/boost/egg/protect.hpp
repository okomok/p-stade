#ifndef BOOST_EGG_PROTECT_HPP
#define BOOST_EGG_PROTECT_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This is the same as `always` tagged with bind expression.


#include <boost/mpl/bool.hpp>
#include <boost/egg/always.hpp>
#include <boost/egg/by_value.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/detail/enable_if.hpp>
#include <boost/egg/is_bind_expression.hpp>
#include <boost/egg/tagged.hpp>


namespace boost { namespace egg {


    namespace protect_detail {
        struct tag;
    }

    template<class Expr>
    struct result_of_protect :
        result_of_tagged<
            typename result_of_always<Expr>::type,
            protect_detail::tag
        >
    { };

    #define BOOST_EGG_PROTECT_L BOOST_EGG_TAGGED_L BOOST_EGG_ALWAYS_L
    #define BOOST_EGG_PROTECT_R BOOST_EGG_ALWAYS_R BOOST_EGG_TAGGED_R
    #define BOOST_EGG_PROTECT(F) BOOST_EGG_PROTECT_L F BOOST_EGG_PROTECT_R


    template<class X>
    struct is_bind_expression_set<X, typename details::enable_if< is_tagged_with<X, protect_detail::tag> >::type> :
        mpl::true_
    { };


    namespace protect_detail {

        struct little
        {
            template<class Me, class Expr>
            struct apply :
                result_of_protect<Expr>
            { };

            template<class Re, class Expr>
            Re call(Expr f) const
            {
                Re r = BOOST_EGG_PROTECT(f);
                return r;
            }
        };

    } // namespace protect_detail

    typedef function<protect_detail::little, by_value> T_protect;
    BOOST_EGG_CONST((T_protect), protect) = {{}};


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif

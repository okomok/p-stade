#ifndef BOOST_EGG_IF_ELSE_HPP
#define BOOST_EGG_IF_ELSE_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/lambda/if.hpp> // return_type_2
#include <boost/egg/by_perfect.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/detail/adl_barrier.hpp>
#include <boost/egg/detail/derived_from.hpp>
#include <boost/egg/detail/if_use_default.hpp>


namespace boost { namespace egg {


    namespace if_else_detail {


        template<class Return>
        struct little
        {
            template<class Me, class C, class A1, class A2>
            struct apply :
                details::eval_if_use_default< Return,
                    lambda::return_type_2<lambda::other_action<lambda::ifthenelsereturn_action>, A1, A2>
                >
            { };

            template<class Re, class C, class A1, class A2>
            Re call(C &c, A1 &a1, A2 &a2) const
            {
                return c ? a1 : a2;
            }
        };


    } // namespace if_else_detail


    template<class Return = use_default, class Strategy = by_perfect>
    struct X_if_else : details::derived_from<
        function<if_else_detail::little<Return>, Strategy> >
    { };

    typedef X_if_else<>::base_class T_if_else;
    typedef T_if_else T_if_else_;
BOOST_EGG_ADL_BARRIER(if_else_detail) {
    BOOST_EGG_CONST((T_if_else_), if_else_) = {{}};
}


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif

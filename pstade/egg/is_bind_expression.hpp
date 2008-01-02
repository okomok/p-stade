#ifndef PSTADE_EGG_IS_BIND_EXPRESSION_HPP
#define PSTADE_EGG_IS_BIND_EXPRESSION_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/bool.hpp>
#include <pstade/enable_if.hpp>
#include "./bll/functor_fwd.hpp"


namespace boost { namespace _bi {

    template<class R, class F, class L>
    class bind_t;

} }


namespace pstade { namespace egg {


    template<class X, class EnableIf>
    struct is_bind_expression_base :
        boost::mpl::false_
    { };


    template<class X>
    struct is_bind_expression :
        is_bind_expression_base<X, enabler>
    { };

    template<class X>
    struct is_bind_expression<X const> :
        is_bind_expression<X>
    { };

    template<class X>
    struct is_bind_expression<X volatile> :
        is_bind_expression<X>
    { };

    template<class X>
    struct is_bind_expression<X const volatile> :
        is_bind_expression<X>
    { };


    template<class T>
    struct is_bind_expression< boost::lambda::lambda_functor<T> > :
        boost::mpl::true_
    { };


    template<class R, class F, class L>
    struct is_bind_expression< boost::_bi::bind_t<R, F, L> > :
        boost::mpl::true_
    { };


} } // namespace pstade::egg


#endif

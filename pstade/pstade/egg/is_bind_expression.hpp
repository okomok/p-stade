#ifndef PSTADE_EGG_IS_BIND_EXPRESSION_HPP
#define PSTADE_EGG_IS_BIND_EXPRESSION_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
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


    // enable_if layer
    //

    template<class X, class EnableIf>
    struct is_bind_expression_set :
        boost::mpl::false_
    { };


    // tag layer
    //

    template<class X>
    struct bind_expression_tag
    {
        typedef void type;
    };

    template<class X>
    struct bind_expression_tag<X const> :
        bind_expression_tag<X>
    { };

    template<class X>
    struct bind_expression_tag<X volatile> :
        bind_expression_tag<X>
    { };

    template<class X>
    struct bind_expression_tag<X const volatile> :
        bind_expression_tag<X>
    { };

    template<class X, class Tag>
    struct is_bind_expression_tagged :
        is_bind_expression_set<X, enabler>
    { };


    // type layer
    //

    template<class X>
    struct is_bind_expression :
        is_bind_expression_tagged<X, typename bind_expression_tag<X>::type>
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

    template<class X>
    struct is_bind_expression<X &>;


    // predefined customizations
    //

    template<class T>
    struct is_bind_expression< boost::lambda::lambda_functor<T> > :
        boost::mpl::true_
    { };

    template<class R, class F, class L>
    struct is_bind_expression< boost::_bi::bind_t<R, F, L> > :
        boost::mpl::true_
    { };


} } // namespace pstade::egg


#include "./detail/suffix.hpp"
#endif

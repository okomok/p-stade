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


namespace pstade { namespace egg {


    template<class X>
    struct is_bind_expression :
        boost::mpl::false_
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


} } // namespace pstade::egg


#endif

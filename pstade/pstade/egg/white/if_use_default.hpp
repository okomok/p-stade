#ifndef PSTADE_EGG_WHITE_IF_USE_DEFAULT_HPP
#define PSTADE_EGG_WHITE_IF_USE_DEFAULT_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2006-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Copyright 2005, 2006 Cryolite.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>
#include "./boost_use_default_fwd.hpp"


namespace boost { namespace egg { namespace white {


    template< class X, class Then, class Else = X >
    struct if_use_default :
        mpl::if_< is_same<X, use_default>,
            Then,
            Else
        >
    { };


    template< class X, class Then, class Else = mpl::identity<X> >
    struct eval_if_use_default :
        mpl::eval_if< is_same<X, use_default>,
            Then,
            Else
        >
    { };


} } } // namespace boost::egg::white


#endif

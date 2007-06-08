#ifndef PSTADE_USE_DEFAULT_HPP
#define PSTADE_USE_DEFAULT_HPP
#include "./prelude.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
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


namespace boost {

    struct use_default;

}


namespace pstade {


    template< class X, class Then, class Else = X >
    struct if_use_default :
        boost::mpl::if_< boost::is_same<X, boost::use_default>,
            Then,
            Else
        >
    { };


    template< class X, class Then, class Else = boost::mpl::identity<X> >
    struct eval_if_use_default :
        boost::mpl::eval_if< boost::is_same<X, boost::use_default>,
            Then,
            Else
        >
    { };


} // namespace pstade


#endif

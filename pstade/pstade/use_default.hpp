#ifndef PSTADE_USE_DEFAULT_HPP
#define PSTADE_USE_DEFAULT_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>


namespace boost {

    struct use_default;

}


namespace pstade {


    template< class Defaultable, class To >
    struct defaultable_to :
        boost::mpl::if_< boost::is_same<Defaultable, boost::use_default>,
            To,
            Defaultable
        >
    { };


    template< class Defaultable, class ToFun >
    struct defaultable_eval_to :
        boost::mpl::eval_if< boost::is_same<Defaultable, boost::use_default>,
            ToFun,
            boost::mpl::identity<Defaultable>
        >
    { };


} // namespace pstade


#endif

#ifndef PSTADE_DEFAULT_HPP
#define PSTADE_DEFAULT_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/constant.hpp>


namespace pstade {


    struct default_t
    { };


    PSTADE_CONSTANT(default_, (default_t))


    template<class From, class To>
    struct default_to :
        boost::mpl::if_< boost::is_same<From, default_t>,
            To,
            From
        >
    { };


    template<class From, class To>
    struct default_eval_to :
        boost::mpl::eval_if< boost::is_same<From, default_t>,
            To,
            boost::mpl::identity<From>
        >
    { };



} // namespace pstade


#endif

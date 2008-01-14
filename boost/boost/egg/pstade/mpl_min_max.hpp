#ifndef PSTADE_MPL_MIN_MAX_HPP
#define PSTADE_MPL_MIN_MAX_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Works around macros which have the same names.


#include <boost/mpl/if.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/less.hpp>


namespace pstade {


    template<class N1, class N2>
    struct mpl_min :
        boost::mpl::if_<boost::mpl::less<N1, N2>, N1, N2>
    { };

    template<class N1, class N2>
    struct mpl_max :
        boost::mpl::if_<boost::mpl::less<N1, N2>, N2, N1>
    { };


    template<class T, T N1, T N2>
    struct mpl_min_c :
        boost::mpl::integral_c<T, (N1 < N2) ? N1 : N2>
    { };

    template<class T, T N1, T N2>
    struct mpl_max_c :
        boost::mpl::integral_c<T, (N1 < N2) ? N2 : N1>
    { };


} // namespace pstade


#endif

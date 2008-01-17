#ifndef PSTADE_EGG_DETAIL_MPL_PLACEHOLDERS_HPP
#define PSTADE_EGG_DETAIL_MPL_PLACEHOLDERS_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/arg.hpp>
#include <boost/mpl/placeholders.hpp> // inclusion guaranteed


namespace pstade { namespace egg {


    typedef boost::mpl::placeholders::_ mpl_x;
    typedef boost::mpl::arg<1> mpl_1;
    typedef boost::mpl::arg<2> mpl_2;
    typedef boost::mpl::arg<3> mpl_3;
    typedef boost::mpl::arg<4> mpl_4;
    typedef boost::mpl::arg<5> mpl_5;
    typedef boost::mpl::arg<6> mpl_6;
    typedef boost::mpl::arg<7> mpl_7;
    typedef boost::mpl::arg<8> mpl_8;
    typedef boost::mpl::arg<9> mpl_9;
    typedef boost::mpl::arg<10> mpl_10;


} } // namespace pstade::egg


#endif

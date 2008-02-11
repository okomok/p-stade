#ifndef PSTADE_EGG_DETAIL_STD_FORWARD_HPP
#define PSTADE_EGG_DETAIL_STD_FORWARD_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/identity.hpp>


namespace pstade { namespace egg {


    template<class T> inline
    T &&std_forward(typename boost::mpl::identity<T>::type &&a)
    {
        return a;
    }


} } // namespace pstade::egg


#endif

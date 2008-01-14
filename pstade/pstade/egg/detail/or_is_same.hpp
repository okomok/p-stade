#ifndef PSTADE_EGG_DETAIL_OR_IS_SAME_HPP
#define PSTADE_EGG_DETAIL_OR_IS_SAME_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_same.hpp>
#include "./bytag_at.hpp"


namespace pstade { namespace egg { namespace detail {


    template<class T1, class T2, class U>
    struct or_is_same :
        boost::mpl::or_<
            boost::is_same<T1, U>,
            boost::is_same<T2, U>
        >
    { };


} } } // namespace pstade::egg::detail


#endif

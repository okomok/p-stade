#ifndef PSTADE_EGG_DETAIL_IS_CALLING_STRATEGY_OF_HPP
#define PSTADE_EGG_DETAIL_IS_CALLING_STRATEGY_OF_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/and.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/has_xxx.hpp>


namespace pstade { namespace egg { namespace detail {


    PSTADE_HAS_TYPE(calling_strategy)


    template<class Tag, class Baby>
    struct is_same_calling_strategy :
        boost::is_same<Tag, typename Baby::calling_strategy>
    { };


    template<class Tag, class Baby>
    struct is_calling_strategy_of :
        boost::mpl::and_<
            has_calling_strategy<Baby>,
            is_same_calling_strategy<Tag, Baby>
        >
    { };


} } } // namespace pstade::egg::detail


#endif

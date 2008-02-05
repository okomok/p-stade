#ifndef PSTADE_EGG_DETAIL_STRATEGY_OF_HPP
#define PSTADE_EGG_DETAIL_STRATEGY_OF_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/type_traits/remove_cv.hpp>
#include "../function_fwd.hpp"


namespace pstade { namespace egg { namespace detail {


    template<class Function> // derived from `function<>`.
    struct strategy_of_impl
    {
        typedef typename Function::strategy_type type;
    };

    template<class Little, class Strategy>
    struct strategy_of_impl< function<Little, Strategy> > // for incomplete context.
    {
        typedef Strategy type;
    };


    template<class Function>
    struct strategy_of :
        strategy_of_impl<typename boost::remove_cv<Function>::type>
    { };


} } } // namespace pstade::egg::detail


#endif

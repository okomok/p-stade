#ifndef PSTADE_EGG_DETAIL_SIG_HPP
#define PSTADE_EGG_DETAIL_SIG_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/int.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/utility/result_of.hpp>


#if !defined(PSTADE_EGG_PROVIDE_SIG_MAX_ARITY)
    #define PSTADE_EGG_PROVIDE_SIG_MAX_ARITY 10 // follows 'tuple'.
#endif


#define PSTADE_EGG_DETAIL_SIG() <pstade/egg/detail/sig_iteration.hpp>


#endif

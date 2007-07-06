#ifndef PSTADE_EGG_DETAIL_SIG_TEMPLATE_HPP
#define PSTADE_EGG_DETAIL_SIG_TEMPLATE_HPP
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
#include <pstade/result_of.hpp>


#if !defined(PSTADE_EGG_SIG_TEMPLATE_MAX_ARITY)
    #define PSTADE_EGG_SIG_TEMPLATE_MAX_ARITY 10 // follows 'tuple'.
#endif


#define PSTADE_EGG_SIG_TEMPLATE() <pstade/egg/detail/sig_template_iteration.hpp>


#endif

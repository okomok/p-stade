#ifndef PSTADE_AUTO_FUN_HPP
#define PSTADE_AUTO_FUN_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/typeof/typeof.hpp>


#if !defined(BOOST_TYPEOF_NATIVE)
    #include <boost/function.hpp>
    #define PSTADE_AUTO_FUN(Sig, Var, Fun) boost::function<Sig> Var = Fun
    #define PSTADE_AUTO_FUN_TPL(Sig, Var, Fun) boost::function<Sig> Var = Fun
#else
    #define PSTADE_AUTO_FUN(Sig, Var, Fun) BOOST_AUTO(Var, Fun)
    #define PSTADE_AUTO_FUN_TPL(Sig, Var, Fun) BOOST_AUTO_TPL(Var, Fun)
#endif


#endif

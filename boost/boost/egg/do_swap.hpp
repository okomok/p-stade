#ifndef BOOST_EGG_DO_SWAP_HPP
#define BOOST_EGG_DO_SWAP_HPP
#include "./detail/prefix.hpp"


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <algorithm> // swap
#include <boost/egg/pstade/boost_workaround.hpp>
#include <boost/egg/pstade/pod_constant.hpp>


namespace pstade { namespace egg {


    struct T_do_swap
    {
        typedef void result_type;

        template<class T>
        void operator()(T& a, T& b) const
        {
#if BOOST_WORKAROUND(BOOST_MSVC, == 1310) // msvc-7.1
            using namespace std;
#else
            using std::swap;
#endif
            swap(a, b);
        }
    };


    PSTADE_POD_CONSTANT((T_do_swap), do_swap) = {};


} } // namespace pstade::egg


#endif

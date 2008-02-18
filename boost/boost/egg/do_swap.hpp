#ifndef BOOST_EGG_DO_SWAP_HPP
#define BOOST_EGG_DO_SWAP_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <algorithm> // swap
#include <boost/egg/const.hpp>
#include <boost/egg/detail/boost_workaround.hpp>


namespace boost { namespace egg {


    struct T_do_swap
    {
        typedef void result_type;

        template<class T>
        void operator()(T &a, T &b) const
        {
#if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
            using namespace std;
#else
            using std::swap;
#endif
            swap(a, b);
        }
    };

    BOOST_EGG_CONST((T_do_swap), do_swap) = {};


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif

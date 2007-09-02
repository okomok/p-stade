#ifndef PSTADE_FOR_DEBUG_HPP
#define PSTADE_FOR_DEBUG_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <exception>
#include <boost/throw_exception.hpp>
#include <pstade/pod_constant.hpp>


namespace pstade {


    struct for_debug_error :
        std::exception
    {
        char const *what() const throw() // override
        {
            return "pstade::for_debug_error";
        }
    };


    struct op_for_debug
    {
        typedef void result_type;

        void operator()() const
        {
        #if defined(NDEBUG)
            boost::throw_exception(for_debug_error());
        #endif
        }
    };


    PSTADE_POD_CONSTANT((op_for_debug), for_debug) = {};


} // namespace pstade


#endif

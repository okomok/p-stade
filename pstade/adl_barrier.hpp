#ifndef PSTADE_ADL_BARRIER_HPP
#define PSTADE_ADL_BARRIER_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Using-directive is beyond ADL.


// Note:
//
// A nested namespace cannot be supported well;
/*
namespace barrier {
   namespace op {
       struct j { };
   }
}
using namespace barrier;

namespace op { struct i{ }; }

op::i aa; // 'op' is ambiguous!
*/


#include <boost/config.hpp> // BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
#include <boost/preprocessor/cat.hpp>


#define PSTADE_ADL_BARRIER(Id) \
    namespace PSTADE_ADL_BARRIER_name(Id) { \
    } \
    using namespace PSTADE_ADL_BARRIER_name(Id); \
    namespace PSTADE_ADL_BARRIER_name(Id) \
/**/


#define PSTADE_ADL_BARRIER_name(Id) \
    BOOST_PP_CAT(pstade_adl_barrier_of_, Id) \
/**/


// Deprecated
//
#if !defined(BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP)

    #define PSTADE_ADL_BARRIER_OPEN(Id) \
        namespace PSTADE_ADL_BARRIER_name(Id) { \
        } \
        using namespace PSTADE_ADL_BARRIER_name(Id); \
        namespace PSTADE_ADL_BARRIER_name(Id) { \
    /**/

    #define PSTADE_ADL_BARRIER_CLOSE(Id) \
        } \
    /**/

#else

    #define PSTADE_ADL_BARRIER_OPEN(Id) \
    /**/

    #define PSTADE_ADL_BARRIER_CLOSE(Id) \
    /**/

#endif // !defined(BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP)


#endif

#ifndef PSTADE_FAT_DETAIL_BINARY_PRED_HPP
#define PSTADE_FAT_DETAIL_BINARY_PRED_HPP
#include "./prefix.hpp"


// PStade.Fat
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <pstade/egg/object.hpp>


#define PSTADE_FAT_BINARY_PRED(F, Op) \
    struct BOOST_PP_CAT(op_, F) \
    { \
        typedef bool result_type; \
        \
        template<class X, class Y> \
        bool operator()(X const& x, Y const& y) const \
        { \
            return x Op y; \
        } \
    }; \
    \
    PSTADE_EGG_OBJECT((BOOST_PP_CAT(op_,F)), F) = { }; \
/**/


#endif

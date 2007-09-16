#ifndef PSTADE_EGG_DETAIL_DEFAULT_VALUE_HPP
#define PSTADE_EGG_DETAIL_DEFAULT_VALUE_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade { namespace egg {


    template<class Value>
    struct default_value
    {
        Value m_value;

        typedef Value result_type;

        template<class ArgTuple>
        Value operator()(ArgTuple const&) const
        {
            return m_value;
        }
    };


} } // namespace pstade::egg


#endif

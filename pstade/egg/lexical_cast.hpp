#ifndef PSTADE_EGG_LEXICAL_CAST_HPP
#define PSTADE_EGG_LEXICAL_CAST_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/lexical_cast.hpp>
#include <pstade/adl_barrier.hpp>
#include "./specified.hpp"


namespace pstade { namespace egg {


    template<class To>
    struct X_lexical_cast
    {
        typedef X_lexical_cast function_type;
        typedef To result_type;

        template<class From>
        To operator()(From const& from) const
        {
            return boost::lexical_cast<To>(from);
        }
    };


    PSTADE_ADL_BARRIER(lexical_cast) { // for 'boost'
        PSTADE_EGG_SPECIFIED1(lexical_cast, X_lexical_cast, (class))
    }


} } // namespace pstade::egg


#endif

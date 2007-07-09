#ifndef PSTADE_EGG_NUMERIC_CAST_HPP
#define PSTADE_EGG_NUMERIC_CAST_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/assert.hpp>
#include <boost/numeric/conversion/cast.hpp> // numeric_cast
#include <boost/type_traits/is_integral.hpp>
#include <pstade/adl_barrier.hpp>
#include "./specified.hpp"


namespace pstade { namespace egg {


    template<class To>
    struct xp_numeric_cast
    {
        typedef To result_type;

        template<class From>
        To operator()(From const& from) const
        {
            return boost::numeric_cast<To>(from);
        }
    };


    PSTADE_ADL_BARRIER(numeric_cast) { // for 'boost'
        PSTADE_EGG_SPECIFIED1(numeric_cast, xp_numeric_cast, (class))
    }


} } // namespace pstade::egg


#endif

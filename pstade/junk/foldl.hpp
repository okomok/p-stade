#ifndef PSTADE_OVEN_FOLDL_HPP
#define PSTADE_OVEN_FOLDL_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <numeric> // accumulate
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pod_constant.hpp>


namespace pstade { namespace oven {


namespace foldl_detail {


    struct baby
    {
        template< class F, class Z, class Range >
        struct apply :
            pass_by_value<Z>
        { };

        template< class F, class Z, class Range >
        Result call(F& f, Z& z, Range& rng) const
        {
            return std::accumulate(boost::begin(rng), boost::end(rng), z, f);
        }
    };


} // namespace foldl_detail


typedef egg::function<foldl_detail::baby> op_foldl;
PSTADE_POD_CONSTANT((op_foldl), foldl) = {{}};


} } // namespace pstade::oven


#endif

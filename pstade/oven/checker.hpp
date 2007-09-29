#ifndef PSTADE_OVEN_CHECKER_HPP
#define PSTADE_OVEN_CHECKER_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/function.hpp>
#include <pstade/egg/make_function.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "./begin_end.hpp"
#include "./checked.hpp"
#include "./concepts.hpp"


namespace pstade { namespace oven {


namespace checker_detail {


    struct baby
    {
        template< class Myself, class Range, class Begin = op_begin const >
        struct apply :
            result_of<
                Begin(typename result_of<op_make_checked(Range&)>::type)
            >
        { };

        template< class Result, class Range, class Begin >
        Result call(Range& rng, Begin& beg) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            return beg(make_checked(rng));
        }

        template< class Result, class Range >
        Result call(Range& rng) const
        {
            return egg::make_function(*this)(rng, begin);
        }
    };


} // namespace checker_detail


typedef egg::function<checker_detail::baby> op_checker;
PSTADE_POD_CONSTANT((op_checker), checker) = {{}};


} } // namespace pstade::oven


#endif

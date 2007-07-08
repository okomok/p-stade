#ifndef PSTADE_OVEN_CONVERTED_HPP
#define PSTADE_OVEN_CONVERTED_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/deduced_const.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/identity.hpp>
#include <pstade/egg/specified.hpp>
#include <pstade/result_of.hpp>
#include "./concepts.hpp"
#include "./transformed.hpp"


namespace pstade { namespace oven {


template< class To >
struct tp_make_converted
{
    struct baby
    {
        template< class Myself, class Range >
        struct apply :
            result_of<
                xp_make_transformed<To>(Range&, egg::op_identity const&)
            >
        { };

        template< class Result, class Range >
        Result call(Range& rng) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            return xp_make_transformed<To>()(rng, egg::identity);
        }
    };

    typedef egg::function<baby> type;
};


template< class To >
struct xp_make_converted :
    tp_make_converted<To>::type
{ };


PSTADE_EGG_SPECIFIED1(make_converted, xp_make_converted, (class))


namespace converted_detail_ {


    template< class To >
    struct converted
    {
    private:
        converted& operator=(converted const&);    
    };


    template< class Range, class To > inline
    typename result_of<xp_make_converted<To>(Range&)>::type
    operator|(Range& rng, converted<To>)
    {
        return xp_make_converted<To>()(rng);
    }

    template< class Range, class To > inline
    typename result_of<xp_make_converted<To>(PSTADE_DEDUCED_CONST(Range)&)>::type
    operator|(Range const& rng, converted<To>)
    {
        return xp_make_converted<To>()(rng);
    }


} // namespace converted_detail_


using converted_detail_::converted;


} } // namespace pstade::oven


#endif

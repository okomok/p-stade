#ifndef PSTADE_OVEN_CONVERTED_HPP
#define PSTADE_OVEN_CONVERTED_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/functional.hpp> // identity
#include <pstade/specified.hpp>
#include "./concepts.hpp"
#include "./transformed.hpp"


namespace pstade { namespace oven {


template< class To >
struct op_make_converted :
    callable< op_make_converted<To> >
{
    template< class Myself, class Range >
    struct apply :
        boost::result_of<
            op_make_transformed<To>(Range&, op_identity const&)
        >
    { };

    template< class Result, class Range >
    Result call(Range& rng) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
        return op_make_transformed<To>()(rng, identity);
    }
};


PSTADE_SPECIFIED1(make_converted, op_make_converted, 1)


namespace converted_detail_ {


    template< class To >
    struct converted
    {
    private:
        converted& operator=(converted const&);    
    };


    template< class Range, class To > inline
    typename boost::result_of<op_make_converted<To>(Range&)>::type
    operator|(Range& rng, converted<To>)
    {
        return op_make_converted<To>()(rng);
    }

    template< class Range, class To > inline
    typename boost::result_of<op_make_converted<To>(PSTADE_DEDUCED_CONST(Range)&)>::type
    operator|(Range const& rng, converted<To>)
    {
        return op_make_converted<To>()(rng);
    }


} // namespace converted_detail_


using converted_detail_::converted;


} } // namespace pstade::oven


#endif

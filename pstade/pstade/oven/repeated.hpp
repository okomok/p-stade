#ifndef PSTADE_OVEN_REPEATED_HPP
#define PSTADE_OVEN_REPEATED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/utility/result_of.hpp>
#include <pstade/function.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include "./as_single.hpp"
#include "./cycled.hpp"


namespace pstade { namespace oven {


namespace repeated_detail {


    template< class Value, class Size >
    struct baby
    {
        typedef typename
            boost::result_of<
                op_make_cycled(typename boost::result_of<op_as_single(Value&)>::type, Size&)
            >::type
        result_type;

        result_type operator()(Value& v, Size& sz) const
        {
            return make_cycled(as_single(v), sz);
        }
    };


} // namespace repeated_detail


PSTADE_FUNCTION(make_repeated, (repeated_detail::baby<_, _>))
PSTADE_PIPABLE(repeated, (op_make_repeated))


} } // namespace pstade::oven


#endif

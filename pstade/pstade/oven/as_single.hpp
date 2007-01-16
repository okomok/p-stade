#ifndef PSTADE_OVEN_AS_SINGLE_HPP
#define PSTADE_OVEN_AS_SINGLE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// The constant-iterator is the same as the mutable-iterator.
// Const-ness of this range muste be independent from
// const-ness of the 'Value'.


#include <boost/utility/addressof.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace as_single_detail {


    template< class Value >
    struct baby
    {
        typedef
            iter_range<Value *> const
        result;

        result call(Value& v)
        {
            return result(boost::addressof(v), boost::addressof(v) + 1);
        }
    };


} // namespace as_single_detail


PSTADE_FUNCTION(make_as_single, (as_single_detail::baby<_>))
PSTADE_PIPABLE(as_single, (op_make_as_single))


} } // namespace pstade::oven


#endif

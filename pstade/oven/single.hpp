#ifndef PSTADE_OVEN_SINGLE_HPP
#define PSTADE_OVEN_SINGLE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// The constant-iterator is the same as the mutable-iterator.
// Const-ness of this range must be independent from const-ness of the 'X'.


#include "./detail/prelude.hpp"
#include <boost/utility/addressof.hpp>
#include <pstade/function.hpp>
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace single_detail {


    template< class X >
    struct baby
    {
        typedef
            iter_range<X *> const
        result_type;

        result_type operator()(X& x) const
        {
            return result_type(boost::addressof(x), boost::addressof(x) + 1);
        }
    };


} // namespace single_detail


PSTADE_FUNCTION(single, (single_detail::baby<_>))


} } // namespace pstade::oven


#endif

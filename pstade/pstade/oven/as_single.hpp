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
#include <pstade/auxiliary.hpp>
#include <pstade/function.hpp>
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace as_single_detail {


    template< class X >
    struct baby
    {
        typedef
            iter_range<X *> const
        result;

        result call(X& x)
        {
            return result(boost::addressof(x), boost::addressof(x) + 1);
        }
    };


} // namespace as_single_detail


PSTADE_AUXILIARY0(as_single, (function< as_single_detail::baby<boost::mpl::_> >))


} } // namespace pstade::oven


#endif

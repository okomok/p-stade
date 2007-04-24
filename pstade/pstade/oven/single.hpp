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


#include <boost/utility/addressof.hpp>
#include <pstade/auxiliary.hpp>
#include <pstade/callable.hpp>
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace single_detail {


    struct op :
        callable<op>
    {
        template< class Myself, class X >
        struct apply
        {
            typedef
                iter_range<X *> const
            type;
        };

        template< class Result, class X >
        Result call(X& x) const
        {
            return Result(boost::addressof(x), boost::addressof(x) + 1);
        }
    };


} // namespace single_detail


PSTADE_AUXILIARY(0, single, (single_detail::op))


} } // namespace pstade::oven


#endif

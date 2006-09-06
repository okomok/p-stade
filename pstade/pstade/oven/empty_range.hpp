#ifndef PSTADE_OVEN_EMPTY_RANGE_HPP
#define PSTADE_OVEN_EMPTY_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/iterator_range.hpp>
#include <pstade/nullptr.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./range_constantable.hpp"


namespace pstade { namespace oven {


template< class Value >
struct empty_range :
    boost::iterator_range<Value *>,
    private range_constantable<empty_range<Value>, Value const *>,
    private as_lightweight_proxy< empty_range<Value> >
{
    typedef Value const *const_iterator;

private:
    typedef boost::iterator_range<Value *> super_t;
    typedef typename super_t::iterator iter_t;

public:
    empty_range() :
        super_t(iter_t(PSTADE_NULLPTR), iter_t(PSTADE_NULLPTR))
    { }
};


} } // namespace pstade::oven


#endif

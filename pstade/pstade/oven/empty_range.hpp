#ifndef PSTADE_OVEN_EMPTY_RANGE_HPP
#define PSTADE_OVEN_EMPTY_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/implicitly_defined.hpp>
#include <pstade/nullptr.hpp>
#include "./iter_range.hpp"
#include "./lightweight_copyable.hpp"
#include "./range_constantable.hpp"


namespace pstade { namespace oven {


template< class Value >
struct empty_range;


namespace empty_range_detail {


    template< class Value >
    struct super_
    {
        typedef
            iter_range<Value *,
                range_constantable  < empty_range<Value>, Value const *,
                lightweight_copyable< empty_range<Value> > >
            >
        type;
    };


} // namespace empty_range_detail


template< class Value >
struct empty_range :
    empty_range_detail::super_<Value>::type 
{
    typedef Value const *const_iterator;

private:
    typedef typename empty_range_detail::super_<Value>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    empty_range() :
        super_t(iter_t(PSTADE_NULLPTR), iter_t(PSTADE_NULLPTR))
    { }

    PSTADE_IMPLICITLY_DEFINED_COPY_TO_BASE(empty_range, super_t)
};


} } // namespace pstade::oven


#endif

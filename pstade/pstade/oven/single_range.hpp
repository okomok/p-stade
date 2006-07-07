#ifndef PSTADE_OVEN_SINGLE_RANGE_HPP
#define PSTADE_OVEN_SINGLE_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/iterator_range.hpp>
#include <boost/utility/addressof.hpp>
#include "./is_lightweight_proxy.hpp"


namespace pstade { namespace oven {


template< class Value >
struct single_range :
    boost::iterator_range<Value *>
{
private:
    typedef boost::iterator_range<Value *> super_t;

public:
    explicit single_range(Value& v) :
        super_t(boost::addressof(v), boost::addressof(v) + 1)
    { }
};


template< class Value > inline
single_range<Value> const
make_single_range(Value& v)
{
    return single_range<Value>(v);
}


template< class Value > inline
single_range<Value const> const
make_single_range(Value const& v)
{
    return single_range<Value const>(v);
}


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::single_range, 1)


#endif

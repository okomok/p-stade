#ifndef PSTADE_OVEN_DUMMY_RANGE_HPP
#define PSTADE_OVEN_DUMMY_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/iterator_range.hpp>
#include "./dummy_iterator.hpp"
#include "./lightweight_proxy.hpp"


namespace pstade { namespace oven {


namespace dummy_range_detail {


    template< class Incrementable, class Value >
    struct super_
    {
        typedef boost::iterator_range<
            dummy_iterator<Incrementable, Value>
        > type;
    };


} // namespace dummy_range_detail


template< class Incrementable, class Value >
struct dummy_range :
    dummy_range_detail::super_<Incrementable, Value>::type,
    private lightweight_proxy< dummy_range<Incrementable, Value> >
{
private:
    typedef typename dummy_range_detail::super_<Incrementable, Value>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    dummy_range(Incrementable n, Incrementable m) :
        super_t(iter_t(n), iter_t(m))
    { }
};


template< class Value, class Incrementable > inline
dummy_range<Incrementable, Value> const
make_dummy_range(Incrementable n, Incrementable m)
{
    return dummy_range<Incrementable, Value>(n, m);
}


} } // namespace pstade::oven


#endif

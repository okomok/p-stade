#ifndef PSTADE_OVEN_COUNTING_RANGE_HPP
#define PSTADE_OVEN_COUNTING_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/iterator/counting_iterator.hpp>
#include <pstade/if_debug.hpp>
#include <pstade/instance.hpp>
#include <pstade/unused.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace counting_range_detail {


    template< class Incrementable > inline
    void check_range(Incrementable const& i, Incrementable const& j, boost::single_pass_traversal_tag)
    {
        pstade::unused(i, j);
    }


    template< class Incrementable > inline
    void check_range(Incrementable const& i, Incrementable const& j, boost::random_access_traversal_tag)
    {
        BOOST_ASSERT(i <= j);
        pstade::unused(i, j);
    }


    template<
        class Incrementable,
        class CategoryOrTraversal,
        class Difference
    >
    struct super_ :
        iter_range<
            boost::counting_iterator<Incrementable, CategoryOrTraversal, Difference>
        >
    { };


} // namespace counting_range_detail


template<
    class Incrementable,
    class CategoryOrTraversal = boost::use_default,
    class Difference          = boost::use_default
>
struct counting_range :
    counting_range_detail::super_<Incrementable, CategoryOrTraversal, Difference>::type,
    private as_lightweight_proxy< counting_range<Incrementable, CategoryOrTraversal, Difference> >
{
private:
    typedef typename counting_range_detail::super_<Incrementable, CategoryOrTraversal, Difference>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    counting_range(Incrementable const& i, Incrementable const& j) :
        super_t(iter_t(i), iter_t(j))
    {
        typedef typename boost::iterator_traversal<iter_t>::type trv_t;
        PSTADE_IF_DEBUG( counting_range_detail::check_range(i, j, trv_t()); )
    }
};


template< class Incrementable > inline
counting_range<Incrementable> const
make_counting_range(Incrementable const& i, Incrementable const& j)
{
    return counting_range<Incrementable>(i, j);
}


// Note:
// 'make_counting_range(0, non_int_t(i))' doesn't compile.
// 'make_counting_range(non_int_t(0), non_int_t(i))' compiles,
// but seems cumbersome, especially if 'non_int_t' is 
// not easy to know. Also note that something like 'int_range'
// would get stuck into a hell of cast. So we define...
//

template< class Incrementable > inline
counting_range<Incrementable> const
from_0_to(Incrementable const& c)
{
    return counting_range<Incrementable>(0, c);
}

template< class Incrementable > inline
counting_range<Incrementable> const
from_1_to(Incrementable const& c)
{
    return counting_range<Incrementable>(1, c);
}


} } // namespace pstade::oven


#endif

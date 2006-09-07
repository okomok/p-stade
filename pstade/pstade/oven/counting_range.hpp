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
#include <boost/iterator/iterator_categories.hpp>
#include <boost/range/iterator_range.hpp>
#include <pstade/instance.hpp>
#include <pstade/unused.hpp>
#include "./as_lightweight_proxy.hpp"


namespace pstade { namespace oven {


namespace counting_range_detail {


    template< class Incrementable > inline
    void check_range(Incrementable i, Incrementable j, boost::single_pass_traversal_tag)
    {
        pstade::unused(i, j);
    }


    template< class Incrementable > inline
    void check_range(Incrementable i, Incrementable j, boost::random_access_traversal_tag)
    {
        BOOST_ASSERT(i <= j);
        pstade::unused(i, j);
    }


    template< class Incrementable, class CategoryOrTraversal, class Difference >
    struct super_
    {
        typedef boost::iterator_range<
            boost::counting_iterator<Incrementable, CategoryOrTraversal, Difference>
        > type;
    };


} // namespace counting_range_detail


template<
    class Incrementable,
    class CategoryOrTraversal = boost::use_default,
    class Difference = boost::use_default
>
struct counting_range :
    counting_range_detail::super_<Incrementable, CategoryOrTraversal, Difference>::type,
    private as_lightweight_proxy< counting_range<Incrementable, CategoryOrTraversal, Difference> >
{
private:
    typedef typename counting_range_detail::super_<Incrementable, CategoryOrTraversal, Difference>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    counting_range(Incrementable i, Incrementable j) :
        super_t(iter_t(i), iter_t(j))
    {
        typedef typename boost::iterator_traversal<iter_t>::type trv_t;
        counting_range_detail::check_range(i, j, trv_t());
    }
};


template< class Incrementable > inline
counting_range<Incrementable> const
make_counting_range(Incrementable i, Incrementable j)
{
    return counting_range<Incrementable>(i, j);
}



template< class Incrementable1, class Incrementable2 >
counting_range<int> const
int_range(Incrementable1 i, Incrementable2 j)
{
    return counting_range<int>(static_cast<int>(i), static_cast<int>(j));
};


/*
struct int_range :
    counting_range<int>
{
    template< class Incrementable1, class Incrementable2 >
    counting_range<int>(Incrementable1 i, Incrementable2 j) :
        super_t(static_cast<int>(i), static_cast<int>(j))
    { }
};
*/


} } // namespace pstade::oven


#endif

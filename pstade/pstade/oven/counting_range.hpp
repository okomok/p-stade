#ifndef PSTADE_OVEN_COUNTING_RANGE_HPP
#define PSTADE_OVEN_COUNTING_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/range/iterator_range.hpp>
#include <pstade/unused.hpp>
#include "./counting_iterator.hpp"
#include "./lightweight_proxy.hpp"


namespace pstade { namespace oven {


namespace counting_range_detail {


    template< class Incrementable > inline
    void check_range(Incrementable n, Incrementable m, boost::single_pass_traversal_tag)
    {
        pstade::unused(n, m);
    }


    template< class Incrementable > inline
    void check_range(Incrementable n, Incrementable m, boost::random_access_traversal_tag)
    {
        BOOST_ASSERT(n <= m);
        pstade::unused(n, m);
    }


    template< class Incrementable, class CategoryOrTraversal, class Difference >
    struct super_
    {
        typedef boost::iterator_range<
            counting_iterator<Incrementable, CategoryOrTraversal, Difference>
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
    private lightweight_proxy< counting_range<Incrementable, CategoryOrTraversal, Difference> >
{
private:
    typedef typename counting_range_detail::super_<Incrementable, CategoryOrTraversal, Difference>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    counting_range(Incrementable n, Incrementable m) :
        super_t(iter_t(n), iter_t(m))
    {
        typedef typename boost::iterator_traversal<iter_t>::type trv_t;
        counting_range_detail::check_range(n, m, trv_t());
    }
};


template< class Incrementable > inline
counting_range<Incrementable> const
make_counting_range(Incrementable n, Incrementable m)
{
    return counting_range<Incrementable>(n, m);
}


template< class Incrementable > inline
counting_range<Incrementable> const
zero_to(Incrementable c)
{
    return counting_range<Incrementable>(0, c);
}


template< class Incrementable > inline
counting_range<Incrementable> const
one_to(Incrementable c)
{
    return counting_range<Incrementable>(1, c);
}


} } // namespace pstade::oven


#endif

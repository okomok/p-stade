#ifndef PSTADE_OVEN_COUNTING_RANGE_HPP
#define PSTADE_OVEN_COUNTING_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <stdexcept> // range_error
#include <string>
#include <boost/iterator/counting_iterator.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/mpl/if.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/throw_exception.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <pstade/unused.hpp>
#include "./is_lightweight_proxy.hpp"


namespace pstade { namespace oven {


namespace counting_range_detail {


    template< class Iterator >
    struct is_bounds_checkable :
        boost::is_convertible<
            typename boost::iterator_traversal<Iterator>::type,
            boost::random_access_traversal_tag
        >
    { };


    template< class Incrementable >
    struct no_bounds_check
    {
        static void call(Incrementable n, Incrementable m)
        {
            pstade::unused(n, m);
        }
    };


    template< class Incrementable >
    struct bounds_check
    {
        static void call(Incrementable n, Incrementable m)
        {
            if (n > m) {
                std::range_error err("pstade::oven::counting_range - out of range");
                boost::throw_exception(err);
            }
        }
    };


    template< class Incrementable, class Iterator >
    struct bounds_checker :
        boost::mpl::if_< is_bounds_checkable<Iterator>,
            bounds_check<Incrementable>,
            no_bounds_check<Incrementable>
        >::type
    { };


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
    counting_range_detail::super_<Incrementable, CategoryOrTraversal, Difference>::type
{
private:
    typedef typename counting_range_detail::super_<Incrementable, CategoryOrTraversal, Difference>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    explicit counting_range(Incrementable n, Incrementable m) :
        super_t(iter_t(n), iter_t(m))
    {
        counting_range_detail::bounds_checker<Incrementable, iter_t>::call(n, m);
    }
};


template< class Incrementable > inline const
counting_range<Incrementable>
make_counting_range(Incrementable n, Incrementable m)
{
    return counting_range<Incrementable>(n, m);
}


template< class Incrementable > inline const
counting_range<Incrementable>
zero_to(Incrementable c)
{
    return counting_range<Incrementable>(0, c);
}


template< class Incrementable > inline const
counting_range<Incrementable>
one_to(Incrementable c)
{
    return counting_range<Incrementable>(1, c);
}


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::counting_range, 3)


#endif

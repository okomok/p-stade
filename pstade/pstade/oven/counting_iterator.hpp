#ifndef PSTADE_OVEN_COUNTING_ITERATOR_HPP
#define PSTADE_OVEN_COUNTING_ITERATOR_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Why not: 'boost::counting_iterator'
//
// It returns a reference to a value object that is part
// of the iterator object itself, and has the same lifetime as the iterator.
// http://lists.boost.org/Archives/boost/2001/03/9789.php


// Note:
//
// Strictly speaking, this doesn't conform to Forward Iterator Concept.


#include <boost/iterator/counting_iterator.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/type_traits/remove_reference.hpp>


namespace pstade { namespace oven {


template<
    class Incrementable,
    class CategoryOrTraversal,
    class Difference
>
struct counting_iterator;


namespace counting_iterator_detail {


    template<
        class Incrementable,
        class CategoryOrTraversal,
        class Difference
    >
    struct super_
    {
        typedef boost::counting_iterator<Incrementable, CategoryOrTraversal, Difference> base_t;

        typedef boost::iterator_adaptor<
            counting_iterator<Incrementable, CategoryOrTraversal, Difference>,
            base_t,
            boost::use_default,
            boost::use_default,
            typename boost::remove_reference<typename base_t::reference>::type // turn off the bummer!
        > type;
    };


} // namespace counting_iterator_detail


template<
    class Incrementable,
    class CategoryOrTraversal = boost::use_default,
    class Difference = boost::use_default
>
struct counting_iterator :
    counting_iterator_detail::super_<Incrementable, CategoryOrTraversal, Difference>::type
{
private:
    typedef typename counting_iterator_detail::super_<Incrementable, CategoryOrTraversal, Difference>::type super_t;
    
public:
    counting_iterator()
    { }

    counting_iterator(Incrementable x) :
        super_t(x)
    { }

private:
friend class boost::iterator_core_access;
    // as is
};


template< class Incrementable > inline
counting_iterator<Incrementable> const
make_counting_iterator(Incrementable x)
{
  return counting_iterator<Incrementable>(x);
}


} } // namespace pstade::oven


#endif

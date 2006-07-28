#ifndef PSTADE_OVEN_COUNTING_ITERATOR_HPP
#define PSTADE_OVEN_COUNTING_ITERATOR_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// VS: 'boost::counting_iterator'
//
// Boost's returns a reference to a value object that is part
// of the iterator object itself, and has the same lifetime as the iterator.
// (http://lists.boost.org/Archives/boost/2001/03/9789.php)
// Thus, it is legal, but cannot work with 'reverse_iterator' etc.
// On the other hand, Oven's doesn't conform to the *legacy* forward iterator concept,
// but can work well with them.


#include <boost/iterator/counting_iterator.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_traits.hpp> // iterator_category
#include <boost/type_traits/remove_reference.hpp>
#include <pstade/adl_barrier.hpp>


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
            typename boost::iterator_category<base_t>::type, // forceful category
            typename boost::remove_reference<typename base_t::reference>::type
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


PSTADE_ADL_BARRIER(counting_iterator) { // for Boost


    template< class Incrementable > inline
    counting_iterator<Incrementable> const
    make_counting_iterator(Incrementable x)
    {
      return counting_iterator<Incrementable>(x);
    }


} // ADL barrier


} } // namespace pstade::oven


#endif

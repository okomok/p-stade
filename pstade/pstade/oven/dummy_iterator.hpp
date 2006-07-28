#ifndef PSTADE_OVEN_DUMMY_ITERATOR_HPP
#define PSTADE_OVEN_DUMMY_ITERATOR_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <pstade/nullptr.hpp>
#include "./counting_iterator.hpp"


namespace pstade { namespace oven {


template< class Incrementable, class Value >
struct dummy_iterator;


namespace dummy_iterator_detail {


    template< class Incrementable, class Value >
    struct super_
    {
        typedef boost::iterator_adaptor<
            dummy_iterator<Incrementable, Value>,
            counting_iterator<Incrementable>,
            Value
        > type;
    };


} // namespace dummy_iterator_detail


template< class Incrementable, class Value >
struct dummy_iterator :
    dummy_iterator_detail::super_<Incrementable, Value>::type
{
private:
    typedef typename dummy_iterator_detail::super_<Incrementable, Value>::type super_t;
    typedef typename super_t::reference ref_t;

public:
    dummy_iterator()
    { }

    dummy_iterator(Incrementable i) :
        super_t(i)
    { }

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        BOOST_ASSERT("dummy_iterator dereferenced" && false);

        Value *pval = PSTADE_NULLPTR;
        return *pval;
    }
};


template< class Value, class Incrementable > inline
dummy_iterator<Incrementable, Value> const
make_dummy_iterator(Incrementable i)
{
    return dummy_iterator<Incrementable, Value>(i);
}


} } // namespace pstade::oven


#endif

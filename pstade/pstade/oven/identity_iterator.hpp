#ifndef PSTADE_OVEN_IDENTITY_ITERATOR_HPP
#define PSTADE_OVEN_IDENTITY_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/mpl/assert.hpp>
#include <pstade/dont_care.hpp>
#include <pstade/is_convertible.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/use_default.hpp>
#include "./detail/pure_traversal.hpp"


namespace pstade { namespace oven {


template< class Iterator, class Traversal >
struct identity_iterator;


namespace identity_iterator_detail {


    template<
        class Iterator,
        class Traversal
    >
    struct super_
    {
        typedef typename detail::pure_traversal<Iterator>::type base_trv_t;
        typedef typename use_default_to<Traversal, base_trv_t>::type trv_t;
        BOOST_MPL_ASSERT((is_convertible<base_trv_t, trv_t>));

        typedef
            boost::iterator_adaptor<
                identity_iterator<Iterator, Traversal>,
                Iterator,
                boost::use_default,
                trv_t
            >
        type;
    };


} // namespace identity_iterator_detail


template<
    class Iterator,
    class Traversal = boost::use_default
>
struct identity_iterator :
    identity_iterator_detail::super_<Iterator, Traversal>::type
{
private:
    typedef typename identity_iterator_detail::super_<Iterator, Traversal>::type super_t;

public:
    explicit identity_iterator()
    { }

    explicit identity_iterator(Iterator const& it, dont_care = 0) :
        super_t(it)
    { }

    template< class I, class T >
    identity_iterator(identity_iterator<I, T> const& other,
        typename boost::enable_if_convertible<I, Iterator>::type * = 0
    ) :
        super_t(other.base())
    { }

friend class boost::iterator_core_access;
    // as is.
};


PSTADE_OBJECT_GENERATOR(make_identity_iterator,
    (identity_iterator< deduce<_1, to_value>, deduce<_2, to_value, boost::use_default> >) const)


} } // namespace pstade::oven


#endif

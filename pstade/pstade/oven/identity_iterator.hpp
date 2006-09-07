#ifndef PSTADE_OVEN_IDENTITY_ITERATOR_HPP
#define PSTADE_OVEN_IDENTITY_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_adaptor.hpp>


namespace pstade { namespace oven {


template< class Iterator, class CategoryOrTraversal >
struct identity_iterator;


namespace identity_iterator_detail {


    template< class Iterator, class CategoryOrTraversal >
    struct super_
    {
        typedef boost::iterator_adaptor<
            identity_iterator<Iterator, CategoryOrTraversal>,
            Iterator,
            boost::use_default,
            CategoryOrTraversal
        > type;
    };


} // namespace identity_iterator_detail


template<
    class Iterator,
    class CategoryOrTraversal = boost::use_default
>
struct identity_iterator :
    identity_iterator_detail::super_<Iterator, CategoryOrTraversal>::type
{
private:
    typedef typename identity_iterator_detail::super_<Iterator, CategoryOrTraversal>::type super_t;

public:
    explicit identity_iterator(Iterator const& it) :
        super_t(it)
    { }

    template< class Iterator_ >
    identity_iterator(
        identity_iterator<Iterator_> const& other,
        typename boost::enable_if_convertible<Iterator_, Iterator>::type * = 0
    ) :
        super_t(other.base())
    { }

friend class boost::iterator_core_access;
    // as is.
};


template< class Iterator, class CategoryOrTraversal > inline
identity_iterator<Iterator, CategoryOrTraversal> const
make_identity_iterator(Iterator const& it, CategoryOrTraversal)
{
    return identity_iterator<Iterator, CategoryOrTraversal>(it);
}


template< class Iterator > inline
identity_iterator<Iterator> const
make_identity_iterator(Iterator const& it)
{
    return identity_iterator<Iterator>(it);
}


} } // namespace pstade::oven


#endif

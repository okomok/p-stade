#ifndef PSTADE_OVEN_REVERSE_ITERATOR_HPP
#define PSTADE_OVEN_REVERSE_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Replaces 'boost::reverse_iterator' for the workaround of
// http://std.dkuug.dk/jtc1/sc22/wg21/docs/lwg-defects.html#198


#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/optional.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/object_generator.hpp>
#include "./detail/next_prior.hpp" // prior


namespace pstade { namespace oven {


template< class BidiIter >
struct reverse_iterator;


namespace reverse_iterator_detail {


    template< class BidiIter >
    struct super_
    {
        typedef
            boost::iterator_adaptor<
                reverse_iterator<BidiIter>,
                BidiIter
            >
        type;
    };


} // namespace reverse_iterator_detail


template< class BidiIter >
struct reverse_iterator :
    reverse_iterator_detail::super_<BidiIter>::type
{
private:
    typedef typename reverse_iterator_detail::super_<BidiIter>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename super_t::difference_type diff_t;

public:
    explicit reverse_iterator()
    { }

    explicit reverse_iterator(BidiIter const& it) :
        super_t(it)
    { }

    template< class BidiIter_ >
    reverse_iterator(
        reverse_iterator<BidiIter_> const& other,
        typename boost::enable_if_convertible<BidiIter_, BidiIter>::type * = 0
    ) :
        super_t(other.base())
    { }

private:
    mutable boost::optional<BidiIter> m_cache;

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        if (!m_cache)
            m_cache = detail::prior(this->base());

        return **m_cache;
    }

    void increment()
    {
        --this->base_reference();
        m_cache.reset();
    }

    void decrement()
    {
        ++this->base_reference();
        m_cache.reset();
    }

    void advance(diff_t const& d)
    {
        this->base_reference() += -d;
        m_cache.reset();
    }

    template< class BidiIter_ >
    diff_t distance_to(reverse_iterator<BidiIter_> const& other) const
    {
        return this->base() - other.base();
    }
};


PSTADE_ADL_BARRIER(reverse_iterator) { // for Boost

PSTADE_OBJECT_GENERATOR(make_reverse_iterator,
    (reverse_iterator< deduce<_1, to_value> >) const)

} // ADL barrier


} } // namespace pstade::oven


#endif

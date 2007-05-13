#ifndef PSTADE_OVEN_SHARED_LVALUE_ITERATOR_HPP
#define PSTADE_OVEN_SHARED_LVALUE_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_traits.hpp> // iterator_value
#include <boost/shared_ptr.hpp>


namespace pstade { namespace oven {


template< class Iterator >
struct shared_lvalue_iterator;


namespace shared_lvalue_iterator_detail {


    template< class Iterator >
    struct traversal :
        boost::detail::pure_traversal_tag< // makes 'facade_iterator_category' recompute.
            typename boost::iterator_traversal<Iterator>::type
        >
    { };


    template< class Iterator >
    struct super_
    {
        typedef typename
            boost::iterator_value<Iterator>::type
        value_t;

        typedef
            boost::iterator_adaptor<
                shared_lvalue_iterator<Iterator>,
                Iterator,
                value_t,
                typename traversal<Iterator>::type,
                value_t const&
            >
        type;
    };


} // namespace shared_lvalue_iterator_detail


template< class Iterator >
struct shared_lvalue_iterator :
    shared_lvalue_iterator_detail::super_<Iterator>::type
{
private:
    typedef typename shared_lvalue_iterator_detail::super_<Iterator>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename super_t::value_type val_t;

public:
    explicit shared_lvalue_iterator()
    { }

    explicit shared_lvalue_iterator(Iterator const& it) :
        super_t(it)
    { }

    template< class Iterator_ >
    shared_lvalue_iterator(
        shared_lvalue_iterator<Iterator_> const& other,
        typename boost::enable_if_convertible<Iterator_, Iterator>::type * = 0
    ) :
        super_t(other.base())
    { }

private:
    mutable boost::shared_ptr<val_t> m_pval;

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        if (!m_pval)
            m_pval.reset(new val_t(*this->base()));

        return *m_pval;
    }

    void increment()
    {
        ++this->base_reference();
        m_pval.reset();
    }

    void decrement()
    {
        --this->base_reference();
        m_pval.reset();
    }

    template< class Difference >
    void advance(Difference d)
    {
        this->base_reference() += d;
        m_pval.reset();
    }
};


template< class Iterator > inline
shared_lvalue_iterator<Iterator> const
make_shared_lvalue_iterator(Iterator const& it)
{
    return shared_lvalue_iterator<Iterator>(it);
}


} } // namespace pstade::oven


#endif

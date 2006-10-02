#ifndef PSTADE_OVEN_SET_UNION_ITERATOR_HPP
#define PSTADE_OVEN_SET_UNION_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/functional.hpp> // less
#include "./detail/constant_reference.hpp"
#include "./merge_iterator.hpp"


namespace pstade { namespace oven {


template<
    class Iterator1, class Iterator2,
    class BinaryPred
>
struct set_union_iterator;


namespace set_union_iterator_detail {


    template<
        class Iterator1, class Iterator2,
        class BinaryPred
    >
    struct super_
    {
        typedef boost::iterator_adaptor<
            set_union_iterator<Iterator1, Iterator2, BinaryPred>,
            Iterator1,
            boost::use_default,
            typename merge_iterator_detail::traversal<Iterator1, Iterator2>::type,
            typename detail::constant_reference<Iterator1>::type
        > type;
    };


} // namespace set_union_iterator_detail


template<
    class Iterator1, class Iterator2,
    class BinaryPred = less_fun
>
struct set_union_iterator :
    set_union_iterator_detail::super_<Iterator1, Iterator2, BinaryPred>::type
{
private:
    typedef typename set_union_iterator_detail::super_<Iterator1, Iterator2, BinaryPred>::type super_t;
    typedef typename super_t::reference ref_t;

public:
    set_union_iterator()
    { }

    set_union_iterator(
        Iterator1 const& it1, Iterator1 const& last1,
        Iterator2 const& it2, Iterator2 const& last2,
        BinaryPred const& pred = pstade::less
    ) :
        super_t(it1), m_last1(last1),
        m_it2(it2),   m_last2(last2),
        m_pred(pred)
    { }

template< class, class, class > friend struct set_union_iterator;
    template< class Iterator1_, class Iterator2_ >
    set_union_iterator(
        set_union_iterator<Iterator1_, Iterator2_, BinaryPred> const& other,
        typename boost::enable_if_convertible<Iterator1_, Iterator1>::type * = 0,
        typename boost::enable_if_convertible<Iterator2_, Iterator2>::type * = 0
    ) :
        super_t(other.base()), m_last1(other.m_last1), 
        m_it2(other.m_it2),    m_last2(other.m_last2),
        m_pred(other.m_pred)
    { }

private:
    Iterator1 m_last1;
    Iterator2 m_it2, m_last2;
    BinaryPred m_pred;

    template< class Other >
    bool is_compatible(Other const& other) const
    {
        return m_last1 == other.m_last1 && m_last2 == other.m_last2;
    }

    bool is_end1() const
    {
        return this->base() == m_last1;
    }

    bool is_end2() const
    {
        return m_it2 == m_last2;
    }

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        BOOST_ASSERT(!(is_end1() && is_end2()));

        if (is_end1())
            return *m_it2;
        else if (is_end2())
            return *this->base();

        // Note:
        // If the values are same, SGI STL implementation prefers
        // the value of 'm_it1', but Oven prefers 'm_it2'.
        return merge_iterator_detail::min_(*this->base(), *m_it2, m_pred);
    }

    template< class Other >
    bool equal(Other const& other) const
    {
        BOOST_ASSERT(is_compatible(other));
        return this->base() == other.base() && m_it2 == other.m_it2;
    }

    void increment()
    {
        BOOST_ASSERT(!(is_end1() && is_end2()));

        if (is_end1())
            ++m_it2;
        else if (is_end2())
            ++this->base_reference();
        else if (m_pred(*this->base(), *m_it2))
            ++this->base_reference();
        else if (m_pred(*m_it2, *this->base()))
            ++m_it2;
        else
            ++this->base_reference(), ++m_it2;
    }
};


template< class BinaryPred, class Iterator1, class Iterator2 > inline
set_union_iterator<Iterator1, Iterator2, BinaryPred> const
make_set_union_iterator(
    Iterator1 const& it1, Iterator1 const& last1,
    Iterator2 const& it2, Iterator2 const& last2,
    BinaryPred pred)
{
    return set_union_iterator<Iterator1, Iterator2, BinaryPred>(
        it1, last1, it2, last2, pred);
}


template< class Iterator1, class Iterator2 > inline
set_union_iterator<Iterator1, Iterator2> const
make_set_union_iterator(
    Iterator1 const& it1, Iterator1 const& last1,
    Iterator2 const& it2, Iterator2 const& last2)
{
    return set_union_iterator<Iterator1, Iterator2>(
        it1, last1, it2, last2);
}


} } // namespace pstade::oven


#endif

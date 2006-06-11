#ifndef PSTADE_OVEN_JOINT_ITERATOR_HPP
#define PSTADE_OVEN_JOINT_ITERATOR_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iterator> // advance, distance
#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/reverse_iterator.hpp>
#include <boost/tuple/tuple.hpp>
#include "./detail/minimum_traversal_type.hpp"


namespace pstade { namespace oven {


template< class Iterator1, class Iterator2 >
struct joint_iterator;


namespace joint_iterator_detail {


    template< class Iterator1, class Iterator2 >
    struct traversal
    {
        typedef boost::tuple<Iterator1, Iterator2> iters_t;
        typedef typename detail::
            minimum_traversal<iters_t>::type
        type;
    };


    template< class Iterator1, class Iterator2 >
    struct super_
    {
        typedef boost::iterator_adaptor<
            joint_iterator<Iterator1, Iterator2>,
            Iterator1,
            boost::use_default,
            typename traversal<Iterator1, Iterator2>::type
        > type;
    };


    template< class Iterator1, class Iterator2 >
    void increment(Iterator1& it1, Iterator2& it2, Iterator1 last1)
    {
        if (it1 != last1)
            ++it1;
        else
            ++it2;
    }


    template< class Difference, class Iterator1, class Iterator2 >
    void advance(Iterator1& it1, Iterator2& it2, Difference diff, Iterator1 last1)
    {
        BOOST_ASSERT(diff >= 0);

        if (it1 != last1) {
            Difference d1 = std::distance(it1, last1);
            if (diff > d1) {
                it1 = last1;
                std::advance(it2, diff - d1);
            }
            else {
                std::advance(it1, diff);
            }
        }
        else {
            std::advance(it2, diff);
        }
    }


} // namespace joint_iterator_detail


template< class Iterator1, class Iterator2  >
struct joint_iterator :
    joint_iterator_detail::super_<Iterator1, Iterator2>::type
{
private:
    typedef joint_iterator self_t;
    typedef typename joint_iterator_detail::super_<Iterator1, Iterator2>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename super_t::difference_type diff_t;
    typedef typename super_t::base_type base_t;

public:
    explicit joint_iterator()
    { }

    explicit joint_iterator(
        Iterator1 it1, Iterator1 last1,
        Iterator2 first2, Iterator2 it2
    ) :
        super_t(it1), m_last1(last1),
        m_first2(first2), m_it2(it2)
    { }

template< class, class > friend struct joint_iterator;
    template< class Iterator1_, class Iterator2_ >
    joint_iterator(
        joint_iterator<Iterator1_, Iterator2_> other,
        typename boost::enable_if_convertible<Iterator1_, Iterator1>::type * = 0,
        typename boost::enable_if_convertible<Iterator2_, Iterator2>::type * = 0
    ) :
        super_t(other.base()), m_last1(other.m_last1), 
        m_first2(other.m_first2), m_it2(other.m_it2)
    { }

private:
    base_t m_last1; Iterator2 m_first2; // the joint point
    Iterator2 m_it2;

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        BOOST_ASSERT(valid());

        if (this->base() != m_last1)
            return *this->base();
        else
            return *m_it2;
    }

    bool equal(self_t other) const
    {
        BOOST_ASSERT(valid());
        BOOST_ASSERT(other.valid());
        BOOST_ASSERT(m_last1 == other.m_last1 && m_first2 == other.m_first2 &&
            "incompatible iterators"
        );

        return
            this->base() == other.base() &&
            m_it2 == other.m_it2
        ;
    }

    void increment()
    {
        BOOST_ASSERT(valid());

        joint_iterator_detail::increment(this->base_reference(), m_it2, m_last1);
    }

    void decrement()
    {
        BOOST_ASSERT(valid());

        boost::reverse_iterator<Iterator2> it1(m_it2), last1(m_first2);
        boost::reverse_iterator<base_t> it2(this->base());
        joint_iterator_detail::increment(it1, it2, last1);
        this->base_reference() = it2.base();
        m_it2 = it1.base();
    }

    void advance(diff_t d)
    {
        BOOST_ASSERT(valid());

        if (d >= 0) {
            joint_iterator_detail::advance(this->base_reference(), m_it2, d, m_last1);
        }
        else {
            boost::reverse_iterator<Iterator2> rit1(m_it2), rlast1(m_first2);
            boost::reverse_iterator<base_t> rit2(this->base());
            joint_iterator_detail::advance(rit1, rit2, -d, rlast1);
            this->base_reference() = rit2.base();
            m_it2 = rit1.base();
        }
    }

    diff_t distance_to(self_t other) const
    {
        BOOST_ASSERT(valid());
        BOOST_ASSERT(other.valid());

        if (is_in_range1() && other.is_in_range1())
            return std::distance(this->base(), other.base());
        else if (!is_in_range1() && !other.is_in_range1())
            return std::distance(m_it2, other.m_it2);
        else if (is_in_range1())
            return std::distance(this->base(), m_last1) + std::distance(other.m_first2, other.m_it2);
        else if (!is_in_range1())
            return std::distance(m_it2, m_first2) + std::distance(other.m_last1, other.base());
        else {
            BOOST_ASSERT(false && "when pigs fly.");
            return 0;
        }
    }

private:
    bool valid() const
    { return (!is_in_range1() || m_it2 == m_first2); }

    bool is_in_range1() const
    { return this->base() != m_last1; }
};


template< class Iterator1, class Iterator2 > inline const
joint_iterator<Iterator1, Iterator2>
make_joint_first_iterator(Iterator1 it1, Iterator1 last1, Iterator2 first2)
{
    return joint_iterator<Iterator1, Iterator2>(it1, last1, first2, first2);
}


template< class Iterator1, class Iterator2 > inline const
joint_iterator<Iterator1, Iterator2>
make_joint_second_iterator(Iterator1 last1, Iterator2 first2, Iterator2 it2)
{
    return joint_iterator<Iterator1, Iterator2>(last1, last1, first2, it2);
}


} } // namespace pstade::oven


#endif

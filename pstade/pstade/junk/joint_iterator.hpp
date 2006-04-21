#ifndef PSTADE_OVEN_JOINT_ITERATOR_HPP
#define PSTADE_OVEN_JOINT_ITERATOR_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/zip_iterator.hpp> // detail::minimum_traversal_category_in_iterator_tuple
#include <boost/tuple/tuple.hpp>


namespace pstade { namespace oven {


template< class LeftIter, class RightIter >
struct joint_iterator;


namespace joint_iterator_detail {


    template< class LeftIter, class RightIter >
    struct traversal_tag
    {
        typedef boost::tuple<LeftIter, RightIter> iter_tuple_t;
        typedef typename boost::detail::
            minimum_traversal_category_in_iterator_tuple<iter_tuple_t>::type
        type;
    };


    template< class LeftIter, class RightIter >
    struct super_
    {
        typedef boost::iterator_adaptor<
            joint_iterator<LeftIter, RightIter>,
            LeftIter,
            boost::use_default,
            typename traversal_tag<LeftIter, RightIter>::type
        > type;
    };


    #define PSTADE_OVEN_JOINT_RANGE_IF_DEBUG(X) // X


} // namespace joint_iterator_detail


template< class LeftIter, class RightIter  >
struct joint_iterator :
    joint_iterator_detail::super_<LeftIter, RightIter>::type
{
private:
    typedef joint_iterator self_t;
    typedef typename joint_iterator_detail::super_<LeftIter, RightIter>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename super_t::difference_type diff_t;
    typedef typename super_t::base_type base_t;

public:
    template< class LeftIter2, class RightIter2 >
    joint_iterator(
        LeftIter2 left, RightIter2 right,
        LeftIter2 leftLast, RightIter2 rightFirst
    ) :
        super_t(left), m_right(right),
        m_leftLast(leftLast), m_rightFirst(rightFirst)
    { }

/*
    template< class LeftIter2, class RightIter2 >
    joint_iterator(
        LeftIter2 left, LeftIter2 leftLast, RightIter2 rightFirst
    ) :
        super_t(left), m_right(rightLast),
        m_leftLast(leftLast), m_rightFirst(rightFirst)
    { }

    template< class LeftIter2, class RightIter2 >
    joint_iterator(
        RightIter2 right, LeftIter2 leftLast, RightIter2 rightFirst
    ) :
        super_t(leftLast), m_right(right),
        m_leftLast(leftLast), m_rightFirst(rightFirst)
    { }
*/

    template< class OtherIter > // normal iterator! (always on right, no bounds)
    joint_iterator(OtherIter other) :
        super_t(other), m_leftLast(other),
        m_right(other), m_rightFirst(other)
    { }

    template< class LeftIter2, class RightIter2 >
    joint_iterator(
        joint_iterator<LeftIter2, RightIter2> other,
        typename boost::enable_if_convertible<LeftIter, LeftIter2>::type * = 0,
        typename boost::enable_if_convertible<RightIter, RightIter2>::type * = 0
    ) :
        super_t(other.base()), m_right(other.right_begin()), 
        m_leftLast(other.left_end()), m_rightFirst(other.right_begin())
    { }

public:
    const LeftIter left_end() const
    { return m_leftLast; }
    
    const RightIter right_begin() const
    { return m_rightFirst; };

    bool is_on_left() const
    { 
        return this->base() != m_leftLast;
    }

private:
    RightIter m_right;
    base_t m_leftLast; RightIter m_rightFirst; // the joint point

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        BOOST_ASSERT(valid());

        if (is_on_left()) {
            return *this->base();
        }
        else {
            return *m_right;
        }
    }

    bool equal(self_t other) const
    {
        BOOST_ASSERT(valid());

        BOOST_ASSERT(
            m_leftLast == other.m_leftLast &&
            m_rightFirst == other.m_rightFirst &&
            "incompatible iterators compared"
        );

        return
            this->base() == other.base() &&
            m_right == other.m_right
        ;
    }

    void increment()
    {
        BOOST_ASSERT(valid());

        PSTADE_OVEN_JOINT_RANGE_IF_DEBUG (
            self_t itmp(*this);
        )

        if (is_on_left())
            ++this->base_reference();
        else
            ++m_right;

        PSTADE_OVEN_JOINT_RANGE_IF_DEBUG (
            itmp.advance(1);
            itmp == *this;
        )
    }

    void decrement()
    {
        BOOST_ASSERT(valid());

        PSTADE_OVEN_JOINT_RANGE_IF_DEBUG (
            self_t itmp(*this);
        )

        if (is_on_left() || m_right == m_rightFirst)
            --this->base_reference();
        else
            --m_right;

        PSTADE_OVEN_JOINT_RANGE_IF_DEBUG (
            itmp.advance(-1);
            itmp == *this;
        )
    }

    // random_access_traversal
    //
    void advance(diff_t d)
    {
        BOOST_ASSERT(valid());

        if (d >= 0) {
            if (is_on_left()) {
                diff_t left_d = m_leftLast - this->base();
                if (d > left_d) {
                    this->base_reference() = m_leftLast;
                    m_right += d - left_d;
                }
                else {
                    this->base_reference() += d;
                }
            }
            else {
                m_right += d;
            }
        }
        else {
            d = -d;
            if (is_on_left()) {
                this->base_reference() -= d;
            }
            else {
                diff_t right_d = m_right - m_rightFirst;
                if (d > right_d) {
                    m_right = m_rightFirst;
                    this->base_reference() -= d - right_d;
                }
                else {
                    m_right -= d;
                }
            }
        }
    }

    diff_t distance_to(const self_t& other) const
    {
        BOOST_ASSERT(valid());
        BOOST_ASSERT(other.valid());

        if (is_on_left() && other.is_on_left())
            return std::distance(this->base(), other.base());
        else if (!is_on_left() && !other.is_on_left())
            return std::distance(this->m_right, other.m_right);
        else if (is_on_left())
            return std::distance(this->base(), m_leftLast) + std::distance(other.m_rightFirst, other.m_right);
        else if (!is_on_left())
            return std::distance(m_right, m_rightFirst) + std::distance(other.m_leftLast, other.base());
        else {
            BOOST_ASSERT(false);
            return 0;
        }
    }

private:
    bool valid() const
    {
        return (!is_on_left() || m_right == m_rightFirst);
    }
};


template< class LeftIter, class RightIter > inline const
joint_iterator<LeftIter, RightIter>
make_joint_iterator(
    LeftIter left, RightIter right,
    LeftIter leftLast, RightIter rightFirst
)
{
    return joint_iterator<LeftIter, RightIter>(
        left, right,
        leftLast, rightFirst
    );
}


template< class LeftIter, class RightIter > inline const
joint_iterator<LeftIter, RightIter>
make_joint_left_iterator(
    LeftIter left,
    LeftIter leftLast, RightIter rightFirst
)
{
    return joint_iterator<LeftIter, RightIter>(
        left, rightFirst,
        leftLast, rightFirst
    );
}


template< class LeftIter, class RightIter > inline const
joint_iterator<LeftIter, RightIter>
make_joint_right_iterator(
    RightIter right,
    LeftIter leftLast, RightIter rightFirst
)
{
    return joint_iterator<LeftIter, RightIter>(
        leftLast, right,
        leftLast, rightFirst
    );
}


} } // namespace pstade::oven


#endif

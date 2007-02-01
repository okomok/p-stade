#ifndef PSTADE_OVEN_RECURSION_HPP
#define PSTADE_OVEN_RECURSION_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/function.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/optional.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/function.hpp>
#include <pstade/is_same.hpp>
#include "./begin_end.hpp"
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_difference.hpp"
#include "./range_reference.hpp"
#include "./range_traversal.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


namespace recursion_detail {


    template< class Iterator >
    struct delay_iterator;


    template< class Range >
    struct delay_iterator_super
    {
        typedef
            boost::iterator_facade<
                delay_iterator<Range>,
                typename range_value<Range>::type,
                typename range_pure_traversal<Range>::type,
                typename range_reference<Range>::type,
                typename range_difference<Range>::type
            >
        type;
    };


    template< class Range >
    struct delay_iterator :
        delay_iterator_super<Range>::type
    {
    private:
        typedef typename delay_iterator_super<Range>::type super_t;
        typedef typename super_t::reference ref_t;
        typedef typename super_t::difference_type diff_t;

    public:
        delay_iterator()
        { }

        template< class GetIter >
        delay_iterator(Range& rng, GetIter const& getIter) :
            m_prng(boost::addressof(rng)), m_getIter(getIter)
        { }

        typedef typename range_iterator<Range>::type base_type;

        base_type const& base() const
        {
            return base_reference();
        }

        Range& base_range() const
        {
            return *m_prng;
        }

    private:
        Range *m_prng;
        boost::function<base_type(Range&)> m_getIter;
        mutable boost::optional<base_type> m_obase;

        template< class Other >
        bool is_compatible(Other const& other) const
        {
            return is_same(*m_prng, other.base_range());
        }

        void init_base() const
        {
            if (!m_obase)
                m_obase = m_getIter(*m_prng);
        }

        base_type& base_reference()
        {
            init_base();
            return *m_obase;
        }

        base_type const& base_reference() const
        {
            init_base();
            return *m_obase;
        }

    friend class boost::iterator_core_access;
        ref_t dereference() const
        {
            return *base();
        }

        template< class Other >
        bool equal(Other const& other) const
        {
            return false;
            //BOOST_ASSERT(is_compatible(other));
            //return base() == other.base();
        }

        void increment()
        {
            ++base_reference();
        }

        void decrement()
        {
            --base_reference();
        }

        void advance(diff_t const& d)
        {
            base_reference() += d;
        }

        template< class Other >
        diff_t distance_to(Other const& other) const
        {
            BOOST_ASSERT(is_compatible(other));
            return other.base() - base();
        }
    };


    template< class Range >
    struct baby
    {
        typedef
            delay_iterator<Range>
        iter_t;

        typedef
            iter_range<iter_t> const
        result;

        result call(Range& rng)
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            return result(iter_t(rng, begin), iter_t(rng, end));
        }
    };


} // recursion_detail


PSTADE_FUNCTION(recursion, (recursion_detail::baby<_>))


} } // namespace pstade::oven


#endif

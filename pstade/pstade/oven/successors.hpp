#ifndef PSTADE_OVEN_SUCCESORS_HPP
#define PSTADE_OVEN_SUCCESORS_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/as.hpp>
#include <pstade/function.hpp>
#include <pstade/functional.hpp> // identity
#include <pstade/has_xxx.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./detail/constant_reference.hpp"
#include "./detail/minimum_pure.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace successors_detail {


    namespace here = successors_detail;


    template< class Iterator, class BinaryFun >
    struct succeed_iterator;


    PSTADE_HAS_TYPE(is_constant)


    template< class Iterator, class BinaryFun >
    struct succeed_iterator_super
    {
        typedef
            boost::iterator_adaptor<
                succeed_iterator<Iterator, BinaryFun>,
                Iterator,
                boost::use_default,
                typename detail::minimum_pure<
                    boost::forward_traversal_tag,
                    typename boost::iterator_traversal<Iterator>::type
                >::type,
                typename boost::mpl::eval_if< has_is_constant<BinaryFun>,
                    detail::constant_reference<Iterator>,
                    boost::mpl::identity<boost::use_default>
                >::type
            >
        type;
    };


    template< class Iterator, class Traversal = typename detail::pure_traversal<Iterator>::type >
    struct op_assert_not_old
    {
        Iterator operator()(Iterator const& now) const
        {
            BOOST_ASSERT(m_old != now);
            return now;
        }

        explicit op_assert_not_old(Iterator const& old) :
            m_old(old)
        { }

    private:
        Iterator m_old;
    };

    template< class Iterator >
    struct op_assert_not_old<Iterator, boost::single_pass_traversal_tag> :
        op_identity
    {
        explicit op_assert_not_old(Iterator const&)
        { }
    };

#if !defined(NDEBUG)
    template< class Iterator > inline
    op_assert_not_old<Iterator> assert_not_old(Iterator const& old)
    {
        return op_assert_not_old<Iterator>(old);
    }
#else
    template< class Iterator> inline
    op_identity const& assert_not_old(Iterator const&)
    {
        return identity;
    }
#endif


    template< class Iterator, class BinaryFun >
    struct succeed_iterator :
        succeed_iterator_super<Iterator, BinaryFun>::type
    {
    private:
        typedef typename succeed_iterator_super<Iterator, BinaryFun>::type super_t;
        typedef typename super_t::reference ref_t;

    public:
        succeed_iterator()
        { }

        succeed_iterator(Iterator const& it, BinaryFun const& elector, Iterator const& last) :
            super_t(it), m_elector(elector), m_last(last)
        { }

        template< class F >
        succeed_iterator(succeed_iterator<F, BinaryFun> const& other,
            typename boost::enable_if_convertible<F, Iterator>::type * = 0
        ) :
            super_t(other.base()), m_elector(other.elector()), m_last(other.end())
        { }

        BinaryFun const& elector() const
        {
            return m_elector;
        }

        Iterator const& end() const
        {
            return m_last;
        }

    private:
        BinaryFun m_elector;
        Iterator m_last;

        template< class Other >
        bool is_compatible(Other const& other) const
        {
            return m_last == other.end();
        }

        bool is_end() const
        {
            return this->base() == m_last;
        }

    friend class boost::iterator_core_access;
        ref_t dereference() const
        {
            BOOST_ASSERT(!is_end());
            return *this->base();
        }

        template< class F >
        bool equal(succeed_iterator<F, BinaryFun> const& other) const
        {
            BOOST_ASSERT(is_compatible(other));
            return this->base() == other.base();
        }

        void increment()
        {
            BOOST_ASSERT(!is_end());
            this->base_reference() = here::assert_not_old(this->base())(
                m_elector(this->base(), as_cref(m_last))
            );
        }
    };


    template< class Range, class BinaryFun >
    struct baby
    {
        typedef
            succeed_iterator<
                typename range_iterator<Range>::type,
                typename pass_by_value<BinaryFun>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(Range& rng, BinaryFun& elector) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

            return result_type(
               iter_t(boost::begin(rng), elector, boost::end(rng)),
               iter_t(boost::end(rng),   elector, boost::end(rng))
            );
        }
    };


} // namespace successors_detail


PSTADE_FUNCTION(make_successors, (successors_detail::baby<_, _>))
PSTADE_PIPABLE(successors, (op_make_successors))


} } // namespace pstade::oven


#endif


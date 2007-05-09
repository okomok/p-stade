#ifndef PSTADE_OVEN_FUZIPPED_HPP
#define PSTADE_OVEN_FUZIPPED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Copyright David Abrahams and Thomas Becker 2000-2006. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/version.hpp>
#if BOOST_VERSION >= 103500


#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/fusion/sequence/conversion/as_vector.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/mpl.hpp>
#include <boost/fusion/sequence/view/transform_view.hpp>
#include <boost/mpl/placeholders.hpp> // missing from 'minimum_category.hpp'
#include <boost/iterator/detail/minimum_category.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/affect.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include <pstade/polymorphic.hpp>
#include <pstade/remove_cvr.hpp>
#include "./begin_end.hpp"
#include "./deref.hpp"
#include "./detail/pure_traversal.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace fuzipped_detail {


    namespace fusion = boost::fusion;
    namespace mpl = boost::mpl;


    struct increment_iterator
    {
        template< class Iterator >
        void operator()(Iterator& it) const
        {
            ++it;
        }
    };

    struct decrement_iterator
    {
        template< class Iterator >
        void operator()(Iterator& it) const
        {
            --it;
        }
    };

    template< class Difference >
    struct advance_iterator
    {
        template< class Iterator >
        void operator()(Iterator& it) const
        {
            it += m_n;
        }

        explicit advance_iterator(Difference n) :
            m_n(n)
        { }

    private:
        Difference m_n;
    };


    struct dereference_iterator
    {
        template< class Iterator >
        struct result :
            boost::iterator_reference<Iterator>
        { };

        template< class Iterator >
        typename result<Iterator>::type
        operator()(Iterator const& it) const
        {
            return *it;
        }
    };


    template< class IteratorSeq >
    struct zip_iterator;


    template< class IteratorSeq >
    struct zip_iterator_super
    {
        typedef
            typename fusion::result_of::transform<
                IteratorSeq const,
                dereference_iterator
                // For some reason, gcc-3.4 dislikes this...
                // typename boost::result_of<op_polymorphic(op_deref const&)>::type
            >::type
        val_t;

        typedef typename
            boost::iterator_difference<
                typename mpl::front<IteratorSeq>::type
            >::type
        diff_t;

        typedef typename
            mpl::fold<
                typename mpl::transform_view< IteratorSeq, detail::pure_traversal<mpl::_1> >::type,
                boost::random_access_traversal_tag,
                boost::detail::minimum_category<>
            >::type
        trv_t;

        typedef
            boost::iterator_facade<
                zip_iterator<IteratorSeq>,
                val_t,
                trv_t,
                val_t,
                diff_t
            >
        type;
    };


    template< class IteratorSeq >
    struct zip_iterator :
        zip_iterator_super<IteratorSeq>::type
    {
    private:
        typedef typename zip_iterator_super<IteratorSeq>::type super_t;
        typedef typename super_t::reference ref_t;
        typedef typename super_t::difference_type diff_t;

    public:
        explicit zip_iterator()
        { }

        explicit zip_iterator(IteratorSeq const& its) :
            m_its(its)
        { }

        template< class I >
        zip_iterator(zip_iterator<I> const& other,
            typename boost::enable_if_convertible<I, IteratorSeq>::type * = 0
        ) :
            m_its(other.iterator_sequence())
        { }

        IteratorSeq const& iterator_sequence() const
        {
            return m_its;
        }

    private:
        IteratorSeq m_its;

    friend class boost::iterator_core_access;
        ref_t dereference() const
        {
            return fusion::transform(m_its, dereference_iterator());
            // return fusion::transform(m_its, polymorphic(deref));
        }

        template< class I >
        bool equal(zip_iterator<I> const& other) const
        {
            return m_its == other.iterator_sequence();
        }

        void increment()
        {
            fusion::for_each(m_its, increment_iterator());
        }

        void decrement()
        {
            fusion::for_each(m_its, decrement_iterator());
        }

        void advance(diff_t n)
        {
            fusion::for_each(m_its, advance_iterator<diff_t>(n));
        }

        template< class I >
        diff_t distance_to(zip_iterator<I> const& other) const
        {
            return *fusion::begin(other.iterator_sequence()) - *fusion::begin(m_its);
        }
    };


    template< class RangeSeq >
    struct baby
    {
        // Prefer a view to 'transform', keeping the mutability of elements.
        typedef
            fusion::transform_view<
                RangeSeq,
                typename boost::result_of<op_polymorphic(op_begin const&)>::type
            >
        begin_iters_t;

        typedef
            fusion::transform_view<
                RangeSeq,
                typename boost::result_of<op_polymorphic(op_end const&)>::type
            >
        end_iters_t;

        typedef
            zip_iterator<
                // Copy the iterators by 'as_vector', following 'boost::zip_iterator'.
                typename fusion::result_of::as_vector<begin_iters_t>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(RangeSeq& seq) const
        {
            begin_iters_t begin_iters(seq, polymorphic(begin));
            end_iters_t end_iters(seq, polymorphic(end));

            return result_type(
                iter_t( fusion::as_vector(begin_iters) ),
                iter_t( fusion::as_vector(end_iters) )
            );
        }
    };


} // namespace fuzipped_detail


PSTADE_FUNCTION(make_fuzipped, (fuzipped_detail::baby<_>))
PSTADE_PIPABLE(fuzipped, (op_make_fuzipped))


} } // namespace pstade::oven


#endif // #if BOOST_VERSION >= 103500


#endif

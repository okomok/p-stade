#ifndef PSTADE_OVEN_ADJACENT_TRANSFORMED_HPP
#define PSTADE_OVEN_ADJACENT_TRANSFORMED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// The Adaptor version of 'std::adjacent_difference'.


// Question:
//
// See "../../libs/oven/example/adjacent_difference.cpp".
// Should this contain the first value of base range?
// This is symmetrical to 'scanned', which requires
// the first value to be passed. So, it's intuitive
// not to contain the first value of base range, IMO.


#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/range/empty.hpp>
#include <boost/type.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/deferred.hpp>
#include <pstade/fuse.hpp>
#include <pstade/pack.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include <pstade/remove_cvr.hpp>
#include <pstade/use_default.hpp>
#include "./concepts.hpp"
#include "./dropped.hpp"
#include "./popped.hpp"
#include "./range_iterator.hpp"
#include "./range_traversal.hpp"
#include "./read.hpp"
#include "./transformed.hpp"
#include "./zipped.hpp"


namespace pstade { namespace oven {


namespace adjacent_transformed_detail {


    template< class Iterator, class BinaryFun, class Reference, class Value >
    struct adjacent_transform_iterator;


    template< class Iterator, class BinaryFun, class Reference, class Value >
    struct adjacent_transform_iterator_super
    {
        typedef
            boost::iterator_adaptor<
                adjacent_transform_iterator<Iterator, BinaryFun, Reference, Value>,
                Iterator,
                Value,
                boost::single_pass_traversal_tag,
                Reference
            >
        type;
    };


    struct begin_tag { };
    struct end_tag { };


    template< class Iterator, class BinaryFun, class Reference, class Value >
    struct adjacent_transform_iterator :
        adjacent_transform_iterator_super<Iterator, BinaryFun, Reference, Value>::type
    {
    private:
        typedef typename adjacent_transform_iterator_super<Iterator, BinaryFun, Reference, Value>::type super_t;
        typedef typename super_t::reference ref_t;
        typedef typename boost::iterator_value<Iterator>::type base_value_t;

    public:
        adjacent_transform_iterator(Iterator it, BinaryFun fun, begin_tag) :
            super_t(it), m_fun(fun)
        {
            increment();
        }

        adjacent_transform_iterator(Iterator it, BinaryFun fun, end_tag) :
            super_t(it), m_fun(fun)
        { }

    template < class, class, class, class > friend struct adjacent_transform_iterator;
        template< class I, class R, class V >
        adjacent_transform_iterator(adjacent_transform_iterator<I, BinaryFun, R, V> const& other,
            typename boost::enable_if_convertible<I, Iterator>::type * = 0
        ) :
            super_t(other.base()), m_fun(other.m_fun), m_prev(other.m_prev)
        { }

        BinaryFun function() const
        {
            return m_fun;
        }

    private:
        BinaryFun m_fun;
        base_value_t m_prev;

    friend class boost::iterator_core_access;
        ref_t dereference() const
        {
            return m_fun(m_prev, read(this->base()));
        }

        void increment()
        {
            m_prev = read(this->base());
            ++this->base_reference();
        }
    };


    template< class Range, class BinaryFun, class Reference, class Value >
    struct make_single_pass
    {
        typedef typename
            range_iterator<Range>::type
        base_iter_t;

        typedef typename
            pass_by_value<BinaryFun>::type
        fun_t;

        typedef typename
            boost::iterator_value<base_iter_t>::type
        base_value_t;

        typedef typename
            iterator_read<base_iter_t>::type
        read_t;

        typedef typename
            use_default_eval_to<
                Reference,
                boost::result_of<
                    PSTADE_DEFERRED(fun_t const)(base_value_t const&, read_t)
                >
            >::type
        ref_t;

        typedef typename
            use_default_eval_to<
                Value,
                remove_cvr<ref_t>
            >::type
        val_t;

        typedef
            adjacent_transform_iterator<
                base_iter_t, fun_t, val_t, ref_t
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        type;
    };


    template< class Range, class BinaryFun, class Reference, class Value >
    struct make_multi_pass :
        boost::result_of<
            op_make_transformed<Reference, Value>(
                typename boost::result_of<
                    op_make_zipped(
                        typename boost::result_of<
                            op_pack(
                                typename boost::result_of<op_make_popped(Range&)>::type,
                                typename boost::result_of<op_make_dropped(Range&, int)>::type
                            )
                        >::type
                    )
                >::type,
                typename boost::result_of<op_fuse(BinaryFun&)>::type
            )
        >
    { };


} // namespace adjacent_transformed_detail


template<
    class Reference = boost::use_default,
    class Value     = boost::use_default
>
struct op_make_adjacent_transformed :
    callable< op_make_adjacent_transformed<Reference, Value> >
{
    template< class Myself, class Range, class BinaryFun >
    struct apply :
        boost::mpl::eval_if<
            boost::is_convertible<
                typename range_traversal<Range>::type, boost::forward_traversal_tag
            >,
            adjacent_transformed_detail::make_multi_pass<Range, BinaryFun, Reference, Value>,
            adjacent_transformed_detail::make_single_pass<Range, BinaryFun, Reference, Value>
        >
    { };

    template< class Result, class Range, class BinaryFun >
    Result call(Range& rng, BinaryFun& fun) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
        BOOST_ASSERT(!boost::empty(rng));
        return aux(boost::type<Result>(), rng, fun, typename range_traversal<Range>::type());
    }

    template< class Result, class Range, class BinaryFun >
    Result aux(boost::type<Result>, Range& rng, BinaryFun& fun, boost::forward_traversal_tag) const
    {
        PSTADE_CONCEPT_ASSERT((Forward<Range>));

        return
            op_make_transformed<Reference, Value>()(
                make_zipped(
                    pack(make_popped(rng), make_dropped(rng, 1))
                ),
                fuse(fun)
            );
    }

    template< class Result, class Range, class BinaryFun >
    Result aux(boost::type<Result>, Range& rng, BinaryFun& fun, boost::single_pass_traversal_tag) const
    {
        typedef typename Result::iterator iter_t;
        return Result(
            iter_t(boost::begin(rng), fun, adjacent_transformed_detail::begin_tag()), 
            iter_t(boost::end(rng),   fun, adjacent_transformed_detail::end_tag())
        );
    }
};


PSTADE_CONSTANT(make_adjacent_transformed, (op_make_adjacent_transformed<>))
PSTADE_PIPABLE(adjacent_transformed, (op_make_adjacent_transformed<>))


} } // namespace pstade::oven


#endif

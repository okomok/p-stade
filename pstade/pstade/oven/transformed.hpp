#ifndef PSTADE_OVEN_TRANSFORMED_HPP
#define PSTADE_OVEN_TRANSFORMED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Consider the following simple functor.
//
// struct id
// {
//     typedef int const& result_type;
//     result_type operator()(int const& x) const
//     { return x; }
// };
//
// A transformed range whose 'reference' is 'int'(non-reference)
// cannot work with this functor because of dangling reference.
// A transformed range's 'reference' type is sometimes
// orthogonal to functor's 'result_type'.


// References:
//
// [1] Eric Niebler, transform_range, Boost.RangeEx, 2004.
// [2] David Abrahams, Jeremy Siek, Thomas Witt, transform_iterator, Boost.Iterator, 2003.


#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/constable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include <pstade/remove_cvr.hpp>
#include <pstade/use_default.hpp>
#include "./concepts.hpp"
#include "./detail/pure_traversal.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace transformed_detail {


    // IteratorCategory must be recomputed using 'detail::pure_traversal'.
    // For example, consider 'rng|zipped|unzipped'.
    // 'UnaryFun' may resurrect lvalue-ness of the base range,
    // then a RandomAccess*Input* Iterator can turn into the RandomAccess.
    // Though 'identities' can do the same thing, this will compile faster.


    template< class UnaryFun, class Iterator, class Reference, class Value >
    struct transform_iterator;


    template< class UnaryFun, class Iterator, class Reference, class Value >
    struct transform_iterator_super
    {
        typedef
            boost::iterator_adaptor<
                transform_iterator<UnaryFun, Iterator, Reference, Value>,
                Iterator,
                Value,
                typename detail::pure_traversal<Iterator>::type,
                Reference
            >
        type;
    };


    template< class UnaryFun, class Iterator, class Reference, class Value >
    struct transform_iterator :
        transform_iterator_super<UnaryFun, Iterator, Reference, Value>::type
    {
    private:
        typedef typename transform_iterator_super<UnaryFun, Iterator, Reference, Value>::type super_t;

    public:
        transform_iterator()
        { }

        transform_iterator(Iterator it, UnaryFun fun) :
            super_t(it), m_fun(fun)
        { }

        template< class I, class R, class V >
        transform_iterator(transform_iterator<UnaryFun, I, R, V> const& other,
            typename boost::enable_if_convertible<I, Iterator>::type * = 0
        ) :
            super_t(other.base()), m_fun(other.function())
        { }

        UnaryFun function() const
        {
            return m_fun;
        }

        // boost compatible
        UnaryFun functor() const
        {
            return function();
        }

    private:
        UnaryFun m_fun;

    friend class boost::iterator_core_access;
        typename super_t::reference dereference() const
        {
            return m_fun(*this->base());
        }
    };


} // namespace transformed_detail


template<
    class Reference = boost::use_default,
    class Value     = boost::use_default
>
struct op_make_transformed :
    callable< op_make_transformed<Reference, Value> >
{
    template< class Myself, class Range, class UnaryFun >
    struct apply
    {
        typedef typename
            range_iterator<Range>::type
        base_iter_t;

        typedef typename
            pass_by_value<UnaryFun>::type
        fun_t;

        typedef typename
            boost::iterator_reference<base_iter_t>::type
        base_ref_t;

        typedef typename
            use_default_eval_to<
                Reference,
                boost::result_of<PSTADE_CONSTABLE_TPL(fun_t const)(base_ref_t)>
            >::type
        ref_t;

        typedef typename
            use_default_eval_to<
                Value,
                remove_cvr<ref_t>
            >::type
        val_t;

        typedef
            transformed_detail::transform_iterator<
                fun_t,
                base_iter_t,
                ref_t,
                val_t
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        type;
    };

    template< class Result, class Range, class UnaryFun >
    Result call(Range& rng, UnaryFun& fun) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

        typedef typename Result::iterator iter_t;
        return Result(
            iter_t(boost::begin(rng), fun),
            iter_t(boost::end(rng),   fun)
        );
    }
};


PSTADE_CONSTANT(make_transformed, (op_make_transformed<>))
PSTADE_PIPABLE(transformed, (op_make_transformed<>))


} } // namespace pstade::oven


#endif

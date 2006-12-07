#ifndef PSTADE_OVEN_TRANSFORM_RANGE_HPP
#define PSTADE_OVEN_TRANSFORM_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Port of: Boost.RangeEx
//
// Copyright 2004 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Boost.Iterator doesn't use 'result_of'.
// 'result_of' seems to have many problems
// even under modern compilers. But we must go!


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
// cannot work this functor because of dangling reference.
// A transformed range's 'reference' type is sometimes
// orthogonal to functor's 'result_type'.


#include <boost/iterator/iterator_traits.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/pipable.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/singleton.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace transform_range_detail {


    template< class Iterator, class UnaryFun >
    struct default_reference
    {
        typedef typename boost::iterator_reference<Iterator>::type ref_t;
        typedef typename boost::result_of<UnaryFun(ref_t)>::type type;
    };


    template<
        class Range,
        class UnaryFun,
        class Reference,
        class Value
    >
    struct super_
    {
        typedef typename range_iterator<Range>::type iter_t;

        typedef typename boost::mpl::eval_if<
            boost::is_same<Reference, boost::use_default>,
            default_reference<iter_t, UnaryFun>,
            boost::mpl::identity<Reference>
        >::type ref_t;

        typedef typename iter_range<
            boost::transform_iterator<
                UnaryFun, iter_t, ref_t, Value
            >
        >::type type;
    };


} // namespace transform_range_detail


template<
    class Range,
    class UnaryFun,
    class Reference = boost::use_default,
    class Value = boost::use_default
>
struct transform_range :
    transform_range_detail::super_<Range, UnaryFun, Reference, Value>::type,
    private as_lightweight_proxy< transform_range<Range, UnaryFun, Reference, Value> >
{
    PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
    typedef UnaryFun function_type;

private:
    typedef typename transform_range_detail::super_<Range, UnaryFun, Reference, Value>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    transform_range(Range& rng, UnaryFun const& fun) :
        super_t(
            iter_t(boost::begin(rng), fun),
            iter_t(boost::end(rng), fun)
        )
    { }

    function_type const function() const
    {
        return this->begin().functor();
    }

    typedef Range pstade_oven_range_base_type;
};


struct op_make_transform_range :
    callable<op_make_transform_range>
{
    template< class Myself, class Range, class UnaryFun >
    struct apply
    {
        typedef typename pass_by_value<UnaryFun>::type fun_t;
        typedef transform_range<Range, fun_t> const type;
    };

    template< class Result, class Range, class UnaryFun >
    Result call(Range& rng, UnaryFun& fun) const
    {
        return Result(rng, fun);
    }
};


PSTADE_SINGLETON_CONST(make_transform_range, op_make_transform_range)
PSTADE_PIPABLE(transformed, op_make_transform_range)


} } // namespace pstade::oven


#endif

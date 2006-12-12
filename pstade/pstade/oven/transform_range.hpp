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
// cannot work with this functor because of dangling reference.
// A transformed range's 'reference' type is sometimes
// orthogonal to functor's 'result_type'.


#include <boost/iterator/iterator_traits.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/pipable.hpp>
#include <pstade/unparenthesize.hpp>
#include <pstade/use_default.hpp>
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

        typedef typename
            defaultable_eval_to< Reference, default_reference<iter_t, UnaryFun> >::type
        ref_t;

        typedef
            iter_range<
                boost::transform_iterator<
                    UnaryFun, iter_t, ref_t, Value
                >
            >
        type;
    };


} // namespace transform_range_detail


template<
    class Range,
    class UnaryFun,
    class Reference = boost::use_default,
    class Value     = boost::use_default
>
struct transform_range :
    transform_range_detail::super_<Range, UnaryFun, Reference, Value>::type,
    private as_lightweight_proxy< transform_range<Range, UnaryFun, Reference, Value> >
{
    PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
    typedef transform_range type;
    typedef UnaryFun function_type;

private:
    typedef typename transform_range_detail::super_<Range, UnaryFun, Reference, Value>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    transform_range(Range& rng, UnaryFun const& fun) :
        super_t(
            iter_t(boost::begin(rng), fun),
            iter_t(boost::end(rng),   fun)
        )
    { }

    function_type const function() const // 'boost::transform_iterator' doesn't return reference.
    {
        return this->begin().functor();
    }

    typedef Range pstade_oven_range_base_type;
};


PSTADE_OBJECT_GENERATOR(make_transform_range,
    PSTADE_UNPARENTHESIZE((transform_range< deduce_to_qualified<from_1>, deduce_to_value<from_2> >)) const)
PSTADE_PIPABLE(transformed, op_make_transform_range)


} } // namespace pstade::oven


#endif

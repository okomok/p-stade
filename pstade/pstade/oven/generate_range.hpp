#ifndef PSTADE_OVEN_GENERATE_RANGE_HPP
#define PSTADE_OVEN_GENERATE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// 'Generator' can be a reference type.


#include <boost/iterator/iterator_categories.hpp> // single_pass_traversal_tag
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/ref.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/pass_by.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./detail/concept_check.hpp"
#include "./identity_range.hpp"
#include "./range_base.hpp"
#include "./transform_range.hpp"


namespace pstade { namespace oven {


namespace generate_range_detail {


    template< class Generator >
    struct gen_fun
    {
        typedef typename boost::result_of<Generator()>::type result_type;

        template< class T >
        result_type operator()(T const&) const
        {
            return m_gen();
        }

        explicit gen_fun(Generator const& gen) :
            m_gen(gen)
        { }

    private:
        Generator m_gen;
    };


    template< class Generator >
    struct gen_fun<Generator&>
    {
        typedef typename boost::remove_cv<Generator>::type plain_gen_t;
        typedef typename boost::result_of<plain_gen_t()>::type result_type;

        template< class T >
        result_type operator()(T const&) const
        {
            return (*m_pgen)();
        }

        explicit gen_fun(Generator& gen) :
            m_pgen(boost::addressof(gen))
        { }

    private:
        Generator *m_pgen; // be a pointer for Assignable.
    };


    template<
        class Range,
        class Generator,
        class Reference,
        class Value
    >
    struct super_
    {
        typedef transform_range<
            identity_range<Range, boost::single_pass_traversal_tag> const,
            gen_fun<Generator>,
            Reference,
            Value
        > type;
    };


} // namespace generate_range_detail


template<
    class Range,
    class Generator,
    class Reference = boost::use_default,
    class Value     = boost::use_default
>
struct generate_range :
    generate_range_detail::super_<Range, Generator, Reference, Value>::type,
    private as_lightweight_proxy< generate_range<Range, Generator, Reference, Value> >
{
    typedef Generator generator_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(Range, SinglePassRangeConcept);
    typedef typename generate_range_detail::super_<Range, Generator, Reference, Value>::type super_t;
    typedef typename range_base<super_t>::type base_t;
    typedef typename super_t::function_type fun_t;

public:
    generate_range(Range& rng, Generator gen) :
        super_t(base_t(rng), fun_t(gen))
    { }
};


namespace generate_range_detail {


    template< class Generator >
    struct unwrap :
        boost::mpl::eval_if< boost::is_reference_wrapper<Generator>,
            boost::add_reference<typename boost::unwrap_reference<Generator>::type>,
            boost::mpl::identity<Generator>
        >
    { };


    struct baby_make
    {
        template< class Myself, class Range, class Generator >
        struct apply
        {
            typedef typename unwrap<typename pass_by_value<Generator>::type>::type gen_t;
            typedef generate_range<Range, gen_t> const type;
        };

        template< class Result, class Range, class Generator >
        Result call(Range& rng, Generator& gen)
        {
            return Result(rng, gen);
        }
    };


} // namespace generate_range_detail


PSTADE_EGG_FUNCTION(make_generate_range, generate_range_detail::baby_make)
PSTADE_EGG_PIPABLE(generation, generate_range_detail::baby_make)


} } // namespace pstade::oven


#endif

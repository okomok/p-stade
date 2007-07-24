#ifndef PSTADE_OVEN_GENERATION_HPP
#define PSTADE_OVEN_GENERATION_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/optional/optional.hpp>
#include <pstade/egg/adapt.hpp>
#include <pstade/egg/generator.hpp>
#include <pstade/egg/identity.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include <pstade/unused.hpp>
#include "./iter_range.hpp"
#include "./unfold.hpp"


namespace pstade { namespace oven {


namespace generation_detail {


    struct ignored_t { };


    template< class StoppableGenerator >
    struct ignore_then
    {
        typedef ignore_then is_nonpure;

        typedef typename
            result_of<StoppableGenerator()>::type
        result_type;

        result_type operator()(ignored_t) // not 'const'
        {
            return m_gen();
        }

        explicit ignore_then()
        { }

        explicit ignore_then(StoppableGenerator gen) :
            m_gen(gen)
        { }

    private:
        StoppableGenerator m_gen;
    };


    template< class StoppableGenerator >
    struct base
    {
        typedef
            ignore_then<
                typename pass_by_value<StoppableGenerator>::type
            >
        ignore_then_gen_t;

        typedef typename
            result_of<
                op_unfold(ignored_t, ignore_then_gen_t, egg::op_identity const&)
            >::type
        result_type;

        result_type operator()(StoppableGenerator& gen) const
        {
            return unfold(ignored_t(), ignore_then_gen_t(gen), egg::identity);
        }
    };


} // namespace generation_detail


typedef PSTADE_EGG_ADAPT((generation_detail::base<boost::mpl::_>)) op_generation;
PSTADE_POD_CONSTANT((op_generation), generation) = PSTADE_EGG_ADAPT_INITIALIZER();


namespace nonstop_detail {


    template< class Generator >
    struct result_
    {
        typedef
            boost::optional<
                typename result_of<Generator()>::type
            >
        result_type;

        result_type operator()()
        {
            return result_type(m_gen());
        }

        explicit result_()
        { }

        explicit result_(Generator gen) :
            m_gen(gen)
        { }

    private:
        Generator m_gen;        
    };


} // namespace nonstop_detail


typedef
    egg::generator<
        nonstop_detail::result_< egg::deduce<boost::mpl::_1, egg::as_value> >
    >::type
op_nonstop;

PSTADE_POD_CONSTANT((op_nonstop), nonstop) = PSTADE_EGG_GENERATOR_INITIALIZER();


} } // namespace pstade::oven


#endif

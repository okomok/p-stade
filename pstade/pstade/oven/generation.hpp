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
#include <pstade/function.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/result_of.hpp>
#include "./detail/begin_end_tag.hpp"
#include "./detail/generator_iterator.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace generation_detail {


    template< class StoppableGenerator >
    struct baby
    {
        typedef
            detail::generator_iterator<
                typename pass_by_value<StoppableGenerator>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(StoppableGenerator& gen) const
        {
            return result_type(
                iter_t(gen, detail::begin_tag()),
                iter_t(gen, detail::end_tag())
            );
        }
    };


} // namespace generation_detail


PSTADE_FUNCTION(generation, (generation_detail::baby<_>))


namespace nonstop_detail {


    template< class Generator >
    struct return_op
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

        explicit return_op()
        { }

        explicit return_op(Generator gen) :
            m_gen(gen)
        { }

    private:
        Generator m_gen;        
    };


} // namespace nonstop_detail


PSTADE_OBJECT_GENERATOR(nonstop,
    (nonstop_detail::return_op< deduce<_1, as_value> >))


} } // namespace pstade::oven


#endif

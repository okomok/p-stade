#ifndef PSTADE_OVEN_GENERATION_HPP
#define PSTADE_OVEN_GENERATION_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/optional.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/const_function.hpp>
#include <pstade/function.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/pass_by.hpp>
#include "./generate_iterator.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace generation_detail {


    template< class Generator >
    struct baby
    {
        typedef
            generate_iterator<
                typename pass_by_value<Generator>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(Generator& gen) const
        {
            return result_type(iter_t(gen, begin), iter_t(gen, end));
        }
    };


} // namespace generation_detail


PSTADE_FUNCTION(generation, (generation_detail::baby<_>))


namespace innumerable_detail {


    template< class Generator_ >
    struct return_op
    {
        typedef
            boost::optional<
                typename boost::result_of<PSTADE_CONST_FUNCTION(Generator_)()>::type
            >
        result_type;

        result_type operator()()
        {
            return result_type(m_gen());
        }

        explicit return_op(Generator_ const& gen) :
            m_gen(gen)
        { }

    private:
        Generator_ m_gen;        
    };


} // namespace innumerable_detail


PSTADE_OBJECT_GENERATOR(innumerable,
    (innumerable_detail::return_op< deduce<_1, to_value> >))


} } // namespace pstade::oven


#endif

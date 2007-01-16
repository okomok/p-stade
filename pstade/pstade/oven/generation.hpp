#ifndef PSTADE_OVEN_GENERATION_HPP
#define PSTADE_OVEN_GENERATION_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/bool.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/function.hpp>
#include <pstade/pass_by.hpp>
#include "./generate_iterator.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace generation_detail {


    // It is always SinglePass if Generator is reference.
    template< class Generator >
    struct baby
    {
        typedef
            generate_iterator<Generator&>
        iter_t;

        typedef
            iter_range<iter_t> const
        result;

        result call(Generator& gen)
        {
            return result(
                iter_t(gen, boost::mpl::true_()),
                iter_t(gen, boost::mpl::false_())
            );
        }
    };


} // namespace generation_detail


PSTADE_FUNCTION(generation, (generation_detail::baby<_>))


struct op_generation_copied :
    callable<op_generation_copied>
{
    template< class Myself, class Generator, class Traversal = boost::single_pass_traversal_tag >
    struct apply
    {
        typedef
            generate_iterator<
                typename pass_by_value<Generator>::type,
                typename pass_by_value<Traversal>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        type;
    };

    template< class Result, class Generator, class Traversal >
    Result call(Generator& gen, Traversal&) const
    {
        typedef typename Result::iterator iter_t;
        return Result(
                iter_t(gen, boost::mpl::true_()),
                iter_t(gen, boost::mpl::false_())
        );
    }

    template< class Result, class Generator >
    Result call(Generator& gen) const
    {
        return (*this)(gen, boost::single_pass_traversal_tag());
    }
};


PSTADE_CONSTANT(generation_copied, (op_generation_copied))


} } // namespace pstade::oven


#endif

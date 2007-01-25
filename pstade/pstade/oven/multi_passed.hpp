#ifndef PSTADE_OVEN_MULTI_PASSED_HPP
#define PSTADE_OVEN_MULTI_PASSED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/spirit/iterator/multi_pass.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pipable.hpp>
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


template<
    class InputPolicy     = boost::spirit::multi_pass_policies::input_iterator,
    class OwnershipPolicy = boost::spirit::multi_pass_policies::ref_counted,
    class CheckingPolicy  = boost::spirit::multi_pass_policies::buf_id_check,
    class StoragePolicy   = boost::spirit::multi_pass_policies::std_deque
>
struct op_make_multi_passed :
    callable< op_make_multi_passed<InputPolicy, OwnershipPolicy, CheckingPolicy, StoragePolicy> >
{
    template< class Myself, class InputIterRange >
    struct apply
    {
        // InputIterRange is the undocumented concept by Boost.Spirit

        typedef
            boost::spirit::multi_pass<
                typename range_iterator<InputIterRange>::type,
                InputPolicy, OwnershipPolicy, CheckingPolicy, StoragePolicy
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        type;
    };

    template< class Result, class InputIterRange >
    Result call(InputIterRange& rng) const
    {
        return Result(rng);
    }
};


PSTADE_CONSTANT(make_multi_passed, (op_make_multi_passed<>))
PSTADE_PIPABLE(multi_passed, (op_make_multi_passed<>))


} } // namespace pstade::oven


#endif

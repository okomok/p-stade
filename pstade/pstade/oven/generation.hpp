#ifndef PSTADE_OVEN_GENERATION_HPP
#define PSTADE_OVEN_GENERATION_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/function.hpp>
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


} } // namespace pstade::oven


#endif

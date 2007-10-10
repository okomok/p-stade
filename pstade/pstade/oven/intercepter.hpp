#ifndef PSTADE_OVEN_INTERCEPTER_HPP
#define PSTADE_OVEN_INTERCEPTER_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/make_function.hpp>
#include <pstade/pass_by.hpp>
#include "./applier.hpp"
#include "./concepts.hpp"
#include "./detail/baby_to_adaptor.hpp"
#include "./eater.hpp"


namespace pstade { namespace oven {


namespace intercepter_detail {


    struct baby
    {
        template< class Myself, class IteratorFrom, class IteratorTo = void >
        struct apply :
            pass_by_value<IteratorTo>
        {};

        template< class Result, class IteratorFrom, class IteratorTo >
        Result call(IteratorFrom&, IteratorTo& to) const
        {
            PSTADE_CONCEPT_ASSERT((Output<IteratorFrom>));
            PSTADE_CONCEPT_ASSERT((Output<IteratorTo>));
            return to;
        }

        template< class Myself, class IteratorFrom >
        struct apply<Myself, IteratorFrom> :
            result_of<T_eater()>
        {};

        template< class Result, class IteratorFrom >
        Result call(IteratorFrom&) const
        {
            return eater();
        }
    };


} // namespace intercepter_detail


PSTADE_OVEN_BABY_TO_ADAPTOR(intercepter, (intercepter_detail::baby))


} } // namespace pstade::oven


#endif

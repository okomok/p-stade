#ifndef PSTADE_SAUSAGE_ENUMERATE_HPP
#define PSTADE_SAUSAGE_ENUMERATE_HPP


// PStade.Sausage
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/decay_function.hpp>
#include <pstade/egg/function.hpp>
#include "./detail/customization_of.hpp"
#include "./enumerate_argument.hpp"


namespace pstade { namespace sausage {


namespace enumerate_detail {


    struct baby
    {
        template< class Unused, class Enumerable, class EnumFtor >
        struct result :
            egg::decay_function<EnumFtor>
        { };

        template< class Result, class Enumerable, class EnumFtor >
        Result call(Enumerable& e, EnumFtor& fun)
        {
            typedef typename detail::customization_of<Enumerable>::type cust_t;
            typedef typename enumerate_argument<Enumerable>::type arg_t;

            return cust_t().template enumerate<arg_t>(e, fun);
        }
    };


} // namespace enumerate_detail


PSTADE_EGG_FUNCTION(enumerate, enumerate_detail::baby)


} } // namespace pstade::sausage


#endif

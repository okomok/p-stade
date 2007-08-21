#ifndef PSTADE_OVEN_APPLIER_HPP
#define PSTADE_OVEN_APPLIER_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Replaces 'boost::function_output_iterator',
// which is not adaptable using 'iterator_adaptor',
// and has no way to access its functor.
// Note that OutputIterator cannot always be implemented by using
// 'iterator_facade'; because of the postfix-increment implementation.


#include <pstade/egg/generator.hpp>
#include <pstade/pod_constant.hpp>
#include "./detail/function_output_iterator.hpp"


namespace pstade { namespace oven {


typedef
    egg::generator<
        detail::function_output_iterator< egg::deduce<boost::mpl::_1, egg::as_value> > const
    >::type
op_applier;


PSTADE_POD_CONSTANT((op_applier), applier) = PSTADE_EGG_GENERATOR;


} } // namespace pstade::oven


#endif

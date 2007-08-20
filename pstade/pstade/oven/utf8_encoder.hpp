#ifndef PSTADE_OVEN_UTF8_ENCODER_HPP
#define PSTADE_OVEN_UTF8_ENCODER_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/regex/pending/unicode_iterator.hpp> // utf8_output_iterator
#include <pstade/egg/generator.hpp>
#include <pstade/pod_constant.hpp>


namespace pstade { namespace oven {


typedef
    egg::generator<
        boost::utf8_output_iterator< egg::deduce<boost::mpl::_1, egg::as_value> > const
    >::type
op_utf8_encoder;


PSTADE_POD_CONSTANT((op_utf8_encoder), utf8_encoder) = PSTADE_EGG_GENERATOR_TYPE;


} } // namespace pstade::oven


#endif

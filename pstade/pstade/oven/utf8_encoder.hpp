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
#include <pstade/object_generator.hpp>


namespace pstade { namespace oven {


PSTADE_OBJECT_GENERATOR(utf8_encoder,
    (boost::utf8_output_iterator< deduce<_1, as_value> >) const)


} } // namespace pstade::oven


#endif

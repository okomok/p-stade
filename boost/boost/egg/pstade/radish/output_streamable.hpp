#ifndef PSTADE_RADISH_OUTPUT_STREAMABLE_HPP
#define PSTADE_RADISH_OUTPUT_STREAMABLE_HPP


// PStade.Radish
//
// Copyright Shunsuke Sogame 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// maybe rejected; doesn't work even under modern compilers.


#include <iosfwd> // basic_ostream
#include <boost/egg/pstade/adl_barrier.hpp>
#include "./null_injector.hpp"


namespace pstade { namespace radish {

PSTADE_ADL_BARRIER(output_streamable) {


template<
    class Derived,
    class Injector = null_injector<Derived>
>
struct output_streamable :
    Injector
{
    template< class CharT, class Traits >
    friend
    std::basic_ostream<CharT, Traits>&
    operator<<(std::basic_ostream<CharT, Traits>& os, Derived const& x)
    {
        pstade_radish_output(x, os);
        return os;
    }
};


} // ADL barrier

} } // namespace pstade::radish


#endif

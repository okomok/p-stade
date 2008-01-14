#ifndef PSTADE_RADISH_INPUT_STREAMABLE_HPP
#define PSTADE_RADISH_INPUT_STREAMABLE_HPP


// PStade.Radish
//
// Copyright Shunsuke Sogame 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// maybe rejected; doesn't work even under modern compilers.


#include <iosfwd> // basic_istream
#include <boost/egg/pstade/adl_barrier.hpp>
#include "./null_injector.hpp"


namespace pstade { namespace radish {

PSTADE_ADL_BARRIER(input_streamable) {


template<
    class Derived,
    class Injector = null_injector<Derived>
>
struct input_streamable :
    Injector
{
    template< class CharT, class Traits >
    friend
    std::basic_istream<CharT, Traits>&
    operator>>(std::basic_istream<CharT, Traits>& is, Derived& x)
    {
        pstade_radish_input(x, is);
        return is;
    }
};


} // ADL barrier

} } // namespace pstade::radish


#endif

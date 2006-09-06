#ifndef PSTADE_CANDY_EMPTY_HPP
#define PSTADE_CANDY_EMPTY_HPP


// PStade.Candy
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade { namespace candy {


template< class Flags > inline
bool empty(Flags fs)
{
    return (fs == 0);
}


} } // namespace pstade::candy


#endif

#ifndef PSTADE_CANDY_COMPLEMENT_HPP
#define PSTADE_CANDY_COMPLEMENT_HPP


// PStade.Candy
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade { namespace candy {


template< class Flags > inline
Flags complement(Flags fs)
{
    // See: candy::intersection

    // Note: you cannot use integral_cast.
    return static_cast<Flags>(~fs);
}


} } // namespace pstade::candy


#endif

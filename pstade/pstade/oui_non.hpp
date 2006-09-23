#ifndef PSTADE_OUI_NON_HPP
#define PSTADE_OUI_NON_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)



namespace pstade {


struct oui { char a[1]; oui(bool) { } };
struct non { char a[2]; };


// See: 'to_ptr' at <boost/foreach.hpp>
template< class T >
T *& make_ptr_ref();


} // namespace pstade


#endif

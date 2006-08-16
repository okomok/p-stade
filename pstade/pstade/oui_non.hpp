#ifndef PSTADE_OUI_NON_HPP
#define PSTADE_OUI_NON_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/bool.hpp>


namespace pstade {


struct oui { char a[1]; };
struct non { char a[2]; };


// See: 'to_ptr' at <boost/foreach.hpp>
template< class T >
T *& make_ptr_ref();


} // namespace pstade


#define PSTADE_IS_OUI(Expr) \
    boost::mpl::bool_< sizeof(Expr) == sizeof(pstade::oui) > \
/**/


#endif

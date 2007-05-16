#ifndef PSTADE_SAUSAGE_DETAIL_CUSTOMIZATION_OF_TYPE_HPP
#define PSTADE_SAUSAGE_DETAIL_CUSTOMIZATION_OF_TYPE_HPP


// PStade.Sausage
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/remove_rcv.hpp>
#include "../customization.hpp"


namespace pstade { namespace sausage { namespace detail {


template< class T >
struct customization_of
{
    typedef customization<
        typename remove_rcv<T>::type
    > type;
};


} } } // namespace pstade::sausage::detail


#endif

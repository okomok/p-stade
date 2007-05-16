#ifndef PSTADE_CANDY_DETAIL_GREATER_SIZE_TYPE_HPP
#define PSTADE_CANDY_DETAIL_GREATER_SIZE_TYPE_HPP


// PStade.Candy
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/greater.hpp>
#include <boost/mpl/sizeof.hpp>


namespace pstade { namespace candy { namespace detail {


template< class Flags0, class Flags1 >
struct greater_size :
    boost::mpl::if_<
        boost::mpl::greater<
            boost::mpl::sizeof_<Flags0>,
            boost::mpl::sizeof_<Flags1>
        >,
        Flags0,
        Flags1
    >
{ };


} } } // namespace pstade::candy::detail


#endif

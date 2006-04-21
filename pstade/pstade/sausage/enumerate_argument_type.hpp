#ifndef PSTADE_SAUSAGE_ENUMERATE_ARGUMENT_TYPE_HPP
#define PSTADE_SAUSAGE_ENUMERATE_ARGUMENT_TYPE_HPP


// PStade.Sausage
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_volatile.hpp>
#include "./customization.hpp"
#include "./detail/customization_of_type.hpp"


namespace pstade { namespace sausage {


template< class Enumerable >
struct enumerate_argument
{
private:
    typedef typename detail::customization_of<Enumerable>::type cust_t;
    typedef typename boost::remove_reference<Enumerable>::type no_ref_t;
    typedef typename boost::remove_volatile<no_ref_t>::type no_vol_t;

public:
    typedef typename cust_t::template enumerate_argument<no_vol_t>::type type;
};


} } // namespace pstade::sausage


#endif

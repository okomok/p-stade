#ifndef PSTADE_OVEN_DETAIL_PROPAGATE_HPP
#define PSTADE_OVEN_DETAIL_PROPAGATE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/apply.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/remove_reference.hpp>


namespace pstade { namespace oven { namespace detail {


template< class OuterValue, class GetInner >
struct inner_value
{
    typedef typename boost::mpl::apply<GetInner, OuterValue>::type inner_t;
    
    typedef typename boost::mpl::eval_if< boost::is_const<OuterValue>,
        boost::add_const<inner_t>,
        boost::mpl::identity<inner_t>
    >::type type;
};


template< class Outer, class GetInner >
struct propagate
{
    typedef typename boost::remove_reference<Outer>::type out_val_t;
    typedef typename inner_value<out_val_t, GetInner>::type in_val_t;

    typedef typename boost::mpl::eval_if< boost::is_reference<Outer>,
        boost::add_reference<in_val_t>,
        boost::mpl::identity<in_val_t>
    >::type type;
};


} } } // namespace pstade::oven::detail


#endif

#ifndef PSTADE_OVEN_DETAIL_PROPAGATE_HPP
#define PSTADE_OVEN_DETAIL_PROPAGATE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://d.hatena.ne.jp/y-hamigaki/20060726


#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/add_volatile.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_volatile.hpp>
#include <boost/type_traits/remove_reference.hpp>


namespace pstade { namespace oven { namespace detail {


template< class From, class To >
struct propagate
{
    typedef typename boost::is_reference<
        From
    >::type is_reference;

    typedef typename boost::is_const<
        typename boost::remove_reference<From>::type
    >::type is_const;

    typedef typename boost::is_volatile<
        typename boost::remove_reference<From>::type
    >::type is_volatile;

    typedef typename boost::mpl::eval_if< is_const,
        boost::add_const<To>,
        boost::mpl::identity<To>
    >::type c_to_t;

    typedef typename boost::mpl::eval_if< is_volatile,
        boost::add_volatile<c_to_t>,
        boost::mpl::identity<c_to_t>
    >::type v_to_t;

    typedef typename boost::mpl::eval_if< is_reference,
        boost::add_reference<v_to_t>,
        boost::mpl::identity<v_to_t>
    >::type type;
};


} } } // namespace pstade::oven::detail


#endif

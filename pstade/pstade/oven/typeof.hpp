#ifndef PSTADE_OVEN_TYPEOF_HPP
#define PSTADE_OVEN_TYPEOF_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_categories.hpp>
#include <boost/typeof/typeof.hpp>
#include "./any_range.hpp"
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()


#if !defined(PSTADE_OVEN_NO_TYPEOF_REGISTRATION_OF_TRAVERSAL_TAGS)
BOOST_TYPEOF_REGISTER_TYPE(boost::incrementable_traversal_tag)
BOOST_TYPEOF_REGISTER_TYPE(boost::single_pass_traversal_tag)
BOOST_TYPEOF_REGISTER_TYPE(boost::forward_traversal_tag)
BOOST_TYPEOF_REGISTER_TYPE(boost::bidirectional_traversal_tag)
BOOST_TYPEOF_REGISTER_TYPE(boost::random_access_traversal_tag)
#endif
BOOST_TYPEOF_REGISTER_TEMPLATE(pstade::oven::any_range, 4)


// 'range_value', 'range_reference' and 'range_difference' must be registered.
#if !defined(BOOST_TYPEOF_NATIVE)
    #define PSTADE_OVEN_AUTO(Var, Rng) BOOST_AUTO(Var, pstade::oven::make_any_range(Rng))
    #define PSTADE_OVEN_AUTO_TPL(Var, Rng) BOOST_AUTO_TPL(Var, pstade::oven::make_any_range(Rng))
#else
    #define PSTADE_OVEN_AUTO BOOST_AUTO
    #define PSTADE_OVEN_AUTO_TPL BOOST_AUTO_TPL
#endif


#endif

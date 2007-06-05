#ifndef PSTADE_OVEN_TYPEOF_HPP
#define PSTADE_OVEN_TYPEOF_HPP
#include "./prelude.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_categories.hpp>
#include <boost/typeof/typeof.hpp>
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()


namespace pstade { namespace oven {


template< class Reference, class Traversal, class Value, class Difference >
struct any_iterator;

template< class Reference, class Traversal, class Value, class Difference >
struct any_range;


} } // namespace pstade::oven


BOOST_TYPEOF_REGISTER_TEMPLATE(pstade::oven::any_iterator, 4)
BOOST_TYPEOF_REGISTER_TEMPLATE(pstade::oven::any_range, 4)

#if !defined(PSTADE_OVEN_NO_TYPEOF_REGISTRATION_OF_TRAVERSAL_TAGS)
    BOOST_TYPEOF_REGISTER_TYPE(boost::incrementable_traversal_tag)
    BOOST_TYPEOF_REGISTER_TYPE(boost::single_pass_traversal_tag)
    BOOST_TYPEOF_REGISTER_TYPE(boost::forward_traversal_tag)
    BOOST_TYPEOF_REGISTER_TYPE(boost::bidirectional_traversal_tag)
    BOOST_TYPEOF_REGISTER_TYPE(boost::random_access_traversal_tag)
#endif


#endif

#ifndef BOOST_EGG_BLL_RETURN_TYPE_HPP
#define BOOST_EGG_BLL_RETURN_TYPE_HPP
#include <boost/egg/detail/prefix.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/bll/extension_fwd.hpp>


#include <boost/tuple/tuple.hpp>

namespace boost { namespace lambda {
    using boost::tuples::null_type;
} }

#include <boost/lambda/detail/lambda_fwd.hpp>
#include <boost/lambda/detail/lambda_traits.hpp>

#include <boost/lambda/detail/return_type_traits.hpp>
#include <boost/lambda/detail/operator_return_type_traits.hpp>
#include <boost/lambda/detail/member_ptr.hpp>


#include <boost/egg/detail/suffix.hpp>
#endif

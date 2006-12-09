#ifndef PSTADE_OBJECT_GENERATOR_HPP
#define PSTADE_OBJECT_GENERATOR_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// A lightweight 'callable' for simple object generators.


#include <boost/mpl/apply.hpp>
#include <boost/mpl/placeholders.hpp> // _1
#include <boost/preprocessor/cat.hpp>
#include <pstade/constant.hpp>
#include <pstade/lambda_sig.hpp>
#include <pstade/pass_by.hpp>


namespace pstade {


    // To: MPL LambdaExpression.

    template< class To >
    struct object_generator :
        lambda_sig
    {
        template< class Signature >
        struct result;

        template< class Self, class A0 >
        struct result<Self(A0)> :
            boost::mpl::apply1<To, typename pass_by_value<A0>::type>
        { };

        // pass by value; see "./value.hpp"
        template< class A0 >
        typename boost::mpl::apply1<To, A0>::type
        operator()(A0 a0) const
        {
            return typename boost::mpl::apply1<To, A0>::type(a0);
        }
    };


    #define PSTADE_OBJECT_GENERATOR(O, T) \
        typedef \
            pstade::object_generator< T<boost::mpl::placeholders::_1> > \
        BOOST_PP_CAT(op_, O); \
        \
        PSTADE_CONSTANT(O, BOOST_PP_CAT(op_, O)) \
    /**/


} // namespace pstade


#endif

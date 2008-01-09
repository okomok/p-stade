#ifndef PSTADE_EGG_RETURN_HPP
#define PSTADE_EGG_RETURN_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/lambda.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/result_of.hpp>
#include "./by_perfect.hpp"
#include "./by_value.hpp"
#include "./detail/little_return_result.hpp"
#include "./generator.hpp"
#include "./use_brace2.hpp"


namespace pstade { namespace egg {


    template<class Base, class Lambda, class Strategy = by_perfect>
    struct result_of_return_
    {
        typedef
            function<detail::little_return_result<Base, Lambda>, Strategy>
        type;
    };


    #define PSTADE_EGG_RETURN_L { {
    #define PSTADE_EGG_RETURN_R } }
    #define PSTADE_EGG_RETURN(F) PSTADE_EGG_RETURN_L F PSTADE_EGG_RETURN_R


    template<class Lambda>
    struct X_return_ :
        generator<
            typename result_of_return_<
                deduce<boost::mpl::_1, as_value>,
                typename boost::mpl::lambda<Lambda>::type
            >::type,
            boost::use_default,
            use_brace2,
            by_value
        >::type
    { };


    template<class Lambda, class Base> inline
    typename result_of<X_return_<Lambda>(Base&)>::type return_(Base base)
    {
        return X_return_<Lambda>()(base);
    }


} } // namespace pstade::egg


#endif

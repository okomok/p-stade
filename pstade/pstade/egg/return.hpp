#ifndef PSTADE_EGG_RETURN_HPP
#define PSTADE_EGG_RETURN_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/result_of.hpp>
#include "./by_perfect.hpp"
#include "./by_value.hpp"
#include "./construct_braced2.hpp"
#include "./detail/little_return_result.hpp"
#include "./generator.hpp"


namespace pstade { namespace egg {


    template<
        class Base,
        class Return   = boost::use_default,
        class Strategy = by_perfect,
        class Tag      = boost::use_default
    >
    struct result_of_return
    {
        typedef
            function<detail::little_return_result<Base, Return, Strategy, Tag>, Strategy>
        type;
    };

    #define PSTADE_EGG_RETURN_L { {
    #define PSTADE_EGG_RETURN_R } }
    #define PSTADE_EGG_RETURN(F) PSTADE_EGG_RETURN_L F PSTADE_EGG_RETURN_R


    template<
        class Return   = boost::use_default,
        class Strategy = by_perfect,
        class Tag      = boost::use_default
    >
    struct X_return :
        generator<
            typename result_of_return<deduce<mpl_1, as_value>, Return, Strategy, Tag>::type,
            by_value,
            X_construct_braced2<>
        >::type
    { };

    template<class Return, class Base> inline
    typename result_of<X_return<Return>(Base&)>::type return_(Base base)
    {
        return X_return<Return>()(base);
    }


} } // namespace pstade::egg


#endif

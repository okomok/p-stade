#ifndef PSTADE_EGG_NOT_HPP
#define PSTADE_EGG_NOT_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/derived_from.hpp>
#include <pstade/pod_constant.hpp>
#include "./by_perfect.hpp"
#include "./by_value.hpp"
#include "./construct_variadic1.hpp"
#include "./detail/tuple_fuse.hpp"
#include "./generator.hpp"
#include "./return.hpp"
#include "./variadic.hpp"


namespace pstade { namespace egg {


    namespace not_detail {


        template<class Base>
        struct little_result
        {
            Base m_base;

            Base const& base() const
            {
                return m_base;
            }

            template<class Me, class Args>
            struct apply
            {
                typedef bool type;
            };

            template<class Re, class Args>
            Re call(Args& args) const
            {
                return !detail::tuple_fuse(egg::return_<bool>(m_base))(args);
            }
        };


    } // namespace not_detail


    template<class Base, class Strategy = by_perfect>
    struct result_of_not :
        variadic<
            not_detail::little_result<Base>,
            Strategy,
            boost::use_default,
            use_nullary_result
        >
    { };

    #define PSTADE_EGG_NOT_L PSTADE_EGG_VARIADIC_L {
    #define PSTADE_EGG_NOT_R } PSTADE_EGG_VARIADIC_R
    #define PSTADE_EGG_NOT(F) PSTADE_EGG_NOT_L F PSTADE_EGG_NOT_R


    template<class Strategy = by_perfect>
    struct X_not : derived_from_eval<
        generator<
            typename result_of_not<deduce<mpl_1, as_value>, Strategy>::type,
            by_value,
            X_construct_variadic1<>
        >
    >
    { };

    typedef X_not<>::base_class T_not;
    typedef T_not T_not_;
    PSTADE_POD_CONSTANT((T_not_), not_) = PSTADE_EGG_GENERATOR();


} } // namespace pstade::egg


#include "./detail/suffix.hpp"
#endif

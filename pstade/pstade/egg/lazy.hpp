#ifndef PSTADE_EGG_LAZY_HPP
#define PSTADE_EGG_LAZY_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/derived_from.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include <pstade/use_default.hpp>
#include "./bll/bind.hpp"
#include "./by_cref.hpp"
#include "./by_ref.hpp"
#include "./by_value.hpp"
#include "./construct_variadic1.hpp"
#include "./detail/tuple_fuse.hpp"
#include "./detail/tuple_prepend.hpp"
#include "./generator.hpp"
#include "./variadic.hpp"


namespace pstade { namespace egg {


    namespace lazy_detail {


        template<class Base, class Bind>
        struct little_result
        {
            Base m_base;

            Base const &base() const
            {
                return m_base;
            }

            template<class Me, class Args>
            struct apply :
                result_of<
                    typename result_of<
                        detail::T_tuple_fuse(Bind)
                    >::type(typename result_of<detail::X_tuple_prepend<by_ref>(Args &, Base const &)>::type)
                >
            { };

            template<class Re, class Args>
            Re call(Args &args) const
            {
                return detail::tuple_fuse(Bind())
                    (detail::X_tuple_prepend<by_ref>()(args, m_base));
            }
        };


    } // namespace lazy_detail


    template<class Base, class Bind = boost::use_default>
    struct result_of_lazy :
        variadic<
            lazy_detail::little_result<Base, typename if_use_default<Bind, T_bll_bind>::type>,
            by_cref
        >
    { };

    #define PSTADE_EGG_LAZY_L PSTADE_EGG_VARIADIC_L {
    #define PSTADE_EGG_LAZY_R } PSTADE_EGG_VARIADIC_R
    #define PSTADE_EGG_LAZY(F) PSTADE_EGG_LAZY_L F PSTADE_EGG_LAZY_R


    template<class Bind = boost::use_default>
    struct X_lazy : derived_from_eval<
        generator<
            typename result_of_lazy<deduce<mpl_1, as_value>, Bind>::type,
            by_value,
            X_construct_variadic1<>
        > >
    { };

    typedef X_lazy<>::base_class T_lazy;
    PSTADE_POD_CONSTANT((T_lazy), lazy) = PSTADE_EGG_GENERATOR();


} } // namespace pstade::egg


#include "./detail/suffix.hpp"
#endif

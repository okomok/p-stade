#ifndef PSTADE_EGG_LAZY_HPP
#define PSTADE_EGG_LAZY_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include <pstade/use_default.hpp>
#include "./bll/bind.hpp"
#include "./by_cref.hpp"
#include "./by_value.hpp"
#include "./construct_variadic1.hpp"
#include "./fuse.hpp"
#include "./generator.hpp"
#include "./tuple/prepend.hpp"
#include "./variadic.hpp"


namespace pstade { namespace egg {


    namespace lazy_detail {


        template<class Base, class Bind>
        struct little_result
        {
            typedef typename if_use_default<Bind, T_bll_bind>::type bind_t;

            Base m_base;

            Base const& base() const
            {
                return m_base;
            }

            template<class Myself, class Args>
            struct apply :
                result_of<
                    typename result_of<
                        T_fuse(bind_t)
                    >::type(typename result_of<T_tuple_prepend(Args&, Base const&)>::type)
                >
            { };

            template<class Result, class Args>
            Result call(Args& args) const
            {
                return fuse(bind_t())(tuple_prepend(args, m_base));
            }
        };


    } // namespace lazy_detail


    template<class Base, class Bind = boost::use_default>
    struct result_of_lazy :
        variadic<lazy_detail::little_result<Base, Bind>, by_cref>
    { };

    #define PSTADE_EGG_LAZY_L PSTADE_EGG_VARIADIC_L {
    #define PSTADE_EGG_LAZY_R } PSTADE_EGG_VARIADIC_R
    #define PSTADE_EGG_LAZY(F) PSTADE_EGG_LAZY_L F PSTADE_EGG_LAZY_R


    template<class Bind = boost::use_default>
    struct X_lazy :
        generator<
            typename result_of_lazy<deduce<mpl_1, as_value>, Bind>::type,
            by_value,
            X_construct_variadic1<>
        >::type
    { };

    typedef X_lazy<>::function_type T_lazy;
    PSTADE_POD_CONSTANT((T_lazy), lazy) = PSTADE_EGG_GENERATOR();


} } // namespace pstade::egg


#endif

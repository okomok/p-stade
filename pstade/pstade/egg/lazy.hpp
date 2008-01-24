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
            typedef typename if_use_default<Bind, T_bll_bind>::type bind_type;

            Base m_base;
            bind_type m_bind;

            Base const& base() const
            {
                return m_base;
            }

            template<class Myself, class Args>
            struct apply :
                result_of<
                    typename result_of<
                        T_fuse(bind_type const&)
                    >::type(typename result_of<T_tuple_prepend(Args&, Base const&)>::type)
                >
            { };

            template<class Result, class Args>
            Result call(Args& args) const
            {
                return fuse(m_bind)(tuple_prepend(args, m_base));
            }
        };


    } // namespace lazy_detail


    template<class Base, class Bind = boost::use_default>
    struct result_of_lazy :
        variadic<lazy_detail::little_result<Base, Bind>, by_cref>
    { };

    // PSTADE_EGG_VARIADIC_L { F, B } PSTADE_EGG_VARIADIC_R
    #define PSTADE_EGG_LAZY_L PSTADE_EGG_VARIADIC_L {
    #define PSTADE_EGG_LAZY_M ,
    #define PSTADE_EGG_LAZY_DEFAULT_BIND PSTADE_EGG_BLL_BIND_INIT
    #define PSTADE_EGG_LAZY_R } PSTADE_EGG_VARIADIC_R
    #define PSTADE_EGG_LAZY(F) PSTADE_EGG_LAZY_L F PSTADE_EGG_LAZY_M PSTADE_EGG_LAZY_DEFAULT_BIND PSTADE_EGG_LAZY_R


    typedef
        generator<
            result_of_lazy< deduce<mpl_1, as_value>, deduce<mpl_2, as_value, boost::use_default> >::type,
            by_value,
            X_construct_variadic1<>
        >::type
    T_lazy;

    PSTADE_POD_CONSTANT((T_lazy), lazy) = PSTADE_EGG_GENERATOR();


} } // namespace pstade::egg


#endif

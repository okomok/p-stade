#ifndef PSTADE_EGG_INDIRECT_HPP
#define PSTADE_EGG_INDIRECT_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// 'boost::indirect_iterator<>' is famous.
// This is intended as "indirect_function<>".
// See also 'boost::indirect_fun'.


#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "./by_perfect.hpp"
#include "./by_value.hpp"
#include "./detail/functional1.hpp" // dereference
#include "./fuse.hpp"
#include "./generator.hpp"
#include "./use_variadic1.hpp"
#include "./variadic.hpp"


namespace pstade { namespace egg {


    namespace indirect_detail {


        template<class Ptr>
        struct little_result
        {
            Ptr m_ptr;

            template<class Myself, class Args>
            struct apply :
                result_of<
                    typename result_of<
                        T_fuse(typename result_of<T_dereference(Ptr const&)>::type)
                    >::type(Args&)
                >
            { };

            template<class Result, class Args>
            Result call(Args& args) const
            {
                return fuse(*m_ptr)(args);
            }
        };


    } // namespace indirect_detail


    template<class Ptr, class Strategy = by_perfect>
    struct result_of_indirect :
        variadic<indirect_detail::little_result<Ptr>, Strategy, use_nullary_result>
    { };

    #define PSTADE_EGG_INDIRECT_L PSTADE_EGG_VARIADIC_L {
    #define PSTADE_EGG_INDIRECT_R } PSTADE_EGG_VARIADIC_R
    #define PSTADE_EGG_INDIRECT(P) PSTADE_EGG_INDIRECT_L P PSTADE_EGG_INDIRECT_R


    template<class Strategy = by_perfect>
    struct X_indirect :
        generator<
            typename result_of_indirect<deduce<mpl_1, as_value>, Strategy>::type,
            by_value,
            use_variadic1
        >::type
    { };

    typedef X_indirect<>::function_type T_indirect;
    PSTADE_POD_CONSTANT((T_indirect), indirect) = PSTADE_EGG_GENERATOR();


} } // namespace pstade::egg


#endif

#ifndef PSTADE_EGG_ALWAYS_HPP
#define PSTADE_EGG_ALWAYS_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// `always` doesn't unwrap reference_wrapper.
// Consider: always( always(boost::ref(k))(1,2) );


#include <pstade/pod_constant.hpp>
#include "./by_cref.hpp"
#include "./by_perfect.hpp"
#include "./construct_unfused1.hpp"
#include "./detail/bound.hpp"
#include "./generator.hpp"
#include "./unfuse.hpp"


namespace pstade { namespace egg {


    namespace always_detail {


        template<class Bound>
        struct fused_result
        {
            Bound m_bound;

            Bound base() const
            {
                return m_bound;
            }

            typedef typename detail::unbound<Bound>::type result_type;

            template<class Args>
            result_type operator()(Args const &) const
            {
                return m_bound;
            }
        };


        template<class Reference>
        struct fused_ref_result
        {
            Reference m_ref;

            Reference base() const
            {
                return m_ref;
            }

            typedef Reference result_type;

            template<class Args>
            result_type operator()(Args const &) const
            {
                return m_ref;
            }
        };


    } // namespace always_detail


    // always
    //

    template<class Bound>
    struct result_of_always :
        result_of_unfuse<
            always_detail::fused_result<Bound>,
            use_nullary_result,
            boost::use_default,
            by_cref
        >
    { };

    #define PSTADE_EGG_ALWAYS_L PSTADE_EGG_UNFUSE_L {
    #define PSTADE_EGG_ALWAYS_R } PSTADE_EGG_UNFUSE_R
    #define PSTADE_EGG_ALWAYS(V) PSTADE_EGG_ALWAYS_L V PSTADE_EGG_ALWAYS_R

    typedef
        generator<
            result_of_always< deduce<mpl_1, detail::as_bound> >::type,
            by_cref,
            X_construct_unfused1<>
        >::type
    T_always;

    PSTADE_POD_CONSTANT((T_always), always) = PSTADE_EGG_GENERATOR();


    // always_ref
    //

    template<class Reference>
    struct result_of_always_ref :
        result_of_unfuse<
            always_detail::fused_ref_result<Reference>,
            use_nullary_result,
            boost::use_default,
            by_cref
        >
    { };

    #define PSTADE_EGG_ALWAYS_REF_L PSTADE_EGG_UNFUSE_L {
    #define PSTADE_EGG_ALWAYS_REF_R } PSTADE_EGG_UNFUSE_R
    #define PSTADE_EGG_ALWAYS_REF(R) PSTADE_EGG_ALWAYS_REF_L R PSTADE_EGG_ALWAYS_REF_R

    typedef
        generator<
            result_of_always_ref< deduce<mpl_1, as_ref> >::type,
            by_perfect,
            X_construct_unfused1<>
        >::type
    T_always_ref;

    PSTADE_POD_CONSTANT((T_always_ref), always_ref) = PSTADE_EGG_GENERATOR();


} } // namespace pstade::egg


#include "./detail/suffix.hpp"
#endif

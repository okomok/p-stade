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


#include <boost/utility/addressof.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "./by_cref.hpp"
#include "./by_perfect.hpp"
#include "./by_value.hpp"
#include "./construct_unfused1.hpp"
#include "./generator.hpp"
#include "./unfuse.hpp"


namespace pstade { namespace egg {


    // always
    //

    namespace always_detail {

        template<class Value>
        struct fused_result
        {
            Value m_value;

            Value const &base() const
            {
                return m_value;
            }

            typedef Value const &result_type;

            template<class Args>
            result_type operator()(Args const &) const
            {
                return m_value;
            }
        };

    } // namespace always_detail

    template<class Value>
    struct result_of_always :
        result_of_unfuse<
            always_detail::fused_result<Value>,
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
            result_of_always< deduce<mpl_1, as_value> >::type,
            by_value,
            X_construct_unfused1<>
        >::type
    T_always;

    PSTADE_POD_CONSTANT((T_always), always) = PSTADE_EGG_GENERATOR();


    // always_ref
    //

    namespace always_ref_detail {

        template<class T>
        struct fused_result
        {
            T *m_ptr; // Use pointer for Regular.

            T &base() const
            {
                return *m_ptr;
            }

            typedef T &result_type;

            template<class Args>
            result_type operator()(Args const &) const
            {
                return *m_ptr;
            }
        };

        struct little
        {
            typedef
                X_unfuse<use_nullary_result, boost::use_default, by_cref>
            unfuse_t;

            template<class Me, class T>
            struct apply :
                result_of<unfuse_t(fused_result<T> &)>
            { };

            template<class Re, class T>
            Re call(T &t) const
            {
                fused_result<T> f = {boost::addressof(t)};
                return unfuse_t()(f);
            }

        };

    } // namespace always_ref_detail

    typedef function<always_ref_detail::little, by_perfect> T_always_ref;
    PSTADE_POD_CONSTANT((T_always_ref), always_ref) = PSTADE_EGG_GENERATOR();


} } // namespace pstade::egg


#include "./detail/suffix.hpp"
#endif

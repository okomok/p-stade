#ifndef BOOST_EGG_ALWAYS_HPP
#define BOOST_EGG_ALWAYS_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
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
#include <boost/egg/by_cref.hpp>
#include <boost/egg/by_perfect.hpp>
#include <boost/egg/by_value.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/construct_unfused1.hpp>
#include <boost/egg/generator.hpp>
#include <boost/egg/result_of.hpp>
#include <boost/egg/unfuse.hpp>


namespace boost { namespace egg {


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
            use_default,
            by_cref
        >
    { };

    #define BOOST_EGG_ALWAYS_L BOOST_EGG_UNFUSE_L {
    #define BOOST_EGG_ALWAYS_R } BOOST_EGG_UNFUSE_R
    #define BOOST_EGG_ALWAYS(V) BOOST_EGG_ALWAYS_L V BOOST_EGG_ALWAYS_R

    typedef
        generator<
            result_of_always< deduce<mpl::_1, as_value> >::type,
            by_value,
            X_construct_unfused1<>
        >::type
    T_always;

    BOOST_EGG_CONST((T_always), always) = BOOST_EGG_GENERATOR();


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
                X_unfuse<use_nullary_result, use_default, by_cref>
            unfuse_t;

            template<class Me, class T>
            struct apply :
                result_of_<unfuse_t(fused_result<T> &)>
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
    BOOST_EGG_CONST((T_always_ref), always_ref) = BOOST_EGG_GENERATOR();


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif

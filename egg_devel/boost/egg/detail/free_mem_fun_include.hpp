

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if !defined(cv_qualifier)
    #error Please define cv_qualifier.
#endif


    template<class R, class T BOOST_PP_ENUM_TRAILING_PARAMS(n, class A)>
    struct result_of_free<R (T::*)(fparams) cv_qualifier>
    {
        typedef result_of_free type;

        typedef R result_type;
        typedef R (T::*base_t)(fparams) cv_qualifier;

        details::wrap<base_t> m_wrap;

        base_t const &base() const
        {
            return m_wrap.base;
        }

        template<class U>
        result_type operator()(U &u BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(n, A, a)) const
        {
            return details::free_call<R, T>(m_wrap.base, u BOOST_PP_ENUM_TRAILING_PARAMS(n, a));
        }

        template<class U>
        result_type operator()(U const &u BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(n, A, a)) const
        {
            return details::free_call<R, T>(m_wrap.base, u BOOST_PP_ENUM_TRAILING_PARAMS(n, a));
        }
    };


#undef  cv_qualifier

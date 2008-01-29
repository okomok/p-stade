

// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if !defined(cv_qualifier)
    #error Please define cv_qualifier.
#endif


    template<class ResultType, class T BOOST_PP_ENUM_TRAILING_PARAMS(n, class A)>
    struct result_<ResultType (T::*)(args) cv_qualifier>
    {
        typedef ResultType (T::*base_type)(args) cv_qualifier;

        typedef ResultType result_type;

        base_type m_base;

        base_type const& base() const
        {
            return m_base;
        }

        template<class U>
        result_type operator()(U& u BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(n, A, a)) const
        {
            return detail::free_call<T, result_type>(m_base, u BOOST_PP_ENUM_TRAILING_PARAMS(n, a));
        }

        template<class U>
        result_type operator()(U const& u BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(n, A, a)) const
        {
            return detail::free_call<T, result_type>(m_base, u BOOST_PP_ENUM_TRAILING_PARAMS(n, a));
        }
    };


#undef  cv_qualifier

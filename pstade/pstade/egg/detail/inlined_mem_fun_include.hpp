

// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if !defined(cv_qualifier)
    #error Please define cv_qualifier.
#endif


    template<class R, class T BOOST_PP_ENUM_TRAILING_PARAMS(n, class A), R (T::*ptr)(fparams) cv_qualifier>
    struct inlined<R (T::*)(fparams) cv_qualifier, ptr>
    {
        typedef inlined type;

        typedef R result_type;

        template<class U>
        result_type operator()(U& u BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(n, A, a)) const
        {
            return detail::free_call<R, T>(ptr, u BOOST_PP_ENUM_TRAILING_PARAMS(n, a));
        }

        template<class U>
        result_type operator()(U const& u BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(n, A, a)) const
        {
            return detail::free_call<R, T>(ptr, u BOOST_PP_ENUM_TRAILING_PARAMS(n, a));
        }
    };


#undef  cv_qualifier

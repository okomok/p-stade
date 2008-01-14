#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_OVEN_PARALLEL_HPP
#define PSTADE_OVEN_PARALLEL_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Turns a base object into ParallelSafe one.


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/egg/pstade/pod_constant.hpp>
#include <boost/egg/pstade/preprocessor.hpp>
#include <boost/egg/pstade/result_of.hpp>
#include "./apply_decl.hpp"
#include "./by_value.hpp"
#include "./config.hpp" // BOOST_EGG_MAX_ARITY, BOOST_EGG_HAS_THREADS
#include "./function_facade.hpp"
#include "./generator.hpp"

#if defined(BOOST_EGG_HAS_THREADS)
    #include <boost/detail/lightweight_mutex.hpp>
#endif


namespace pstade { namespace egg {


    namespace parallel_detail {


        template<class Base>
        struct result_ :
            function_facade<result_<Base>, typename result_of<Base()>::type>
        {
#if defined(BOOST_EGG_HAS_THREADS)
        private:
            typedef boost::detail::lightweight_mutex mutex_t;
            typedef mutex_t::scoped_lock scoped_lock_t;
        public:
#endif

        // 0ary
            template<class Result>
            Result call() const
            {
#if defined(BOOST_EGG_HAS_THREADS)
                scoped_lock_t lock(*m_pmtx);
#endif
                return (*m_pbase)();
            }

        // 1ary-
            template<class Myself, BOOST_EGG_APPLY_DECL_PARAMS(BOOST_EGG_MAX_ARITY, A)>
            struct BOOST_EGG_APPLY_DECL;

            #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_EGG_MAX_ARITY, <boost/egg/parallel.hpp>))
            #include BOOST_PP_ITERATE()

            explicit result_(Base base) :
                m_pbase(new Base(base))
#if defined(BOOST_EGG_HAS_THREADS)
                , m_pmtx(new mutex_t())
#endif
            { }

            Base& base() const
            {
                return *m_pbase;
            }

        private:
            boost::shared_ptr<Base> m_pbase;
#if defined(BOOST_EGG_HAS_THREADS)
            boost::shared_ptr<mutex_t> m_pmtx;
#endif
        };


    } // namespace parallel_detail


    typedef
        generator<
            parallel_detail::result_< deduce<boost::mpl::_1, as_value> >,
            boost::use_default,
            boost::use_default,
            by_value
        >::type
    T_parallel;

    PSTADE_POD_CONSTANT((T_parallel), parallel) = BOOST_EGG_GENERATOR();


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)> :
        result_of<Base(PSTADE_PP_ENUM_PARAMS_WITH(n, A, &))>
    { };

    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
#if defined(BOOST_EGG_HAS_THREADS)
        scoped_lock_t lock(*m_pmtx);
#endif
        return (*m_pbase)(BOOST_PP_ENUM_PARAMS(n, a));
    }


#undef n
#endif

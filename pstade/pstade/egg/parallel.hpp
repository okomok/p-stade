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


#include <boost/shared_ptr.hpp>
#include <pstade/derived_from.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "./by_cref.hpp"
#include "./by_perfect.hpp"
#include "./by_value.hpp"
#include "./config.hpp" // PSTADE_EGG_HAS_THREADS
#include "./function_facade.hpp"
#include "./fuse.hpp"
#include "./unfuse.hpp"

#if defined(PSTADE_EGG_HAS_THREADS)
    #include <boost/detail/lightweight_mutex.hpp>
#endif


namespace pstade { namespace egg {


    namespace parallel_detail {


        template<class Base>
        struct fused_result :
            function_facade<fused_result<Base>, by_cref, use_nullary_result>
        {
#if defined(PSTADE_EGG_HAS_THREADS)
        private:
            typedef boost::detail::lightweight_mutex mutex_t;
            typedef mutex_t::scoped_lock scoped_lock_t;

        public:
#endif
            template<class Me, class Args>
            struct apply :
                result_of<
                    typename result_of<T_fuse(Base &)>::type(Args &)
                >
            { };

            template<class Re, class Args>
            Re call(Args &args) const
            {
#if defined(PSTADE_EGG_HAS_THREADS)
                scoped_lock_t lock(*m_pmtx);
#endif
                return fuse(*m_pbase)(args);
            }

            explicit fused_result(Base base) :
                m_pbase(new Base(base))
#if defined(PSTADE_EGG_HAS_THREADS)
                , m_pmtx(new mutex_t())
#endif
            { }

            Base &base() const
            {
                return *m_pbase;
            }

        private:
            boost::shared_ptr<Base> m_pbase;
#if defined(PSTADE_EGG_HAS_THREADS)
            boost::shared_ptr<mutex_t> m_pmtx;
#endif
        };


        template<class Strategy>
        struct little
        {
            typedef
                X_unfuse<use_nullary_result, boost::use_default, Strategy>
            unfuse_t;

            template<class Me, class Base>
            struct apply :
                result_of<unfuse_t(fused_result<Base>)>
            { };

            template<class Re, class Base>
            Re call(Base base) const
            {
                return unfuse_t()(fused_result<Base>(base));
            }
        };


    } // namespace parallel_detail


    template<class Strategy = by_perfect>
    struct X_parallel : derived_from<
        function<parallel_detail::little<Strategy>, by_value>
    >
    { };

    typedef X_parallel<>::base_class T_parallel;
    PSTADE_POD_CONSTANT((T_parallel), parallel) = {{}};


} } // namespace pstade::egg


#include "./detail/suffix.hpp"
#endif

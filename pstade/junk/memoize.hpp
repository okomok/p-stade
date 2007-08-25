#ifndef PSTADE_EGG_MEMOIZE_HPP
#define PSTADE_EGG_MEMOIZE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://www.kmonos.net/wlog/52.php
// http://d.hatena.ne.jp/Cryolite/20050902#p1


#include <map>
#include <boost/any.hpp>
#include <boost/assert.hpp>
#include <boost/shared_ptr.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "./config.hpp" // PSTADE_EGG_HAS_THREADS
#include "./fix.hpp"
#include "./function_facade.hpp"

#if defined(PSTADE_EGG_HAS_THREADS)
    #include <boost/detail/lightweight_mutex.hpp>
#endif


namespace pstade { namespace egg {


    namespace memoize_detail {


#if defined(PSTADE_EGG_HAS_THREADS)
        typedef boost::detail::lightweight_mutex mutex_t;
        typedef boost::detail::lightweight_mutex::scoped_lock scoped_lock_t;
#endif

        struct op_wrap_ :
            function_facade<op_wrap_>
        {
            template<class Myself, class Base, class Fixed, class Arg>
            struct apply :
                result_of<
                    typename result_of<Base(Fixed&)>::type(Arg&)
                >
            { };

            template<class Result, class Base, class Fixed, class Arg>
            Result call(Base& base, Fixed& fixed, Arg const& arg) const
            {
                typedef std::map<Arg, Result> map_t;

                // Hmm, cleary recursive lock...
#if defined(PSTADE_EGG_HAS_THREADS)
                scoped_lock_t lock(*m_pmtx);
#endif

                if (m_pany->empty()) {
                    *m_pany = map_t();
                }

                map_t& m = boost::any_cast<map_t&>(*m_pany);

                typename map_t::iterator it = m.find(arg);
                if (it != m.end())
                    return it->second;
                else
                    return m[arg] = base(fixed)(arg);
            }

            op_wrap_() :
                m_pany(new boost::any())
#if defined(PSTADE_EGG_HAS_THREADS)
                , m_pmtx(new mutex_t())
#endif
            { }

        private:
            boost::shared_ptr<boost::any> m_pany;
#if defined(PSTADE_EGG_HAS_THREADS)
            boost::shared_ptr<mutex_t> m_pmtx;
#endif
        };


        struct baby
        {
            template<class Myself, class Base_>
            struct apply :
                result_of<
                    op_fix(
                        typename result_of<
                            typename result_of<op_curry3(op_wrap_)>::type(typename result_of<op_curry2(Base_&)>::type)
                        >::type
                    )
                >
            { };

            template<class Result, class Base_>
            Result call(Base_& base) const
            {
                return fix(
                    curry3(op_wrap_())(curry2(base))
                );
            }
        };


    } // namespace memoize_detail


    typedef function<memoize_detail::baby> op_memoize;
    PSTADE_POD_CONSTANT((op_memoize), memoize) = {{}};


} } // namespace pstade::egg


#endif

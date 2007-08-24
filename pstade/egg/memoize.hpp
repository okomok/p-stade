#ifndef PSTADE_EGG_MEMOIZE_HPP
#define PSTADE_EGG_MEMOIZE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Concept:
//
// Any RecusionBlock b, the following must be met:
//   1. typeof(b)::result_type is a valid expression.
//   2. typeof(b)::argument_type is a valid expression.
//   3. For any unspecified object r and typeof(b)::argument_type object a,
//        b(r, a) is a valid expression.
//
// See also:
//
// http://www.kmonos.net/wlog/52.php
// http://d.hatena.ne.jp/Cryolite/20050902#p1


#include <map>
#include <boost/assert.hpp>
#include <boost/config.hpp> // BOOST_HAS_THREADS
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <pstade/pod_constant.hpp>
#include "./generator.hpp"

#if defined(BOOST_HAS_THREADS)
    #include <boost/detail/lightweight_mutex.hpp>
#endif


namespace pstade { namespace egg {


    namespace memoize_detail {


        template<class Argument, class Result>
        struct memo :
            private boost::noncopyable
        {
        private:
            typedef std::map<Argument, Result> table_t;

        public:
            template<class Fix, class RecursionBlock>
            Result const& apply(Fix fix, RecursionBlock block, Argument const& a)
            {
#if defined(BOOST_HAS_THREADS)
                boost::detail::lightweight_mutex::scoped_lock lock(m_mutex);
#endif
                typename table_t::iterator it = m_table.find(a);
                if (it != m_table.end())
                    return it->second;
                else
                    return m_table[a] = block(fix, a);
            }

        private:
            table_t m_table;
#if defined(BOOST_HAS_THREADS)
    mutable boost::detail::lightweight_mutex m_mutex;
#endif
        };


        // This can't be static-initialized.

        template<class RecursionBlock>
        struct fix
        {
            typedef typename RecursionBlock::argument_type argument_type;
            typedef typename RecursionBlock::result_type result_type;
            typedef memo<argument_type, result_type> memo_type;

            result_type operator()(argument_type const& a) const
            {
                return m_pmemo->apply(*this, m_block, a);
            }

            explicit fix(RecursionBlock block) :
                m_block(block), m_pmemo(new memo_type())
            { }

        private:
            RecursionBlock m_block;
            memo_type *m_pmemo;
        };


    } // namespace memoize_detail


    typedef
        generator<
            memoize_detail::fix< deduce<boost::mpl::_1, as_value> >
        >::type
    op_memoize;

    PSTADE_POD_CONSTANT((op_memoize), memoize) = PSTADE_EGG_GENERATOR;


} } // namespace pstade::egg


#endif

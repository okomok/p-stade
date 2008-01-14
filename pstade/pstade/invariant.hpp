#ifndef PSTADE_INVARIANT_HPP
#define PSTADE_INVARIANT_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n1962.html


#include <boost/assert.hpp>
#include <boost/noncopyable.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/scoped_ptr.hpp>
#include <pstade/debug.hpp>
#include <pstade/nonconstructible.hpp>
#include <pstade/pod_constant.hpp>


namespace pstade {


    class invariant_access :
        private nonconstructible
    {
    public:
        template<class T>
        static void detail_invariant(T const &x)
        {
            x.pstade_invariant();
        }
    };


    struct T_invariant
    {
        typedef bool result_type; // for assert macro.

        template<class InvariantAssertable>
        result_type operator()(InvariantAssertable const &ia) const
        {
            debugging();

            try {
                invariant_access::detail_invariant(ia);
            }
            catch (...) {
                BOOST_ASSERT(!"class invariant is broken.");
            }

            return true;
        }
    };

    PSTADE_POD_CONSTANT((T_invariant), invariant) = {};


    namespace invariant_detail {


        struct placeholder
        {
            virtual void pstade_invariant() const = 0;
            virtual ~placeholder() { }
        };

        template<class InvariantAssertable>
        struct holder :
            placeholder
        {
            explicit holder(InvariantAssertable const &ia) :
                m_ia(ia)
            { }

            virtual void pstade_invariant() const
            {
                invariant(m_ia);
            }

            InvariantAssertable const &m_ia;
        };


        struct evaluator :
            private boost::noncopyable
        {
            template<class InvariantAssertable>
            evaluator(InvariantAssertable const &ia, bool ctor, bool dtor) :
                m_pia(new holder<InvariantAssertable>(ia)),
                m_dtor(dtor)
            {
                if (ctor)
                    invariant(*m_pia);
            }

            ~evaluator()
            {
                if (m_dtor)
                    invariant(*m_pia);
            }

        private:
            boost::scoped_ptr<placeholder> m_pia;
            bool m_dtor;
        };


    } // namespace invariant_detail


} // namespace pstade


#if !defined(NDEBUG)

    #define PSTADE_INVARIANT(As) \
        friend class pstade::invariant_access; \
        void pstade_invariant() const \
        { \
            PSTADE_INVARIANT_expand(As) \
        } \
    /**/

        #define PSTADE_INVARIANT_expand(As) BOOST_PP_SEQ_FOR_EACH(PSTADE_INVARIANT_expand_op, ~, As)
        #define PSTADE_INVARIANT_expand_op(R, _, A) BOOST_ASSERT("broken class invariant:" && (A));

    #define PSTADE_INVARIANT_ASSERT() \
        pstade::invariant(*this); \
    /**/

    #define PSTADE_INVARIANT_SCOPE() \
        pstade::invariant_detail::evaluator pstade_invariant_detail_evaluator_of(*this, true, true); \
    /**/

#else

    #define PSTADE_INVARIANT(As)
    #define PSTADE_INVARIANT_ASSERT()
    #define PSTADE_INVARIANT_SCOPE()

#endif // !defined(NDEBUG)


#endif

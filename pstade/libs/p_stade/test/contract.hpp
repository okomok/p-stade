#ifndef PSTADE_CONTRACT_HPP
#define PSTADE_CONTRACT_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n1962.html


#include <cassert> // revival!
#include <stdexcept> // logic_error
#include <boost/assert.hpp>
#include <boost/mpl/aux_/preprocessor/token_equal.hpp>
#include <boost/noncopyable.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <pstade/debugging.hpp>
#include <pstade/nonconstructible.hpp>


namespace pstade {


// class invariants
//

class contract_access :
    private nonconstructible
{
public:
    template< class T > static
    void detail_invariant(T const& x)
    {
        pstade::debugging();
        x.pstade_invariant();
    }
};


template< class T > inline
void invariant(T const& x)
{
    try {
        contract_access::detail_invariant(x);
    }
    catch (...) {
        BOOST_ASSERT("class invariant is broken." && false);
    }
}


namespace invariant_checker_detail {


    struct placeholder
    {
        virtual void pstade_invariant() const = 0;
        virtual ~placeholder() { }
    };


    template< class T >
    struct holder :
        placeholder
    {
        explicit holder(T const& x) :
            m_x(x)
        { }

        virtual void pstade_invariant() const
        {
            pstade::invariant(m_x);
        }

        T const& m_x;
    };


    struct impl :
        private boost::noncopyable
    {
        template< class T >
        explicit impl(T const& x, bool pre, bool post) :
            m_px(new holder<T>(x)), m_post(post)
        {
            if (pre)
                pstade::invariant(*m_px);
        }

        ~impl()
        {
            if (m_post)
                pstade::invariant(*m_px);
        }

    private:
        boost::scoped_ptr<placeholder> m_px;
        bool m_post;
    };


} // namespace invariant_checker_detail


struct invariant_checker
    // must be copyable for 'catch'.
    // See Standard 15.1/5 or 15.3/16.
{
    template< class T >
    explicit invariant_checker(T const& x, bool pre, bool post) :
        m_pimpl(new invariant_checker_detail::impl(x, pre, post))
    { };

private:
    boost::shared_ptr<invariant_checker_detail::impl> m_pimpl;
};


namespace contract_detail {


    template< class Result >
    struct result_box :
        std::logic_error
    {
        explicit result_box(Result const& result) :
            std::logic_error("'PSTADE_POSTCONDITION(*void*)' is not allowed."),
            m_result(result)
        { }

        Result const& operator *() const
        {
            return m_result;
        }

    private:
        Result m_result;
    };


    struct baby_return
    {
        template< class Unused, class T >
        struct result
        {
        #if !defined(NDEBUG)
            
        #else
            typedef T& type;
        #endif
        };

        template< class Result, class T >
        Result call(T& x)
        {
        #if !defined(NDEBUG)
            return x;
    #else
            
    #endif
        }
    };


    struct never_thrown
    { };


} // namespace contract_detail





#else


#endif

} // namespace pstade


// macros
//

#if !defined(NDEBUG)

    #define PSTADE_RETURN(result) \
        pstade::contract_detail::return_(result) \
    /**/


    #define PSTADE_PRECONDITION(As) \
        { \
            As \
            try \
    /**/

    #define PSTADE_POSTCONDITION(Result) \
        BOOST_PP_IIF (BOOST_MPL_PP_TOKEN_EQUAL(Result, void), \
            PSTADE_POSTCONDITION_void, \
            PSTADE_POSTCONDITION_non_void \
        )(Result) \
    /**/

        #if !defined(BOOST_MPL_PP_TOKEN_EQUAL_void)
            #define BOOST_MPL_PP_TOKEN_EQUAL_void(A) \
                A \
            /**/
        #endif

        #define PSTADE_POSTCONDITION_void(Void) \
            catch (pstade::contract_detail::never_thrown const&) { \
                    PSTADE_POSTCONDITION_void_ \
        /**/

        #define PSTADE_POSTCONDITION_void_(As) \
                    As \
                } \
            } \
        /**/

        #define PSTADE_POSTCONDITION_non_void(Result) \
                catch (pstade::contract_detail::result_box< Result > const& result) { \
                    PSTADE_POSTCONDITION_non_void_ \
        /**/

        #define PSTADE_POSTCONDITION_non_void_(As) \
                    As \
                    return *result; \
                } \
            } \
        /**/

    #define PSTADE_INVARIANT(As) \
        friend class pstade::contract_access; \
        void pstade_invariant() const \
        { \
            As \
        } \
    /**/

    // See Standard 15.1/4.
    #define PSTADE_PUBLIC_PRECONDITION(As) \
        { \
            As \
            pstade::invariant_checker pstade_detail_invariant_checker_of(*this, true, true); \
            try \
    /**/

    #define PSTADE_CONSTRUCTOR_PRECONDITION() \
        { \
            As \
            pstade::invariant_checker pstade_detail_invariant_checker_of(*this, false, true); \
            try \
    /**/

    #define PSTADE_DESTRUCTOR_PRECONDITION() \
        { \
            As \
            pstade::invariant_checker pstade_detail_invariant_checker_of(*this, true, false); \
            try \
    /**/

    #define PSTADE_BLOCK_INVARIANT(As) \
        try { \
            As \
        } \
        catch (...) { \
            BOOST_ASSERT("block invariant is broken." && false); \
        } \
    /**/

#else

    #define PSTADE_RETURN(result) return (result)

    #define PSTADE_PRECONDITION(As)
    #define PSTADE_POSTCONDITION(Result) PSTADE_POSTCONDITION_
    #define PSTADE_POSTCONDITION_(As)

    #define PSTADE_INVARIANT(As)
    #define PSTADE_PUBLIC_PRECONDITION(As)
    #define PSTADE_CONSTRUCTOR_PRECONDITION(As)
    #define PSTADE_DESTRUCTOR_PRECONDITION(As)

    #define PSTADE_BLOCK_INVARIANT(As)

#endif // !defined(NDEBUG)


#endif

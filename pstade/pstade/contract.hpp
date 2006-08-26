#ifndef PSTADE_CONTRACT_HPP
#define PSTADE_CONTRACT_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n1962.html


#include <cassert> // revival!
#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <pstade/for_debug.hpp>
#include <pstade/nonconstructible.hpp>
#include <pstade/unused.hpp>


// Workarounds
//

#if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
    // VC7.1 function-try-block doesn't support function templates.
    #define PSTADE_CONTRACT_NO_FUNCTION_TEMPLATE_TRY_BLOCK
#endif


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
        pstade::for_debug();
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
        explicit impl(T const& x, bool ctor, bool dtor) :
            m_px(new holder<T>(x)), m_dtor(dtor)
        {
            if (ctor)
                pstade::invariant(*m_px);
        }

        ~impl()
        {
            if (m_dtor)
                pstade::invariant(*m_px);
        }

    private:
        boost::scoped_ptr<placeholder> m_px;
        bool m_dtor;
    };


} // namespace invariant_checker_detail


struct invariant_checker
    // must be copyable for 'catch'.
    // See Standard 15.1/5 or 15.3/16.
{
    template< class T >
    explicit invariant_checker(T const& x, bool ctor, bool dtor) :
        m_pimpl(new invariant_checker_detail::impl(x, ctor, dtor))
    { };

private:
    boost::shared_ptr<invariant_checker_detail::impl> m_pimpl;
};


namespace contract_detail {


    // Note:
    // cannot be derived from 'std::exception',
    // otherwise VC7.1/8 complains.
    struct goto_handler
    { };


    inline
    void suppress_unreachable_code_warning()
    { }


} // namespace contract_detail


} // namespace pstade


// macros
//

#if !defined(NDEBUG)

    #define PSTADE_PRECONDITION(As) \
        try { \
            As \
            throw pstade::contract_detail::goto_handler(); \
        } \
        catch (pstade::contract_detail::goto_handler const&) \
    /**/

    // See Standard 15.1/4.
    #define PSTADE_PUBLIC_PRECONDITION(As) \
        try { \
            As \
            throw pstade::invariant_checker(*this, true, true); \
        } \
        catch (pstade::invariant_checker const&) \
    /**/

    #define PSTADE_BLOCK_INVARIANT(As) \
        try { \
            As \
            pstade::contract_detail::suppress_unreachable_code_warning(); \
        } \
        catch (...) { \
            BOOST_ASSERT("block invariant is broken." && false); \
        } \
    /**/

    #define PSTADE_CONSTRUCTOR_PRECONDITION(As) \
        As \
        pstade::invariant_checker pstade_contract_detail_ctor_invariant_checker_of(*this, false, true); \
    /**/

    #define PSTADE_DESTRUCTOR_PRECONDITION(As) \
        As \
        pstade::invariant_checker pstade_contract_detail_dtor_invariant_checker_of(*this, true, false); \
    /**/

    // Workaround
    #if !defined(PSTADE_CONTRACT_NO_FUNCTION_TEMPLATE_TRY_BLOCK)
        #define PSTADE_PRECONDITION_        PSTADE_PRECONDITION
        #define PSTADE_PUBLIC_PRECONDITION_ PSTADE_PUBLIC_PRECONDITION
    #else
        #define PSTADE_PRECONDITION_(As)
        #define PSTADE_PUBLIC_PRECONDITION_(As)
    #endif

#else

    #define PSTADE_PRECONDITION(As)
    #define PSTADE_PUBLIC_PRECONDITION(As)
    #define PSTADE_BLOCK_INVARIANT(As)

    #define PSTADE_CONSTRUCTOR_PRECONDITION(As)
    #define PSTADE_DESTRUCTOR_PRECONDITION(As)

    #define PSTADE_PRECONDITION_(As)
    #define PSTADE_PUBLIC_PRECONDITION_(As)

#endif // !defined(NDEBUG)


#define PSTADE_INVARIANT \
    friend class pstade::contract_access; \
    void pstade_invariant() const \
/**/


#endif

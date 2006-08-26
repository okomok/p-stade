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
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/utility/enable_if.hpp>
#include <pstade/for_debug.hpp>
#include <pstade/has_xxx.hpp>
#include <pstade/implies.hpp>
#include <pstade/nonconstructible.hpp>
#include <pstade/overload.hpp>


namespace pstade {


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


namespace invariant_detail {


    PSTADE_HAS_TYPE(pstade_invariant_checkable)


    // member function
    //
    template< class T > inline
    typename boost::enable_if<has_pstade_invariant_checkable<T>,
    void>::type aux(T const& x)
    {
        contract_access::detail_invariant(x);
    }


    // ADL
    //
    template< class T > inline
    void pstade_invariant(T const& x)
    {
        pstade_invariant(x, overload<>());
    }

    template< class T > inline
    typename boost::disable_if<has_pstade_invariant_checkable<T>,
    void>::type aux(T const& x)
    {
        pstade_invariant(x);
    }


} // namespace invariant_detail


template< class T > inline
bool invariant(T const& x)
{
    try {
        invariant_detail::aux(x);
    }
    catch (...) {
        BOOST_ASSERT("invariant is broken." && false);
    }

    return true; // for 'assert'.
}


namespace invariant_checker_detail {


    struct placeholder
    {
        typedef int pstade_invariant_checkable;
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


} // namespace invariant_checker_detail


struct invariant_checker :
    private boost::noncopyable
{
    template< class T >
    explicit invariant_checker(T const& x, bool ctor, bool dtor) :
        m_px(new invariant_checker_detail::holder<T>(x)),
        m_dtor(dtor)
    {
        if (ctor)
            pstade::invariant(*m_px);
    }

    ~invariant_checker()
    {
        if (m_dtor)
            pstade::invariant(*m_px);
    }

private:
    boost::scoped_ptr<invariant_checker_detail::placeholder> m_px;
    bool m_dtor;
};


} // namespace pstade


// macros
//

#define PSTADE_CLASS_INVARIANT \
    typedef int pstade_invariant_checkable; \
    friend class pstade::contract_access; \
    void pstade_invariant() const \
/**/


#if !defined(NDEBUG)

    #define PSTADE_PUBLIC_PRECONDITION \
        pstade::invariant_checker pstade_contract_detail_public_precond_checker_of(*this, true, true); \
    /**/

    #define PSTADE_CONSTRUCTOR_PRECONDITION \
        pstade::invariant_checker pstade_contract_detail_ctor_invariant_checker_of(*this, false, true); \
    /**/

    #define PSTADE_DESTRUCTOR_PRECONDITION \
        pstade::invariant_checker pstade_contract_detail_dtor_invariant_checker_of(*this, true, false); \
    /**/

#else

    #define PSTADE_PUBLIC_PRECONDITION
    #define PSTADE_CONSTRUCTOR_PRECONDITION
    #define PSTADE_DESTRUCTOR_PRECONDITION

#endif // !defined(NDEBUG)


#define PSTADE_PRECONDITION
#define PSTADE_POSTCONDITION
#define PSTADE_INVARIANT


#endif

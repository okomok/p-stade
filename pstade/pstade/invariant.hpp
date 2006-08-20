#ifndef PSTADE_INVARIANT_HPP
#define PSTADE_INVARIANT_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>


namespace pstade {


#if !defined(NDEBUG)


struct invariant :
    private boost::noncopyable
{
    // friend
    //
    class access
    {
    public:
        template< class T > static
        bool detail_holds(T& x)
        {
            return x.pstade_invariant();
        }
    };

    // type erasure
    //
    struct placeholder
    {
        virtual bool holds() const = 0;
        virtual ~placeholder() { }
    };

    template< class T >
    struct holder :
        placeholder
    {
        explicit holder(T& x) :
            m_x(x)
        { }

        virtual bool holds() const
        {
            return access::detail_holds(m_x);
        }

        T& m_x;
    };

    // ctor/dtor
    //
    template< class T >
    explicit invariant(T& x) :
        m_px(new holder<T>(x))
    {
        BOOST_ASSERT(m_px->holds());
    }

    ~invariant()
    {
        BOOST_ASSERT(m_px->holds());
    }

private:
    boost::scoped_ptr<placeholder> m_px;
};


#else


struct invariant :
    private boost::noncopyable
{
    class access
    { };

    template< class T >
    explicit invariant(T& )
    { }
};


#endif // !defined(NDEBUG)


} // namespace pstade


#endif

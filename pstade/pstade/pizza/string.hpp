#ifndef PSTADE_PIZZA_STRING_HPP
#define PSTADE_PIZZA_STRING_HPP


// PStade.Pizza
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // ptrdiff_t
#include <sstream>
#include <string>
#include <boost/assert.hpp>
#include <boost/microsoft/sdk/tchar.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include <boost/mpl/if.hpp>
#include <boost/noncopyable.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/throw_exception.hpp>
#include <pstade/oven/array_range.hpp>
#include <pstade/oven/null_terminate_range.hpp>
#include <pstade/tomato/c_str.hpp>
#include <pstade/tomato/diet/valid.hpp>
#include "./access.hpp"
#include "./detail/has_pstade_pizza_profile.hpp"
#include "./error.hpp"


namespace pstade { namespace pizza {


struct value_not_found :
    error
{
    value_not_found(const std::string& msg) :
        error(msg)
    { }
};


namespace string_detail {


    struct member_function
    {
        template< class Profile > static
        bool call(Profile& pr, const TCHAR *pszValueName, TCHAR *pFirst, TCHAR *pLast)
        {
            return access::detail_query_string(pr, pszValueName, pFirst, pLast);
        }
    };


    struct adl_customization
    {
        template< class Profile > static
        bool call(Profile& pr, const TCHAR *pszValueName, TCHAR *pFirst, TCHAR *pLast)
        {
            return pstade_pizza_query_string(pr, pszValueName, pFirst, pLast, overload());
        }
    };


    struct placeholder
    {
        virtual ~placeholder()
        { }

        bool query_string(const TCHAR *pszValueName, TCHAR *pFirst, TCHAR *pLast)
        {
            return query_string_impl(pszValueName, pFirst, pLast);
        }
    
    protected:
        virtual bool query_string_impl(const TCHAR *pszValueName, TCHAR *pFirst, TCHAR *pLast) = 0;
    };


    template< class Profile >
    struct holder :
        placeholder
    {
        explicit holder(Profile& pr) :
            m_held(pr)
        { }
    
    protected:
        virtual bool query_string_impl(const TCHAR *pszValueName, TCHAR *pFirst, TCHAR *pLast)
        {
            typedef typename
            boost::mpl::if_< detail::has_pstade_pizza_profile<Profile>,
                member_function,
                adl_customization
            >::type impl_t;

            return impl_t::call(m_held, pszValueName, pFirst, pLast);
        }

    private:
        Profile& m_held;
    };


    inline
    void throw_error(const TCHAR *pszValueName)
    {
        std::stringstream msg;
        msg << "<value-name>" << pszValueName << "</value-name>";
        value_not_found err(msg.str());
        boost::throw_exception(err);
    };


    typedef oven::array_range<TCHAR>
    buffer_t;


    struct buffer_initer
    {
        template< class Profile >
        buffer_initer(Profile& pr, const TCHAR *pszValueName, std::size_t bufsz) :
            m_ptr(new holder<Profile>(pr)),
            m_buf(1 + bufsz)
        {
            BOOST_ASSERT(diet::valid(pszValueName));
            BOOST_ASSERT(!boost::empty(m_buf));

            if (!m_ptr->query_string(pszValueName, boost::begin(m_buf), boost::end(m_buf)))
                string_detail::throw_error(pszValueName);

            BOOST_ASSERT(oven::is_null_terminated(m_buf));
        }

    protected:
        boost::scoped_ptr<placeholder> m_ptr;
        buffer_t m_buf;
    };


} // namespace string_detail


struct string :
    private string_detail::buffer_initer,
    oven::null_terminate_range<string_detail::buffer_t>,
    private boost::noncopyable
{
    typedef const TCHAR *const_iterator;
    typedef string pstade_tomato_cstringizable; // yes!

private:
    typedef string_detail::buffer_initer initer_t; 
    typedef oven::null_terminate_range<string_detail::buffer_t> super_t;

public:
    template< class Profile, class CStringizable >
    explicit string(Profile& pr, const CStringizable& valueName, std::ptrdiff_t bufsz = 256) :
        initer_t(pr, tomato::c_str(valueName), bufsz),
        super_t(m_buf)
    { }

    const TCHAR *c_str() const
    { return boost::begin(m_buf); }

    const TCHAR *pstade_tomato_c_str() const
    { return c_str(); }
};


} } // namespace pstade::pizza


#endif

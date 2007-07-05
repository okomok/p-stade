#ifndef PSTADE_PIZZA_STRING_HPP
#define PSTADE_PIZZA_STRING_HPP


// PStade.Pizza
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // ptrdiff_t
#include <sstream>
#include <string>
#include <boost/assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/noncopyable.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/throw_exception.hpp>
#include <pstade/gravy/sdk/tchar.hpp>
#include <pstade/gravy/sdk/windows.hpp>
#include <pstade/detail/overload.hpp>
#include <pstade/oven/array_range.hpp>
#include <pstade/oven/as_c_str.hpp>
#include <pstade/oven/range_constantable.hpp>
#include <pstade/result_of.hpp>
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
        bool call(Profile& pr, TCHAR const *pszValueName, TCHAR *pFirst, TCHAR *pLast)
        {
            return access::detail_query_string(pr, pszValueName, pFirst, pLast);
        }
    };


    struct adl_customization
    {
        template< class Profile > static
        bool call(Profile& pr, TCHAR const *pszValueName, TCHAR *pFirst, TCHAR *pLast)
        {
            return pstade_pizza_query_string(pr, pszValueName, pFirst, pLast, pstade::detail::overload<>());
        }
    };


    struct placeholder
    {
        virtual ~placeholder()
        { }

        bool query_string(TCHAR const *pszValueName, TCHAR *pFirst, TCHAR *pLast)
        {
            return override_query_string(pszValueName, pFirst, pLast);
        }
    
    protected:
        virtual bool override_query_string(TCHAR const *pszValueName, TCHAR *pFirst, TCHAR *pLast) = 0;
    };


    template< class Profile >
    struct holder :
        placeholder
    {
        explicit holder(Profile& pr) :
            m_held(pr)
        { }
    
    protected:
        bool override_query_string(TCHAR const *pszValueName, TCHAR *pFirst, TCHAR *pLast)
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
    void throw_error(TCHAR const *pszValueName)
    {
        std::stringstream msg;
        msg << "<value-name>" << pszValueName << "</value-name>";
        value_not_found err(msg.str());
        boost::throw_exception(err);
    };


    typedef oven::array_range<TCHAR>
    buffer_t;


    struct buffer_init
    {
        template< class Profile >
        buffer_init(Profile& pr, TCHAR const *pszValueName, std::size_t bufsz) :
            m_ptr(new holder<Profile>(pr)),
            m_buf(1 + bufsz)
        {
            BOOST_ASSERT(!boost::empty(m_buf));

            if (!m_ptr->query_string(pszValueName, boost::begin(m_buf), boost::end(m_buf)))
                string_detail::throw_error(pszValueName);

            BOOST_ASSERT(oven::contains_zero(m_buf));
        }

    protected:
        boost::scoped_ptr<placeholder> m_ptr;
        buffer_t m_buf;
    };


} // namespace string_detail


struct string :
    private string_detail::buffer_init,
    result_of<oven::op_as_c_str(string_detail::buffer_t&)>::type,
    private oven::range_constantable<string, TCHAR const *>,
    private boost::noncopyable
{
    typedef TCHAR const *const_iterator;

private:
    typedef string_detail::buffer_init init_t; 
    typedef result_of<oven::op_as_c_str(string_detail::buffer_t&)>::type super_t;

public:
    template< class Profile, class CStringizable >
    string(Profile& pr, CStringizable const& valueName, std::ptrdiff_t bufsz = 256) :
        init_t(pr, gravy::c_str(valueName), bufsz),
        super_t(oven::as_c_str(m_buf))
    { }

    friend
    TCHAR const *pstade_gravy_c_str(string const& self)
    {
        return boost::begin(self.m_buf);
    }
};


} } // namespace pstade::pizza


#endif

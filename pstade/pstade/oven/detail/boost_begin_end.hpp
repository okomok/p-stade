

// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Works around the bug that Boost.StringAlgorithm calls
// unqualified 'begin/end', then unintentional ADL is triggered.


#include <boost/range/result_iterator.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>



// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//



// begin
//


#ifndef BOOST_RANGE_BEGIN_HPP
#define BOOST_RANGE_BEGIN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <boost/type_traits/remove_const.hpp>
#include <boost/range/config.hpp>

#ifdef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
#include <boost/range/detail/begin.hpp>
#else

#include <boost/range/iterator.hpp>
#include <boost/range/const_iterator.hpp>

namespace boost
{

#if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564)) && \
    !BOOST_WORKAROUND(__GNUC__, < 3) \
    /**/
namespace range_detail
{
#endif

    //////////////////////////////////////////////////////////////////////
    // primary template
    //////////////////////////////////////////////////////////////////////

    template< typename C >
    inline BOOST_DEDUCED_TYPENAME range_const_iterator<C>::type
    boost_range_begin( const C& c )
    {
        return c.begin();
    }

    template< typename C >
    inline BOOST_DEDUCED_TYPENAME range_iterator<
                                                                        typename remove_const<C>::type >::type
    boost_range_begin( C& c )
    {
        return c.begin();
    }

    //////////////////////////////////////////////////////////////////////
    // pair
    //////////////////////////////////////////////////////////////////////

    template< typename Iterator >
    inline Iterator boost_range_begin( const std::pair<Iterator,Iterator>& p )
    {
        return p.first;
    }

    template< typename Iterator >
    inline Iterator boost_range_begin( std::pair<Iterator,Iterator>& p )
    {
        return p.first;
    }

    //////////////////////////////////////////////////////////////////////
    // array
    //////////////////////////////////////////////////////////////////////

    template< typename T, std::size_t sz >
    inline const T* boost_range_begin( const T (&array)[sz] )
    {
        return array;
    }

    template< typename T, std::size_t sz >
    inline T* boost_range_begin( T (&array)[sz] )
    {
        return array;
    }


    //////////////////////////////////////////////////////////////////////
    // string
    //////////////////////////////////////////////////////////////////////

#if 1 || BOOST_WORKAROUND(__MWERKS__, <= 0x3204 ) || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
// CW up to 9.3 and borland have troubles with function ordering
    inline const char* boost_range_begin( const char* s )
    {
        return s;
    }

    inline char* boost_range_begin( char* s )
    {
        return s;
    }

    inline const wchar_t* boost_range_begin( const wchar_t* s )
    {
        return s;
    }

    inline wchar_t* boost_range_begin( wchar_t* s )
    {
        return s;
    }
#else
    inline const char* boost_range_begin( const char*& s )
    {
        return s;
    }

    inline char* boost_range_begin( char*& s )
    {
        return s;
    }

    inline const wchar_t* boost_range_begin( const wchar_t*& s )
    {
        return s;
    }

    inline wchar_t* boost_range_begin( wchar_t*& s )
    {
        return s;
    }
#endif

#if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564)) && \
    !BOOST_WORKAROUND(__GNUC__, < 3) \
    /**/
} // namespace 'range_detail'
#endif


///////////////////////////////////////////////////////////////////////////////

    struct pstade_op_begin :
        pstade::callable<pstade_op_begin>
    {
        template<class Myself, class Range>
        struct apply :
            range_result_iterator<Range>
        { };

        template<class Result, class Range>
        Result call(Range& rng) const
        {
            using namespace range_detail;
            return boost_range_begin(rng);
        }
    };

    PSTADE_CONSTANT(begin, (pstade_op_begin))


    struct pstade_op_const_begin :
        pstade::callable<pstade_op_const_begin>
    {
        template<class Myself, class Range>
        struct apply :
            range_const_iterator<Range>
        { };

        template<class Result, class Range>
        Result call(Range const& rng) const
        {
            using namespace range_detail;
            return boost_range_begin(rng);
        }
    };

    PSTADE_CONSTANT(const_begin, (pstade_op_const_begin))

///////////////////////////////////////////////////////////////////////////////


} // namespace boost

#endif // BOOST_NO_FUNCTION_TEMPLATE_ORDERING


#endif 



// end
//


#ifndef BOOST_RANGE_END_HPP
#define BOOST_RANGE_END_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <boost/type_traits/remove_const.hpp>
#include <boost/range/config.hpp>

#ifdef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
#include <boost/range/detail/end.hpp>
#else

#include <boost/range/detail/implementation_help.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/const_iterator.hpp>

namespace boost
{

#if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564)) && \
    !BOOST_WORKAROUND(__GNUC__, < 3) \
    /**/
namespace range_detail
{
#endif

        //////////////////////////////////////////////////////////////////////
        // primary template
        //////////////////////////////////////////////////////////////////////

        template< typename C >
        inline BOOST_DEDUCED_TYPENAME range_const_iterator<C>::type
        boost_range_end( const C& c )
        {
            return c.end();
        }

        template< typename C >
                inline BOOST_DEDUCED_TYPENAME range_iterator<
                                        typename remove_const<C>::type >::type
        boost_range_end( C& c )
        {
            return c.end();
        }

        //////////////////////////////////////////////////////////////////////
        // pair
        //////////////////////////////////////////////////////////////////////

        template< typename Iterator >
        inline Iterator boost_range_end( const std::pair<Iterator,Iterator>& p )
        {
            return p.second;
        }

        template< typename Iterator >
        inline Iterator boost_range_end( std::pair<Iterator,Iterator>& p )
        {
            return p.second;
        }

        //////////////////////////////////////////////////////////////////////
        // array
        //////////////////////////////////////////////////////////////////////

        template< typename T, std::size_t sz >
        inline const T* boost_range_end( const T (&array)[sz] )
        {
            return range_detail::array_end<T,sz>( array );
        }

        template< typename T, std::size_t sz >
        inline T* boost_range_end( T (&array)[sz] )
        {
            return range_detail::array_end<T,sz>( array );
        }

        //////////////////////////////////////////////////////////////////////
        // string
        //////////////////////////////////////////////////////////////////////

#if 1 || BOOST_WORKAROUND(__MWERKS__, <= 0x3204 ) || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
// CW up to 9.3 and borland have troubles with function ordering
        inline char* boost_range_end( char* s )
        {
            return range_detail::str_end( s );
        }

        inline wchar_t* boost_range_end( wchar_t* s )
        {
            return range_detail::str_end( s );
        }

        inline const char* boost_range_end( const char* s )
        {
            return range_detail::str_end( s );
        }

        inline const wchar_t* boost_range_end( const wchar_t* s )
        {
            return range_detail::str_end( s );
        }
#else
        inline char* boost_range_end( char*& s )
        {
            return range_detail::str_end( s );
        }

        inline wchar_t* boost_range_end( wchar_t*& s )
        {
            return range_detail::str_end( s );
        }

        inline const char* boost_range_end( const char*& s )
        {
            return range_detail::str_end( s );
        }

        inline const wchar_t* boost_range_end( const wchar_t*& s )
        {
            return range_detail::str_end( s );
        }
#endif

#if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564)) && \
    !BOOST_WORKAROUND(__GNUC__, < 3) \
    /**/
} // namespace 'range_detail'
#endif


///////////////////////////////////////////////////////////////////////////////

    struct pstade_op_end :
        pstade::callable<pstade_op_end>
    {
        template<class Myself, class Range>
        struct apply :
            range_result_iterator<Range>
        { };

        template<class Result, class Range>
        Result call(Range& rng) const
        {
            using namespace range_detail;
            return boost_range_end(rng);
        }
    };

    PSTADE_CONSTANT(end, (pstade_op_end))


    struct pstade_op_const_end :
        pstade::callable<pstade_op_const_end>
    {
        template<class Myself, class Range>
        struct apply :
            range_const_iterator<Range>
        { };

        template<class Result, class Range>
        Result call(Range const& rng) const
        {
            using namespace range_detail;
            return boost_range_end(rng);
        }
    };

    PSTADE_CONSTANT(const_end, (pstade_op_const_end))

///////////////////////////////////////////////////////////////////////////////


} // namespace 'boost'



#endif // BOOST_NO_FUNCTION_TEMPLATE_ORDERING


#endif

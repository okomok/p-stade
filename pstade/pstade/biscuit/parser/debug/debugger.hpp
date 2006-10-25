#ifndef PSTADE_BISCUIT_PARSER_DEBUG_DEBUGGER_HPP
#define PSTADE_BISCUIT_PARSER_DEBUG_DEBUGGER_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iostream>
#include <string>
#include <typeinfo>
#include <boost/config.hpp> // NO_STD_WSTREAMBUF
#include <boost/foreach.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/or.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/instance.hpp>
#include <pstade/ios_init.hpp>
#include <pstade/is_ndebug.hpp>
#include <pstade/napkin/config.hpp> // NO_WIDESTRING
#include <pstade/napkin/ostream.hpp>
#include <pstade/napkin/ostream_char.hpp>
#include <pstade/oven/range_iterator.hpp>


namespace pstade { namespace biscuit {


namespace debugger_detail {


    PSTADE_INSTANCE(napkin::ostream, os, (std::cout))

    struct get_ostream
    {
        typedef napkin::ostream type;
        static napkin::ostream& call() { return os; }
    };    
    
    
#if !defined(PSTADE_NAPKIN_NO_WIDESTRING)

    PSTADE_INSTANCE(napkin::wostream, wos, (std::wcout))

    struct get_wostream
    {
        typedef napkin::wostream type;
        static napkin::wostream& call() { return wos; }
    };

#endif


    PSTADE_INSTANCE(int, class_trace_indent_count, value)

    struct indents
    {
        indents()
        {
            int spaces = 2 * class_trace_indent_count;
            m_str = std::string(spaces, ' ');
            ++class_trace_indent_count;
        }

        ~indents()
        {
            --class_trace_indent_count;
        }

        template< class OStream >
        OStream& output(OStream& out)
        {
            int spaces = 2 * class_trace_indent_count;
            for (int i = 0; i < spaces; ++i)
                out << ' ';

            return out;
        }

        std::string m_str;
    };


    template< class ParserName, class Parser, class On, class GetOStream >
    struct super_
    {
        struct on_release
        {
            template< class State, class UserState >
            static bool parse(State& s, UserState& us)
            {
                return Parser::parse(s, us);
            }

            typedef on_release type;
        };

        struct on_debug
        {
            template< class State, class UserState >
            static bool parse(State& s, UserState& us)
            {
                typedef typename GetOStream::type os_t;
                typedef typename napkin::ostream_char<os_t>::type char_t;
                typedef typename oven::range_iterator<State>::type iter_t;

                // If L'x' != 'x', output strings might look broken.
                // But 'type_info' doesn't support 'wstring', *never mind*.
                //
                indents inds;
                std::type_info const& tid = typeid(ParserName);
                std::string tag = std::string(tid.name());

                {
                    std::string stag = inds.m_str + tag + ": \"";

                    BOOST_FOREACH (char_t ch, stag) {
                        GetOStream::call() << ch;
                    }

                    for (iter_t it = s.get_cur(); it != boost::end(s); ++it) {
                        GetOStream::call() << *it;
                    }

                    GetOStream::call() << '"';
                    GetOStream::call() << '\n';
                }

                bool ok = Parser::parse(s, us);
                
                {
                    char em = ok ? '/' : '#';
                    std::string etag = inds.m_str + em + tag + ": \"";

                    BOOST_FOREACH (char_t ch, etag) {
                        GetOStream::call() << ch;
                    }

                    for (iter_t it = s.get_cur(); it != boost::end(s); ++it) {
                        GetOStream::call() << *it;
                    }

                    GetOStream::call() << '"';
                    GetOStream::call() << '\n';
                }

                return ok;
            }
            
            typedef on_debug type;
        };

        typedef typename boost::mpl::eval_if<
            boost::mpl::or_< is_ndebug<>, boost::mpl::not_<On> >,
            on_release,
            on_debug
        >::type type;
    };


} // namespace debugger_detail


// debugger
//

template<
    class ParserName,
    class Parser,
    class On = boost::mpl::true_
>
struct debugger :
    debugger_detail::super_<ParserName, Parser, On, debugger_detail::get_ostream>::type
{ };


template< class StringOutputable > inline
void debugger_reset_ostream(StringOutputable& out)
{
    debugger_detail::os.reset(out);
}


#if !defined(PSTADE_NAPKIN_NO_WIDESTRING)


// wdebugger
//
template<
    class ParserName,
    class Parser,
    class On = boost::mpl::true_
>
struct wdebugger :
    debugger_detail::super_<ParserName, Parser, On, debugger_detail::get_wostream>::type
{ };


template< class WideStringOutputable > inline
void wdebugger_reset_ostream(WideStringOutputable& out)
{
    debugger_detail::wos.reset(out);
}


#endif // !defined(BOOST_NO_STD_WSTREAMBUF)


} } // namespace pstade::biscuit


#endif

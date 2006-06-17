#ifndef PSTADE_BISCUIT_PARSER_DEBUG_DEBUGGER_HPP
#define PSTADE_BISCUIT_PARSER_DEBUG_DEBUGGER_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <string>
#include <typeinfo>
#include <boost/foreach.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/result_iterator.hpp>
#include <pstade/is_debug.hpp>

#if !defined(PSTADE_BISCUIT_DEBUG_OUT) && !defined(_WIN32_WCE)
    #include <iostream>
    #define PSTADE_BISCUIT_DEBUG_OUT std::cout
#endif


namespace pstade { namespace biscuit {


template< class Char = char, class Traits = std::char_traits<Char> >
struct basic_ostream_type
{
    typedef std::basic_ostream<Char, Traits> type;
};


namespace debugger_detail {

    // Note: if inline is missing, the compiler doesn't remove s_count.
    inline int& class_trace_indent_count()
    {
        static int s_count = 0;
        return s_count;
    }

    struct indents
    {
        indents()
        {
            int spaces = 2 * class_trace_indent_count();
            m_str = std::string(spaces, ' ');
            ++class_trace_indent_count();
        }

        ~indents()
        {
            --class_trace_indent_count();
        }

        template< class OStream >
        OStream& output(OStream& out)
        {
            int spaces = 2 * class_trace_indent_count();
            for (int i = 0; i < spaces; ++i)
                out << ' ';

            return out;
        }

        std::string m_str;
    };

    template< class ParserName, class Parser, class On > //class GetOStream >
    struct debugger_base
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
                typedef typename boost::range_result_iterator<State>::type iter_t;
                typedef boost::range_result_iterator<std::string>::type siter_t;

                indents inds;
                std::type_info const& tid = typeid(ParserName);
                std::string tag = std::string(tid.name());

                {
                    std::string stag = inds.m_str + tag + ": \"";
                    BOOST_FOREACH (char ch, stag) {
                        PSTADE_BISCUIT_DEBUG_OUT << ch;
                    }
                    for (iter_t it = s.get_cur(); it != boost::end(s); ++it) {
                        PSTADE_BISCUIT_DEBUG_OUT << *it;
                    }
                    PSTADE_BISCUIT_DEBUG_OUT << '"';
                    PSTADE_BISCUIT_DEBUG_OUT << '\n';
                }

                bool ok = Parser::parse(s, us);
                
                {
                    char em = ok ? '/' : '#';
                    std::string etag = inds.m_str + em + tag + ": \"";
                    BOOST_FOREACH (char ch, etag) {
                        PSTADE_BISCUIT_DEBUG_OUT << ch;
                    }
                    for (iter_t it = s.get_cur(); it != boost::end(s); ++it) {
                        PSTADE_BISCUIT_DEBUG_OUT << *it;
                    }
                    PSTADE_BISCUIT_DEBUG_OUT << '"';
                    PSTADE_BISCUIT_DEBUG_OUT << '\n';
                }

                return ok;
            }
            
            typedef on_debug type;
        };

        typedef typename boost::mpl::eval_if<
            boost::mpl::and_< pstade::is_debug<>, On >,
            on_debug,
            on_release
        >::type type;
    };

} // namespace debugger_detail


template<
    class ParserName,
    class Parser,
    class On = boost::mpl::true_
>
struct debugger :
    debugger_detail::debugger_base<ParserName, Parser, On>::type
{ };


} } // namespace pstade::biscuit


#endif

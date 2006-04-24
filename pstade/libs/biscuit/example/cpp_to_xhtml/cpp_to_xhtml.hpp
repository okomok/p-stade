#ifndef PSTADE_LIB_BISCUIT_EXAMPLE_CPP_TO_XHTML_HPP
#define PSTADE_LIB_BISCUIT_EXAMPLE_CPP_TO_XHTML_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Emulation of legacy Spirit's sample from
// http://spirit.sourceforge.net/distrib/spirit_1_6_1/libs/spirit/example/application/cpp_to_html/cpp_to_html.cpp
// Same bugs stand!


#include <iostream>
#include <string>
#include <boost/range.hpp>
#include <boost/noncopyable.hpp>


#include <pstade/biscuit.hpp>
#include "./cpp_keyword.hpp"


namespace cpp_to_xhtml
{
    using namespace biscuit;


    struct program;
    struct preprocessor;
    struct comment;
    struct keyword;
    struct special;
    struct string_;
    struct literal;
    struct number;
    struct identifier;
    struct spaces;
    typedef program start;

    struct escape0_action
    {
        void operator()(boost::sub_range<std::string>, std::ostream& out) { out << "&amp;"; }
    };
    struct escape1_action
    {
        void operator()(boost::sub_range<std::string>, std::ostream& out) { out << "&lt;"; }
    };
    struct escape2_action
    {
        void operator()(boost::sub_range<std::string>, std::ostream& out) { out << "&gt;"; }
    };
    struct escape3_action
    {
        void operator()(boost::sub_range<std::string>, std::ostream& out) { out << "&quot;"; }
    };

    struct output_
    {
        void operator()(boost::sub_range<std::string> rng, std::ostream& out)
        {
            out << std::string(boost::begin(rng), boost::end(rng));
        }
    };

    struct xhtml_special :
        or_<
            actor< chseq<'&'>, escape0_action >,
            actor< chseq<'<'>, escape1_action >,
            actor< chseq<'>'>, escape2_action >,
            actor< chseq<'"'>, escape3_action >
        >
    { };

    // vc8 requires '&' ( sub_range cannot be used as 'value' under vc8 )
    void escape_xhtml(boost::sub_range<std::string>  &  rng, std::ostream& out)
    {
        iterate<xhtml_special>(rng, out, output_());
    }

    // actions
    struct on_keyword
    {
        void operator()(boost::sub_range<std::string> rng, std::ostream& out)
        {
            out << "<span class=\"cpp_keyword\">";
            escape_xhtml(rng, out);
            out << "</span>";
        }
    };
    
    struct on_preprocessor
    {
        void operator()(boost::sub_range<std::string> rng, std::ostream& out)
        {
            out << "<span class=\"cpp_pp_directive\">";
            escape_xhtml(rng, out);
            out << "</span>";
        }
    };
    
    struct on_string_
    {
        void operator()(boost::sub_range<std::string> rng, std::ostream& out)
        {
            out << "<span class=\"cpp_string_literal\">";
            escape_xhtml(rng, out);
            out << "</span>";
        }
    };
    
    struct on_unexpected_char
    {
        void operator()(boost::sub_range<std::string> rng, std::ostream& out)
        {
            escape_xhtml(rng, out);
        }
    };
    
    struct on_comment
    {
        void operator()(boost::sub_range<std::string> rng, std::ostream& out)
        {
            out << "<span class=\"cpp_comment\">";
            escape_xhtml(rng, out);
            out << "</span>";
        }
    };

    struct on_identifier
    {
        void operator()(boost::sub_range<std::string> rng, std::ostream& out)
        {
            escape_xhtml(rng, out);
        }
    };

    struct on_special
    {
        void operator()(boost::sub_range<std::string> rng, std::ostream& out)
        {
            escape_xhtml(rng, out);
        }
    };

    struct on_literal
    {
        void operator()(boost::sub_range<std::string> rng, std::ostream& out)
        {
            out << "<span class=\"cpp_string_literal\">";
            escape_xhtml(rng, out);
            out << "</span>";
        }
    };

    struct on_number
    {
        void operator()(boost::sub_range<std::string> rng, std::ostream& out)
        {
            out << "<span class=\"cpp_number_literal\">";
            escape_xhtml(rng, out);
            out << "</span>";
        }
    };

    struct on_spaces
    {
        void operator()(boost::sub_range<std::string> rng, std::ostream& out)
        {
            escape_xhtml(rng, out);
        }
    };

    struct spaces :
        star<space>
    { };

    struct spaces_with_action :
        actor< star<space>, on_spaces >
    { };

    struct program :
        seq<
            spaces_with_action,
            star<
                or_<
                    actor< preprocessor,    on_preprocessor >,
                    actor< comment,             on_comment >,
                    actor< keyword,             on_keyword >,
                    actor< identifier,      on_identifier >,
                    actor< special,             on_special >,
                    actor< string_,             on_string_ >,
                    actor< literal,             on_literal >,
                    actor< number,              on_number >,
                    actor< any,                     on_unexpected_char >
                >
            >
        >
    { };
    
    struct preprocessor :
        seq<
            chseq<'#'>,
            seq< or_< alpha, chseq<'_'> >, star< or_<alnum, chseq<'_'> > > >,
            spaces
        >
    { };
    
    struct cpp_comment_p :
        seq< chseq<'/','/'>, star_before< any, eol > >
    { };
    
    struct c_comment_p :
        seq< chseq<'/','*'>, star_until< any, chseq<'*','/'> > >
    { };
    
    struct comment :
        seq<
            plus< or_< c_comment_p, cpp_comment_p > >,
            spaces
        >
    { };

    struct keyword :
        seq<
            cpp_keyword,
            not_< before< or_< alnum, chseq<'_'> > > >,
            spaces
        >
    { };
    
    struct special :
        seq<
            or_<
                chset<'~','!','%','^','&','*','(',')','+','='>,
                chset<'{','[','}',']',':',';',',','<','.','>'>,
                chset<'?','/','|','\\','-'>
            >,
            spaces
        >
    { };
    
    struct string_ :
        seq<
            opt< chset<'l','L'> >,
            seq<
                chseq<'"'>,
                star<
                    or_<
                        seq< chseq<'\\'>, any >,
                        not_< chseq<'"'> >
                    >
                >
            >,
            chseq<'"'>
        >
    { };

    struct literal :
        seq<
            opt< chset<'l','L'> >,
            seq<
                chseq<'\''>,
                star<
                    or_<
                        seq< chseq<'\\'>, any >,
                        not_< chseq<'\''> >
                    >
                >,
                chseq<'\''>
            >
        >
    { };


    struct real_p :
        seq<
            opt< chset<'+','-'> >,
            or_<
                seq< plus<digit>, chseq<'.'>, plus<digit> >,
                seq< plus<digit>, chseq<'.'> >,
                seq< chseq<'.'>, plus<digit> >,
                plus<digit>
            >,
            opt<
                seq<
                    chset<'e','E'>,
                    opt< chset<'+','-'> >,
                    plus<digit>
                >
            >
        >
    { };
    
    struct hex_p :
        plus<
            or_< chrng<'0','9'>, chrng<'a','f'>, chrng<'A','F'> >
        >
    { };
    
    struct oct_p :
        plus<
            chrng<'0','7'>
        >
    { };

    struct number :
        seq<
            or_<
                real_p,
                seq< as_lower< chseq<'0','x'> >, hex_p >,
                seq< chseq<'0'>, oct_p >
            >,
            star< as_lower< chset<'l','d','f','u'> > >,
            spaces
        >
    { };
    
    struct identifier :
        seq<
            seq<
                or_< alpha, chseq<'_'> >,
                star< or_< alnum, chseq<'_'> > >
            >,
            spaces
        >
    { };

}


// thanks to http://cham.ne.jp/piro/p_cp.html
inline std::string& tab2space(std::string& str_, int tab_ = 2) {
    std::string::size_type t_, n_, i_, nb_=0;
    while ((nb_ = t_ = str_.find('\t',nb_)) != std::string::npos) {
        n_ = str_.rfind('\n',t_) + 1;
        if (n_ == std::string::npos) n_ = 0;
        i_ = tab_ - (t_ - n_)%tab_;
        str_.replace(t_, 1, i_, ' ');
    }
    return str_;
}


#endif

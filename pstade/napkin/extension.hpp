#ifndef PSTADE_NAPKIN_EXTENSION_HPP
#define PSTADE_NAPKIN_EXTENSION_HPP


// PStade.Napkin
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <string> // basic_string
#include <boost/foreach.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <pstade/apple/is_sequence.hpp>
#include <pstade/has_xxx.hpp>
#include <pstade/oven/as_c_str.hpp>


namespace pstade_napkin_extension {


    struct output
    { };


    namespace detail {


        struct default_output
        {
            template< class T, class String >
            static void call(T& out, String psz)
            {
                out << psz;
            }
        };


        struct std_sequence_output
        {
            template< class T, class CharT >
            static void call(T& out, const CharT *psz)
            {
                BOOST_FOREACH (CharT ch, psz|pstade::oven::as_c_str) {
                    out.push_back(ch);
                    // out.insert(out.end(), ch);
                }
            }
        };


        PSTADE_HAS_TYPE(is_saving)
        PSTADE_HAS_TYPE(is_loading)

        template< class T >
        struct is_boost_archive :
            boost::mpl::and_<
                has_is_saving<T>,
                has_is_loading<T>
            >
        { };

        struct boost_archive_output
        {
            template< class T, class CharT >
            static void call(T& out, const CharT *psz)
            {
                std::basic_string<CharT> tmp(psz);
                out << tmp;
            }
        };


    } // namespace detail


    template< class T, class String > inline
    void pstade_napkin_(output, T& out, String psz)
    {
        typedef typename
        boost::mpl::eval_if< pstade::apple::is_sequence<T>,
            boost::mpl::identity<detail::std_sequence_output>,
            boost::mpl::eval_if< detail::is_boost_archive<T>,
                boost::mpl::identity<detail::boost_archive_output>,
                boost::mpl::identity<detail::default_output>
            >
        >::type impl_t;

        impl_t::call(out, psz);
    }


} // namespace pstade_napkin_extension


#endif

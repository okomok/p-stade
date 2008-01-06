#ifndef PSTADE_EGG_DETAIL_NAMED_EXTENSION_HPP
#define PSTADE_EGG_DETAIL_NAMED_EXTENSION_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/enable_if.hpp>


namespace pstade { namespace egg {

    template<class Function, int N>
    struct error_Nth_argument_must_be_supplied;

} }


namespace pstade_egg_extension {


    template<class X, int Index>
    struct default_value_error
    {
        typedef pstade::egg::error_Nth_argument_must_be_supplied<X, Index> result_type;
    };


    struct named_parameter_default
    {
        // Hmm, Keyword is preferable, but keyword_of<Index> would be needed.
        template<class X, int Index>
        struct default_ :
            default_value_error<X, Index>
        { };

        template<class X, class Keyword>
        struct index_of :
            Keyword::default_index_type
        { };
    };


    template<class Function, class EnableIf>
    struct named_parameter_base :
        named_parameter_default
    { };

    template<class Function>
    struct named_parameter_tag
    {
        typedef void type;
    };

    template<class Function, class Tag = typename named_parameter_tag<Function>::type>
    struct named_parameter :
        named_parameter_base<Function, pstade::enabler>
    { };


    using pstade::enable_if;


} // namespace pstade_egg_extension


namespace pstade { namespace egg { namespace detail {


    template<class Function, class Keyword>
    struct keyword_to_index
    {
        typedef pstade_egg_extension::named_parameter<Function> ext_t;
        typedef typename ext_t::template index_of<Function, Keyword>::type type;
    };


    template<class Function, class Index>
    struct make_default_value
    {
        typedef pstade_egg_extension::named_parameter<Function> ext_t;
        typedef typename ext_t::template default_<Function, Index::value> fun_t;
        typedef typename fun_t::result_type result_type;

        template<class Iter, class PrecedingArgs>
        result_type operator()(Iter, PrecedingArgs& args) const
        {
            return fun_t()(args);
        }
    };


} } } // namespace pstade::egg::detail


#endif

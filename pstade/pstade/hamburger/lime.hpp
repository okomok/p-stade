#ifndef PSTADE_HAMBURGER_LIME_HPP
#define PSTADE_HAMBURGER_LIME_HPP


// PStade.Hamburger
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/range/empty.hpp>
#include <pstade/lime/extension.hpp>
#include <pstade/lime/save.hpp> // save_default
#include <pstade/oven/copy_range.hpp>
#include <pstade/oven/equals.hpp>
#include <pstade/oven/to_function.hpp>
#include <pstade/unused.hpp>
#include <pstade/ustring.hpp>
#include "./element.hpp"
#include "./factory.hpp"
#include "./include.hpp"
#include "./load_save.hpp"
#include "./log.hpp"


namespace pstade_lime_extension {


    inline
    pstade::hamburger::element *
    pstade_lime_(new_node, pstade::hamburger::element& parent, pstade::ustring const& childName)
    {
        return pstade::hamburger::create_element(parent, childName);
    }


    template< class OutIter > inline
    void
    pstade_lime_(save_node, pstade::hamburger::element& node, OutIter const& out)
    {
        namespace lime = pstade::lime;
        namespace oven = pstade::oven;
        namespace hamburger = pstade::hamburger;
        using namespace pstade::hamburger;

        if (boost::empty(node%Name_includedHref))
            return lime::save_default(node, out);

        if (!oven::equals(node%Name_serializable, Value_true))
            return lime::save_default(node, oven::to_function(pstade::unused));

        try {
            hamburger::save(node, node%Name_includedHref);
            // return lime::save_file_default(node, oven::copy_range<std::string>(node%Name_includedHref));
        }
        catch (lime::save_error const& err) {
            BOOST_ASSERT(false);
            hamburger::log << err.what();
        }
    }


} // namespace pstade_lime_extension


#endif

#ifndef PSTADE_HAMBURGER_LIME_HPP
#define PSTADE_HAMBURGER_LIME_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/range/empty.hpp>
#include <pstade/lime/save.hpp> // save_default
#include <pstade/oven/equals.hpp>
#include <pstade/oven/null_outputter.hpp>
#include <pstade/oven/sequence_cast.hpp>
#include <pstade/overload.hpp>
#include <pstade/ustring.hpp>
#include "./element.hpp"
#include "./factory.hpp"
#include "./include.hpp"
#include "./load_save.hpp"
#include "./log.hpp"


inline
pstade::hamburger::element *
pstade_lime_new_node(pstade::hamburger::element& parent, pstade::ustring childName, pstade::overload<>)
{
    return pstade::hamburger::create_element(parent, childName);
}


template< class OutIter > inline
void
pstade_lime_save_node(pstade::hamburger::element& node, OutIter out, pstade::overload<>)
{
    using namespace pstade;
    using namespace hamburger;

    if (boost::empty(node%Name_includedHref))
        return lime::save_default(node, out);

    if (!oven::equals(node%Name_serializable, Value_true))
        return lime::save_default(node, oven::null_outputter);

    try {
		hamburger::save(node, node%Name_includedHref);
        // return lime::save_file_default(node, oven::sequence_cast<std::string>(node%Name_includedHref));
    }
    catch (lime::save_error& err) {
        BOOST_ASSERT(false);
        hamburger::log << err.what();
    }
}


#endif

#ifndef PSTADE_HAMBURGER_INCLUDE_HPP
#define PSTADE_HAMBURGER_INCLUDE_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <algorithm> // find_if
#include <boost/foreach.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/core.hpp> // _1
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <boost/ref.hpp>
#include <pstade/instance.hpp>
#include <pstade/ketchup/core.hpp>
#include <pstade/is_same.hpp>
#include <pstade/oven/copy_range.hpp>
#include <pstade/oven/distance.hpp>
#include <pstade/statement.hpp>
#include <pstade/ustring.hpp>
#include <pstade/what.hpp>
#include "./element.hpp"
#include "./factory.hpp"
#include "./lime.hpp"
#include "./load_save.hpp"
#include "./log.hpp"


namespace pstade { namespace hamburger {


PSTADE_INSTANCE(const ustring, Name_includedHref,   ("includedHref"))
PSTADE_INSTANCE(const ustring, Name_serializable,   ("serializable"))


namespace include_detail {


    PSTADE_INSTANCE(const ustring, Name_href, ("href"))


} // namespace include_detail


struct include :
    element
{
public:
    include()
    {
        *this%Name_visible = Value_false;
    }

protected:
    void override_create()
    {
        BOOST_ASSERT(boost::empty(*this));

        ustring path = *this%include_detail::Name_href;

        // Todo:
        // build_path(path, ...) using 'lime::root(*this)%Name_moduleFileName'

        try {
            hamburger::load(*this, path);
        }
        catch (lime::load_error& ) {
            BOOST_ASSERT(false);
            // log << pstade::what("include-error", "failed to load:" + oven::copy_range<std::string>(path));
        }

        boost::optional<element&> pa = parent();
        BOOST_ASSERT(pa);

        namespace bll = boost::lambda;

        // read-only access, thread-safe MAYBE.
        iterator here = std::find_if(
            boost::begin(*pa), boost::end(*pa),
            // m_self for passing the two same types 'element' to 'is_same' 
            bll::bind<bool>(pstade::is_same, boost::ref(m_self), bll::_1)
        );

        BOOST_ASSERT(oven::distance(*this) == 1); // only xml root element

        iterator first = begin();
        element& xmlroot = *first;
        xmlroot.detail_construct(*pa, xmlroot.name()); // change parent!
        xmlroot%Name_includedHref = path;
        xmlroot%Name_serializable = *this%Name_serializable;
        (*pa).transfer(here, first, *this); // transfer xmlroot to here

        // 'first' is invalid here.
        xmlroot.create();
        // don't touch here cause 'create' might make threads.
    }
};


namespace include_detail {


    PSTADE_STATEMENT(Register,
        hamburger::register_element<include>("include");
    )


} // namespace include_detail


} } // namespace pstade::hamburger


#endif

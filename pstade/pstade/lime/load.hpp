#ifndef PSTADE_LIME_LOAD_HPP
#define PSTADE_LIME_LOAD_HPP


// PStade.Lime
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <memory> // auto_ptr
#include <stack>
#include <boost/assert.hpp>
#include <boost/range/empty.hpp>
#include <boost/throw_exception.hpp>
#include <pstade/biscuit/algorithm/match.hpp>
#include <pstade/biscuit/parser.hpp>
#include <pstade/nullptr.hpp>
#include <pstade/oven/copy_range.hpp>
#include <pstade/oven/distance.hpp>
#include <pstade/oven/range_value.hpp>
#include <pstade/oven/slice_range.hpp>
#include <pstade/unused.hpp>
#include <pstade/ustring.hpp>
#include <pstade/what.hpp>
#include "./error.hpp"
#include "./intrinsic.hpp"
#include "./new_node.hpp"
#include "./xml.hpp"


namespace pstade { namespace lime {


namespace load_detail {


    // user state
    //
    template< class NodeValue >
    struct context
    {
        typedef NodeValue node_value;

        node_value& top()
        {
            BOOST_ASSERT(!is_top_null());
            return *(m_stack.top());
        }

        bool is_top_null() const
        {
            return m_stack.top() == PSTADE_NULLPTR;
        }

        void push(node_value *pn)
        {
            m_stack.push(pn);
        }

        void pop()
        {
            m_stack.pop();
        }

        void reset_current_AttName(ustring const& n)
        {
            m_curAttName = n;
        }

        ustring const& current_AttName() const
        {
            return m_curAttName;
        }

        bool valid() const
        {
            return m_stack.size() > 1; // always has root.
        }

    private:
        std::stack<node_value *> m_stack;
        ustring m_curAttName;
    };


    // actions
    //

    struct on_TagName
    {
        template< class SubRange, class Context >
        void operator()(SubRange const& rng, Context& cxt)
        {
            if (cxt.is_top_null()) {
                cxt.push(PSTADE_NULLPTR);
                return;
            }

            ustring name = rng|oven::copied;

            typedef typename Context::node_value val_t;
            std::auto_ptr<val_t> pn(lime::new_node(cxt.top(), name));

            if (pn.get())
                cxt.top().push_back(pn.get());
    
            cxt.push(pn.release());
        }
    };


    struct on_CharData
    {
        template< class SubRange, class Context >
        void operator()(SubRange const& rng, Context& cxt)
        {
            if (cxt.is_top_null())
                return;

            ustring data = rng|oven::copied;

            typedef typename Context::node_value val_t;
            std::auto_ptr<val_t> pn(lime::new_node(cxt.top(), i_CharData));
            if (!pn.get())
                return;

            pn->attributes()[i_attName] = data;
            cxt.top().push_back(pn.release());
        }
    };


    struct on_Reference
    {
        template< class SubRange, class Context >
        void operator()(SubRange const& rng, Context& cxt)
        {
            if (cxt.is_top_null())
                return;

            ustring data = rng|oven::copied;

            typedef typename Context::node_value val_t;
            std::auto_ptr<val_t> pn(lime::new_node(cxt.top(), i_Reference));
            if (!pn.get())
                return;

            pn->attributes()[i_attName] = data;
            cxt.top().push_back(pn.release());
        }
    };


    struct on_AttName
    {
        template< class SubRange, class Context >
        void operator()(SubRange const& rng, Context& cxt)
        {
            if (cxt.is_top_null())
                return;

            ustring name = rng|oven::copied;
            cxt.reset_current_AttName(name);
        }
    };


    struct on_AttValue
    {
        template< class SubRange, class Context >
        void operator()(SubRange const& rng, Context& cxt)
        {
            if (cxt.is_top_null())
                return;

            ustring val = rng|oven::copied;
            BOOST_ASSERT(oven::distance(val) >= 2);

            cxt.top().attributes()[cxt.current_AttName()]
                = val|oven::sliced(1, -1); // remove " "
        }
    };


    struct on_ETag
    {
        template< class SubRange, class Context >
        void operator()(SubRange const& rng, Context& cxt)
        {
            BOOST_ASSERT(cxt.valid());

            cxt.pop();
            pstade::unused(rng);
        }
    };


    typedef xml::parser<
        on_TagName, on_AttName, on_AttValue, on_ETag,
        on_CharData, on_Reference
    >::type xml_parser;


} // namespace load_detail


struct load_error :
    error
{
    load_error() :
        error(pstade::what("lime", "load_error"))
    { }
};


template< class Node, class ForwardRange >
void load(Node& root, ForwardRange const& rng)
{
    typedef typename oven::range_value<Node>::type val_t;
    load_detail::context<val_t> cxt;
    cxt.push(&root);

    if (!biscuit::match<load_detail::xml_parser>(rng, cxt)) {
        load_error err;
        boost::throw_exception(err);
    }
}


} } // namespace pstade::lime


#endif

#ifndef PSTADE_LIME_LOAD_HPP
#define PSTADE_LIME_LOAD_HPP


// PStade.Lime
//
// Copyright MB 2005-2006.
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
#include <pstade/melon.hpp>
#include <pstade/nullptr.hpp>
#include <pstade/oven/distance.hpp>
#include <pstade/oven/sequence_cast.hpp>
#include <pstade/oven/slice_range.hpp>
#include <pstade/unused.hpp>
#include <pstade/ustring.hpp>
#include <pstade/what.hpp>
#include "./error.hpp"
#include "./intrinsic.hpp"
#include "./new_node.hpp"
#include "./node_value_type.hpp"


namespace pstade { namespace lime {


namespace load_detail {


    // user state
    //
    template< class NodeValue >
    struct context
    {
        typedef NodeValue node_value_type;

        node_value_type& top()
        {
            BOOST_ASSERT(!is_top_null());
            return *(m_stack.top());
        }

        bool is_top_null() const
        {
            return m_stack.top() == PSTADE_NULLPTR;
        }

        void push(node_value_type *pn)
        {
            m_stack.push(pn);
        }

        void pop()
        {
            m_stack.pop();
        }

        void reset_current_AttName(ustring n)
        {
            m_curAttName = n;
        }

        ustring current_AttName() const
        {
            return m_curAttName;
        }

        bool valid() const
        {
            return m_stack.size() > 1; // always has root.
        }

    private:
        std::stack<node_value_type *> m_stack;
        ustring m_curAttName;
    };


    // actions
    //

    struct name_action
    {
        template< class SubRange, class Context >
        void operator()(SubRange rng, Context& cxt)
        {
            if (cxt.is_top_null()) {
                cxt.push(PSTADE_NULLPTR);
                return;
            }

            ustring name = oven::sequence(rng);

            typedef typename Context::node_value_type val_t;
            std::auto_ptr<val_t> pn(lime::new_node(cxt.top(), name));

            if (pn.get())
                cxt.top().push_back(pn.get());
    
            cxt.push(pn.release());
        }
    };


    struct charData_action
    {
        template< class SubRange, class Context >
        void operator()(SubRange rng, Context& cxt)
        {
            if (cxt.is_top_null())
                return;

            ustring data = oven::sequence(rng);

            typedef typename Context::node_value_type val_t;
            std::auto_ptr<val_t> pn(lime::new_node(cxt.top(), i_CharData));
            if (!pn.get())
                return;

            pn->attributes()[i_attName] = data;
            cxt.top().push_back(pn.release());
        }
    };


    struct reference_action
    {
        template< class SubRange, class Context >
        void operator()(SubRange rng, Context& cxt)
        {
            if (cxt.is_top_null())
                return;

            ustring data = oven::sequence(rng);

            typedef typename Context::node_value_type val_t;
            std::auto_ptr<val_t> pn(lime::new_node(cxt.top(), i_Reference));
            if (!pn.get())
                return;

            pn->attributes()[i_attName] = data;
            cxt.top().push_back(pn.release());
        }
    };


    struct attName_action
    {
        template< class SubRange, class Context >
        void operator()(SubRange rng, Context& cxt)
        {
            if (cxt.is_top_null())
                return;

            ustring name = oven::sequence(rng);
            cxt.reset_current_AttName(name);
        }
    };


    struct attValue_action
    {
        template< class SubRange, class Context >
        void operator()(SubRange rng, Context& cxt)
        {
            if (cxt.is_top_null())
                return;

            ustring val = oven::sequence(rng);
            BOOST_ASSERT(oven::distance(val) >= 2);

            cxt.top().attributes()[cxt.current_AttName()]
                = val|oven::sliced(1, -1); // remove " "
        }
    };


    struct eTag_action
    {
        template< class SubRange, class Context >
        void operator()(SubRange rng, Context& cxt)
        {
            BOOST_ASSERT(cxt.valid());

            cxt.pop();
            pstade::unused(rng);
        }
    };


    // parsers
    //

    struct name     : biscuit::actor< melon::Name<>,        name_action >       { };
    struct attName  : biscuit::actor< melon::Name<>,        attName_action >    { };
    struct attValue : biscuit::actor< melon::AttValue<>,    attValue_action >   { };
    struct charData : biscuit::actor< melon::CharData<>,    charData_action >   { };
    struct reference: biscuit::actor< melon::Reference<>,   reference_action >  { };
    struct eTag     : biscuit::actor< melon::ETag<>,        eTag_action >       { };


    struct attribute: melon::Attribute<attName, attValue>   { };
    struct sTag     : melon::STag<name, attribute>          { };


    struct emptyElemTag : biscuit::lazy_actions<
        biscuit::seq<
            melon::EmptyElemTag<name, attribute>,
            biscuit::actor< biscuit::eps, eTag_action >
        >
    >
    { };


    struct element : melon::element<
        melon::content< element, charData, reference >,
        emptyElemTag, sTag, eTag
    >
    { };


    struct start : melon::document<
        element
    >
    { };


} // namespace load_detail


struct load_error :
    error
{
    explicit load_error() :
        error(pstade::what("lime", "load_error"))
    { }
};


template< class Node, class ForwardRange >
void load(Node& root, const ForwardRange& rng)
{
    typedef typename node_value<Node>::type val_t;
    load_detail::context<val_t> cxt;
    cxt.push(&root);

    if (!biscuit::match<load_detail::start>(rng, cxt)) {
        load_error err;
        boost::throw_exception(err);
    }
}


} } // namespace pstade::lime


#endif

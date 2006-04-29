#ifndef PSTADE_LIME_LOAD_HPP
#define PSTADE_LIME_LOAD_HPP


// PStade.Lime
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <stack>
#include <boost/assert.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/throw_exception.hpp>
#include <pstade/biscuit/algorithm/match.hpp>
#include <pstade/biscuit/parser.hpp>
#include <pstade/melon.hpp>
#include <pstade/oven/sequence_cast.hpp>
#include <pstade/oven/slice_range.hpp>
#include "./error.hpp"
#include "./intrinsic.hpp"
#include "./new_node.hpp"
#include "./node.hpp"
#include "./ustring.hpp"


namespace pstade { namespace lime {


namespace load_detail {


    // user state
    //

    template< class Interface >
    struct context
    {
        typedef Interface interface_type;

        std::stack<node<Interface> *> m_stack;
        ustring m_curAttName;

        node<Interface>& top()
        {
            return *(m_stack.top());
        }

        void push(node<Interface> *p)
        {
            m_stack.push(p);
        }

        void pop()
        {
            m_stack.pop();
        }
    };


    // actions
    //

    struct name_action
    {
        template< class SubRange, class Context >
        void operator()(SubRange rng, Context& cxt)
        {
            ustring name = oven::sequence(rng);

            typedef typename Context::interface_type interface_t;
            node<interface_t> *pnode = lime::new_node<interface_t>(cxt.top(), name);

            cxt.top().push_back(pnode);
            cxt.push(pnode);
        }
    };


    struct charData_action
    {
        template< class SubRange, class Context >
        void operator()(SubRange rng, Context& cxt)
        {
            ustring data = oven::sequence(rng);

            typedef typename Context::interface_type interface_t;
            node<interface_t> *pnode = lime::new_node<interface_t>(cxt.top(), i_CharData);

            cxt.top().push_back(pnode);
            (*pnode).att(i_attName) = data;
        }
    };


    struct reference_action
    {
        template< class SubRange, class Context >
        void operator()(SubRange rng, Context& cxt)
        {
            ustring data = oven::sequence(rng);

            typedef typename Context::interface_type interface_t;
            node<interface_t> *pnode = lime::new_node<interface_t>(cxt.top(), i_Reference);

            cxt.top().push_back(pnode);
            (*pnode).att(i_attName) = data;
        }
    };


    struct attName_action
    {
        template< class SubRange, class Context >
        void operator()(SubRange rng, Context& cxt)
        {
            ustring name = oven::sequence(rng);
            cxt.m_curAttName = name;
        }
    };


    struct attValue_action
    {
        template< class SubRange, class Context >
        void operator()(SubRange rng, Context& cxt)
        {
            ustring val = oven::sequence(rng);
            BOOST_ASSERT(boost::size(val) >= 2);

            cxt.top().att(cxt.m_curAttName) =
                // remove " "
                val|oven::sliced(1, -1);
        }
    };


    struct eTag_action
    {
        template< class SubRange, class Context >
        void operator()(SubRange rng, Context& cxt)
        {
            BOOST_ASSERT(boost::size(cxt.m_stack) > 1);

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
        error("pstade::lime::load - xml parsing failed")
    { }
};


template< class Interface, class ForwardRange >
void load(node<Interface>& root, const ForwardRange& rng)
{
    load_detail::context<Interface> cxt;
    cxt.push(&root);

    if (!biscuit::match<load_detail::start>(rng, cxt)) {
        load_error err;
        boost::throw_exception(err);
    }
}


} } // namespace pstade::lime


#endif

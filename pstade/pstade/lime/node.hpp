#ifndef PSTADE_LIME_NODE_HPP
#define PSTADE_LIME_NODE_HPP


// PStade.Lime
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <map>
#include <string>
#include <boost/foreach.hpp>
#include <boost/mpl/empty_base.hpp>
#include <boost/noncopyable.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/optional.hpp>
#include <boost/range/empty.hpp>
#include <boost/throw_exception.hpp>
#include <pstade/garlic/back_inserter.hpp>
#include <pstade/oven/equal.hpp>
#include <pstade/oven/sequence_cast.hpp>
#include <pstade/overload.hpp>
#include "./error.hpp"
#include "./ustring.hpp"


namespace pstade { namespace lime {


struct node_not_found :
    error
{
    explicit node_not_found(std::string what) :
        error(what)
    { }
};


namespace node_detail {


    inline
    void throw_error(ustring name)
    {
        node_not_found err("<node-not-found>" +
            oven::sequence_cast<std::string>(name) + "</node-not-found>");

        boost::throw_exception(err);
    }


    template< class NodeT >
    struct super_
    {
        typedef boost::ptr_vector<NodeT> type;
    };


} // namesapce node_detail


struct default_interface
{ };


template<
    class Interface = default_interface
>
struct node :
    node_detail::super_< node<Interface> >::type,
    Interface,
    private boost::noncopyable
{
private:
    typedef typename node_detail::super_< node<Interface> >::type super_t;

public:
    // structors
    //
    explicit node(ustring name) :
        m_name(name)
    { }

    explicit node(node& parent, ustring name) :
        m_parent(parent), m_name(name) 
    { }

    virtual ~node()
    { }

    // accessors
    //
    boost::optional<node&> parent() const
    {
        BOOST_ASSERT(valid());
        return m_parent;
    }

    ustring name() const
    {
        BOOST_ASSERT(valid());
        return m_name;
    }

    typedef std::map<ustring, ustring>
    attributes_type;

    attributes_type& attributes()
    {
        BOOST_ASSERT(valid());
        return m_atts;
    }

    node& child(ustring childName)
    {
        BOOST_ASSERT(valid());
        return get_child(childName);
    }

    ustring& att(ustring attName)
    {
        BOOST_ASSERT(valid());
        return m_atts[attName];
    }

    // syntax sugars
    //
    node& operator/(ustring childName)
    {
        return child(childName);
    }

    ustring& operator%(ustring attName)
    {
        return att(attName);
    }

    node& operator+=(ustring childName)
    {
        BOOST_ASSERT(valid());
        this->push_back( pstade_lemon_new_node(*this, childName, overload()) );
        return *this;
    }

private:
    boost::optional<node&> m_parent;
    ustring m_name;
    attributes_type m_atts;

    node& get_child(ustring childName)
    {
        node& self = *this; // workaround VC++

        BOOST_FOREACH (node& child, self) {
            if (oven::equals(child.name(), childName))
                return child;
        }

        // Question:
        //   better? maybe not.
        //
        // node *baby = new node(childName);
        // push_back(baby);
        // return *baby;

        node_detail::throw_error(childName);
        return *this; // suppress warning
    }

    bool valid() const
    {
        return !boost::empty(m_name);
    }
};


} } // namespace pstade::lime


#endif

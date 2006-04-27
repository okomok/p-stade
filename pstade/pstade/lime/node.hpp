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
#include <boost/noncopyable.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/optional.hpp>
#include <boost/range/empty.hpp>
#include <pstade/garlic/back_inserter.hpp>
#include <pstade/oven/equal.hpp>
#include <pstade/oven/sequence_cast.hpp>
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


struct node :
    node_detail::super_<node>::type,
    private boost::noncopyable
{
private:
    typedef node_detail::super_<node>::type super_t;

public:
    // structors
    //
    explicit node(ustring name) :
        m_name(name)
    {
        BOOST_ASSERT(!boost::empty(m_name));
    }

    explicit node(ustring name, node& parent) :
        m_name(name), m_parent(parent)
    {
        BOOST_ASSERT(!boost::empty(m_name));
    }

    virtual ~node()
    { }

    // accessors
    //
    typedef std::map<ustring, ustring>
    attributes_type;

    ustring& operator[](ustring attName)
    {
        return m_atts[attName];
    }

    node& operator()(ustring childName)
    {
        boost::ptr_vector<node>& self = *this; // workaround VC++

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

    attributes_type& attributes()
    {
        return m_atts;
    }

    ustring name() const
    {
        return m_name;
    }

    boost::optional<node&> parent() const
    {
        return m_parent;
    }

private:
    ustring m_name;
    boost::optional<node&> m_parent;
    attributes_type m_atts;
};


} } // namespace pstade::lime


#endif

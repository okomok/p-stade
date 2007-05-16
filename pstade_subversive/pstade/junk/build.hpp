#ifndef PSTADE_MILK_TREE_HPP
#define PSTADE_MILK_TREE_HPP


// PStade.Milk
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <map>
#include <boost/foreach.hpp>
#include <boost/noncopyable.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/type_traits/is_const.hpp>
#include "./string.hpp"


namespace pstade { namespace milk {


struct view :
	private boost::noncopyable
{
	explicit view(string name) :
		m_name(name)
	{ }

	string name() const
	{ return m_name; }

	string operator[](string att) const
	{ return m_atts[att]; }

	boost::ptr_vector<view>& nodes()
	{ return m_nodes; }

	const boost::ptr_vector<view>& nodes() const
	{ return m_nodes; }

private:
	string m_name;
	std::map<string, string> m_atts;
	boost::ptr_vector<view> m_nodes;
};


template< class Tree >
struct node :
	boost::mpl::if_< boost::is_const<Tree>,
		boost::ptr_vector<Tree>,
		const boost::ptr_vector<Tree>
	>
{ };


template< class Tree, class Functor > inline
Functor foreach_node(Tree& t, Functor fun)
{
	typedef typename node<Tree>::type node_t;
	
	BOOST_FOREACH (node_t& node, t.nodes()) {
		milk::foreach_node(node, fun);
	}

	fun(t, node);
	return fun;
}


} } // namespace pstade::milk

#endif

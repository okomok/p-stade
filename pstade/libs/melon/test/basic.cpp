#include <pstade/vodka/drink.hpp>
// #include <boost/test/minimal.hpp>


// PStade.Melon
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/melon.hpp>


#include <exception>
#include <iostream>
#include <map>
#include <stack>
#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/foreach.hpp>
#include <boost/noncopyable.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <pstade/biscuit.hpp>
#include <pstade/oven.hpp>
#include <pstade/wine.hpp>


namespace my_melon {


    using namespace pstade;


    typedef std::vector<ucs4_t> string_t;


    // simple_tree
    //

    struct simple_tree :
        boost::noncopyable
    {
    public:
        simple_tree()
        { }

        explicit simple_tree(string_t name) :
            m_name(name)
        { }

        string_t m_name;
        std::map<string_t, string_t> m_atts;
        boost::ptr_vector<simple_tree> m_nodes;
    };


    inline
    void show_tree(simple_tree& t)
    {
        std::wcout << oven::sequence_cast<std::wstring>(t.m_name) << std::endl;

        BOOST_FOREACH(
            pstade::comma_protect<void(std::pair<const string_t, string_t>)>::type& a,
            t.m_atts
        ) {
            std::wcout << "..." << oven::sequence_cast<std::wstring>(a.first) << "=" <<
                oven::sequence_cast<std::wstring>(a.second) << std::endl;
        }

        BOOST_FOREACH(simple_tree& n, t.m_nodes) {
            show_tree(n);
        }
    };


    // user state
    //

    typedef std::stack<simple_tree *> stack_t;


    struct context
    {
        stack_t m_stack;
        string_t m_attName;
    };


    // actions
    //

    struct name_action
    {
        template< class SubRange >
        void operator()(SubRange rng, context& cxt)
        {
            string_t name = oven::sequence(rng);
            simple_tree *ptree = new simple_tree(name);
            cxt.m_stack.top()->m_nodes.push_back(ptree);
            cxt.m_stack.push(ptree);
        }
    };



    PSTADE_INSTANCE(const string_t, charDataAttName,
        (oven::sequence_cast<string_t>(std::string("<CharData>"))))

    struct charData_action
    {
        template< class SubRange >
        void operator()(SubRange rng, context& cxt)
        {
            string_t data = oven::sequence(rng);
            cxt.m_stack.top()->m_atts[charDataAttName] = data;
        }
    };


    struct attName_action
    {
        template< class SubRange >
        void operator()(SubRange rng, context& cxt)
        {
            string_t name = oven::sequence(rng);
            cxt.m_attName = name;
        }
    };


    struct attValue_action
    {
        template< class SubRange >
        void operator()(SubRange rng, context& cxt)
        {
            string_t value = oven::sequence(rng);
            cxt.m_stack.top()->m_atts[cxt.m_attName] = value;
        }
    };


    struct eTag_action
    {
        template< class SubRange >
        void operator()(SubRange rng, context& cxt)
        {
            BOOST_ASSERT(oven::distance(cxt.m_stack) > 1);
            cxt.m_stack.pop();

            pstade::unused(rng);
        }
    };


    // parsers
    //

    struct name : biscuit::actor<
        melon::Name<>, name_action
    >
    { };


    struct attName : biscuit::actor<
        melon::Name<>, attName_action
    >
    { };


    struct attValue : biscuit::actor<
        melon::AttValue<>, attValue_action
    >
    { };


    struct attribute :
        melon::Attribute<attName, attValue>
    { };


    struct sTag :
        melon::STag<name, attribute>
    { };


    struct eTag : biscuit::actor<
        melon::ETag<>, eTag_action
    >
    { };


    struct emptyElemTag : biscuit::lazy_actions<
        biscuit::seq<
            melon::EmptyElemTag<name, attribute>,
            biscuit::actor< biscuit::eps, eTag_action >
        >
    >
    { };


    struct charData : biscuit::actor<
        melon::CharData<>, charData_action
    >
    { };


    struct element;


    struct content : melon::content<
        element, charData
    >
    { };


    struct element : melon::element<
        content, emptyElemTag, sTag, eTag
    >
    { };


    struct start : melon::document<
        element
    >
    { };


} // namespace my_melon


int main(int argc, char *argv[])
{
    using namespace pstade;

    argc = 2;
    BOOST_FOREACH (int i, oven::one_to(argc)) {

        try {
            my_melon::context cxt;
            my_melon::simple_tree root(oven::sequence_cast<my_melon::string_t>(std::string("Root")));
            cxt.m_stack.push(&root);

            PSTADE_REQUIRE((
                biscuit::match<my_melon::start>(
                    oven::file_range<boost::uint8_t>("sample.xml") | // argv[i]) |
                        oven::utf8_decoded,
                    cxt
                )
            ));

            show_tree(root);
        }
        catch(std::exception& err) {
            std::cout << "\n...exception: " << err.what();
        }

    }

    return std::cout << "\n...parsing succeeds, press any key.", pstade::pause();
}

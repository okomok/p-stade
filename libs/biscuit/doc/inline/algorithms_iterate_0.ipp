std::stringstream out; {
    std::string text(" <hello> <!-- xml comment no.1 --> biscuit</hello> <wow>biscuit</wow> <!-- xml comment no.2 -->  ");
    biscuit::iterate<xml_comment_action>(text, out, biscuit::output_action());
}
BOOST_CHECK( oven::equal(out.str(), " <hello> [<!-- xml comment no.1 -->] biscuit</hello> <wow>biscuit</wow> [<!-- xml comment no.2 -->]  ") );

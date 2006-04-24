struct decorate_action
{
    void operator()(boost::sub_range<std::string> rng, std::stringstream& out)
    {
        out << "[" << oven::sequence_cast<std::string>(rng) << "]";
        boost::to_upper(rng);
    }
};

struct xml_comment :
    seq<
        chseq<'<','!','-','-'>,
        star<
            or_<
                minus< any, chseq<'-'> >,
                seq<
                    chseq<'-'>,
                    minus< any, chseq<'-'> >
                >
            >
        >,
        chseq<'-','-','>'>
    >
{ };

struct xml_comment_action :
    actor< xml_comment, decorate_action >
{ };

void test_actor()
{
    std::string text("<!-- xml comment -->");
    std::stringstream out;
    BOOST_CHECK( biscuit::match<xml_comment_action>(text, out) );
    BOOST_CHECK( oven::equal(out.str(), "[<!-- xml comment -->]") );
    BOOST_CHECK( oven::equal(text, "<!-- XML COMMENT -->") );
}
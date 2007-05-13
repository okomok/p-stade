namespace calculator
{
    using namespace biscuit;

    struct do_int
    {
        void operator()(boost::sub_range<std::string> rng, null_state_type)
        {
            std::string s(boost::begin(rng), boost::end(rng));
            std::cout << "PUSH(" << s << ')' << std::endl;
        }
    };

    struct do_add
    {
        void operator()(boost::sub_range<std::string>, null_state_type)
        { std::cout << "ADD\n"; }
    };

    struct do_subt
    {
        void operator()(boost::sub_range<std::string>, null_state_type)
        { std::cout << "SUBTRACT\n"; }
    };

    struct do_mult
    {
        void operator()(boost::sub_range<std::string>, null_state_type)
        { std::cout << "MULTIPLY\n"; }
    };

    struct do_div
    {
        void operator()(boost::sub_range<std::string>, null_state_type)
        { std::cout << "DIVIDE\n"; }
    };

    struct do_neg
    {
        void operator()(boost::sub_range<std::string>, null_state_type)
        { std::cout << "NEGATE\n"; }
    };

    struct start;
    struct expression;
    struct term;
    struct factor;

    struct start :
        identity<expression>
    { };

    struct expression :
        seq<
            term,
            star<
                or_<
                    actor< seq< chseq<'+'>, term >, do_add >,
                    actor< seq< chseq<'-'>, term >, do_subt >
                >
            >
        >
    { };

    struct term :
        seq<
            factor,
            star<
                or_<
                    actor< seq< chseq<'*'>, factor >, do_mult >,
                    actor< seq< chseq<'/'>, factor >, do_div >
                >
            >
        >
    { };

    struct factor :
        or_<
            actor< plus<digit>, do_int >,
            seq< chseq<'('>, expression, chseq<')'> >,
            actor< seq< chseq<'-'>, factor >, do_neg >,
            seq< chseq<'+'>, factor >
        >
    { };
};
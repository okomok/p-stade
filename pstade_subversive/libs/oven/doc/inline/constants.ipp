// Assume your algorithm wants to keep 'rng' from
// unintentional modifications.

template< class Range >
void legacy_way(Range const& rng)
{
    *boost::begin(rng) = 'x';
    *boost::const_begin(rng) = 'x';
}

template< class Range >
void modern_way(Range& rng)
{
    typename boost::result_of<op_make_constants(Range&)>::type safe_rng = rng|constants;
    *boost::begin(safe_rng) = 'x';
}

void test()
{
    std::string str("hello, constants!");
    ::legacy_way(str|identities); // oops, compiles.
    // ::modern_way(str|identities); // error
    // ::legacy_way(str|identities|constants); // error
}
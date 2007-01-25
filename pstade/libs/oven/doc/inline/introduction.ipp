typedef
    any_range<int, boost::single_pass_traversal_tag>
range;

range denominators(int x)
{
    return counting(1, x+1)|filtered(regular(x % lambda::_1 == 0));
}

bool is_prime(int x)
{
    return equals(denominators(x), assign::list_of(1)(x));
}

range primes = iteration(1, regular(lambda::_1 + 1))|filtered(&is_prime);

int main()
{
    pstade::op_lexical_cast<std::string> to_string;
    BOOST_FOREACH (std::string p, primes|taken(500)|transformed(to_string))
        std::cout << p << ',';
}
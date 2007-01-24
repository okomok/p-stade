typedef
    any_range<int, boost::single_pass_traversal_tag>
range;

range denominators(int x)
{
    return counting(1, x+1)|filtered(x % lambda::_1 == 0)|regularized;
}

bool is_prime(int x)
{
    return equals(denominators(x), assign::list_of(1)(x));
}

range primes = iteration(1, lambda::_1 + 1)|regularized|filtered(&is_prime);

int main()
{
    pstade::op_lexical_cast<std::string> to_string;
    BOOST_FOREACH (std::string p, primes|taken(500)|transformed(to_string))
        std::cout << p << ',';
}
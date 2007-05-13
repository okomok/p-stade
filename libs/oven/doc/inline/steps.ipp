int const answer[] = { 0, 40, 80 };
BOOST_CHECK( equals(
    counting(0, 100)|steps(10)|steps(4),
    answer
) );
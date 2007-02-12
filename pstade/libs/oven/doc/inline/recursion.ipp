typedef any_range< int, recursive<> > range_t;
memo_table to_table;
range_t fibs;
int const start[] = { 1, 1 };
fibs =
    start|transformed(pstade::as_value)|
        jointed(
            boost::make_tuple(recursion(fibs), recursion(fibs)|dropped(1))|
            zipped_with(regular(lambda::_1 + lambda::_2))
        )
         | memoized(to_table)
;

std::cout << (fibs|taken(30));
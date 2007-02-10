any_range< int, recursive<boost::single_pass_traversal_tag> > fibs;
int const start[] = { 1, 1 };
fibs =
    start|transformed(pstade::as_value)|
        jointed(
            boost::make_tuple(recursion(fibs), recursion(fibs)|dropped(1))|
                zipped_with(regular(lambda::_1 + lambda::_2))
        )
;

std::cout << (fibs|taken(20));
napkin::ostream os;

os.reset(std::cout);
os << "to cout:" << 1 << '\n';

os.reset(std::wcout);
os << "to wcout";

std::ofstream fout("log.txt");
os.reset(fout);
os << "to file:" << 3.14;

os << boost::format("%2% %1%")
    % "boost" % "using";

std::stringstream sout;
os.reset(sout);
os << "to string stream:" << 'x';

os.reset(napkin::dout);
os << "to debugger:" << sout.str();

os.reset(napkin::nout);
os << "to trash box";

std::vector<char> vout;
os.reset(vout);
os << "to sequence";

std::string strout;
os.reset(strout);
os << "to string";
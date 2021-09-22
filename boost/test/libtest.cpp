#include <iostream>
#include <boost/filesystem.hpp>

using namespace boost::filesystem;

int main(int argc, char *argv[])
{
    std::cout << "打印输出\n";
    if (argc < 2)
    {
        std::cout << "Usage: tut1 path\n";
        return 1;
    }
    std::cout << argv[1] << " " << file_size(argv[1]) << std::endl;
    return 0;
}
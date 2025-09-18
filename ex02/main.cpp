#include "PmergeMe.hpp"

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <números...>" << std::endl;
        return 1;
    }
    try {
        PmergeMe sorter(argc, argv);
        sorter.sort(argc,argv);
    } catch (const std::exception& e) {
        std::cerr << "Excepción: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

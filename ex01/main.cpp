#include <iostream>
#include <cstdlib>
#include "Serializer.hpp"

using std::cout;
using std::cerr;
using std::endl;

int	main(int argc, char **argv)
{
    if (argc > 1 && argv)
    {
        cerr << "serializer: error: command-line arguments not ok" << '\n';
        return EXIT_FAILURE;
    }

    data_t data;
    uintptr_t reinterpreted;

    data.str_example = std::string("test");
    reinterpreted = Serializer::serialize(&data);

    cout << "OG foo (Data) Address = " << &data << endl
         << "str_example value = " << data.str_example << endl;

    cout << endl;

    cout << "Reinterpreted data value = " << reinterpreted << endl;

    cout << endl;

    data_t *deserialized;

    deserialized = Serializer::deserialize(reinterpreted);

    cout << "Deserialized Address = " << deserialized << endl
         << "str_example value = " << deserialized->str_example << endl;

    return EXIT_SUCCESS;
}
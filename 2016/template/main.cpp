#include "../common.hpp"

auto part_1([[maybe_unused]] std::string_view input)
{
    return "";
}

auto part_2([[maybe_unused]] std::string_view input)
{
    return "";
}

int main(int argc, char **argv)
{
    auto args = get_args(argc, argv);
    auto input = read_all_text(args.front());
    std::cout << "Part 1: " << part_1(input) << std::endl
              << "Part 2: " << part_2(input) << std::endl 
              << std::endl;

    return 0;
}

#include "../common.hpp"

std::optional<size_t> next_char(std::string_view s, char c)
{
    if(size_t res = s.find(c); res != std::string_view::npos) 
    {
        return res;
    }
    return std::nullopt;
}

enum Version
{
    VERSION_1, VERSION_2
};

std::string decompress(std::string_view input, Version version)
{
    std::stringstream ss;
    std::string_view s = input;
    std::optional<size_t> open_par = next_char(input, '(');

    if(!open_par)
    {
        return as_string(s);
    }

    for(; open_par; open_par = next_char(s, '('))
    {
        ss << s.substr(0, *open_par);
        s = s.substr(*open_par + 1);
        const size_t close_par = *next_char(s, ')');
        const auto comp_params = split(s.substr(0, close_par), "x");
        const int size = parse_int(comp_params[0]);
        const int count = parse_int(comp_params[1]);

        s = s.substr(close_par + 1);

        std::string to_append = version == VERSION_2 
            ? decompress(s.substr(0, size), VERSION_2)
            : as_string(s.substr(0, size));
        for(int i = 0; i < count; i++)
        {
            ss << to_append;
        }
        s = s.substr(size);

    }
    ss << s;

    return ss.str();
}

auto part_1([[maybe_unused]] std::string_view input)
{
    return trim(decompress(input, VERSION_1), " \r\n").size();
}

auto part_2([[maybe_unused]] std::string_view input)
{
    return trim(decompress(input, VERSION_2), " \r\n").size();
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

#include "../common.hpp"
#include <iterator>

std::vector<std::string> parse_input(std::string_view input)
{
    std::vector<std::stringstream> streams;

    const auto strs = lines(input);
    streams.resize(strs[0].size());
    for (auto line : lines(input))
    {
        for(size_t i = 0; i < streams.size(); i++)
        {
            streams[i] << line[i];
        }
    }

    std::vector<std::string> result;

    std::transform(streams.begin(), streams.end(),
        std::back_inserter(result), 
        [](const std::stringstream &ss){ return ss.str(); });

    return result;
}

char max_symbol(std::string_view s)
{
    std::map<char, int> counts;
    for(char c : s)
    {
        counts[c]++;
    }

    return std::max_element(
        counts.begin(), counts.end(),
        [](const auto &a, const auto &b){ return a.second < b.second; }
    )->first;
}

char min_symbol(std::string_view s)
{
    std::map<char, int> counts;
    for(char c : s)
    {
        counts[c]++;
    }

    return std::min_element(
        counts.begin(), counts.end(),
        [](const auto &a, const auto &b){ return a.second < b.second; }
    )->first;
}

auto part_1([[maybe_unused]] std::string_view input)
{
    std::stringstream ss;
    for(auto s : parse_input(input))
    {
        ss << max_symbol(s);
    }
    return ss.str();
}

auto part_2([[maybe_unused]] std::string_view input)
{
    std::stringstream ss;
    for(auto s : parse_input(input))
    {
        ss << min_symbol(s);
    }
    return ss.str();
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

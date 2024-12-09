#include "../common.hpp"

bool is_abba(std::string_view s)
{
    return s.size() == 4 && s[0] == s[3] && s[1] == s[2] && s[0] != s[1];
}

bool contains_abba(std::string_view s)
{
    for(size_t i = 0; i < s.size() - 3; i++)
    {
        if(is_abba(s.substr(i, 4)))
        {
            return true;
        }
    }
    return false;
}

bool supports_tls(std::string_view s)
{
    auto parts = split(s, "[]");
    for(size_t i = 1; i < parts.size(); i += 2)
    {
        if(contains_abba(parts[i])) return false;
    }
    for(size_t i = 0; i < parts.size(); i += 2)
    {
        if(contains_abba(parts[i])) return true;
    }
    return false;
}

bool is_aba(std::string_view s)
{
    return s.size() == 3 && s[0] == s[2] && s[0] != s[1];
}

bool is_bab(std::string_view s, std::string_view aba)
{
    return s.size() == 3 && s[0] == aba[1] && s[1] == aba[0] && s[2] == aba[1];
}

bool supports_ssl(std::string_view s)
{
    std::vector<std::string_view> parts = split(s, "[]");
    std::vector<std::string_view> abas;
    for(size_t i = 0; i < parts.size(); i += 2)
    {
        for(size_t j = 0; j < parts[i].size() - 2; j++)
        {
            auto s = parts[i].substr(j, 3);
            if(is_aba(s))
            {
                abas.push_back(s);
            }
        }
    }

    for(size_t i = 1; i < parts.size(); i += 2)
    {
        for(size_t j = 0; j < parts[i].size() - 2; j++)
        {
            for(auto aba : abas)
            {
                if(is_bab(parts[i].substr(j, 3), aba)) 
                {
                    return true;
                }
            }
        }
    }
    return false;
}

auto part_1([[maybe_unused]] std::string_view input)
{
    const auto ls = lines(input);
    return std::count_if(ls.begin(), ls.end(), supports_tls);
}

auto part_2([[maybe_unused]] std::string_view input)
{
    const auto ls = lines(input);
    return std::count_if(ls.begin(), ls.end(), supports_ssl);
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

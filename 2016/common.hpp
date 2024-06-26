#ifndef COMMON_HPP
#define COMMON_HPP

#include <bits/stdc++.h>

typedef std::vector<std::string> strvec;

std::deque<std::string_view> get_args(int argc, char **argv)
{
    std::deque<std::string_view> result;
    
    for(int current = 1; current < argc; current++)
    {
        result.push_back(argv[current]);
    }
    return result;
}

std::string read_all_text(std::filesystem::path filename)
{
    std::ifstream fin(filename);
    std::stringstream buf;
    buf << fin.rdbuf();
    return buf.str();
}

static inline std::vector<std::string_view> split(std::string_view str, std::string_view delim = " ")
{
    if (str.empty())
    {
        return {""};
    }

    std::vector<std::string_view> result;
    size_t index = 0;
    size_t count = 0;

    for (size_t i = 0; i < str.size(); i++)
    {
        char c = str[i];
        if (delim.find(c) == std::string_view::npos)
        {
            count++;
        }
        else
        {
            result.emplace_back(str.substr(index, count));
            index = i + 1;
            count = 0;
        }
    }
    result.emplace_back(str.substr(index, count));

    return result;
}

static inline std::vector<std::string_view> lines(std::string_view str)
{
    if (str.empty())
    {
        return {""};
    }
    std::string delim = "\r\n";

    std::vector<std::string_view> result;
    size_t index = 0;
    size_t count = 0;

    for (size_t i = 0; i < str.size(); i++)
    {
        int ret = 0;
        switch(str[i])
        {
            case '\r':
                ret = 1;
            case '\n':
                result.emplace_back(str.substr(index, count));
                index = i + 1 + ret;
                count = 0;
                break;
            default:
                count++;
        }
    }

    if (result.back().empty())
    {
        result.pop_back();
    }

    return result;
}

static inline std::string_view trim_left(std::string_view str, std::string_view chars)
{
    size_t index = 0;
    while(chars.find(str[index]) != chars.npos)
    {
        index++;
    }

    return std::string_view(str.data() + index, str.size() - index);
}

static inline std::string_view trim_right(std::string_view str, std::string_view chars)
{
    size_t index = str.size() - 1;
    while(chars.find(str[index]) != chars.npos)
    {
        index--;
    }

    return std::string_view(str.data(), index + 1);
}

static inline std::string_view trim(std::string_view str, std::string_view chars = " ")
{
    return trim_left(trim_right(str, chars), chars);
}

static inline int parse_int(std::string_view s)
{
    int result;
    std::from_chars(s.data(), s.data() + s.size(), result);
    return result;
}

static inline std::string as_string(std::string_view s)
{
    return {s.data(), s.size()};
}

#endif // COMMON_HPP

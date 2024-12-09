#include "../common.hpp"

std::vector<std::array<int, 3>> parse_input(std::string_view input)
{
    std::vector<std::array<int, 3>> result;
    for(auto line : split(input, "\r\n"))
    {
        if(line.empty()) continue;

        std::array<int, 3> triangle;
        size_t index = 0;

        for(auto num_s : split(line, " \t"))
        {
            if(num_s.empty()) continue;
            assert(index < 3);

            int num;
            std::from_chars(num_s.data(), num_s.data() + num_s.size(), num);
            triangle[index] = num;

            index++;
        }

        result.emplace_back(triangle);
    }

    return result;
}

std::vector<std::array<int, 3>> rotate(std::vector<std::array<int, 3>> triangles)
{
    assert(triangles.size() % 3 == 0);

    std::vector<std::array<int, 3>> result;
    for(size_t col = 0; col < 3; col++)
    {
        for(size_t row = 0; row + 2 < triangles.size(); row += 3)
        {
            result.emplace_back(std::array<int, 3>{
                triangles[row    ][col],
                triangles[row + 1][col],
                triangles[row + 2][col]});
        }
    }

    return result;
}

bool is_valid_triangle(std::array<int, 3> triangle)
{
    int a = triangle[0];
    int b = triangle[1];
    int c = triangle[2];
    return a < b + c && b < a + c && c < a + b; 
}

auto part_1([[maybe_unused]] std::string_view input)
{
    auto triangles = parse_input(input);
    return std::count_if(triangles.begin(), triangles.end(), is_valid_triangle);
}

auto part_2([[maybe_unused]] std::string_view input)
{
    auto triangles = rotate(parse_input(input));
    return std::count_if(triangles.begin(), triangles.end(), is_valid_triangle);
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

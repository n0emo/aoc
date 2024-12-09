#include "../common.hpp"

auto part_1([[maybe_unused]] std::string_view input)
{
    std::stringstream answer;

    int x = 1;
    int y = 1;
    char numpad[3][3] = 
    {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };
	
    for(auto line : split(input, "\n\r"))
    {
        if(line.empty()) continue;
        
        for(auto dir : trim(line))
        {
            switch(dir)
            {
                case 'U': y--; break;
                case 'D': y++; break;
                case 'L': x--; break;
                case 'R': x++; break;
                default: std::terminate();
            }

            if(y > 2) y = 2;
            if(y < 0) y = 0;
            if(x > 2) x = 2;
            if(x < 0) x = 0;
        }

        answer << numpad[y][x];
    }

    return answer.str();
}

auto part_2([[maybe_unused]] std::string_view input)
{
    std::stringstream answer;

    int x = 0;
    int y = 2;
    char numpad[5][5] = 
    {
        {'0', '0', '1', '0', '0'}, 
        {'0', '2', '3', '4', '0'},
        {'5', '6', '7', '8', '9'},
        {'0', 'A', 'B', 'C', '0'},
        {'0', '0', 'D', '0', '0'},
    };
	
    for(auto line : split(input, "\n\r"))
    {
        if(line.empty()) continue;
        
        for(auto dir : trim(line))
        {
            int new_x = x;
            int new_y = y;
            switch(dir)
            {
                case 'U': new_y--; break;
                case 'D': new_y++; break;
                case 'L': new_x--; break;
                case 'R': new_x++; break;
                default: std::terminate();
            }
            
            if(new_x >= 0 && new_x < 5 &&
               new_y >= 0 && new_y < 5 &&
               numpad[new_y][new_x] != '0')
            {
                x = new_x;
                y = new_y;
            }
        }

        answer << numpad[y][x];
    }

    return answer.str();
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

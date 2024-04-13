#include "../common.hpp"

enum TurnDirection
{
    TURN_LEFT, TURN_RIGHT,
};

enum Direction
{
    UP, DOWN, LEFT, RIGHT
};

Direction turn(Direction dir, TurnDirection turn_dir)
{
    bool l = turn_dir == TURN_LEFT;
    switch(dir)
    {
        case UP:    return l ? LEFT  : RIGHT;
        case DOWN:  return l ? RIGHT : LEFT;
        case LEFT:  return l ? DOWN  : UP;
        case RIGHT: return l ? UP    : DOWN;
    }
    std::cout << "Error: unknown direction '" << dir << '\'' << std::endl;
    std::terminate();
}

struct Step
{
    TurnDirection direction;
    int32_t amount;
};

std::vector<Step> parse_input(std::string_view input)
{
    input = trim(input, " \n\r");
    std::vector<Step> steps;
    for(auto s : split(input, ", "))
    {
        if(s.empty()) continue;

        TurnDirection direction;
        switch(s[0])
        {
            case 'R':
                direction = TURN_RIGHT;
                break;
            case 'L':
                direction = TURN_LEFT;
                break;
            default:
                std::cout << "Error: unknown direction " << s[0] << std::endl;
                std::terminate();
        };
        
        int32_t amount = 0;
        auto amount_str = trim_left(s, "RL");
        std::from_chars(amount_str.data(), amount_str.data() + amount_str.size(), amount);
        steps.emplace_back(Step{direction, amount});
    }

    return steps;
}

auto part_1([[maybe_unused]] std::string_view input)
{
    Direction current_direction = RIGHT;
    int32_t x = 0;
    int32_t y = 0;

    for (auto step : parse_input(input))
    {
        current_direction = turn(current_direction, step.direction);

        switch(current_direction)
        {
            case UP:    y += step.amount; break;
            case DOWN:  y -= step.amount; break;
            case LEFT:  x -= step.amount; break;
            case RIGHT: x += step.amount; break;
        }
    }
    
    return std::abs(x) + std::abs(y);
}

auto part_2([[maybe_unused]] std::string_view input)
{
    std::set<std::pair<int32_t, int32_t>> visited;
    Direction current_direction = RIGHT;
    int32_t x = 0;
    int32_t y = 0;

    for (auto step : parse_input(input))
    {
        current_direction = turn(current_direction, step.direction);
        
        for(int i = 0; i < step.amount; i++)
        {
            visited.insert({x, y});
            switch(current_direction)
            {
                case UP:    y++; break;
                case DOWN:  y--; break;
                case LEFT:  x--; break;
                case RIGHT: x++; break;
            }

            if(visited.find({x, y}) != visited.end())
            {
                return std::abs(x) + std::abs(y);
            }
        }
    }
    
    return -1;
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

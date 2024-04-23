#include "../common.hpp"

bool constexpr botlog = false;

struct Bot
{
    size_t chip_count = 0;
    std::array<uint64_t, 2> chips = {};

    void give(uint64_t chip) 
    {
        switch(chip_count)
        {
            case 0:
                chips[0] = chip;
                break;
            case 1:
                chips[1] = chip;
                if(chips[1] < chips[0])
                {
                    std::swap(chips[0], chips[1]);
                }
                break;
            default:
                throw std::exception();
        }
        
        chip_count++;
    }

    uint64_t low() const
    {
        if(chip_count != 2)
        {
            throw std::exception();
        }
        return chips[0];
    }

    uint64_t high() const
    {
        if(chip_count != 2)
        {
            throw std::exception();
        }
        return chips[1];
    }

    void clear()
    {
        chip_count = 0;
    }
};

enum class InstructionType
{
    ValueToBot,
    BotGives
};

struct ValueTo
{
    uint64_t bot;
    uint64_t value;
};

struct BotRule
{
    uint64_t low_to;
    uint64_t high_to;
    bool low_output;
    bool high_output;
};

struct Instructions
{
    std::vector<ValueTo> values;
    std::map<uint64_t, BotRule> rules;
};

Instructions parse_input(std::string_view input)
{
    Instructions result;
    for(auto line : lines(input))
    {
        auto strs = split(line);
        if(strs[0] == "value")
        {
            // value 5 goes to bot 2
            uint64_t value = parse_int(strs[1]);
            uint64_t bot = parse_int(strs[5]);
            result.values.emplace_back(ValueTo {bot, value});
        }
        else if(strs[0] == "bot")
        {
            // bot 2 gives low to bot 1 and high to output 0
            uint64_t giver = parse_int(strs[1]);
            uint64_t bot_low = parse_int(strs[6]);
            uint64_t bot_high = parse_int(strs[11]);
            bool low_output = strs[5] == "output";
            bool high_output = strs[10] == "output";
            result.rules.insert({
                giver,
                BotRule {
                    bot_low,
                    bot_high,
                    low_output,
                    high_output,
            }});
        }
    }
    return result;
}

void perform_operation(
    uint64_t bot,
    std::map<uint64_t, Bot> &bots,
    std::map<uint64_t, uint64_t> &bins,
    const Instructions &instructions,
    std::optional<uint64_t> &answer)
{
    Bot &b = bots[bot];
    if(b.chip_count != 2)
    {
        return;
    }

    if(b.low() == 17 && b.high() == 61 && !answer)
    {
        answer = bot;
    }
    
    BotRule rule = instructions.rules.at(bot);
    
    if constexpr (botlog)
    {
        std::cout << "Bot " << bot 
            << " gives " << b.low() << " to " 
            << (rule.low_output ? "output" : "bot") << " " << rule.low_to
            << " and " << b.high() << " to " 
            << (rule.high_output ? "output" : "bot") << " " << rule.high_to
            << std::endl;
    }

    if(rule.low_output)
    {
        bins[rule.low_to] = b.low();
    }
    else 
    {
        bots[rule.low_to].give(b.low());
        perform_operation(rule.low_to, bots, bins, instructions, answer);
    }

    if(rule.high_output)
    {
        bins[rule.high_to] = b.high();
    }
    else 
    {
        bots[rule.high_to].give(b.high());
        perform_operation(rule.high_to, bots, bins, instructions, answer);
    }
    b.clear();
}

void traverse(
    std::map<uint64_t, Bot> &bots,
    std::map<uint64_t, uint64_t> &bins,
    const Instructions &instructions,
    std::optional<uint64_t> &answer
)
{
    for(const auto &value_to : instructions.values)
    {
        if constexpr (botlog)
        {
            std::cout << "Value " << value_to.value 
                << " goes to bot " << value_to.bot << std::endl;
        }
        bots[value_to.bot].give(value_to.value);
        perform_operation(value_to.bot, bots, bins, instructions, answer);
    }
}

auto part_1([[maybe_unused]] std::string_view input)
{
    std::map<uint64_t, Bot> bots;
    std::map<uint64_t, uint64_t> bins;
    Instructions instructions = parse_input(input);
    std::optional<uint64_t> answer;
    traverse(bots, bins, instructions, answer);
    std::stringstream ss;
    answer ? ss << *answer
           : ss << "no such bot";
    return ss.str();
}

auto part_2([[maybe_unused]] std::string_view input)
{
    std::map<uint64_t, Bot> bots;
    std::map<uint64_t, uint64_t> bins;
    Instructions instructions = parse_input(input);
    std::optional<uint64_t> answer;
    traverse(bots, bins, instructions, answer);
    return bins[0] * bins[1] * bins[2];
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

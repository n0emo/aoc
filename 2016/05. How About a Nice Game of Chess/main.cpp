#include "../common.hpp"
#include <sys/types.h>
#include <md5.h>

bool is_filled(char pass[8])
{
    for(int i = 0; i < 8; i++)
    {
        if(pass[i] == '\0') 
        {
            return false;
        }
    }
    return true;
}

void md5_hash(char *input, char *output)
{
    MD5Context context;
    MD5Init(&context);
    MD5Update(&context, (uint8_t *)input, strlen(input));
    MD5End(&context, output);
}

auto part_1([[maybe_unused]] std::string input)
{
    auto input1 = input.substr(0, input.size() - 1);
    const char *s = input1.c_str();
    char buf[50];

    char md5[33];
    size_t pass_size = 0;
    std::stringstream pass;

    for(uint32_t i = 0; i < INT_MAX && pass_size < 8; i++)
    {
        sprintf(buf, "%s%u", s, i);
        md5_hash(buf, md5);
        if(strncmp("00000", md5, 5) == 0)
        {
            pass << md5[5];
            pass_size++;
        }
    }

    return pass.str(); 
}

auto part_2([[maybe_unused]] std::string input)
{
    auto input1 = input.substr(0, input.size() - 1);
    const char *s = input1.c_str();
    char buf[50];

    char md5[33];
    char pass[8] = {0};

    for(uint32_t i = 0; i < INT_MAX && !is_filled(pass); i++)
    {
        sprintf(buf, "%s%u", s, i);
        md5_hash(buf, md5);
        if(strncmp("00000", md5, 5) == 0)
        {
            int pos = md5[5] - '0';
            if(pass[pos] == '\0' && pos < 8)
            {
                pass[pos] = md5[6];
            }
        }
    }

    return std::string(pass, 8);
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

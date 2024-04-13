#include "../common.hpp"

struct Room
{
   std::string name;
    int sector_id;
    std::string checksum;
};

std::vector<Room> parse_input(std::string_view input)
{
    std::vector<Room> result;
    for(auto line : split(input, " \n\r"))
    {
        if(line.empty()) continue;

        auto strs = split(line, "-");
        Room room;
        
        std::stringstream ss;
        auto it = strs.begin();
        ss << *it++;
        for(; it != strs.end() - 1; ++it)
        {
            ss << '-' << *it;
        }
        room.name = ss.str();

        auto sector_id_and_checksum = split(strs.back(), "[]");

        std::from_chars(sector_id_and_checksum[0].data(),
                        sector_id_and_checksum[0].data() + sector_id_and_checksum.size(),
                        room.sector_id);
        room.checksum = sector_id_and_checksum[1];

        result.push_back(room);
    }
    return result;
}

std::string calculate_checksum(const Room &room)
{
    std::map<char, size_t> counts;

    for(auto c : room.name)
    {
        if(c != '-') counts[c]++;
    }

    std::vector<std::pair<char, size_t>> counts_vec(counts.begin(), counts.end());
    std::stable_sort(counts_vec.begin(), counts_vec.end(),
         [](auto a, auto b){ return a.second > b.second;});

    std::string result;
    result.resize(5);
    std::transform(counts_vec.begin(), counts_vec.begin() + 5,
                   result.begin(),
                   [](auto p){ return p.first; });

    return result;
}

char rotate(char c, int amount)
{
    const int alphabet_size = 26;
    c += amount % alphabet_size;
    if((unsigned int)(unsigned char)c > 'z') c -= alphabet_size;
    return c;
}

auto part_1([[maybe_unused]] std::string_view input)
{
    std::vector<Room> rooms = parse_input(input);
    std::vector<Room> valid_rooms;

    std::copy_if(rooms.begin(), rooms.end(),
                 std::back_inserter(valid_rooms), 
                 [](auto r) {return r.checksum == calculate_checksum(r); });

    return std::accumulate(
        valid_rooms.begin(), valid_rooms.end(), 
        0, [](auto acc, auto r){return acc + r.sector_id;});
}

auto part_2([[maybe_unused]] std::string_view input)
{
    std::vector<Room> temp_rooms = parse_input(input);
    std::vector<Room> rooms;

    std::copy_if(temp_rooms.begin(), temp_rooms.end(),
                 std::back_inserter(rooms), 
                 [](auto r) {return r.checksum == calculate_checksum(r); });

    std::cout << std::endl;
    for(auto room : rooms)
    {
        std::cout << "    ";
        for(char c : room.name)
        {
            std::cout << (c == '-' ? ' ' : rotate(c, room.sector_id));
        }
        std::cout << ": " << room.sector_id << std::endl;
    }
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

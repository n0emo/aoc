#include "../common.hpp"

const size_t rows = 6;
const size_t columns = 50;

class Board 
{
private:
    std::array<std::array<bool, columns>, rows> m_board;

public:
    Board()
    {
        for(auto &row : m_board)
        {
            for(auto &column : row)
            {
                column = false;
            }
        }
    }

    size_t rows() const { return m_board.size(); }
    size_t columns() const { return m_board[0].size(); }

    size_t count_lit() const 
    {
        size_t count = 0;
        for(const auto &row : m_board)
        {
            for(const auto &column : row)
            {
                count += column;
            }
        }
        return count;
    }

    bool &operator()(size_t row, size_t column)
    {
        return m_board[row][column];
    }

    void print() const
    {
        for(const auto &row : m_board)
        {
            for(const auto &column : row)
            {
                std::cout << (column ? "#" : ".");    
            }
            std::cout << '\n';
        }

        std::flush(std::cout);
    }
};

class Operation
{
private:
    int m_op1;
    int m_op2;

public:
    explicit Operation(int op1, int op2) 
        : m_op1(op1), m_op2(op2) {}
    virtual ~Operation() = default;

    int op1() const { return m_op1; }
    int op2() const { return m_op2; }

    virtual void apply(Board &board) const = 0;
};

class Rect : public Operation
{
public:
    using Operation::Operation;

    void apply(Board &board) const override 
    {
        for(int i = 0; i < op1(); i++)
        {
            for(int j = 0; j < op2(); j++)
            {
                board(j, i) = true;
            }
        }
    }
};

class RotateRow : public Operation
{
public:
    using Operation::Operation;

    void apply(Board &board) const override 
    {
        for(int i = 0; i < op2(); i++)
        {
            bool carry = board(op1(), board.columns() - 1);
            for(int j = board.columns() - 1; j > 0; j--)
            {
                board(op1(), j) = board(op1(), j - 1);
            }
            board(op1(), 0) = carry;
        }
    }
};

class RotateColumn : public Operation
{
public:
    using Operation::Operation;

    void apply(Board &board) const override 
    {
        for(int i = 0; i < op2(); i++)
        {
            bool carry = board(board.rows() - 1, op1());
            for(int j = board.rows() - 1; j > 0; j--)
            {
                board(j, op1()) = board(j - 1, op1());
            }
            board(0, op1()) = carry;
        }
    }
};

int parse_int(std::string_view s)
{
    int result;
    std::from_chars(s.data(), s.data() + s.size(), result);
    return result;
}

std::vector<std::unique_ptr<Operation>> parse_input(std::string_view input)
{
    std::vector<std::unique_ptr<Operation>> result;

    for(auto line : lines(input))
    {
        auto parts = split(line, " ");
        if(parts[0] == "rect")
        {
            auto ops = split(parts[1], "x");
            result.emplace_back(std::make_unique<Rect>(
                parse_int(ops[0]), parse_int(ops[1])));
        }
        else if(parts[0] == "rotate")
        {
            auto op1 = split(parts[2], "=")[1];
            auto op2 = parts[4];

            if(parts[1] == "row")
            {
                result.emplace_back(std::make_unique<RotateRow>(
                    parse_int(op1), parse_int(op2)));
            }
            else if(parts[1] == "column")
            {
                result.emplace_back(std::make_unique<RotateColumn>(
                    parse_int(op1), parse_int(op2)));
            }
            else
            {
                throw std::invalid_argument("Unknown rotation type " + std::string(parts[1]));
            }
        }
        else 
        {
            throw std::invalid_argument("Unknown operation type " + std::string(parts[0]));
        }
    }

    return result;
}

auto part_1([[maybe_unused]] std::string_view input)
{
    Board board;
    for(const auto &op : parse_input(input))
    {
        op->apply(board);
    }
    return board.count_lit();
}

auto part_2([[maybe_unused]] std::string_view input)
{
    Board board;
    for(const auto &op : parse_input(input))
    {
        op->apply(board);
    }
    std::cout << std::endl;
    board.print(); 
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

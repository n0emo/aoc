namespace SpiralMemory;

static class Spiral
{
    public static int Part1(int input)
    {
        var sqrt = (int)Math.Sqrt(input) + 3;
        var grid = new int[sqrt, sqrt];

        var pos = new Point(sqrt / 2, sqrt / 2);
        var prev = pos;
        var directionProvider = new DirectionProvider();

        for (int i = 0; i < input; i++)
        {
            prev = pos;
            grid[pos.X, pos.Y] = i + 1;
            pos = directionProvider.NextStep(pos);
        }

        return Math.Abs(prev.X - sqrt / 2) + Math.Abs(prev.Y - sqrt / 2);
    }

    public static int Part2(int input)
    {
        var sqrt = (int)Math.Sqrt(input);
        var grid = new int[sqrt, sqrt];

        var pos = new Point(sqrt / 2, sqrt / 2);
        var prev = pos;
        var directionProvider = new DirectionProvider();

        for (int i = 0; i < input; i++)
        {
            prev = pos;
            var sum = GetNeightboursSum(grid, pos);
            if (sum > input)
            {
                return sum;
            }
            grid[pos.X, pos.Y] = sum;
            pos = directionProvider.NextStep(pos);
        }

        throw new Exception();
    }

    static int GetNeightboursSum(int[,] grid, Point pos)
    {
        int sum =
            grid[pos.X + 1, pos.Y]
            + grid[pos.X, pos.Y + 1]
            + grid[pos.X + 1, pos.Y + 1]
            + grid[pos.X - 1, pos.Y]
            + grid[pos.X, pos.Y - 1]
            + grid[pos.X - 1, pos.Y - 1]
            + grid[pos.X - 1, pos.Y + 1]
            + grid[pos.X + 1, pos.Y - 1];

        return sum == 0 ? 1 : sum;
    }
}

struct Point
{
    public int X { get; set; }
    public int Y { get; set; }

    public Point(int x, int y)
    {
        X = x;
        Y = y;
    }
}

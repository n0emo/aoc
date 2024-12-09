namespace SpiralMemory;

internal class Program
{
    private static void Main(string[] args)
    {
        foreach (var arg in args.Skip(1))
        {
            var input = int.Parse(arg);
            Console.WriteLine("Solving for {0}:", input);
            Console.WriteLine("Part 1: {0}", Spiral.Part1(input));
            Console.WriteLine("Part 2: {0}", Spiral.Part2(input));
        }
    }
}

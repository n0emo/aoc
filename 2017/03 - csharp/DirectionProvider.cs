namespace SpiralMemory;

class DirectionProvider
{
    private enum Direction
    {
        RIGHT,
        UP,
        LEFT,
        DOWN
    }

    private Direction _currentDirection;
    private int _changeCounter;
    private decimal _nextDirection;

    public DirectionProvider()
    {
        _currentDirection = Direction.DOWN;
        _changeCounter = 0;
        _nextDirection = 0.5m;
    }

    public Point NextStep(Point point)
    {
        ChangeDirection();
        (int new_x, int new_y) = _currentDirection switch
        {
            Direction.RIGHT => (point.X + 1, point.Y),
            Direction.UP => (point.X, point.Y - 1),
            Direction.LEFT => (point.X - 1, point.Y),
            Direction.DOWN => (point.X, point.Y + 1),
            _ => throw new Exception(),
        };

        _changeCounter++;
        return new Point(new_x, new_y);
    }

    private void ChangeDirection()
    {
        if (_changeCounter >= Math.Floor(_nextDirection))
        {
            switch (_currentDirection)
            {
                case Direction.RIGHT:
                    _currentDirection = Direction.UP;
                    break;
                case Direction.UP:
                    _currentDirection = Direction.LEFT;
                    break;
                case Direction.LEFT:
                    _currentDirection = Direction.DOWN;
                    break;
                case Direction.DOWN:
                    _currentDirection = Direction.RIGHT;
                    break;
            }
            _changeCounter = 0;
            _nextDirection += 0.5m;
        }
    }
}

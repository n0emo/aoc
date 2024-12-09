program maze
    implicit none

    interface
        subroutine solve_file(path)
            character(len=*), intent(in) :: path
        end subroutine
    end interface
    
    integer :: arg_count
    integer :: current_arg
    character(len=100) :: filepath

    current_arg = 1
    arg_count = command_argument_count()

    do while(current_arg <= arg_count)
        call get_command_argument(current_arg, filepath)
        print *, "Solving ", filepath
        call solve_file(filepath)
        current_arg = current_arg + 1
    end do
end program

subroutine solve_file(path)
    implicit none

    character(len=*), intent(in) :: path

    interface
        integer function part1(jumps_arr, length)
            integer, intent(in) :: jumps_arr(:)
            integer, intent(in) :: length
        end function part1
        integer function part2(jumps_arr, length)
            integer, intent(in) :: jumps_arr(:)
            integer, intent(in) :: length
        end function part2
    end interface

    integer :: error
    integer :: iounit
    integer :: jump, current
    integer :: jumps(10000)
    integer :: result1, result2

    open(file=path, newunit=iounit)
    
    current = 1
    do
        read(iounit, "(I10)", iostat=error) jump
        select case(error)
            case(0)
                jumps(current:current) = jump
                current = current + 1
            case default
                exit
        end select
    end do
    
    close(unit=iounit)

    result1 = part1(jumps, current - 1)
    print *, "Part 1:", result1
    result2 = part2(jumps, current - 1)
    print *, "Part 2:", result2
end subroutine


integer function part1(jumps_arr, length)
    implicit none

    integer, intent(in) :: jumps_arr(:)
    integer, intent(in) :: length

    integer, allocatable :: jumps(:)
    integer :: count, current, jump

    jumps = jumps_arr
    current = 1
    count = 0

    do while(current <= length)
        jump = jumps(current)
        jumps(current) = jumps(current) + 1
        current = current + jump
        count = count + 1
    end do

    part1 = count
end function part1


integer function part2(jumps_arr, length)
    implicit none

    integer, intent(in) :: jumps_arr(:)
    integer, intent(in) :: length

    integer, allocatable :: jumps(:)
    integer :: count, current, jump

    jumps = jumps_arr
    current = 1
    count = 0

    do while(current <= length)
        jump = jumps(current)
        if(jump >= 3) then
            jumps(current) = jumps(current) - 1
        else 
            jumps(current) = jumps(current) + 1
        end if

        current = current + jump
        count = count + 1
    end do

    part2 = count
end function part2

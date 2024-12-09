package main

import (
    "fmt"
    "strings"
    "strconv"
)

func getFuel(mass int) int {
    fuel := (mass / 3) - 2
    if fuel < 0 {
        fuel = 0
    }

    return fuel
}

func SolveDay01Part1(contents string) string {
    lines := strings.Split(contents, "\n")

    sum := 0
    for _, line := range lines {
        num := 0

        _, err := fmt.Sscanf(line, "%d", &num)
        if err == nil {
            sum += getFuel(num)
        }
    }

    return strconv.Itoa(sum)
}

func SolveDay01Part2(contents string) string {
    lines := strings.Split(contents, "\n")

    sum := 0
    for _, line := range lines {
        num := 0

        _, err := fmt.Sscanf(line, "%d", &num)
        if err == nil {
            module_sum := 0
            for fuel := getFuel(num); fuel > 0; fuel = getFuel(fuel) {
                module_sum += fuel
            }

            sum += module_sum
        }
    }

    return strconv.Itoa(sum)
}


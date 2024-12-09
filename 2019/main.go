package main

import (
    "fmt"
    "io"
    "log"
    "os"
)

type Solve struct {
    Part1 func(string) string
    Part2 func(string) string
}

var solves = [...]Solve {
    { SolveDay01Part1, SolveDay01Part2 },
    { SolveDay02Part1, SolveDay02Part2 },
}

func main() {
    dayNum := 0
    _, err := fmt.Sscanf(os.Args[1], "%d", &dayNum)
    if err != nil {
        log.Fatalln(err)
    }

    if dayNum > len(solves) || dayNum < 1 {
        log.Fatalln("Invalid day number")
    }

    solve := solves[dayNum - 1]

    for _, arg := range os.Args[2:] {
        fmt.Printf("%s:\n", arg)

        file, err := os.Open(arg)
        if err != nil {
            log.Fatalln(err)
        }

        defer func() {
            err := file.Close()
            if err != nil {
                log.Fatalln(err)
            }
        }()

        contents, err := io.ReadAll(file)
        if err != nil {
            log.Fatalln(err)
        }

        result1 := solve.Part1(string(contents[:]))
        fmt.Printf("  1: %s\n", result1)

        result2 := solve.Part2(string(contents[:]))
        fmt.Printf("  2: %s\n", result2)
    }
}

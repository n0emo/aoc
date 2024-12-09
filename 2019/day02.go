package main

import (
    "strings"
    "strconv"
)

func readIndirect(memory []int, index int) int {
    return memory[memory[index]]
}

func writeIndirect(memory []int, index int, value int) {
    memory[memory[index]] = value
}

func getMemory(input string) []int {
    program := strings.Split(strings.TrimSpace(input), ",")
    memory := make([]int, len(program))
    for index, value := range program {
        num, err := strconv.Atoi(value)
        if err != nil {
            continue
        }

        memory[index] = num
    }

    return memory
}

func interpret(memory []int) {
    ip := 0 // Instruction pointer

    for {
        if ip >= len(memory) {
            goto end
        }

        opcode := memory[ip]
        switch opcode {
            case 1:
                value := readIndirect(memory, ip + 1) + readIndirect(memory, ip + 2)
                writeIndirect(memory, ip + 3, value)
                ip += 4
            case 2:
                value := readIndirect(memory, ip + 1) * readIndirect(memory, ip + 2)
                writeIndirect(memory, ip + 3, value)
                ip += 4
            case 99:
                goto end
        }
    }

end:
}

func SolveDay02Part1(contents string) string {
    memory := getMemory(contents)
    memory[1] = 12
    memory[2] = 2

    interpret(memory)

    return strconv.Itoa(memory[0])
}

func SolveDay02Part2(contents string) string {
    memory := getMemory(contents)
    for noun := range 100 {
        for verb := range 100 {
            memoryCopy := make([]int, len(memory))
            copy(memoryCopy, memory)
            memoryCopy[1] = noun
            memoryCopy[2] = verb

            interpret(memoryCopy)

            if memoryCopy[0] == 19690720 {
                answer := 100 * noun + verb
                return strconv.Itoa(answer)
            }
        }
    }

    return "Not found"
}

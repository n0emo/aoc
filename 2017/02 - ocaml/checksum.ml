let parse_lines file =
    let content = open_in file in
    let lines = ref [] in
    try
        while true; do
            lines := input_line content :: !lines
        done; !lines
    with End_of_file ->
        close_in content;
        List.rev !lines ;;

let parse_line line = 
    let splitted: string list = String.split_on_char ' ' line in
    let filtered = List.filter (fun s -> s != "") splitted in
    List.map (int_of_string) filtered ;;

let min_list nums = List.fold_right min nums max_int
let max_list nums = List.fold_right max nums min_int
    
let part1 file = 
    let str_lines = parse_lines file in
    let lines = List.map parse_line str_lines in
    let diffs = List.map (fun nums -> (max_list nums) - (min_list nums)) lines in
    List.fold_right (+) (diffs) 0 ;;
    
exception EarlyReturn of int

let find_div nums =
    let ns = Array.of_list nums in
    try
        for i = 0 to List.length nums - 1 do
            for j = 0 to List.length nums - 1 do
                if (i != j) && (ns.(i) mod ns.(j) = 0) then raise (EarlyReturn (ns.(i) / ns.(j)))
            done;
        done;
        min_int
    with EarlyReturn result -> result
    

let part2 file = 
    let str_lines = parse_lines file in
    let lines = List.map parse_line str_lines in
    let divs = List.map (fun l -> find_div l) lines in
    List.fold_right (+) (divs) 0 ;;

for i = 1 to Array.length Sys.argv - 1 do
    let file = Sys.argv.(i) in
    Printf.printf "Solving %s.\n" file;
    Printf.printf "Part 1: %i\n" (part1 file);
    Printf.printf "Part 2: %i\n" (part2 file)
done;


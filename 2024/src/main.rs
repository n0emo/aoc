mod day01;
mod day02;

use std::error::Error;

use clap::Parser;

pub trait Solver {
    fn part_1(&self, content: &str) -> Result<String, Box<dyn Error>> {
        let _ = content;
        Err("Not yet implemented".into())
    }

    fn part_2(&self, content: &str) -> Result<String, Box<dyn Error>> {
        let _ = content;
        Err("Not yet implemented".into())
    }
}

const SOLVERS: &[&dyn Solver] = &[
    &day01::Day01,
    &day02::Day02,
];

#[derive(Parser, Debug)]
pub struct Args {
    #[arg(long, short)]
    day: usize,

    files: Vec<String>,
}

fn main() -> Result<(), Box<dyn Error>> {
    let args = Args::parse();

    let day = args.day;
    if day< 1 || day > SOLVERS.len() {
        let e = format!("The day is out of range! Possible values are [1..{}]", SOLVERS.len());
        return Err(e.into())
    }

    for file in args.files {
        println!("Solving {file}");
        let content = std::fs::read_to_string(file)?;
        let solver = SOLVERS[args.day - 1];
        println!("  Part 1: {}", solver.part_1(&content).unwrap_or_else(|e| format!("Error: {e:?}")));
        println!("  Part 2: {}", solver.part_2(&content).unwrap_or_else(|e| format!("Error: {e:?}")));
    }

    Ok(())
}


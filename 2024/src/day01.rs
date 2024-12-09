use std::error::Error;

use crate::Solver;

pub struct Day01;

struct Input {
    left: Vec<i32>,
    right: Vec<i32>,
}

fn parse_input(content: &str) -> Input {
    let (left, right) = content.lines()
        .map(|l| l.split_whitespace().map(|s| s.to_owned()))
        .filter_map(|mut i| Some((
            i.next()?.parse::<i32>().ok()?,
            i.next()?.parse::<i32>().ok()?,
        )))
        .unzip();

    Input { left, right }
}

impl Solver for Day01 {
    fn part_1(&self, content: &str) -> Result<String, Box<dyn Error>> {
        let mut input = parse_input(content);
        input.left.sort();
        input.right.sort();
        let answer: i32 = input.left.iter()
            .zip(input.right)
            .map(|(l, r)| (l - r).abs())
            .sum();

        Ok(answer.to_string())
    }

    fn part_2(&self, content: &str) -> Result<String, Box<dyn Error>>{
        let input = parse_input(content);
        let answer: i32 = input.left.iter()
            .map(|n| n * input.right.iter().filter(|m| n == *m).count() as i32)
            .sum();

        Ok(answer.to_string())
    }
}

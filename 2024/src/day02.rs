use crate::Solver;

struct Input {
    reports: Vec<Vec<i32>>
}

pub struct Day02;

fn parse_input(content: &str) -> Input {
    let reports = content.lines()
        .map(|l| l.split_whitespace()
            .filter_map(|s| s.parse().ok())
            .collect())
        .collect();

    Input { reports }
}

fn examine_report(report: &Vec<i32>, condition: impl Fn(i32, i32) -> bool) -> bool {
    report.iter()
        .zip(report.iter().skip(1))
        .all(|(l, r)| condition(*l, *r))
}

fn examine_report_tolerate(report: &Vec<i32>, condition: impl Fn(i32, i32) -> bool) -> bool {
    if report.is_empty() {
        return false;
    }

    let mut report = report.clone();
    let mut removed = report.pop().unwrap();

    if examine_report(&report, &condition) {
        return true;
    }

    for i in (0..report.len()).rev() {
        (removed, report[i]) = (report[i], removed);
        if examine_report(&report, &condition) {
            return true;
        }
    }

    false
}

impl Solver for Day02 {
    fn part_1(&self, content: &str) -> Result<String, Box<dyn std::error::Error>> {
        let Input { reports } = parse_input(content);
        let answer = reports.iter()
            .filter(|r| examine_report(r, |l, r| (1..=3).contains(&(l - r))) ||
                        examine_report(r, |l, r| (1..=3).contains(&(r - l))))
            .count();

        Ok(answer.to_string())
    }

    fn part_2(&self, content: &str) -> Result<String, Box<dyn std::error::Error>> {
        let Input { reports } = parse_input(content);
        let answer = reports.iter()
            .filter(|r| examine_report_tolerate(r, |l, r| (1..=3).contains(&(l - r))) ||
                        examine_report_tolerate(r, |l, r| (1..=3).contains(&(r - l))))
            .count();

        Ok(answer.to_string())
    }
}

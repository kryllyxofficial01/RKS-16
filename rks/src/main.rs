use std::fs::File;
use std::io::{BufReader, BufRead};
use crate::utils::compiler::Compiler;

pub mod utils;

fn main() {
    let file = File::open("src/tests/test.rks").expect("Could not find the file");
    let reader = BufReader::new(file);

    let mut lines: Vec<String> = Vec::new();
    for line in reader.lines() {
        lines.push(line.unwrap());
    }

    for line in lines {
        Compiler::compile(line);
    }
}

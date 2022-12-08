use std::fs::File;
use std::io::{BufReader, BufRead};
use crate::utils::compiler::Compiler;

pub mod utils;

fn main() {
    let file = File::open("src/tests/test.rks").expect("Could not find the file");
    let reader = BufReader::new(file);

    for line in reader.lines() {
        Compiler::compile(line.unwrap());
    }
}

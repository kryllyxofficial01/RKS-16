use std::fs::File;
use std::io::{BufReader, BufRead};

use crate::utils::{compiler::compiler::Compiler, error::error::Error};

pub mod utils;

fn main() {
    let file = File::open("src/tests/test.rks").expect("Could not find the file");
    let reader = BufReader::new(file);

    let mut i = 1;
    for line in reader.lines() {
        let instruction = line.unwrap();
        
        let error = Error::new(instruction, i);
        let compiler = Compiler::new(&instruction, error);

        i += 1;
    }
}

use std::fs::File;
use std::io::{BufReader, BufRead};
use crate::utils::compiler::compiler::Compiler;

pub mod utils;

fn main() {
    let file = File::open("src/tests/test.rks").expect("Could not find the file");
    let reader = BufReader::new(file);

    let compiler = Compiler::default();
    for line in reader.lines() {
        let compiled = compiler.compile(line.unwrap());
		println!("{:?}", compiled);
    }
}

use std::fs;
use std::io::{BufReader, BufRead};
use std::path::PathBuf;

use crate::utils::{compiler::compiler::Compiler, error::error::Error};

pub mod utils;

fn main() {
    let filename = "src/tests/test.rks";
    let location = fs::canonicalize(&(PathBuf::from(filename))).unwrap();
    
    let file = fs::File::open(filename).expect("Could not find the file");
    let reader = BufReader::new(file);

    let mut lineno = 1;
    for line in reader.lines() {
        let instruction = line.unwrap();
        
        let error = Error::new(&instruction, lineno, location.to_str().unwrap().to_string());
        let compiler = Compiler::new(&instruction, error);

        let compiled = compiler.compile();
        println!("{:?}", compiled);

        lineno += 1;
    }
}

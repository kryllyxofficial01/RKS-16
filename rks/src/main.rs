use std::collections::HashMap;
use std::fs::{self, File};
use std::io::{BufReader, BufRead};
use std::path::PathBuf;

use crate::utils::{compiler::compiler::Compiler, assembler::assembler::Assembler, error::error::Error};

pub mod utils;

fn main() {
    let filename = "../tests/test.rks";
    let location = fs::canonicalize(&(PathBuf::from(filename))).unwrap();
    
    let file = &fs::File::open(filename).expect("Could not find the file");
    let reader = BufReader::new(file);

    println!("Compiling...");

    let labels: HashMap<String, u32> = find_labels(reader.lines().collect::<Result<_, _>>().unwrap());

    let mut instructions: Vec<String> = Vec::new();
    let mut lineno = 1;

    for line in BufReader::new(file).lines() {
        let instruction = &line.unwrap();
        
        if instruction != "" && &instruction[..1] != ";" {
            let error = Error::new(instruction, lineno, location.to_str().unwrap().to_string());
            let mut compiler = Compiler::new(instruction, error);

            let mut compiled = compiler.compile();
            if compiled.len() == 1 {
                compiled.push("0".repeat(10).to_string());
            }
            instructions.push(compiled.join(""));
        }

        lineno += 1;
    }

    println!("\nAssembling...");
    let assembler = Assembler::new(instructions);
    assembler.assemble(&(location.to_str().unwrap()[0..location.to_str().unwrap().len()-4].to_string()));
}

fn find_labels(instructions: Vec<String>) -> HashMap<String, u32> {
    let mut labels: HashMap<String, u32> = HashMap::new();

    for instruction in instructions {
        
    }

    return labels;
}
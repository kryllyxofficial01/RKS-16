#![warn(non_snake_case)]

use std::collections::HashMap;
use std::fs;
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

    let instructions: Vec<String> = clean(reader.lines().collect::<Result<_, _>>().unwrap(), location.to_str().unwrap().to_string());
    // let labels: HashMap<String, u32> = cleaned.1;

    // println!("{:?}", labels);
    
    let mut lineno = 1;
    let mut binary: Vec<String> = Vec::new();
    for instruction in instructions {
        let error = Error::new(&instruction, lineno, location.to_str().unwrap().to_string());
        let mut compiler = Compiler::new(&instruction, error);

        let mut compiled = compiler.compile();
        if compiled.len() == 1 {
            compiled.push("0".repeat(10).to_string());
        }
        binary.push(compiled.join(""));

        lineno += 1;
    }

    println!("\nAssembling...");
    let assembler = Assembler::new(binary);
    assembler.assemble(&(location.to_str().unwrap()[0..location.to_str().unwrap().len()-4].to_string()));
}

fn clean(mut lines: Vec<String>, location: String) -> Vec<String> {
    let mut labels: HashMap<String, u32> = HashMap::new();
    let mut instructions: Vec<String> = Vec::new();

    lines.retain(|i| i.trim() != "" && !i.trim().starts_with(";"));

    println!("{:?}", lines);
    std::process::exit(0);

    let mut lineno = 1;
    let mut i: i32 = -1;
    let mut inLabel = false;
    for line in lines {
        let error = Error::new(&line, lineno, location.clone());

        if line.starts_with(".") {
            let mut idx = 1;
            let mut label = String::new();
            while idx != line.len() {
                label.push(line.chars().nth(idx).unwrap());
                idx += 1;
            }

            println!("{label}");

            if label == "stop" {
                if !inLabel {
                    error.print_stacktrace("LabelError", "Attempted to stop a label, but no label has been started".to_string())
                }
                else {
                    inLabel = false;
                }
            }
            else {
                if inLabel {
                    error.print_stacktrace("LabelError", "Attempted to start a label, but the previous label has not been closed".to_string())
                }
                else {
                    inLabel = true;

                }
            }
        }

        lineno += 1;
    }

    return instructions;
}
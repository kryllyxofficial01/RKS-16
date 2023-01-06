#![allow(non_snake_case, unused_variables, unused_mut)]

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
    let mut labels: HashMap<String, (u32, Vec<String>)> = HashMap::new();
    let mut instructions: Vec<String> = Vec::new();

    lines.retain(|i| i.trim() != "" && !i.trim().starts_with(";"));

    let mut lineno = 1;
    let mut i: i32 = -1;
    let mut inLabel = false;
	let mut labelName = String::new();
    for line in &lines.clone() {
        // let error = Error::new(&line, lineno, location.clone());
		let line = &line.trim().to_string();

		if !inLabel {
			if line.starts_with(".") && line != ".stop" {
	            let mut idx = 1;
	            let mut label = String::new();
	            while idx != line.len() {
	                label.push(line.chars().nth(idx).unwrap());
	                idx += 1;
	            }

				labels.insert(label.clone(), ((i+1).try_into().unwrap(), Vec::new()));
				inLabel = true;
				labelName = label;
			}
			else {
				i += 1
			}
		}
		else {
			if line == ".stop" {
				inLabel = false;
				
				lines.retain(|i| *i != ".".to_string() + &labelName);
				for instruction in &labels.get_mut(&labelName).unwrap().1 {
					lines.retain(|i| i.trim() != instruction);
				}
				lines.retain(|i| *i != ".stop".to_string());
			}
			
			labels.get_mut(&labelName).unwrap().1.push(line.trim().to_string());
			i += 1;
		}

        lineno += 1;
	}

	for i in 0..labels.keys().len() {
		let keys = &labels.keys().cloned().collect::<Vec<String>>();
		let mut content = &mut labels.get(&keys[i]).unwrap().to_owned();

		if i != 0 {
			content.0 = labels.get(&keys[i-1]).unwrap().1.len() as u32;
		}

		println!("{:?}", content)
	}
	
	print!("{:?}", instructions);

    return instructions;
}
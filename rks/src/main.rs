#![allow(non_snake_case, unused_variables, unused_mut, dead_code)]

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

	let cleaned = clean(reader.lines().collect::<Result<_, _>>().unwrap(), location.to_str().unwrap().to_string());
    let instructions = cleaned.0;
	let labels = cleaned.1;
    
    let mut lineno = 1;
    let mut binary: Vec<String> = Vec::new();
    for instruction in instructions {
        let error = Error::new(&instruction, lineno, location.to_str().unwrap().to_string());
        let mut compiler = Compiler::new(&instruction, labels.clone(), error);

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

fn clean(mut lines: Vec<String>, location: String) -> (Vec<String>, Vec<(String, u32, Vec<String>)>) {
    let mut labels: Vec<(String, u32, Vec<String>)> = Vec::new();

	lines = lines.iter().map(|i| i.trim().to_string()).collect();
	lines.retain(|i| i != "" && !i.starts_with(";"));

	let mut isLabel = false;
	let mut i = 0;
	let mut idx = 0;
	let mut indexes: Vec<u32> = Vec::new();
	for line in lines.clone() {
		if line.starts_with(".") && line != ".stop" && !isLabel {
			labels.push((line[1..].to_string(), 0, Vec::new()));
			indexes.push(idx);
			isLabel = true;
		}
		else if line == ".stop" && isLabel {
			labels.get_mut(i).unwrap().2.push(line.to_string());
			indexes.push(idx);
			isLabel = false;
			i += 1;
		}
		else if isLabel {
			labels.get_mut(i).unwrap().2.push(line.to_string());
			indexes.push(idx);
		}

		idx += 1;
	}

	for index in indexes {
		*lines.get_mut(index as usize).unwrap() = String::new();
	}
	lines.retain(|i| i != "");

	labels.reverse();
	for label in &labels {
		lines = [label.clone().2, lines].concat();
	}

	labels.reverse();
	for i in 0..lines.len() {
		for idx in 0..labels.len() {
			if idx != 0 {
				labels.get_mut(idx).unwrap().1 = labels.get(idx-1).unwrap().2.len() as u32;
			}
		}
	}

    return (lines, labels)
}
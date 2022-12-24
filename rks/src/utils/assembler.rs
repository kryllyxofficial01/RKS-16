#![allow(non_snake_case, unused_must_use)]

pub mod assembler {
	use std::{fs::File, io::Write};

	pub struct Assembler {
		instructions: Vec<String>
	}

	impl Assembler {
		pub fn new(instructions: Vec<String>) -> Self {
			Self {
				instructions: instructions
			}
		}

		pub fn assemble(&self, path: &String) {
			let mut file = File::create(path).unwrap();

			println!("Writing to output file...");
			for instruction in &self.instructions {
				file.write_all((instruction.to_owned() + "\n").as_bytes());
			}
		}
	}
}

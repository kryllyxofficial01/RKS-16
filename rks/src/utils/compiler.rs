#![allow(non_snake_case)]

use substring::Substring;

pub mod compiler {
    use std::collections::HashMap;

    pub struct Compiler<'a> {
		instructions: HashMap<&'a str, &'a str>
	}

	impl Default for Compiler<'_> {
		fn default() -> Self {
			Self { 
				instructions: HashMap::from(
					[
						("NOP", "000000"),
						("LDA", "000001")
					]
				) 
			}
		}
	}

	impl Compiler<'_> {
		pub fn compile(&self, line: String) -> Vec<&str> {
			let instruction: Vec<&str> = line.split(" ").collect();
			let cmd = instruction.get(0);
			let args = &instruction[1..instruction.len()];
	
			let mut binary: Vec<&str> = Vec::new();
			binary.push(self.instructions.get(&cmd.unwrap() as &str).unwrap());
	
			for arg in args {
				let prefix = arg.chars().next().unwrap();
				if prefix == '!' {
					
				}
			}

			return binary;
		}
	}
}
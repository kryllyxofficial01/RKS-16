#![allow(non_snake_case)]

pub mod Compiler {
	pub fn compile(line: String) {
		let mut instruction: Vec<&str> = line.split(" ").collect();
		let cmd = instruction.get(0); instruction.remove(0);
		let args: Vec<&str> = instruction;

		for arg in args {
			let prefix = arg.chars().next().unwrap();
			if prefix == '!' {
				
			}
		}
	}
}
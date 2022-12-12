#![allow(non_snake_case)]

pub mod compiler {
    use std::collections::HashMap;

    use crate::utils::error::error::Error;

    pub struct Compiler<'a> {
		instructions: HashMap<&'a str, (&'a str, u8)>,
		registers: HashMap<&'a str, i8>,
		line: String,
		error: Error
	}

	impl Compiler<'_> {
		pub fn new(line: &String, error: Error) -> Self {
			Self { 
				instructions: HashMap::from(
					[
						("NOP", ("000000", 0)),
						("LDA", ("000001", 1)),
						("LDB", ("000010", 1)),
						("LDC", ("000011", 1)),
						("LDD", ("000100", 1)),
						("SWP", ("000101", 2)),
						("MOV", ("000110", 2)),
						("STA", ("000111", 1)),
						("STB", ("001000", 1)),
						("STC", ("001001", 1)),
						("STD", ("001010", 1)),
						("STAO", ("001011", 1)),
						("LRA", ("001100", 1)),
						("LRB", ("001101", 1)),
						("LRC", ("001110", 1)),
						("LRD", ("001111", 1)),
						("PSH", ("010000", 1)),
						("PUL", ("010001", 1)),
						("ISP", ("010010", 0)),
						("DSP", ("010011", 0)),
						("ADD", ("010100", 2)),
						("SUB", ("010101", 2)),
						("MUL", ("010110", 2)),
						("DIV", ("010111", 2)),
						("AND", ("011000", 2)),
						("OR", ("011001", 2)),
						("NOR", ("011010", 2)),
						("XOR", ("011011", 2)),
						("NOT", ("011100", 1)),
						("INC", ("011101", 1)),
						("DEC", ("011110", 1)),
						("JMP", ("011111", 1)),
						("CMP", ("100000", 2)),
						("JZ", ("100001", 1)),
						("JN", ("100010", 1)),
						("JO", ("100011", 1)),
						("HLT", ("100100", 0))
					]
				),
				registers: HashMap::from(
					[
						("A", 0),
						("B", 1),
						("C", 2),
						("D", 3),
						("AO", 4),
						("F", 5),
						("PC", 6),
						("SP", 7)
					]
				),
				line: line.to_string(),
				error: error
			}
		}

		pub fn compile(&self) -> Vec<String> {
			let instruction: Vec<&str> = self.line.split(" ").collect();
			let cmd = &self.instructions.get(&instruction.get(0).unwrap().to_uppercase() as &str).unwrap().0.to_string();
			let args = &instruction[1..];
	
			let mut binary: Vec<String> = Vec::new();
			binary.push(cmd.to_string());
	
			for arg in args {
				let mut i = arg.chars().into_iter();
				let prefix = i.next().unwrap();
				let mut bin = String::new();
				
				if prefix == '!' {
					bin = self.bin(&arg[1..]);
				}
				else if prefix == '@' {
					if !self.registers.contains_key(&arg[1..]) {
						self.error.print_stacktrace("RegisterIDError".to_string(), format!("Unknown register ID '{}'", &arg[1..]));
					}

					if &(*self.registers.get(&arg[1..].to_uppercase() as &str).unwrap() as usize) <= &4 {
						bin = self.bin(&self.registers.get(&arg[1..].to_uppercase() as &str).unwrap().to_string());
					}
					else {
						self.error.print_stacktrace("RegisterIDError".to_string(), format!("Illegal use of register '{}'", &arg[1..]))
					}
				}
				else if prefix == '0' {
					let base = prefix.to_string() + &i.next().unwrap().to_string();
					
					if base == "0b" {
						bin = arg[2..].to_string();
					}
					else if base == "0x" {

					}
					else {
						self.error.print_stacktrace("BaseError".to_string(), format!("Unknown base '{}'", base));
					}
				}

				let repeat = cmd.len() + bin.len();
				if repeat > 16 {
					self.error.print_stacktrace("OverflowError".to_string(), format!("Immediate value '{}' goes over 10-bit limit", &arg[1..]))
				}

				binary.push(format!("{}", "0".repeat(16 - repeat)) + &bin.to_string());
			}

			if &binary[1..].len() > &(self.instructions.get(&instruction.get(0).unwrap().to_uppercase() as &str).unwrap().1 as usize) {
				self.error.print_stacktrace("ArgError".to_string(), format!("Too many arguments; instruction only takes {} argument(s)", self.instructions.get(&cmd.to_uppercase() as &str).unwrap().1));
			}

			return binary;
		}

		fn bin(&self, immediate: &str) -> String {
			return format!("{:b}", immediate.parse::<u16>().unwrap());
		}
	}
}

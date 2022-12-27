#![allow(non_snake_case)]

pub mod compiler {
    use std::collections::HashMap;
	use to_binary::BinaryString;

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
						("LRA", ("001011", 1)),
						("LRB", ("001100", 1)),
						("LRC", ("001101", 1)),
						("LRD", ("001110", 1)),
						("PSH", ("001111", 1)),
						("PUL", ("010000", 1)),
						("ISP", ("010001", 1)),
						("DSP", ("010010", 1)),
						("ADD", ("010011", 2)),
						("SUB", ("010100", 2)),
						("MUL", ("010101", 2)),
						("DIV", ("010110", 2)),
						("AND", ("010111", 2)),
						("OR", ("011000", 2)),
						("NOR", ("011001", 2)),
						("XOR", ("011010", 2)),
						("NOT", ("011011", 1)),
						("INC", ("011100", 1)),
						("DEC", ("011101", 1)),
						("JMP", ("011110", 1)),
						("CMP", ("011111", 2)),
						("JZ", ("100000", 1)),
						("JN", ("100001", 1)),
						("JO", ("100010", 1)),
						("HLT", ("100011", 0))
					]
				),
				registers: HashMap::from(
					[
						("A", 0),
						("B", 1),
						("C", 2),
						("D", 3),
						("F", 4),
						("PC", 5),
						("SP", 6)
					]
				),
				line: line.to_string(),
				error: error
			}
		}

		pub fn compile(&self) -> Vec<String> {
			let mut binary: Vec<String> = Vec::new();
			let instruction: Vec<&str> = self.line.split(" ").collect();
			
			if self.instructions.contains_key(instruction.get(0).unwrap().to_uppercase().as_str()) {
				let cmd = &self.instructions.get(&instruction.get(0).unwrap().to_uppercase() as &str).unwrap().0.to_string();
				let args = &instruction[1..];

				println!("Current instruction: {} -> {}", instruction.get(0).unwrap().to_lowercase(), cmd);

				binary.push(cmd.to_string());

				if args.len() == self.instructions.get(&instruction.get(0).unwrap().to_uppercase() as &str).unwrap().1 as usize {
					for arg in args {
						let mut i = arg.chars().into_iter();
						let prefix = i.next().unwrap();
						let mut bin = String::new();
						let mut start = 1;
	
						if &arg[1..] == "" {
							self.error.print_stacktrace("RegisterIDError", "Missing argument info".to_string());
						}
						
						if prefix == '!' {
							bin = self.bin(&arg[1..]);
						}
						else if prefix == '@' {
							if !self.registers.contains_key(&arg[1..]) {
								self.error.print_stacktrace("RegisterIDError", format!("Unknown register ID '{}'", &arg[1..]));
							}
	
							// if &(*self.registers.get(&arg[1..].to_uppercase() as &str).unwrap() as usize) <= &4 {
							// 	bin = self.bin(&self.registers.get(&arg[1..].to_uppercase() as &str).unwrap().to_string());
							// }
							// else {
							// 	self.error.print_stacktrace("RegisterIDError".to_string(), format!("Illegal use of register '{}'", &arg[1..]))
							// }
	
							bin = self.bin(&self.registers.get(&arg[1..].to_uppercase() as &str).unwrap().to_string());
						}
						else if prefix == '0' {
							let base = prefix.to_string() + &i.next().unwrap().to_string();
							start = 2;
							
							if base == "0b" {
								bin = arg[2..].to_string();
							}
							else if base == "0x" {
								bin = BinaryString::from_hex(&arg[2..]).unwrap().to_string();
							}
							else {
								self.error.print_stacktrace("BaseError", format!("Unknown base '{}'", base));
							}
						}
						else {
							self.error.print_stacktrace("ArgError", format!("Unknown prefix '{}'", prefix));
						}
	
						bin = bin.trim_start_matches("0").to_string();
						let repeat = cmd.len() + bin.len();
						if repeat > 16 {
							self.error.print_stacktrace("OverflowError", format!("Value '{}' goes over 10-bit limit", &arg[start..]))
						}
	
						binary.push("0".repeat(16 - repeat) + &bin.to_string());
					}
				}
				else {
					if args.len() > self.instructions.get(&instruction.get(0).unwrap().to_uppercase() as &str).unwrap().1 as usize {
						self.error.print_stacktrace("ArgError", format!("Too many arguments; instruction only takes {} argument(s)", self.instructions.get(instruction.get(0).unwrap().to_uppercase().as_str()).unwrap().1));
					}
					else {
						self.error.print_stacktrace("ArgError", format!("Missing {} argument(s)", self.instructions.get(instruction.get(0).unwrap().to_uppercase().as_str()).unwrap().1 - args.len() as u8))
					}
				}
			}
			else {
				self.error.print_stacktrace("InstructionError", format!("Unknown instruction '{}'", instruction.get(0).unwrap()));
			}

			if binary[1..].len() == 2 {
				for arg in &binary.clone()[1..] {
					let mut arg_val = arg.trim_start_matches("0");
					if arg_val == "" {
						arg_val = "0";
					}

					let index = binary.iter().position(|i| i == arg).unwrap();
					binary[index] = "0".repeat(5 - arg_val.len()) + &arg_val.to_string();
				}
			}

			return binary;
		}

		fn bin(&self, immediate: &str) -> String {
			for character in immediate.chars() {
				if !character.is_numeric() {
					self.error.print_stacktrace("ValueError", format!("Invalid value '{}'", immediate));
				}
			}

			let mut bin = 0;
			match immediate.parse::<u16>() {
				Ok(immediate) => bin = immediate,
    			Err(_) => self.error.print_stacktrace("ValueError", format!("Value '{}' goes over 10-bit limit", immediate)),
			}

			return format!("{:b}", bin);
		}
	}
}

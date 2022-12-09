#![allow(non_snake_case)]

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
						("LDA", "000001"),
						("LDB", "000010"),
						("LDC", "000011"),
						("LDD", "000100"),
						("SWP", "000101"),
						("MOV", "000110"),
						("STA", "000111"),
						("STB", "001000"),
						("STC", "001001"),
						("STD", "001010"),
						("STAO", "001011"),
						("LRA", "001100"),
						("LRB", "001101"),
						("LRC", "001110"),
						("LRD", "001111"),
						("PSH", "010000"),
						("PUL", "010001"),
						("ISP", "010010"),
						("DSP", "010011"),
						("ADD", "010100"),
						("SUB", "010101"),
						("MUL", "010110"),
						("DIV", "010111"),
						("AND", "011000"),
						("OR", "011001"),
						("NOR", "011010"),
						("XOR", "011011"),
						("NOT", "011100"),
						("INC", "011101"),
						("DEC", "011110"),
						("JMP", "011111"),
						("CMP", "100000"),
						("JZ", "100001"),
						("JN", "100010"),
						("JO", "100011"),
						("HLT", "100100")
					]
				) 
			}
		}
	}

	impl Compiler<'_> {
		pub fn compile(&self, line: String) -> Vec<String> {
			let instruction: Vec<&str> = line.split(" ").collect();
			let cmd = instruction.get(0);
			let args = &instruction[1..];
	
			let mut binary: Vec<String> = Vec::new();
			binary.push(self.instructions.get(&cmd.unwrap().to_uppercase() as &str).unwrap().to_string());
	
			for arg in args {
				let prefix = arg.chars().next().unwrap();
				let mut bin = String::new();
				
				if prefix == '!' {
					bin = self.bin(&arg[1..]);
				}

				binary.push(bin.to_string());
			}

			return binary;
		}

		fn bin(&self, immediate: &str) -> String {
			return format!("{:b}", immediate.parse::<i16>().unwrap());
		}
	}
}

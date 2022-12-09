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
						("LDA", "000001")
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
			binary.push(self.instructions.get(&cmd.unwrap() as &str).unwrap().to_string());
	
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

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

			let mut hex: Vec<Vec<String>> = Vec::new();
			let mut line = 0;
			hex.push(Vec::new());
			for instruction in &self.instructions {
				let index = self.instructions.iter().position(|i| i == instruction).unwrap();
				if index % 16 == 0 {
					line += 1;
					hex.push(Vec::new());
				}

				hex[line].push(self.hex(instruction.to_string()));
			}
			hex.remove(0);

			file.write_all(b"v3.0 hex words plain\n");
			for vec in hex {
				let data = vec.join(" ") + "\n";
				file.write_all(data.as_bytes());
			}
		}

		fn hex(&self, data: String) -> String {
			let hexadecimal: u32 = u32::from_str_radix(data.as_str(), 2).unwrap();
    		return format!("{:01$x}", hexadecimal, 4);
		}
	}
}
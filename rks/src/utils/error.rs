#![allow(non_snake_case)]

pub mod error {
	pub struct Error {
		line: String,
		lineno: i128,
		location: String
	}

	impl Error {
		pub fn new(line: &String, lineno: i128, location: String) -> Self {
			Self {
				line: line.to_string(),
				lineno: lineno,
				location: location
			}
		}

		pub fn print_stacktrace(&self, error_name: &str, reason: String) {
			println!("\n\x1b[31mError - at line {} in <{}>", self.lineno, self.location);
			println!("\t{}", self.line);
			println!("{}: {}\n\x1b[0m", error_name, reason);

			std::process::exit(0);
		}
	}
}
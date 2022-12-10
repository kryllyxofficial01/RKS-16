#![allow(non_snake_case)]

pub mod error {
	pub struct Error {
		line: String,
		lineno: i128
	}

	impl Error {
		pub fn new(line: String, lineno: i128) -> Self {
			Self {
				line: line,
				lineno: lineno
			}
		}
	}
}
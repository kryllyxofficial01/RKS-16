use std::fs::File;
use std::io::{BufReader, BufRead};

fn main() {
    let file = File::open("src/test.rks").expect("Could not find the file");
    let reader = BufReader::new(file);

    let mut lines: Vec<String> = Vec::new();
    for line in reader.lines() {
        lines.push(line.unwrap());
    }

    println!("{:?}", lines);
}

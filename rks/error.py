import sys

class Error:
    def __init__(self, line: str, lineno: int, location: str) -> None:
        self.line = line.strip()
        self.lineno = lineno
        self.location = location
    
    def print_stacktrace(self, error_name: str, reason: str) -> None:
        print(f"\n\033[0;31mError - at line {self.lineno} in <{self.location}>")
        print(f"\t{self.line}\n" if self.line[-1] != "\n" else f"\t{self.line}")
        print(f"{error_name}: {reason}\033[0;0m\n")

        sys.exit(-1)
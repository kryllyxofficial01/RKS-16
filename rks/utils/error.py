import sys

class Error:
    def __init__(self, line, lineno, location):
        self.line = line
        self.lineno = lineno
        self.location = location
    
    def print_stacktrace(self, error_name, reason):
        print(f"\n\033[0;31mError - at line {self.lineno} in <{self.location}>")
        print(f"\t{self.line}\n" if self.line[-1] != "\n" else f"\t{self.line}")
        print(f"{error_name}: {reason}\033[0;0m\n")

        sys.exit(-1)
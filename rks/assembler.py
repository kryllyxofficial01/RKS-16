class Assembler:
    def __init__(self, instruction: str) -> None:
        self.instruction = instruction
    
    @staticmethod
    def clean(instructions: list[str]) -> None:
        for i in range(len(instructions)):
            instructions[i] = instructions[i].strip()
            if instructions[i].strip()[0] == ";":
                instructions[i] = ""
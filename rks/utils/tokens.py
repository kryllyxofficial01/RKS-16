from typing import Union

class Token:
	def __init__(self, type: str, value: str) -> None:
		self.type = type
		self.value = value

	def __repr__(self) -> str:
		return f"{self.type}:{self.value}"

class TokenTypes:
	class Number(Token):
		def __init__(self, type: str, value: Union[int, float]) -> None:
			super().__init__(type, value)

	class Symbol(Token):
		def __init__(self, type: str) -> None:
			super().__init__(type, value="")
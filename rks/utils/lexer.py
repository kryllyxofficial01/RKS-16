from typing import Union

from .tokens import TokenTypes
from .error import Error

class Lexer:
	DIGITS = "0123456789"
	
	def __init__(self, instruction: str, error: Error) -> None:
		self.instruction = instruction
		self.error = error
		self.position = 0
		self.current_char = self.instruction[self.position]

	def lex(self) -> list:
		tokens = []

		while self.current_char != None:
			if self.current_char in self.DIGITS:
				number = self.getNumber()
				tokens.append(TokenTypes.Number(
					"INTEGER" if isinstance(number, int) else "FLOAT",
					number
				))

			elif self.current_char == "+": tokens.append(TokenTypes.Symbol("PLUS"))
			elif self.current_char == "-": tokens.append(TokenTypes.Symbol("MINUS"))
			elif self.current_char == "*": tokens.append(TokenTypes.Symbol("ASTERICK"))
			elif self.current_char == "-": tokens.append(TokenTypes.Symbol("FORWARD_SLASH"))
			elif self.current_char == "(": tokens.append(TokenTypes.Symbol("LEFT_PAREN"))
			elif self.current_char == ")": tokens.append(TokenTypes.Symbol("RIGHT_PAREN"))

			self.next_char()

		return tokens

	def next_char(self) -> None:
		self.position += 1
		try: self.current_char = self.instruction[self.position]
		except IndexError: self.current_char = None

	def getNumber(self) -> Union[int, float]:
		number = ""
		decimal_count = 0

		while self.current_char != None and self.current_char in f"{self.DIGITS}.":
			if self.current_char == ".":
				decimal_count += 1

			number += self.current_char
			self.next_char()

		return int(number) if decimal_count == 0 else float(number)
"""Queue-based string processor from Algorithms Coursework 1."""

from collections import deque
from typing import Sequence


class StringProcessor:
    """Process alternating string operands and ``+`` / ``-`` operators left-to-right."""

    @staticmethod
    def _subtract_characters(source: str, characters: str) -> str:
        """Remove every character from *source* that appears in *characters*."""
        blocked = set(characters)
        return "".join(character for character in source if character not in blocked)

    def process(self, tokens: Sequence[str]) -> str:
        """Return the result of processing a coursework-style token sequence.

        Addition concatenates strings. Subtraction removes every occurrence of
        each character contained in the right-hand operand from the current
        result. A queue is used because the specification processes tokens from
        left to right.
        """
        if not tokens:
            return ""
        if len(tokens) % 2 == 0:
            raise ValueError("Expected: string, operator, string, ...")

        queue = deque(tokens)
        result = queue.popleft()

        while queue:
            operator = queue.popleft()
            operand = queue.popleft()

            if operator == "+":
                result += operand
            elif operator == "-":
                result = self._subtract_characters(result, operand)
            else:
                raise ValueError(f"Unsupported operator: {operator!r}")

        return result


COURSEWORK_CASES = [
    (["x", "+", "yz"], "xyz"),
    (["32", "+", "+5", "+", "-8", "+", " = 29."], "32+5-8 = 29."),
    (["Look, Example:", "+", " Here", "-", ": ,"], "LookExampleHere"),
    (["any", "+", "tnx", "-", "nx", "-", "y"], "at"),
]


if __name__ == "__main__":
    processor = StringProcessor()
    for index, (tokens, expected) in enumerate(COURSEWORK_CASES, start=1):
        actual = processor.process(tokens)
        print(f"Case {index}: {actual!r} | expected={expected!r} | pass={actual == expected}")

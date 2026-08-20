"""26-bucket alphabet hash table with chaining."""

from typing import List


class AlphabetHashTable:
    """Map a-z to 26 buckets and retain duplicate letters through chaining."""

    def __init__(self) -> None:
        self._buckets: List[List[str]] = [[] for _ in range(26)]

    @staticmethod
    def hash_letter(letter: str) -> int:
        if len(letter) != 1 or not letter.isalpha() or not letter.isascii():
            raise ValueError("Expected one ASCII alphabetic character")
        return ord(letter.lower()) - ord("a")

    def add(self, letter: str) -> None:
        normalized = letter.lower()
        self._buckets[self.hash_letter(normalized)].append(normalized)

    def add_text(self, text: str) -> None:
        for character in text.lower():
            if "a" <= character <= "z":
                self.add(character)

    def contains(self, letter: str) -> bool:
        index = self.hash_letter(letter)
        return bool(self._buckets[index])

    def occurrences(self, letter: str) -> int:
        return len(self._buckets[self.hash_letter(letter)])

    def buckets(self) -> List[List[str]]:
        return [bucket.copy() for bucket in self._buckets]


if __name__ == "__main__":
    table = AlphabetHashTable()
    table.add_text("Mohamed Ibrahim")
    for index, bucket in enumerate(table.buckets()):
        if bucket:
            print(f"{chr(ord('a') + index)}: {' -> '.join(bucket)}")

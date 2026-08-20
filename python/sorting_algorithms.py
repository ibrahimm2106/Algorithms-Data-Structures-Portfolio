"""Sorting algorithms demonstrated in Algorithms Coursework 2."""

from typing import List, Sequence, Tuple


def merge_sort(values: Sequence[int]) -> List[int]:
    if len(values) <= 1:
        return list(values)

    middle = len(values) // 2
    left = merge_sort(values[:middle])
    right = merge_sort(values[middle:])

    merged: List[int] = []
    left_index = right_index = 0

    while left_index < len(left) and right_index < len(right):
        if left[left_index] <= right[right_index]:
            merged.append(left[left_index])
            left_index += 1
        else:
            merged.append(right[right_index])
            right_index += 1

    merged.extend(left[left_index:])
    merged.extend(right[right_index:])
    return merged


def quick_sort(values: Sequence[int]) -> List[int]:
    """Quick sort using the last element as pivot, matching the coursework brief."""
    items = list(values)

    def partition(low: int, high: int) -> int:
        pivot = items[high]
        boundary = low - 1
        for cursor in range(low, high):
            if items[cursor] <= pivot:
                boundary += 1
                items[boundary], items[cursor] = items[cursor], items[boundary]
        items[boundary + 1], items[high] = items[high], items[boundary + 1]
        return boundary + 1

    def sort(low: int, high: int) -> None:
        if low < high:
            pivot_index = partition(low, high)
            sort(low, pivot_index - 1)
            sort(pivot_index + 1, high)

    sort(0, len(items) - 1)
    return items


def insertion_sort(values: Sequence[int]) -> List[int]:
    items = list(values)
    for index in range(1, len(items)):
        key = items[index]
        cursor = index - 1
        while cursor >= 0 and items[cursor] > key:
            items[cursor + 1] = items[cursor]
            cursor -= 1
        items[cursor + 1] = key
    return items


def insertion_sort_trace(values: Sequence[int]) -> Tuple[List[int], List[List[int]]]:
    """Return sorted output plus each insertion-pass state for visual explanation."""
    items = list(values)
    trace = [items.copy()]
    for index in range(1, len(items)):
        key = items[index]
        cursor = index - 1
        while cursor >= 0 and items[cursor] > key:
            items[cursor + 1] = items[cursor]
            cursor -= 1
        items[cursor + 1] = key
        trace.append(items.copy())
    return items, trace


COURSEWORK_ARRAY = [2, 3, 5, 8, 6, 8, 9, 5]


if __name__ == "__main__":
    print("Input:     ", COURSEWORK_ARRAY)
    print("Merge:     ", merge_sort(COURSEWORK_ARRAY))
    print("Quick:     ", quick_sort(COURSEWORK_ARRAY))
    print("Insertion: ", insertion_sort(COURSEWORK_ARRAY))

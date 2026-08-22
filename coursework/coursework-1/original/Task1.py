class StringProcessor:
    """Handles basic string addition and subtraction."""

    def process_operations(self, operations):
        """
        Process an array of strings and operations sequentially.

        :param operations: List of strings and operators ["+", "-"].
        :return: Final processed string.
        """
        result = ""  # Initialize the result
        operation = "+"  # Default operation

        for item in operations:
            if item in ["+", "-"]:
                operation = item  # Update the operation
            else:
                if operation == "+":
                    result += item  # Add strings
                elif operation == "-":
                    result = result.replace(item, "")  # Simplify subtraction logic
        
        return result


# Fewer Test Cases for Task 1
def test_task1():
    processor = StringProcessor()
    test_cases = [
        (["x", "+", "yz"], "xyz"),
        (["32", "+", "+5"], "32+5"),
    ]

    print("Task 1: Simplified String Processor Results")
    for i, (input_data, expected) in enumerate(test_cases, 1):
        output = processor.process_operations(input_data)
        print(f"Test Case {i}: Input={input_data} | Output={output} | Expected={expected} | Pass={output == expected}")


# Run Task 1 tests
test_task1()

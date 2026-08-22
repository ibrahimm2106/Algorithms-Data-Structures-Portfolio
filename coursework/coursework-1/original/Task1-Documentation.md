# Task 1 Documentation — Original Coursework Note

This page preserves the substance of the short documentation submitted alongside the original String Processor prototype.

## Original explanation

The program processes a sequence containing strings together with addition and subtraction operations. Processing begins from the left side of the sequence and continues until all operations have been applied.

- **Addition** combines/concatenates strings.
- **Subtraction** removes content from the working string.
- After each operation, the intermediate result becomes the input to the next operation.
- The final string is produced after the complete sequence has been processed.

The original Word document also included a screenshot of the program output as evidence that the prototype ran.

## Portfolio follow-up

The original prototype is preserved in [`Task1.py`](Task1.py). The later portfolio implementation in [`../../../python/string_processor.py`](../../../python/string_processor.py) completes the four coursework test cases and implements the task explicitly with a queue so the left-to-right processing model is represented directly in code.

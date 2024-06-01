#  Selection Sort
#  Using a Loop we iterate through every element
#  and swap its position with the smallest one on the right side (using a nested loop). (if there is such)

numbers = [5, 2, 1, 7, 9, 12]

# My implementation
for index in range(len(numbers)):
    current_smallest_element = None
    current_smallest_index = None

    for i in range(index + 1, len(numbers)):
        if current_smallest_element is None or numbers[i] < current_smallest_element:
            current_smallest_element = numbers[i]
            current_smallest_index = i

    if current_smallest_element is not None and current_smallest_element < numbers[index]:
        numbers[index], numbers[current_smallest_index] = current_smallest_element, numbers[index]

print(numbers)

# Predefined implementation
for index in range(len(numbers)):
    current_smallest_index = index

    for i in range(index + 1, len(numbers)):
        if numbers[i] < numbers[current_smallest_index]:
            current_smallest_index = i

    if current_smallest_index != index:
        numbers[index], numbers[current_smallest_index] = numbers[current_smallest_index], numbers[index]

print(numbers)

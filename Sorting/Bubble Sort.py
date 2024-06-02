# Insertion Sort

# Starting from the second element, we compare the current value with the previous elements
# This way the sublist on the left side is always sorted.
# Using a nested loop, we start from the last element of the sublist and compare it with the current value
# If the inspected value is greater than the current value, we move it to the right
# else we put the current value in the next inspected value's index
# If we reach the first element of the sublist, we put the current value in the first index

def insertion_sort(lst):
    for i in range(1, len(lst)):
        current_value = lst[i]
        lst[i] = None
        
        # print(f'Ordered list on the left side: {lst[:i]}.'
        #       f'\nCurrent value: {current_value}.'
        #       f'\nCurrent list: {lst}.'
        #       f'\n---')

        for index in range(i - 1, -1, -1):
            inspected_value = lst[index]
            if inspected_value > current_value:
                lst[index + 1], lst[index] = lst[index], None
                # If the inspected element is greater, we shift it to the right
                # With setting the current index to None we remove it's redundant value
            else:
                lst[index + 1] = current_value
                # If the inspected value is less, then we put the current value in the next inspected value's index
                break
        else:
            lst[lst.index(None)] = current_value

    return lst


lst = [5, 3, 1, 2, 4]

sorted_list = insertion_sort(lst)

print(sorted_list)

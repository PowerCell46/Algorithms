# Bubble Sort

# Starting from the first element, we compare every two values and move the bigger one to the right.
# When we reach the end, we know the last element is the biggest one, so on the next iteration, we start again from the
# first, but this time we do one less comparing in the end.

def bubble_sort(lst):
    list_length = len(lst)

    while list_length > 0:

        for index in range(1, list_length):
            previous_value = lst[index - 1]
            current_value = lst[index]
            if previous_value > current_value:
                lst[index - 1], lst[index] = lst[index], lst[index - 1]
        else:
            list_length -= 1

    return lst


lst = [5, 3, 8, 6, 7, 2]

sorted_lst = bubble_sort(lst)

print(sorted_lst)

data = [9, 5, 7, 4, 2, 8, 1, 10, 6, 3]


def merge_sort(lst):
    if len(lst) < 2:
        return lst

    left_side = lst[:(len(lst) // 2)]
    right_side = lst[(len(lst) // 2):]

    left_side = merge_sort(left_side)
    right_side = merge_sort(right_side)

    print(f'Left side: {left_side}')
    print(f'Right Side: {right_side}')

    merged = merge(left_side, right_side)
    print(f'Merged: {merged}')

    return merged


def merge(left_side, right_side):
    # When the left side or the right is empty, it means that this is an individual item and is already sorted

    if not len(left_side):
        return right_side
    if not len(right_side):
        return left_side

    result = []
    left_index = 0
    right_index = 0
    total_len = len(left_side) + len(right_side)

    while len(result) < total_len:
        if left_side[left_index] < right_side[right_index]:
            result.append(left_side[left_index])
            left_index += 1
        else:
            result.append(right_side[right_index])
            right_index += 1

        if left_index == len(left_side):
            result.extend(right_side[right_index:])
            break
        elif right_index == len(right_side):
            result.extend(left_side[left_index:])
            break

    return result

sorted_data = merge_sort(data)

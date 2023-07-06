'''
TASK 1. Summ
'''

import sys

start, end, min_length, current_sum, result = 0, 0, 10**12, 0, None
n, target_sum = map(int, input().split())
array = list(map(int, input().split()))

if sum(array) < target_sum:
    print("No summ")
    sys.exit()

while end < n:
    current_sum += array[end]
    while current_sum >= target_sum:
        if end - start + 1 < min_length or (end - start + 1 == min_length and current_sum > result[1]):
            length = end - start
            min_length = length + 1
            result = (min_length, current_sum, start, end)
        current_sum -= array[start]
        start += 1
    end += 1

print(f"Length = {result[0]}")
print(f"Sum = {result[1]}")
print(f"Start = {result[2]}")
print(f"Finish = {result[3]}")

'''
TASK 2. 3 arrays
'''

n1, array1 = int(input()), list(map(int,input().split()))
n2, array2 = int(input()), list(map(int,input().split()))
n3, array3 = int(input()), list(map(int,input().split()))

i1, i2, i3 = 0, 0, 0
min_diff, result = 10**12, [0,0,0] 

while i1 < len(array1) and i2 < len(array2) and i3 < len(array3):
    max_val, min_val = max(array1[i1], array2[i2], array3[i3]), min(array1[i1], array2[i2], array3[i3])
    if max_val - min_val < min_diff: 
        result, min_diff = [array1[i1], array2[i2], array3[i3]], max_val - min_val
    if min_val == array2[i2]: 
        i2 += 1
    elif min_val == array1[i1]: 
        i1 += 1
    else: 
        i3 += 1

print('Numbers =', *result)
print('Result =', min_diff)

'''
TASK 1. Insertion Sort
'''

num_elements = int(input())
elements = [int(x) for x in input().split()]

print("Initial array:")
print(*elements)

for i in range(1, num_elements):
    for j in range(i, 0, -1):
        if elements[j] < elements[j-1]:
            elements[j], elements[j-1] = elements[j-1], elements[j]
        else:
            break
    print(f"Insertion - Element #{i}")
    print(*elements, '')


'''
TASK 2. Bucket sort
'''

num_elements = int(input())
elements = [float(x) for x in input().split()]
formatted_elements = elements.copy()

for i in range(len(formatted_elements)):
    formatted_elements[i] = format(formatted_elements[i], '.2f')

print("Initial array:")
print(*formatted_elements, '')
print()

min_element, max_element = 10**9, -10**9
for element in elements:
    element = float(element)
    if element < min_element:
        min_element = element
    if element > max_element:
        max_element = element

threshold = (max_element - min_element) / (2 * num_elements)
if threshold == 0:
    threshold = min_element

buckets = []
for _ in range(2 * num_elements):
    buckets.append([])

for j in range(num_elements):
    index = (elements[j] - min_element) // threshold + ((elements[j] - min_element) % threshold > 0)
    if int(index - 1) < 0:
        buckets[0].append(elements[j])
    else:
        if elements[j] % threshold == 0 and elements[j] != max_element:
            buckets[int(index)].append(elements[j])
        elif elements[j] == max_element:
            buckets[-1].append(elements[j])
        else:
            buckets[int(index - 1)].append(elements[j])

for k in range(len(buckets)):
    if len(buckets[k]) != 0:
        print('Bucket:')
        formatted_bucket = buckets[k].copy()
        
        for i in range(len(formatted_bucket)):
            formatted_bucket[i] = format(formatted_bucket[i], '.2f')
        
        print(*formatted_bucket, '')
        
        num_bucket_elements = len(buckets[k])
        for i in range(num_bucket_elements - 1):
            flag = 0
            for j in range(num_bucket_elements - i - 1):
                if buckets[k][j] > buckets[k][j + 1]:
                    buckets[k][j], buckets[k][j + 1] = buckets[k][j + 1], buckets[k][j]
                    flag = 1
            if flag == 0:
                break
        
        print('Sorted bucket:')
        formatted_bucket = buckets[k].copy()
        
        for i in range(len(formatted_bucket)):
            formatted_bucket[i] = format(formatted_bucket[i], '.2f')
        
        print(*formatted_bucket, '')
        print()

print('Final array:')
for bucket in buckets:
    if len(bucket) != 0:
        formatted_bucket = bucket.copy()
        
        for i in range(len(formatted_bucket)):
            formatted_bucket[i] = format(formatted_bucket[i], '.2f')
        
        print(*formatted_bucket, '', end='')

'''
TASK 3. Two-sided insertions
'''

num_elements = int(input())
elements = [int(x) for x in input().split()]

print('Step 0:')
print(*elements)

for i in range(1, int(num_elements // 2)):
    for j in range(i, 0, -1):
        if elements[j] < elements[j - 1]:
            elements[j], elements[j - 1] = elements[j - 1], elements[j]
    for k in range(i, 0, -1):
        if elements[-k] > elements[-k - 1]:
            elements[-k - 1], elements[-k] = elements[-k], elements[-k - 1]
    print(f'Step {i}:')
    print(*elements)

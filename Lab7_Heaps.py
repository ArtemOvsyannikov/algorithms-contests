'''
TASK 1. Building a heap
'''

changes, size, array = [], int(input()), [int(i) for i in input().split()]
for index in range(size // 2, -1, -1):
    while index < size:
        left_child, right_child = 2 * index + 1, 2 * index + 2
        current = index
        if right_child < size:
            if array[right_child] < array[current]: 
                current = right_child
        if left_child < size:
            if array[left_child] < array[current]: 
                current = left_child
        if current != index: 
            pass
        else:
            break
        changes.append([index, current])
        array[index], array[current] = array[current], array[index]
        index = current
print(len(changes))
for change in changes:
    a, b = change[0], change[1]
    print(a, b)

'''
TASK 2. Parallel processing
'''

def read_input():
    input_data = list(map(int, input().split()))
    num_workers, jobs = input_data[0], list(map(int,input().split()))
    heap = [[0, i] for i in range(num_workers)]
    return input_data, num_workers, jobs, heap

input_data, num_workers, jobs, heap = read_input()

def process_jobs():
    for job in jobs:
        heap[0][0], index = heap[0][0] + job, 0
        print(heap[0][1], heap[0][0]-job)
        while True:
            size, min_index, right_child, left_child = len(heap) - 1, index, 2 * index + 2, 2 * index + 1
            if right_child <= size:
                if heap[right_child][0] < heap[min_index][0] or (heap[right_child][0] == heap[min_index][0] 
                                                               and heap[right_child][1] < heap[min_index][1]): min_index = right_child
            if left_child <= size:
                if heap[left_child][0] < heap[min_index][0] or (heap[left_child][0] == heap[min_index][0] 
                                                              and heap[left_child][1] < heap[min_index][1]): min_index = left_child
            if index == min_index: break
            else:
                heap[index], heap[min_index] = heap[min_index], heap[index]
                index = min_index

process_jobs()

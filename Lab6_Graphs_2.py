'''
TASK 1. Binary tree traversal
'''

num_nodes = int(input())
tree = {}
node_index = 0

for _ in range(num_nodes):
    node_data = input().split()
    key, left, right = node_data[0], int(node_data[1]), int(node_data[2])
    tree[node_index] = [key, left, right]
    node_index += 1

def in_order_traversal(tree, index):
    node = tree[index]
    left_child = node[1]
    right_child = node[2]
    if left_child != -1:
        in_order_traversal(tree, left_child)
    print(node[0], end=' ')
    if right_child != -1:
        in_order_traversal(tree, right_child)

def pre_order_traversal(tree, index):
    node = tree[index]
    print(node[0], end=' ')
    left_child = node[1]
    right_child = node[2]
    if left_child != -1:
        pre_order_traversal(tree, left_child)
    if right_child != -1:
        pre_order_traversal(tree, right_child)

def post_order_traversal(tree, index):
    node = tree[index]
    left_child = node[1]
    right_child = node[2]
    if left_child != -1:
        post_order_traversal(tree, left_child)
    if right_child != -1:
        post_order_traversal(tree, right_child)
    print(node[0], end=' ')

def process_tree(tree):
    in_order_traversal(tree, 0)
    print()
    pre_order_traversal(tree, 0)
    print()
    post_order_traversal(tree, 0)
    print()

process_tree(tree)

'''
TASK 2. Binary tree traversal
'''

import sys

num_nodes = int(input())
tree = {}
node_index = 0
sys.setrecursionlimit(15000)

if num_nodes == 0:
    print('CORRECT')
    sys.exit()

for _ in range(num_nodes):
    node_data = input().split()
    key, left, right = int(node_data[0]), int(node_data[1]), int(node_data[2])
    tree[node_index] = [key, left, right]
    node_index += 1

def in_order_traversal(tree, index):
    node = tree[index]
    left_child = node[1]
    right_child = node[2]
    if left_child > 0:
        in_order_traversal(tree, left_child)
    result.append(node[0])
    if right_child > 0:
        in_order_traversal(tree, right_child)

result = []
in_order_traversal(tree, 0)

if result == sorted(result):
    print('CORRECT')
else:
    print('INCORRECT')

'''
TASK 3. Topological orders
'''

from collections import deque

def topological_sort(graph):
    in_degree = [0] * len(graph)
    for i in range(len(graph)):
        for j in graph[i]:
            in_degree[j] += 1
    queue = deque()
    for i in range(len(in_degree)):
        if in_degree[i] == 0:
            queue.append(i)
    result = []
    while queue:
        node = queue.popleft()
        result.append(node)
        for i in graph[node]:
            in_degree[i] -= 1
            if in_degree[i] == 0:
                queue.append(i)
    if len(result) != len(graph):
        return "Impossible"
    return result

def all_topological_sorts(graph):
    def dfs(graph, visited, stack, in_degree):
        flag = False
        for i in range(len(graph)):
            if in_degree[i] == 0 and not visited[i]:
                visited[i] = True
                stack.append(i)
                for j in graph[i]:
                    in_degree[j] -= 1
                dfs(graph, visited, stack, in_degree)
                visited[i] = False
                stack.pop()
                for j in graph[i]:
                    in_degree[j] += 1
                flag = True
        if not flag:
            results.append(stack[:])

    results = []
    visited = [False] * len(graph)
    stack = []
    in_degree = [0] * len(graph)
    for i in range(len(graph)):
        for j in graph[i]:
            in_degree[j] += 1
    dfs(graph, visited, stack, in_degree)
    return results

num_nodes, graph = int(input()), []
for i in range(num_nodes):
    row = list(map(int,input().split()))
    if len(row) == 1:
        graph.append([])
        continue
    graph.append(row[1:])
result = topological_sort(graph)
if result == "Impossible":
    print(result)
else:
    result = all_topological_sorts(graph)
    if not result:
        print("Impossible")
    else:
        print(len(result))
        for i in sorted(result):
            print(' '.join(map(str, i)))
            
'''
TASK 4. Red-black properties
'''

import sys
sys.setrecursionlimit(15000)

def add_children(num_nodes, children):
    if num_children == 1:
        for i in range(1):
            children.append(num_nodes)
    if num_children == 0:
        for i in range(2):
            children.append(num_nodes)
    return children

def check_black_count(black_count, node_index, count):
    global flag
    node = tree[node_index]
    if node['color'] == 1:
        if not node['children']:
            black_count.append(count)
        for i in node['children']:
            if tree[i]['color'] == 0:
                check_black_count(black_count, i, count)
            else:
                flag = False
                return
    else:
        count += 1
        if not node['children']:
            black_count.append(count)
        for i in node['children']:
            check_black_count(black_count, i, count)

num_nodes = int(input())
tree = []
degree = [0] * num_nodes

for i in range(num_nodes):
    row, children = input().split(), []
    if int(row[0]) > 2:
        print("NO")
        sys.exit()
    num_children = int(row[0])
    for j in range(num_children):
        degree[int(row[j+1])] += 1
        children.append(int(row[j+1]))
    children = add_children(num_nodes, children)
    color = int(row[-1])
    tree.append({'black_count': [], 'children': children, 'color': color})

for i in range(num_nodes):
    if degree[i] == 0:
        root = i

tree.append({'black_count': [], 'children': [], 'color': 0})
flag = True

if tree[root]['color'] == 0:
    a = 1
else:
    print("NO")
    sys.exit()

for index in range(num_nodes):
    check_black_count(tree[index]['black_count'], index, 0)
    if flag:
        continue
    print("NO")
    sys.exit()

for index in range(num_nodes):
    for i in range(len(tree[index]['black_count']) - 1):
        if tree[index]['black_count'][i] == tree[index]['black_count'][i + 1]:
            a= 1
        else:
            print("NO")
            sys.exit()

print("YES")

'''
TASK 5. Combining tables
'''

def find_parent(node, parents):
    if node != parents[node]:
        parents[node] = find_parent(parents[node], parents)
    return parents[node]

num_tables, num_queries = map(int, input().split())
parents = [i for i in range(num_tables)]
sizes = list(map(int, input().split()))
max_size = max(sizes)

for _ in range(num_queries):
    src, dst = map(int, input().split())
    src_parent = find_parent(src-1, parents)
    dst_parent = find_parent(dst-1, parents)
    if src_parent != dst_parent:
        parents[dst_parent] = src_parent
        sizes[src_parent] += sizes[dst_parent]
        max_size = max(max_size, sizes[src_parent])
    print(max_size)

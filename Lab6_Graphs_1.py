'''
TASK 1. Horse
'''

def find_path(x, y, step):
    if (((n*n)%2!=0)and((start_x+start_y)%2 !=0)):
        return False
    visited[x][y], result = True, False
    if step != total - 1:
        moves = []
        for dx, dy in knight_moves:
            new_x, new_y = x + dx, y + dy
            if -1 < new_x < n and -1 < new_y < n:
                if not visited[new_x][new_y]:
                    moves.append((new_x, new_y))
        if len(moves) != 0:
            neighbors = [ (new_x, new_y)for new_x, new_y in moves]
            for new_x, new_y in neighbors:
                if find_path(new_x, new_y, step + 1) != False:
                    board[x][y], result = step, True
                    break
    else:
        board[x][y], result = step, True
    visited[x][y] = False
    return result

n = int(input())
start_x, start_y = map(int,input().split())
print("Graph:")
for i in range(n):
    for j in range(n):
        edges = []
        if i-2 >=0 and j-1>=0:
            edges.append(n*(i-2)+j-1)
        if i-2 >=0 and j+1<n:
            edges.append(n*(i-2)+j+1)
        if i-1 >=0 and j-2>=0:
            edges.append(n*(i-1)+j-2)
        if i-1 >=0 and j+2<n:
            edges.append(n*(i-1)+j+2)
        if i+1 <n and j-2>=0:
            edges.append(n*(i+1)+j-2)
        if i+1 <n and j+2<n:
            edges.append(n*(i+1)+j+2)
        if i+2 <n and j-1>=0:
            edges.append(n*(i+2)+j-1)
        if i+2 <n and j+1<n:
            edges.append(n*(i+2)+j+1)
        if len(edges) == 0:
            print(n*i+j, '- None')
            continue
        print(n*i+j, '-', *edges, '')
knight_moves = [(-2, -1), (-2, 1), (-1, -2), (-1, 2), (1, -2), (1, 2),(2, -1), (2, 1)]
total, step = n**2, 0
board, visited = [[-1] * n for _ in range(n)], [[False] * n for _ in range(n)]
print('Hamiltonian path:')
if find_path(start_x, start_y, step) == False:
    print("No way")
else:
    for row in board:
        print(*row, '')

'''
TASK 2. Maze
'''

n,m = map(int,input().split())
maze = []
for i in range(n):
    row = list(input())
    if 'S' in row:
        start_x = i
        start_y = row.index('S')
    if 'F' in row:
        end_x = i
        end_y = row.index('F')
    maze.append(row)
print("Initial labyrinth:")
for i in range(n):
    print(*maze[i],sep = '')
print("Graph:")
for i in range(n):
    for j in range(m):
        if maze[i][j] == '#':
            print(m*i+j, '- None')
            continue
        edges = []
        if i-1 >= 0 :
            if maze[i-1][j] != '#':
                edges.append(m*(i-1)+j)
        if j-1 >= 0 :
            if maze[i][j-1] != '#':
                edges.append(m*i+j-1)
        if j+1 < m :
            if maze[i][j+1] != '#':
                edges.append(m*i+j+1)
        if i+1 < n :
            if maze[i+1][j] != '#':
                edges.append(m*(i+1)+j)
        if len(edges) == 0:
            print(m*i+j, '- None')
            continue
        print(m*i+j, '-', *edges, '')
new_maze = []
for i in range(n):
    b = [1]*(m)
    new_maze.append(b)
for i in range(n):
    for j in range(m):
        if maze[i][j] != '#':
            new_maze[i][j] = 0
visited = []
for i in range(n):
    b = [-1]*(m)
    visited.append(b)
x, y = start_x, start_y
visited[x][y] = 0
step = 0
queue = [[x,y]]
while True:
    step+=1
    count = 0
    a = 0
    aa = len(queue)
    flagg = 0
    for coords in queue:
        x_tmp, y_tmp = coords[0], coords[1]
        if x_tmp == end_x and y_tmp == end_y:
            flagg = 1 
            break
        if x_tmp-1>=0:
          if visited[x_tmp-1][y_tmp] == -1 and new_maze[x_tmp-1][y_tmp] == 0:
              visited[x_tmp-1][y_tmp] = step
              queue.append([x_tmp-1,y_tmp])
              count +=1
        if y_tmp-1>=0:
          if visited[x_tmp][y_tmp-1] == -1 and new_maze[x_tmp][y_tmp-1] == 0:
              visited[x_tmp][y_tmp-1] = step
              queue.append([x_tmp,y_tmp-1])
              count +=1
        if y_tmp+1<m:
          if visited[x_tmp][y_tmp+1] == -1 and new_maze[x_tmp][y_tmp+1] == 0:
              visited[x_tmp][y_tmp+1] = step
              queue.append([x_tmp,y_tmp+1])
              count +=1
        if x_tmp+1<n:
          if visited[x_tmp+1][y_tmp] == -1 and new_maze[x_tmp+1][y_tmp] == 0:
              visited[x_tmp+1][y_tmp] = step
              queue.append([x_tmp+1,y_tmp])
              count +=1
        a+=1
        if a == aa:
            break
    queue = queue[aa:]
    if flagg:
        break
    if count == 0:
        break

print("BFS result is:")
for i in range(n):
    for j in range(m):
        print(visited[i][j], end = ' ')
    print()
    
'''
TASK 3. Cities
'''

import math

n = int(input())
points, array = [], []
for _ in range(n):
    a = input().split()
    points.append(a[0])
    array.append(a)
graph = {}
for point in points:
    graph[point] = {}
for i in range(n):
    for j in range(3, len(array[i])):
        graph[array[i][0]][array[i][j]] = ((int(array[i][1])-int(array[points.index(array[i][j])][1]))**2+(int(array[i][2])-int(array[points.index(array[i][j])][2]))**2)**0.5
s = input().split()
start, end, unvisited, shortest_path, predecessors  = s[0], s[1], points, {}, {}
for vertex in unvisited:
    shortest_path[vertex] = 10000000 
shortest_path[start] = 0
while unvisited:
    current_min = None
    for node in unvisited:
        if current_min == None or shortest_path[node] < shortest_path[current_min]:
            current_min = node
    connected_nodes = []
    for out_node in points:
        if out_node in graph[current_min].keys():
            connected_nodes.append(out_node)
    neighbors = connected_nodes
    for neighbor in neighbors:
        value = shortest_path[current_min] + graph[current_min][neighbor]
        if value < shortest_path[neighbor]:
            shortest_path[neighbor], predecessors[neighbor]  = value, current_min
    unvisited.remove(current_min)
if shortest_path[end] == 10000000:
    print("Path:")
    print("No way")
else:
    vertex, final_path = end, []
    while vertex != start:
        final_path.append(vertex)
        vertex = predecessors[vertex]
    final_path.append(start)
    print(f"Path is not greater than {math.ceil(shortest_path[end])}")
    print("Path:")
    print(" ".join(reversed(final_path)), '')


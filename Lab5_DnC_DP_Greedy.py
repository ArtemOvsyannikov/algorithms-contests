'''
TASK 1. Grades
'''

def find_best_combo(input_list):
    length = len(input_list)
    if length == 1:
        best_combo = input_list[0]
        return [best_combo], 1

    lengths = [1] * length
    predecessors = [-1] * length

    for i in range(length):
        for j in range(i):
            if input_list[j] <= input_list[i] and lengths[j] + 1 >= lengths[i]:
                lengths[i] = lengths[j] + 1
                predecessors[i] = j

    best_length = max(lengths)
    best_combo = []
    current_index = 1

    for i in range(1, length):
        if lengths[i] >= lengths[current_index]:
            current_index = i

    while current_index != -1:
        best_combo.append(input_list[current_index])
        current_index = predecessors[current_index]

    return list(reversed(best_combo)), best_length


kolvo = int(input())
if kolvo == 1:
    vivod = int(input())
    print('Best length = 1')
    print(f'Best combo is:  {vivod}', end='')
else:
    massivcheg = list(map(int, input().split()))
    best_combo, best_length = find_best_combo(massivcheg)
    print(f'Best length = {best_length}')
    print('Best combo is:  ', end='')
    print(*best_combo)


'''
TASK 2. Convex hull
'''

def Ayanami_Rej(kusko, bukovka_ili_flajochek):
    if len(kusko) <= 3:
        return kusko
    maxx, ind, A, B, C = -1,-1, kusko[len(kusko) - 1][1] - kusko[0][1], kusko[0][0] - kusko[len(kusko) - 1][0], kusko[0][1] * (kusko[len(kusko) - 1][0] - kusko[0][0]) - kusko[0][0] * (kusko[len(kusko) - 1][1] - kusko[0][1])
    for indexx in range(1, len(kusko) - 1):
        if ((A * kusko[indexx][0] + B * kusko[indexx][1] + C) / ((A * A + B * B) ** 0.5))*bukovka_ili_flajochek > maxx:
            maxx = ((A * kusko[indexx][0] + B * kusko[indexx][1] + C) / ((A * A + B * B) ** 0.5)) * bukovka_ili_flajochek
            ind = indexx
    kusochek1, kusochek2 = [], []
    kusochek1.append(kusko[0])
    kusochek2.append(kusko[ind])
    A, B, C = kusko[ind][1] - kusko[0][1], kusko[0][0] - kusko[ind][0], kusko[0][1] * (kusko[ind][0] - kusko[0][0]) - kusko[0][0] * (kusko[ind][1] - kusko[0][1])
    for index in range(1, len(kusko) - 1):
        if ((A * kusko[index][0] + B * kusko[index][1] + C) / ((A * A + B * B) ** 0.5)) * bukovka_ili_flajochek > 0: kusochek1.append(kusko[index])
    A,B,C = kusko[len(kusko) - 1][1] - kusko[ind][1], kusko[ind][0] - kusko[len(kusko) - 1][0], kusko[ind][1] * (kusko[len(kusko) - 1][0] - kusko[ind][0]) - kusko[ind][0] * (kusko[len(kusko) - 1][1] - kusko[ind][1])
    for i_chto in range(1, len(kusko) - 1):
        if ((A * kusko[i_chto][0] + B * kusko[i_chto][1] + C) / ((A * A + B * B) ** 0.5)) * bukovka_ili_flajochek > 0: kusochek2.append(kusko[i_chto])
    kusochek1.append(kusko[ind])
    kusochek2.append(kusko[len(kusko) - 1])
    kusochek1 = Ayanami_Rej(kusochek1,bukovka_ili_flajochek)
    kusochek2 = Ayanami_Rej(kusochek2,bukovka_ili_flajochek)
    kusochek1.pop()
    nevkusno_i_tochki = kusochek1+kusochek2
    return nevkusno_i_tochki

tochechki = []
with open('input.txt') as file:
    for line in file:
        tochechki.append(list(map(int, line.split())))
tochechki.sort()
kusok1, kusok2 = [],[]
kusok1.append(tochechki[0])
kusok2.append(tochechki[0])
A, B, C = tochechki[len(tochechki) - 1][1] - tochechki[0][1], tochechki[0][0] - tochechki[len(tochechki) - 1][0], tochechki[0][1] * (tochechki[len(tochechki) - 1][0] - tochechki[0][0]) - tochechki[0][0] * (tochechki[len(tochechki) - 1][1] - tochechki[0][1])
for i in range(1, len(tochechki)):
    if ((A * tochechki[i][0] + B * tochechki[i][1] + C) / ((A * A + B * B) ** 0.5)) < 0: kusok1.append(tochechki[i])
    elif ((A * tochechki[i][0] + B * tochechki[i][1] + C) / ((A * A + B * B) ** 0.5)) > 0: kusok2.append(tochechki[i])
kusok1.append(tochechki[len(tochechki) - 1])
kusok2.append(tochechki[len(tochechki) - 1])
kusok1 = Ayanami_Rej(kusok1, -1)
kusok2 = Ayanami_Rej(kusok2, 1)
del(kusok2[0])
kusok1.pop()
kusok=kusok1+kusok2
kusok.sort()
print('Convex Hull is:')
for i in range(len(kusok)):
    print(kusok[i][0],kusok[i][1])

'''
TASK 3. Editing
'''

start_word = input()
word_count = int(input())
distances, words = [0] * word_count, []

for i in range(word_count):
    word = input()
    words.append(word)
    start_word_len, word_len = len(start_word), len(word)
    distance_matrix = [[j if i == 0 else i if j == 0 else 0 for j in range(word_len + 1)] for i in range(start_word_len + 1)]
    
    for j in range(1, start_word_len + 1):
        for k in range(1, word_len + 1):
            substitution_cost = 0 if start_word[j - 1] == word[k - 1] else 1
            distance_matrix[j][k] = min(distance_matrix[j - 1][k] + 1,
                                        distance_matrix[j][k - 1] + 1,
                                        distance_matrix[j - 1][k - 1] + substitution_cost)
    distances[i] = distance_matrix[start_word_len][word_len]

min_distance = min(distances)
print(f'Most similar words = {distances.count(min_distance)}')
print(f'Minimal operations needed = {min_distance}')
for i in range(word_count):
    if distances[i] == min_distance:
        print(words[i])


'''
TASK 4. Coins
'''

n, m = map(int, input().split())
grid = [0] * n
start_x, start_y = 0, 0
for i in range(n):
    row = input().split()
    if 'S' in row:
        start_x = i
        start_y = row.index('S')
        row[row.index('S')] = 0
    grid[i] = list(map(int, row))

dp = [[0] * m for _ in range(n)]
for i in range(start_x + 1, n):
    dp[i][start_y] = dp[i - 1][start_y] + grid[i][start_y]
for i in range(start_y + 1, m):
    dp[start_x][i] = dp[start_x][i - 1] + grid[start_x][i]
for i in range(start_x + 1, n):
    for j in range(start_y + 1, m):
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + grid[i][j]

path = []
x, y = n - 1, m - 1
path.append([x, y])
while x != start_x and y != start_y:
    if x == start_x or y == start_y:
        break
    if dp[x - 1][y] >= dp[x][y - 1]:
        x -= 1
        path.append([x, y])
    else:
        y -= 1
        path.append([x, y])
if x == start_x and y != start_y:
    while y != start_y:
        y -= 1
        path.append([x, y])
if x != start_x and y == start_y:
    while x != start_x:
        x -= 1
        path.append([x, y])
path.reverse()
print('Path:')
for i in range(len(path)):
    print(f'({path[i][0]},{path[i][1]}) ', end='')
print()
print(f'Coins: {dp[n - 1][m - 1]}')

'''
TASK 5. Salesman
'''

num_vertices = int(input())
graph = [0] * num_vertices
for index in range(num_vertices):
    graph[index] = list(map(int, input().split()))

min_cost = float('inf')
found_path = False
for start_vertex in range(num_vertices):
    path = []
    cost, prev_vertex = 0, start_vertex
    path.append(start_vertex)
    while len(path) <= num_vertices:
        row = graph[path[-1]]
        min_edge_cost = float('inf')
        next_vertex = -1
        for i in range(len(row)):
            if row[i] != 0 and row[i] < min_edge_cost and (i not in path or path[0] == i and len(path) == len(row)):
                min_edge_cost = row[i]
                next_vertex = i
        if next_vertex != -1:
            path.append(next_vertex)
            cost += graph[prev_vertex][next_vertex]
            prev_vertex = next_vertex
        else:
            break
    if path[0] != path[-1]:
        cost = -1
    if cost != -1 and cost < min_cost:
        min_path = path
        min_cost = cost
        found_path = True

if found_path:
    print('Path:')
    print(*min_path, '')
    print(f'Cost: {min_cost}')
else:
    print('Lost')

    

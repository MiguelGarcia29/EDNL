N = 5
INF = 2147483647
size = N * N
matriz = [[INF] * size for _ in range(size)]

for fila in range(N):
    for col in range(N):
        idx = fila * N + col
        # Conectar con la izquierda
        if col > 0:
            matriz[idx][idx - 1] = 1
        # Conectar con la derecha
        if col < N - 1:
            matriz[idx][idx + 1] = 1
        # Conectar con arriba
        if fila > 0:
            matriz[idx][idx - N] = 1
        # Conectar con abajo
        if fila < N - 1:
            matriz[idx][idx + N] = 1

# Guardar en archivo
with open("grafo_5x5.txt", "w") as f:
    f.write(f"{size}\n")
    for fila in matriz:
        f.write(' '.join(map(str, fila)) + '\n')

print("¡Archivo 'grafo_5x5.txt' generado correctamente!")

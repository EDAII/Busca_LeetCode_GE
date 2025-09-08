import bisect

def findRightInterval(intervals: list[list[int]]) -> list[int]:
    """
    Encontra o "right interval" para cada intervalo na lista de entrada.

    A abordagem usa ordenação e busca binária para uma solução eficiente O(n log n).
    """
    n = len(intervals)
    if n == 0:
        return []

    # 1. Criar uma lista de pares [ponto_de_inicio, indice_original]
    starts_with_indices = []
    for i in range(n):
        starts_with_indices.append([intervals[i][0], i])

    # 2. Ordenar a lista com base nos pontos de início
    starts_with_indices.sort(key=lambda x: x[0])

    # Para a busca binária, é útil ter uma lista separada apenas com os starts
    sorted_starts = [item[0] for item in starts_with_indices]

    # 3. Iterar e buscar o "right interval" para cada intervalo
    result = [-1] * n
    for i in range(n):
        end_point = intervals[i][1]

        # 4. Usar busca binária (bisect_left) para encontrar o primeiro start >= end_point
        # bisect_left encontra o ponto de inserção para manter a ordem,
        # que é exatamente o índice do primeiro elemento >= ao alvo.
        insertion_point = bisect.bisect_left(sorted_starts, end_point)

        # 5. Verificar o resultado da busca
        if insertion_point < n:
            # Se o ponto de inserção está dentro dos limites da lista, encontramos um candidato.
            # O índice original está armazenado em starts_with_indices
            original_index = starts_with_indices[insertion_point][1]
            result[i] = original_index
        # else:
        # Se insertion_point == n, significa que todos os starts são menores que end_point.
        # O resultado para este índice já é -1, então não fazemos nada.

    return result

# Exemplo 1:
intervals1 = [[3,4],[2,3],[1,2]]
print(f"Entrada: {intervals1}")
print(f"Saída: {findRightInterval(intervals1)}") # Esperado: [-1, 0, 1]

# Exemplo 2:
intervals2 = [[1,2]]
print(f"Entrada: {intervals2}")
print(f"Saída: {findRightInterval(intervals2)}") # Esperado: [-1]

# Exemplo 3:
intervals3 = [[1,4],[2,3],[3,4]]
print(f"Entrada: {intervals3}")
print(f"Saída: {findRightInterval(intervals3)}") # Esperado: [-1, 2, -1]

import sys
import random

cantidad = int(sys.argv[1])
rango = int(sys.argv[2])

# Genera números aleatorios y los guarda en el archivo
with open("input.txt", "w") as archivo:
    for _ in range(cantidad):
        numero = random.randint(1, rango)  # Cambia los límites según tus necesidades
        archivo.write(str(numero) + "\n")


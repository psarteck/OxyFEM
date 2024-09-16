import numpy as np


def convert_mesh_file(input_file, output_file):
    with open(input_file, 'r') as f:
        lines = f.readlines()

    # Première ligne : Nombre de points
    num_points = int(lines[0].strip())

    # Extraire les coordonnées des points
    points = []
    for i in range(1, num_points + 1):
        x, y = map(float, lines[i].strip().split())
        # Ajouter une valeur de référence (par exemple, 0 ou un autre nombre si nécessaire)
        ref = 4 if y == 0 else (1 if x == 0 or x == 1 else 0)
        points.append(f"{x} {y} {ref}")

    # Nombre d'éléments (ligne après les coordonnées des points)
    num_elements_line = lines[num_points + 1].strip().split()
    num_elements = int(num_elements_line[0])

    # Extraction des éléments
    elements = []
    for i in range(num_points + 2, num_points + 2 + num_elements):
        element_data = list(map(int, lines[i].strip().split()))
        elements.append(f"{element_data[0]} {element_data[1]} {element_data[2]} 0")

    # Extraction des facettes et des références
    facets = []
    for i in range(num_points + 2 + num_elements, len(lines)):
        facet_data = list(map(int, lines[i].strip().split()))
        facets.append(f"{facet_data[0]} {facet_data[1]} {facet_data[4]}")

    # Construire la sortie finale
    result = [f"{num_points} {num_elements} {len(facets)}"] + points + elements + facets

    # Écrire dans le fichier de sortie
    with open(output_file, 'w') as f:
        f.write("\n".join(result) + "\n")

# Exemple d'utilisation
input_file = 'input_mesh.txt'
output_file = 'output_mesh.txt'

convert_mesh_file(input_file, output_file)

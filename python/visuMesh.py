import matplotlib.pyplot as plt
import matplotlib.tri as tri
import argparse


class Maillage:
    def __init__(self, filepath):
        self.nv = 0  # Nombre de sommets
        self.nt = 0  # Nombre de triangles
        self.ne = 0  # Nombre de segments sur la frontière
        self.sommets = []  # Coordonnées des sommets et labels de frontières
        self.triangles = []  # Définition des triangles avec région
        self.edges = []  # Définition des segments sur la frontière

        # Lecture du fichier .msh
        self.lire_fichier(filepath)

    def lire_fichier(self, filepath):
        with open(filepath, 'r') as f:
            # Lire la première ligne contenant nv, nt, ne
            line = f.readline().strip()
            self.nv, self.nt, self.ne = map(int, line.split())
            
            # Lire les coordonnées des sommets
            for _ in range(self.nv):
                line = f.readline().strip()
                q_x, q_y, boundary_label = line.split()
                self.sommets.append((float(q_x), float(q_y), int(boundary_label)))

            # Lire les triangles
            for _ in range(self.nt):
                line = f.readline().strip()
                sommet1, sommet2, sommet3, region_label = map(int, line.split())
                self.triangles.append((sommet1-1, sommet2-1, sommet3-1, region_label))  # Indexation à partir de 0

            # Lire les segments sur la frontière (edges)
            for _ in range(self.ne):
                line = f.readline().strip()
                sommet1, sommet2, boundary_label = map(int, line.split())
                self.edges.append((sommet1-1, sommet2-1, boundary_label))  # Indexation à partir de 0

    def afficher(self):
        print(f"Nombre de sommets (nv): {self.nv}")
        print(f"Nombre de triangles (nt): {self.nt}")
        print(f"Nombre de segments sur la frontière (ne): {self.ne}\n")

        print("Sommets (x, y, boundary_label):")
        for sommet in self.sommets:
            print(sommet)

        print("\nTriangles (sommet1, sommet2, sommet3, region_label):")
        for triangle in self.triangles:
            print(triangle)

        print("\nSegments sur la frontière (sommet1, sommet2, boundary_label):")
        for edge in self.edges:
            print(edge)

    def afficher_maillage_2d(self):
        # Extraire les coordonnées x et y des sommets
        x = [coord[0] for coord in self.sommets]
        y = [coord[1] for coord in self.sommets]

        # Extraire les triangles
        triangles = [(triangle[0], triangle[1], triangle[2]) for triangle in self.triangles]

        # Créer la figure
        fig, ax = plt.subplots()
        ax.set_aspect('equal')

        # Tracer le maillage avec les triangles
        triangulation = tri.Triangulation(x, y, triangles)
        ax.triplot(triangulation, 'bo-', lw=1, markersize=4)  # Tracer les triangles

        # Tracer les segments sur la frontière
        for edge in self.edges:
            p1 = edge[0]
            p2 = edge[1]
            ax.plot([x[p1], x[p2]], [y[p1], y[p2]], 'r-', lw=2)  # Segments en rouge

        # Tracer les sommets
        for i, (x_i, y_i, label) in enumerate(self.sommets):
            ax.text(x_i, y_i, f'{i+1}', color='black', fontsize=10, ha='right')  # Numérotation des sommets

        # Configurations finales
        ax.set_xlabel('x')
        ax.set_ylabel('y')
        ax.set_title('Visualisation du maillage 2D')
        plt.grid(True)
        plt.show()


# Exemple d'utilisation
if __name__ == "__main__":

    # Initialiser argparse pour récupérer le nom du fichier en paramètre
    parser = argparse.ArgumentParser(description='Afficher un maillage en 2D à partir d\'un fichier .msh')
    
    # Ajouter un argument optionnel pour le chemin du fichier avec une valeur par défaut
    parser.add_argument('filepath', type=str, nargs='?', default='square3x3.msh',
                        help='Path to the .msh file')

    # Lire les arguments
    args = parser.parse_args()

    repertory = "/Users/djo/Desktop/MEF/C++/Meshs/"

    # Remplacez 'votre_fichier.msh' par le chemin vers votre fichier .msh
    maillage = Maillage(repertory + args.filepath)
    maillage.afficher()
    maillage.afficher_maillage_2d()

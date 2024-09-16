#!/bin/bash

# Vérification de la présence d'un argument
if [ $# -ne 2 ]; then
    echo "Usage: $0 <dossier> <fichier_chaine>"
    exit 1
fi

# Récupération des arguments
dossier="$1"
fichier_chaine="$2"

# Vérification si le dossier existe
if [ ! -d "$dossier" ]; then
    echo "Le dossier spécifié n'existe pas."
    exit 1
fi

# Vérification si le fichier de chaîne existe
if [ ! -f "$fichier_chaine" ]; then
    echo "Le fichier de chaîne spécifié n'existe pas."
    exit 1
fi

# Lecture de la chaîne depuis le fichier
chaine=$(cat "$fichier_chaine")

# Parcours des fichiers .h dans le dossier spécifié
for fichier in "$dossier"/*.cpp; do
    if [ -f "$fichier" ]; then
        # Création d'un fichier temporaire pour stocker le contenu original du fichier .h
        fichier_temp=$(mktemp)
        cat "$fichier" > "$fichier_temp"
        
        # Écriture de la chaîne suivie du contenu original dans le fichier .h
        echo "$chaine" | cat - "$fichier_temp" > "$fichier"
        rm "$fichier_temp"
        
        echo "La chaîne a été écrite au début de '$fichier'."
    fi
done

/*---------------------------------------------------------------------------*\

 ██████╗ ██╗  ██╗██╗   ██╗     ███████╗███╗   ███╗
██╔═══██╗╚██╗██╔╝╚██╗ ██╔╝     ██╔════╝████╗ ████║
██║   ██║ ╚███╔╝  ╚████╔╝█████╗█████╗  ██╔████╔██║
██║   ██║ ██╔██╗   ╚██╔╝ ╚════╝██╔══╝  ██║╚██╔╝██║
╚██████╔╝██╔╝ ██╗   ██║        ██║     ██║ ╚═╝ ██║
 ╚═════╝ ╚═╝  ╚═╝   ╚═╝        ╚═╝     ╚═╝     ╚═╝
 * 
 * Copyright (C) 2024 by Matthieu PETIT
\*---------------------------------------------------------------------------*/
#include <iostream>
#include <iomanip> // Pour gérer la mise en forme des sorties
#include <limits>  // Pour gérer les erreurs lors de la lecture
#include <cmath>

#include "FEMAssembly.hpp"


namespace FEMAssembly {

    void AFFSMD(int nblign, 
                const std::vector<int>& adprcl, 
                const std::vector<int>& numcol, 
                const std::vector<int>& adsucl, 
                const std::vector<float>& matris, 
                const std::vector<float>& secmbr, 
                const std::vector<int>& nuddir, 
                const std::vector<float>& valdir) {

        int Lmin, Lmax;

        std::cout << "****** Affichage de la S.M.D. ******" << std::endl;

        while (true) {
            std::cout << "Donner, dans l'intervalle [1, " << nblign << "], les indices min et max des lignes a afficher. Taper q pour arreter." << std::endl;

            // Lecture des indices, on vérifie les erreurs de saisie
            if (!(std::cin >> Lmin >> Lmax)) {
                std::cin.clear(); // Effacer l'état d'erreur
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignorer la ligne incorrecte
                break; // Sortir de la boucle si on tape 'q' ou un caractère non numérique
            }

            // Ajuster pour correspondre à l'indexation C++
            Lmin -= 1;
            Lmax -= 1;

            if (Lmin > Lmax || Lmin < 0 || Lmax >= nblign) {
                std::cout << "Indices invalides. Réessayez." << std::endl;
                continue;
            }

            // Affichage de l'en-tête
            std::cout << "\n   Ligne    SecMbr   Nuddir   Valdir" << std::endl;

            // Affichage des informations de chaque ligne
            for (int i = Lmin; i <= Lmax; i++) {
                std::cout << std::setw(7) << (i+1) << "  " 
                        << std::setw(10) << std::scientific << secmbr[i] << "  " 
                        << std::setw(7) << nuddir[i] << "  " 
                        << std::setw(10) << std::scientific << valdir[i] << std::endl;
            }

            // Affichage de la matrice
            std::cout << "=== MATRICE ===========================" << std::endl;

            if (Lmin == 0) {
                std::cout << "--- Ligne 1 ---" << std::endl;
                std::cout << "Col  1 : " << std::setw(14) << std::fixed << matris[0] << std::endl;
                Lmin = 1;
            }

            for (int i = Lmin; i <= Lmax; i++) {
                std::cout << "--- Ligne " << (i+1) << " ---" << std::endl;
                int j = adprcl[i];

                while (j != 0) {
                    std::cout << "Col " << std::setw(3) << numcol[j] << " : " 
                            << std::setw(14) << std::fixed << matris[nblign + j] << std::endl;
                    j = adsucl[j];
                }

                // Affichage de l'élément diagonal
                std::cout << "Col " << std::setw(3) << (i+1) << " : " 
                        << std::setw(14) << std::fixed << matris[i] << std::endl;
            }
        }
    }


    void AFFSMO(int nblign, 
                const std::vector<int>& adprc0, 
                const std::vector<int>& numco0, 
                const std::vector<float>& matri0, 
                const std::vector<float>& secmb0) {

        int kdeb, kfin, iad, iadnxt, j, k;

        std::cout << "NOMBRE DE LIGNES : " << nblign << std::endl;

        while (true) {
            std::cout << "NUMEROS DE LA PREMIERE ET DE LA DERNIERE LIGNE ?\nTAPER Q POUR TERMINER." << std::endl;

            // Lecture des indices kdeb et kfin avec gestion d'erreur (pour quitter avec 'q')
            if (!(std::cin >> kdeb >> kfin)) {
                std::cin.clear(); // Effacer l'état d'erreur
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignorer la ligne incorrecte
                break; // Sortir de la boucle si on tape 'q'
            }

            // Ajuster pour correspondre à l'indexation C++
            kdeb -= 1;
            kfin -= 1;

            // Vérification des indices
            if (kdeb < 0 || kfin < kdeb || kfin >= nblign) {
                std::cout << "Indices invalides. Réessayez." << std::endl;
                continue;
            }

            // Affichage du header
            std::cout << "\n   LIGNE     SECMB0               MATRI0(coefficients + colonnes)" << std::endl;

            iad = 0; // Initialiser IAD à 0 (correspond à l'indice C++)

            // Si kdeb > 0, ajuster l'indice de départ IAD
            if (kdeb > 0) {
                iad = adprc0[kdeb - 1];
            }

            for (k = kdeb; k <= kfin; k++) {
                iadnxt = adprc0[k];

                // Affichage de la ligne k, le second membre et les coefficients non nuls
                std::cout << std::setw(5) << (k+1) << "  "  // Affichage de l'indice de ligne
                        << std::scientific << std::setw(14) << secmb0[k] << " ";

                // Afficher les coefficients de MATRI0
                for (j = iad; j < iadnxt; j++) {
                    std::cout << std::setw(14) << matri0[j + nblign];
                }
                // Afficher le coefficient diagonal
                std::cout << std::setw(14) << matri0[k] << std::endl;

                // Affichage des numéros de colonnes correspondants
                std::cout << std::setw(20);
                for (j = iad; j < iadnxt; j++) {
                    std::cout << std::setw(12) << numco0[j];
                }
                std::cout << std::setw(12) << (k+1) << std::endl;  // Numéro de colonne pour le coefficient diagonal

                // Mise à jour de l'indice IAD pour la prochaine ligne
                iad = iadnxt;
            }
        }
    }


    void ASSMAT(int i, int j, float x, 
            std::vector<int>& adprcl, 
            std::vector<int>& numcol, 
            std::vector<int>& adsucl, 
            std::vector<float>& lmatri, 
            int& nextad) {
    
        // Vérification si i <= j, ce qui signifie que nous sommes hors de la partie triangulaire inférieure stricte
        if (i <= j) {
            std::cerr << "*Bug* La procédure ASSMAT n'est utilisée que pour l'assemblage de la partie triangulaire stricte. "
                    << "Vous êtes sur le coefficient (" << i << ", " << j << ")." << std::endl;
            std::exit(EXIT_FAILURE); // Stoppe le programme
        }

        // Ajustement des indices pour C++ (indexation de 0)
        i -= 1;
        j -= 1;

        // IAD est l'adresse du premier coefficient de la ligne i
        int iad = adprcl[i];

        if (iad > 0) {
            // La ligne i a déjà été rencontrée : recherche de la colonne j
            while (numcol[iad] != j) {
                int nxt = adsucl[iad];
                if (nxt <= 0) {
                    // Si on atteint la fin de la ligne sans trouver j, on sort pour créer une nouvelle colonne
                    break;
                }
                iad = nxt;
            }

            if (numcol[iad] == j) {
                // L'élément A(i,j) existe déjà : on l'incrémente
                lmatri[iad] += x;
                return; // Sortir de la fonction
            }

            // Création d'une nouvelle colonne j dans la ligne i
            adsucl[iad] = nextad;
        } else {
            // La ligne i n'a pas encore été rencontrée : création de la ligne i
            adprcl[i] = nextad;
        }

        // Création du coefficient A(i,j) (nouvelle ligne ou nouvelle colonne)
        numcol[nextad] = j;
        lmatri[nextad] = x;
        adsucl[nextad] = 0; // Marque la fin de la ligne

        // Mise à jour de la prochaine adresse libre
        nextad++;
    }


    // Prototype de la fonction de tri qui sera utilisée pour trier les colonnes
    void TRI(int size, std::vector<int>::iterator numco, std::vector<float>::iterator matri) {
        // Tri simultané des colonnes et des coefficients
        for (int i = 0; i < size - 1; i++) {
            for (int j = i + 1; j < size; j++) {
                if (*(numco + i) > *(numco + j)) {
                    std::swap(*(numco + i), *(numco + j));
                    std::swap(*(matri + i), *(matri + j));
                }
            }
        }
    }



    void CDESSE(int nblign, 
            std::vector<int>& adprcl, 
            std::vector<int>& numcol, 
            std::vector<int>& adsucl, 
            std::vector<float>& matris, 
            std::vector<float>& secmbr, 
            std::vector<int>& nuddir, 
            std::vector<float>& valdir, 
            std::vector<int>& adprc0, 
            std::vector<int>& numco0, 
            std::vector<float>& matri0, 
            std::vector<float>& secmb0) {

        int admatr, admat0, admat1, admatx;

        // Copier les valeurs de secmbr et matris dans secmb0 et matri0
        for (int i = 0; i < nblign; i++) {
            secmb0[i] = secmbr[i];
            matri0[i] = matris[i];
        }

        // Traitement du premier nœud Dirichlet
        if (nuddir[0] < 0) {
            secmb0[0] = matri0[0] * valdir[0];
        } else if (nuddir[0] <= 0) {
            secmb0[0] = 0.0f;
        }

        // Initialisation des adresses
        admat0 = 1; // Correspond à la première adresse dans A0
        admatx = adprcl[0]; // Première adresse dans la partie triangulaire inférieure de A

        // Boucle sur les lignes à partir de la seconde
        for (int i = 1; i < nblign; i++) {
            admatr = admatx;
            admatx = adprcl[i];
            adprc0[i - 1] = admat0;

            if (nuddir[i] <= 0) {
                // Cas des lignes Dirichlet
                secmb0[i] = 0.0f;
                if (nuddir[i] < 0) {
                    secmb0[i] = matris[i] * valdir[i];
                }

                // Parcours des éléments de la ligne
                while (admatr != 0) {
                    int j = numcol[admatr];
                    if (nuddir[j] > 0) {
                        secmb0[j] -= matris[nblign + admatr] * valdir[i];
                    }
                    admatr = adsucl[admatr];
                }

            } else {
                // Cas des lignes non Dirichlet
                admat1 = admat0;

                // Parcours des éléments de la ligne
                while (admatr != 0) {
                    int j = numcol[admatr];
                    if (nuddir[j] < 0) {
                        // Cas Dirichlet non homogène : mise à jour du second membre
                        secmb0[i] -= matris[nblign + admatr] * valdir[j];
                    } else if (nuddir[j] > 0) {
                        // Conserver le coefficient
                        matri0[nblign + admat0] = matris[nblign + admatr];
                        numco0[admat0] = j;
                        admat0++;
                    }
                    admatr = adsucl[admatr];
                }

                // Tri des colonnes de la ligne par ordre croissant
                if (admat0 > admat1) {
                    TRI(admat0 - admat1, numco0.begin() + admat1, matri0.begin() + nblign + admat1);
                }
            }
        }

        adprc0[nblign - 1] = admat0;
    }


    void ltlpr(int rang, 
           const std::vector<int>& profil, 
           std::vector<float>& ad, 
           std::vector<float>& al, 
           float eps, 
           std::vector<float>& ld, 
           std::vector<float>& ll) {

        int iad, iadnxt, ligne, nbcoef, col, llad;
        float rcoef;

        // Vérification de la première valeur de la diagonale
        if (ad[0] < eps) {
            std::cout << "LA MATRICE A N'EST PAS INVERSIBLE." << std::endl;
            return;
        }

        // Calcul du premier élément de la diagonale de L
        ld[0] = std::sqrt(ad[0]);

        iadnxt = 1; // Position initiale dans le profil

        // Boucle sur les lignes de la matrice à partir de la deuxième ligne
        for (ligne = 1; ligne < rang; ligne++) {
            iad = iadnxt;
            iadnxt = profil[ligne];
            nbcoef = iadnxt - iad;

            // Résolution du sous-système si la ligne contient des éléments dans le profil inférieur
            if (nbcoef > 0) {
                col = ligne - nbcoef;
                // RSPRL(nbcoef, profil[col], ld[col], ll, al, std::vector<float>(ll.begin() + iad, ll.begin() + iadnxt));
            }

            // Calcul du coefficient rcoef à partir de la diagonale et des valeurs du profil
            rcoef = ad[ligne];
            for (llad = iad; llad < iadnxt; llad++) {
                rcoef -= ll[llad] * ll[llad];
            }

            // Vérification si la matrice est non inversible
            if (rcoef < eps) {
                std::cout << "LA MATRICE A N'EST PAS INVERSIBLE." << std::endl;
                return;
            }

            // Calcul de la diagonale de L pour cette ligne
            ld[ligne] = std::sqrt(rcoef);
        }
    }



    void rsprl(int rang, 
           const std::vector<int>& profil, 
           const std::vector<float>& d, 
           const std::vector<float>& l, 
           const std::vector<float>& b, 
           std::vector<float>& x) {

        float epsil = 1e-10;
        int iad, iadnxt, ligne, nbcoef, col, lad;
        float rcoef;

        // Vérification du premier élément de la diagonale
        if (std::abs(d[0]) < epsil) {
            std::cout << "LA MATRICE L N'EST PAS INVERSIBLE." << std::endl;
            return;
        }

        // Calcul de la première solution
        x[0] = b[0] / d[0];

        iad = profil[0]; // Position dans le profil pour la première ligne

        // Boucle sur les lignes restantes
        for (ligne = 1; ligne < rang; ligne++) {
            iadnxt = profil[ligne]; // Position dans le profil pour la ligne actuelle
            nbcoef = iadnxt - iad;  // Nombre de coefficients dans le profil inférieur strict

            // Test servant à limiter le nombre de coefficients
            if (nbcoef >= ligne) {
                nbcoef = ligne - 1;
            }

            col = ligne - nbcoef;  // Première colonne associée

            rcoef = 0.0f;

            // Boucle sur les éléments du profil inférieur strict
            for (lad = iadnxt - nbcoef; lad < iadnxt; lad++) {
                rcoef += l[lad] * x[col];
                col++;
            }

            // Vérification de la diagonale pour éviter la division par zéro
            if (std::abs(d[ligne]) < epsil) {
                std::cout << "LA MATRICE L N'EST PAS INVERSIBLE." << std::endl;
                return;
            }

            // Calcul de la solution pour la ligne actuelle
            x[ligne] = (b[ligne] - rcoef) / d[ligne];

            iad = iadnxt;  // Mise à jour de la position dans le profil
        }
    }


    
}
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
#include <algorithm>

#include "FEMAssembly.hpp"


namespace FEMAssembly {
    using namespace std;
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

    void cdesse(const int NBLIGN, const std::vector<int>& ADPRCL, 
                      const std::vector<int>& NUMCOL,
                      const std::vector<int>& ADSUCL, const std::vector<double>& MATRIS, 
                      const std::vector<double>& SECMBR,
                      const std::vector<int>& NUDDIR, const std::vector<double>& VALDIR,
                      std::vector<int>& ADPRC0, std::vector<int>& NUMCO0, 
                      std::vector<double>& MATRI0, std::vector<double>& SECMB0) {

        int admatr, admat0, admat1, admatx;

        // Loop to copy elements from SECMBR and MATRIS to SECMB0 and MATRI0
        for (int i = 0; i < NBLIGN; ++i) {  
            SECMB0[i] = SECMBR[i];
            MATRI0[i] = MATRIS[i];
        }

        // Processing the first row
        if (NUDDIR[0] < 0) {
            SECMB0[0] = MATRI0[0] * VALDIR[0];
        } else if (NUDDIR[0] <= 0) {
            SECMB0[0] = 0.0;
        }

        // Initializing addresses for the lower triangular part
        admat0 = 1;
        admatx = ADPRCL[0];

        // Main loop starting from the 2nd row
        for (int i = 1; i < NBLIGN ; ++i) {

            admatr = admatx;  // Address of the first coefficient of row i-1
            admatx = ADPRCL[i];  // Address of the first coefficient of row i
            ADPRC0[i - 1] = admat0;  // Updating ADPRC0 for the previous row
            if (NUDDIR[i] <= 0) {
                // Dirichlet case
                SECMB0[i] = 0.0;
                if (NUDDIR[i] < 0) {
                    // cout << "i " << i << endl;
            // cout << "NUDDIR[i] " << NUDDIR[i] << endl;
                    SECMB0[i] = MATRIS[i] * VALDIR[i];
                    // cout << "SECMB0[i] " << SECMB0[i] << endl;
                }

                while (admatr != 0) {
                    int j = NUMCOL[admatr - 1];  // Column number

                    if (NUDDIR[j - 1] > 0) {
                        SECMB0[j - 1] -= MATRIS[NBLIGN + admatr - 1] * VALDIR[i];
                    }
                    admatr = ADSUCL[admatr - 1];  // Address of the next coefficient
                }
            } else {
                // Non-Dirichlet case
                admat1 = admat0 - 1;

                while (admatr != 0) {
                    int j = NUMCOL[admatr - 1];

                    if (NUDDIR[j - 1] < 0) {
                        // Case of a non-homogeneous Dirichlet column
                        SECMB0[i] -= MATRIS[NBLIGN + admatr - 1] * VALDIR[j - 1];
                    } else if (NUDDIR[j - 1] > 0) {
                        // Non-Dirichlet column case: coefficient is kept
                        MATRI0[NBLIGN + admat0 - 1] = MATRIS[NBLIGN + admatr - 1];
                        NUMCO0[admat0 - 1] = j;
                        admat0 += 1;
                    }

                    admatr = ADSUCL[admatr - 1];  // Address of the next coefficient
                }

                // Sorting columns of the row in ascending order
                if (admat0 > admat1) {
                    // Calling the `tri` function to sort NTAB (NUMCO0) and RTAB (MATRI0)
                    tri(admat0 - 1 - admat1, NUMCO0.begin() + admat1, MATRI0.begin() + (NBLIGN + admat1));

                    // tri(admat0 - 1 - admat1, NUMCO0 + admat1, MATRI0 + (*NBLIGN + admat1));

                }
            }
        }

        // Final update of ADPRC0 for the last row
        ADPRC0[NBLIGN - 1] = admat0;
    }

    void tri(int N, std::vector<int>::iterator NTAB, std::vector<double>::iterator RTAB) {
        bool permut;
        int aux1;
        double aux2;

        int i = 0;  
        do {
            permut = false;
            i++;

            // Loop to compare and swap elements in NTAB and RTAB
            for (int j = N - 1; j >= i; --j) {
                if ( *(NTAB + j) < *(NTAB + j - 1) ) {
                    // Swap in NTAB
                    aux1 = *(NTAB + j - 1);
                    *(NTAB + j - 1) = *(NTAB + j);
                    NTAB[j] = aux1;

                    // Swap in RTAB
                    aux2 = *(RTAB + j - 1);
                    *(RTAB + j - 1) = *(RTAB + j);
                    *(RTAB + j) = aux2;

                    permut = true;
                }
            }
        } while (permut);  // Repeat until no more swaps
    }


    
}
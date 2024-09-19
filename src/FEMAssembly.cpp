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

    void ltlpr(int rang, VectorInt& profil, VectorReal::iterator ad, 
           VectorReal::iterator al, Real eps, VectorReal& ld, 
           VectorReal& ll) {
    
        // Check if the first diagonal element is below the threshold eps
        if (*(ad) < eps) {
            std::cerr << "THE MATRIX A IS NOT INVERTIBLE." << std::endl;
            std::exit(EXIT_FAILURE);
        }

        // Initialize the diagonal of L with the square root of the first diagonal element of A
        ld[0] = std::sqrt(*ad);
        int iadnxt = 1;

        // Loop over the rows of the matrix
        for (int ligne = 1 ; ligne < rang ; ++ligne) {
            int iad = iadnxt;
            iadnxt = profil[ligne];
            int nbcoef = iadnxt - iad;

            // Solve the sub-system
            if (nbcoef > 0) {
                int col = ligne - nbcoef;
                FEMAssembly::rsprl(nbcoef, profil.begin() + col, ld.begin() + col, ll, al + iad - 1, ll.begin() + iad - 1);
            }

            // Compute the rcoef coefficient
            Real rcoef = *(ad + ligne);
            for (int llad = iad; llad <= iadnxt - 1 ; ++llad) {
                rcoef -= ll[llad - 1] * ll[llad - 1];
            }

            if (rcoef < eps) {
                std::cerr << "THE MATRIX A IS NOT INVERTIBLE." << std::endl;
                std::exit(EXIT_FAILURE);
            }

            // Update the diagonal of L with the square root of rcoef
            ld[ligne] = std::sqrt(rcoef);
        }
    }

    void rsprl(int rang, 
           VectorInt::iterator profil, 
           VectorReal::iterator d, 
           VectorReal& l, 
           VectorReal::iterator b, 
           VectorReal::iterator x) {
        
        const Real epsil = 1.0e-10;

        // Check the singularity condition for the first diagonal element
        if (std::fabs(*d) < epsil) {
            std::cerr << "THE MATRIX L IS NOT INVERTIBLE. 1" << std::endl;
            std::exit(EXIT_FAILURE);        
        }

        // Compute the first element of the solution
        *x = *b / *d;
        int iad = *profil;

        // Loop over the rows of the matrix
        for (int ligne = 1; ligne < rang; ++ligne) {
            int iadnxt = *(profil + ligne);
            int nbcoef = iadnxt - iad;

            // Check the number of coefficients
            if (nbcoef >= ligne + 1) {
                nbcoef = ligne;
            }

            int col = ligne - nbcoef + 1;
            Real rcoef = 0.0;

            // Compute rcoef
            for (int lad = iadnxt - nbcoef; lad <= iadnxt - 1; ++lad) {
                rcoef += l[lad - 1] * *(x + col - 1);
                ++col;
            }

            // Check the singularity condition for d(ligne)
            if (std::fabs(*(d + ligne)) < epsil) {
                std::cerr << "THE MATRIX L IS NOT INVERTIBLE." << std::endl;
                std::exit(EXIT_FAILURE);
            }

            // Compute the element x(ligne)
            *(x + ligne) = (*(b + ligne) - rcoef) / *(d + ligne);
            iad = iadnxt;
        }
    }


    void rspru(int rang, const VectorInt& profil, const VectorReal& d, 
           const VectorReal& l, const VectorReal& b, VectorReal& x) {
            
        // Epsilon for singularity detection
        const float epsil = 1.e-10;

        // Initialize vector x with values from vector b
        for (int ligne = 0; ligne < rang; ++ligne) {
            x[ligne] = b[ligne];
        }

        // Check if the diagonal is singular (last element)
        if (std::abs(d[rang - 1]) < epsil) {
            std::cerr << "THE MATRIX L IS NOT INVERTIBLE." << std::endl;
            std::exit(EXIT_FAILURE);
        }

        // Divide the last element by the diagonal
        x[rang - 1] = x[rang - 1] / d[rang - 1];

        // Start the backward substitution in the upper triangular system
        int iadnxt = profil[rang - 1];
        for (int ligne = rang - 2; ligne >= 0; --ligne) {
            int iad = profil[ligne];
            int xad = ligne;
            float xconnu = x[ligne + 1];  // Use the already computed element in x

            // Perform row reduction by subtracting products from the lower profile
            for (int lad = iadnxt - 2; lad >= iad - 1; --lad) {
                x[xad] -= l[lad] * xconnu;
                --xad;
            }

            // Check for singularity in the diagonal
            if (std::abs(d[ligne]) < epsil) {
                std::cerr << "THE MATRIX L IS NOT INVERTIBLE." << std::endl;
                std::exit(EXIT_FAILURE);
            }

            // Normalize the diagonal term by dividing
            x[ligne] = x[ligne] / d[ligne];
            iadnxt = iad;
        }
    }

    void cdesse(const int NBLIGN, const VectorInt& ADPRCL, 
                      const VectorInt& NUMCOL,
                      const VectorInt& ADSUCL, const VectorReal& MATRIS, 
                      const VectorReal& SECMBR,
                      const VectorInt& NUDDIR, const VectorReal& VALDIR,
                      VectorInt& ADPRC0, VectorInt& NUMCO0, 
                      VectorReal& MATRI0, VectorReal& SECMB0) {

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
                    // Calling the `sort` function to sort NTAB (NUMCO0) and RTAB (MATRI0)
                    sort(admat0 - 1 - admat1, NUMCO0.begin() + admat1, MATRI0.begin() + (NBLIGN + admat1));

                }
            }
        }

        // Final update of ADPRC0 for the last row
        ADPRC0[NBLIGN - 1] = admat0;
    }

    void sort(int N, VectorInt::iterator NTAB, VectorReal::iterator RTAB) {
        bool permut;
        int aux1;
        Real aux2;

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
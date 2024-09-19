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

#ifndef FEM_ASSEMBLY_H
#define FEM_ASSEMBLY_H


#include <vector>

#include "Types.hpp"

namespace FEMAssembly {

    void ltlpr(int rang, 
               VectorInt& profil, 
               VectorReal::iterator ad, 
               VectorReal::iterator al, 
               Real eps, 
               VectorReal& ld, 
               VectorReal& ll);


    void rsprl(int rang, 
           VectorInt::iterator profil, 
           VectorReal::iterator d, 
           VectorReal& l, 
           VectorReal::iterator b, 
           VectorReal::iterator x);

    void rspru(int rang, 
               const VectorInt& profil, 
               const VectorReal& d, 
               const VectorReal& l, 
               const VectorReal& b, 
               VectorReal& x);
    
    
    void cdesse(const int NBLIGN, const VectorInt& ADPRCL, 
                const VectorInt& NUMCOL,
                const VectorInt& ADSUCL, const VectorReal& MATRIS, 
                const VectorReal& SECMBR,
                const VectorInt& NUDDIR, const VectorReal& VALDIR,
                VectorInt& ADPRC0, VectorInt& NUMCO0, 
                VectorReal& MATRI0, VectorReal& SECMB0);


    void sort(int N, 
              VectorInt::iterator NTAB, 
              VectorReal::iterator RTAB);


}

#endif
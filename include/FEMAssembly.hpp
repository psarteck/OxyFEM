#ifndef FEM_ASSEMBLY_H
#define FEM_ASSEMBLY_H


#include <vector>

namespace FEMAssembly {

    void ltlpr(int rang, 
               std::vector<int>& profil, 
               std::vector<double>::iterator ad, 
               std::vector<double>::iterator al, 
               double eps, 
               std::vector<double>& ld, 
               std::vector<double>& ll);


    void rsprl(int rang, 
           std::vector<int>::iterator profil, 
           std::vector<double>::iterator d, 
           std::vector<double>& l, 
           std::vector<double>::iterator b, 
           std::vector<double>::iterator x);

    void rspru(int rang, 
               const std::vector<int>& profil, 
               const std::vector<double>& d, 
               const std::vector<double>& l, 
               const std::vector<double>& b, 
               std::vector<double>& x);
    
    
    void cdesse(const int NBLIGN, const std::vector<int>& ADPRCL, 
                const std::vector<int>& NUMCOL,
                const std::vector<int>& ADSUCL, const std::vector<double>& MATRIS, 
                const std::vector<double>& SECMBR,
                const std::vector<int>& NUDDIR, const std::vector<double>& VALDIR,
                std::vector<int>& ADPRC0, std::vector<int>& NUMCO0, 
                std::vector<double>& MATRI0, std::vector<double>& SECMB0);


    void sort(int N, 
              std::vector<int>::iterator NTAB, 
              std::vector<double>::iterator RTAB);


}

#endif
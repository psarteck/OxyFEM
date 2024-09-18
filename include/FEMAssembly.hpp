#ifndef FEM_ASSEMBLY_H
#define FEM_ASSEMBLY_H


#include <vector>

namespace FEMAssembly {

    void AFFSMD(int nblign, 
            const std::vector<int>& adprcl, 
            const std::vector<int>& numcol, 
            const std::vector<int>& adsucl, 
            const std::vector<float>& matris, 
            const std::vector<float>& secmbr, 
            const std::vector<int>& nuddir, 
            const std::vector<float>& valdir);

    void AFFSMO(int nblign, 
                const std::vector<int>& adprc0, 
                const std::vector<int>& numco0, 
                const std::vector<float>& matri0, 
                const std::vector<float>& secmb0);

    void ltlpr(int rang, 
           const std::vector<int>& profil, 
           std::vector<float>& ad, 
           std::vector<float>& al, 
           float eps, 
           std::vector<float>& ld, 
           std::vector<float>& ll);


    void rsprl(int rang, 
           const std::vector<int>& profil, 
           const std::vector<float>& d, 
           const std::vector<float>& l, 
           const std::vector<float>& b, 
           std::vector<float>& x);
    
    
    void cdesse(const int NBLIGN, const std::vector<int>& ADPRCL, 
                      const std::vector<int>& NUMCOL,
                      const std::vector<int>& ADSUCL, const std::vector<double>& MATRIS, 
                      const std::vector<double>& SECMBR,
                      const std::vector<int>& NUDDIR, const std::vector<double>& VALDIR,
                      std::vector<int>& ADPRC0, std::vector<int>& NUMCO0, 
                      std::vector<double>& MATRI0, std::vector<double>& SECMB0);


    void tri(int N, std::vector<int>::iterator NTAB, std::vector<double>::iterator RTAB);


}

#endif
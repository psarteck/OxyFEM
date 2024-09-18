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
    
    void ASSMAT(int i, int j, float x, 
            std::vector<int>& adprcl, 
            std::vector<int>& numcol, 
            std::vector<int>& adsucl, 
            std::vector<float>& lmatri, 
            int& nextad);

    void TRI(int size, std::vector<int>::iterator numco, std::vector<double>::iterator matri);


    void CDESSE(int nblign, 
            std::vector<int>& adprcl, 
            std::vector<int>& numcol, 
            std::vector<int>& adsucl, 
            std::vector<double>& matris, 
            std::vector<double>& secmbr, 
            std::vector<int>& nuddir, 
            std::vector<double>& valdir, 
            std::vector<int>& adprc0, 
            std::vector<int>& numco0, 
            std::vector<double>& matri0, 
            std::vector<double>& secmb0);


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
           
    
    void cdesse(const int *NBLIGN, const int *ADPRCL, const int *NUMCOL,
            const int *ADSUCL, const float *MATRIS, const float *SECMBR,
            const int *NUDDIR, const float *VALDIR,
            int *ADPRC0, int *NUMCO0, float *MATRI0, float *SECMB0);


    void tri(int N, int *NTAB, float *RTAB);


}

#endif
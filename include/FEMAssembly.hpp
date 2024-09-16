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

    void TRI(int size, std::vector<int>::iterator numco, std::vector<float>::iterator matri);


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
            std::vector<float>& secmb0);


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
           
    



}

#endif
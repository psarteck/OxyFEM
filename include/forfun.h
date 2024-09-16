extern "C" {
    void affsmd_(const int *nblign, const int *adprcl, const int *numcol,
                 const int *adsucl, const float *matris, const float *secmbr,
                 const int *nuddir, const float *valdir);

    void affsmo_(const int *NBLIGN, const int *ADPRCO, const int *NUMCO0,
                 const float *MATRI0, const float *SECMB0);

    void affsol_(const int *nblign, const float *coor, const float *u,
                 const float *uex, const int *impfch);

    void assmat_(const int *I, const int *J, const float *X, int *ADPRCL,
                 int *NUMCOL, int *ADSUCL, float *LMATRI, int *NEXTAD);

    void cdesse_(const int *NBLIGN, const int *ADPRCL, const int *NUMCOL,
                 const int *ADSUCL, const float *MATRIS, const float *SECMBR,
                 const int *NUDDIR, const float *VALDIR,
                 int *ADPRC0, int *NUMCO0, float *MATRI0, float *SECMB0);

    void impmpr_(const int *IMPFCH, const int *RANG, const int *PROFIL,
                 const float *D, const float *L);

    void ltlpr_(const int *rang, const int *profil, const float *ad,
                const float *al, const float *eps, float *ld, float *ll);

    void rsprl_(const int *rang, const int *profil, const float *d,
                const float *l, const float *b, float *x);

    void rspru_(const int *rang, const int *profil, const float *d,
                const float *l, const float *b, float *x);

    void tri_(const int *N, int *NTAB, float *RTAB);
}


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
#include "FEMIntegrale.hpp"

#define FREEMESH 1

int FEMIntegrale::returnQ(std::string type){
	if(type == "Q1"){
		return 9;
	}
	else if(type == "T1"|| type == "S1"){
		return 3;
	}
    return 0;
}


std::vector<double> FEMIntegrale::baseFunctions(const Node& pts, const std::string type, const int number){
    std::vector<double> valBase;
    if(type == "Q1"){            
        valBase.push_back(pts.getX() - pts.getX()*pts.getY());
        valBase.push_back(pts.getX()*pts.getY());
        valBase.push_back(pts.getY() - pts.getX()*pts.getY());
        valBase.push_back(pts.getX()*pts.getY() - pts.getY() - pts.getX() + 1);   
    }
    else if(type == "T1"){
#if FREEMESH == 1
        if (number % 2 == 1){
#endif
            valBase.push_back(pts.getX());
            valBase.push_back(pts.getY());
            valBase.push_back(1 - pts.getX() - pts.getY());
#if FREEMESH == 1
        }
        else {
            valBase.push_back(1 - pts.getX() - pts.getY());
            valBase.push_back(pts.getX());
            valBase.push_back(pts.getY());
        }
#endif
        
    }
    else if(type == "S1"){
        valBase.push_back(pts.getX());
        valBase.push_back(1-pts.getX());
    }
    else{
            std::cout << "Error : Unkown element type." << std::endl;
    }

    return valBase;
}


std::vector<std::vector<double> > FEMIntegrale::baseDerFunctions(const Node& pts, const std::string type, const int number){
    // (TODO) Deleter number
    std::vector<std::vector<double> > valDerBase;
    if(type == "Q1"){            
        valDerBase.push_back({1-pts.getY(), -pts.getX()});
        valDerBase.push_back({pts.getY(), pts.getX()});
        valDerBase.push_back({-pts.getY(), 1-pts.getX()});
        valDerBase.push_back({pts.getY() - 1, pts.getX() - 1});

        // valDerBase.push_back({1-pts.getY(), pts.getY(), -pts.getY(), pts.getY() - 1});
        // valDerBase.push_back({-pts.getX(), pts.getX(), 1-pts.getX(), pts.getX() - 1});   
    }
    else if(type == "T1"){
#if FREEMESH == 1
        if (number % 2 == 1){
#endif
            valDerBase.push_back({1, 0});
            valDerBase.push_back({0, 1});
            valDerBase.push_back({-1, -1});
#if FREEMESH == 1
        }
        else {
            valDerBase.push_back({-1, -1});
            valDerBase.push_back({1, 0});
            valDerBase.push_back({0, 1});
        }
#endif
        // valDerBase.push_back({1, 0, -1});
        // valDerBase.push_back({0, 1, -1});
    }
    else if(type == "S1"){
        valDerBase.push_back({1});
        valDerBase.push_back({-1});
    }
    else{
            printf("\nError : Unkown element type.\n");
    }

    return valDerBase;
}


std::vector<std::vector<double> > FEMIntegrale::matJacob(const std::vector<Node> selectNodes, const std::vector<std::vector<double> > valDerBase, const std::string type){

    // TO DOO MAKE IT 3D AND BETTER !!!!
    // for(auto node : selectNodes){
    //     cout << "Node : X = " << node.getX() << " Y = " << node.getY()<< endl;
    // }
    int d;
    if(type == "S1"){
        d = 1;
    }
    else{
        d = 2;
    }   
    std::vector<std::vector<double>> Jcob(2, std::vector<double>(d, 0.0));

    for(int i = 0 ; i < 2 ; i++){
        for(int j = 0 ; j < d ; j++){
            for(int k = 0 ; k < selectNodes.size() ; k++){

                // cout << "Node : " << selectNodes[k][i] << endl;
                Jcob[i][j] += selectNodes[k][i] * valDerBase[k][j];
                // cout << "i =" << i << ", j = " << j << ", k = " << k << ", selectNodes : =" << selectNodes[k][i]  << ", valDerVase =" <<  valDerBase[k][j] << endl;
            }
        }
    }
    // cout << endl;
    return Jcob;
}


std::vector<double> FEMIntegrale::transFK(const std::vector<Node> selectNodes, const std::vector<double> valBase){
    // float **ai, float *valBase, int Pk, float *res){
    // TO DO Make it 3D
    std::vector<double> evaluatedPoint(2, 0.0);
    for(int i = 0 ; i < selectNodes.size() ; i++){
        evaluatedPoint[0] += selectNodes[i].getX() * valBase[i];
        evaluatedPoint[1] += selectNodes[i].getY() * valBase[i];
    }
    return evaluatedPoint;
}

void FEMIntegrale::ADWDW(const std::vector<Node> nodes, const std::vector<std::vector<double> > valDerBase, double diffElement, std::vector<double> point, std::vector<std::vector<double> > cofvar, std::vector<std::vector<double> > matInv, std::vector<std::vector<double> >& elemMatrix){

    int i, j, alpha, beta;
	for (i = 0 ; i < nodes.size() ; i++) {
    	for (j = 0 ; j < nodes.size() ; j++) {
    		for(alpha = 0 ; alpha < 2 ; alpha++){
                float pdscai = prodScal(valDerBase, matInv, alpha, j);
                
    			for(beta = 0 ; beta < 2 ; beta++){
                    float pdscaj = prodScal(valDerBase, matInv, beta, i);
      				elemMatrix[i][j] += diffElement * cofvar[alpha][beta] * pdscai * pdscaj;
      			}
      		}
    	}
  	}

}


void FEMIntegrale::WW(const std::vector<Node> nodes, const std::vector<double> valBase, const double diffElement, const double cofvar, std::vector<std::vector<double> >& elemMatrix){

	double coeff;
    // double cofvar = FEMProblem::A00(point);

	for (int i = 0; i < nodes.size() ; i++) {
    	coeff = diffElement*cofvar*valBase[i];
    	for (int j = 0 ; j < nodes.size() ; j++) {
      		elemMatrix[i][j] = elemMatrix[i][j] + coeff*valBase[j];
    	}
  	}
}

void FEMIntegrale::W(const std::vector<Node> nodes, const std::vector<double> valBase, const double diffElement, const double cofvar, std::vector<double>& fElem){
    for (int i = 0 ; i < nodes.size() ; i++) {
        fElem[i] += diffElement * cofvar * valBase[i];
  	}
}


std::vector<std::vector<double> > FEMIntegrale::invert2x2(std::vector<std::vector<double> >& mat, double& det){
    // TO DO FAIRE MIEUX -> EIGEN ???

    // Eigen::MatrixXd matEigen = FEMUtilities::vector2EigenMatrix(mat); 

    std::vector<std::vector<double> > invMat(mat.size(), std::vector<double>(mat[0].size(), 0.0));

    det = mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0];
    
    invMat[0][0] = 1/ det * mat[1][1];
    invMat[0][1] = -1/ det * mat[0][1];
    invMat[1][0] = -1/ det * mat[1][0];
    invMat[1][1] = 1/ det * mat[0][0];

    return invMat;

}


double FEMIntegrale::prodScal(std::vector<std::vector<double> > Mat1, std::vector<std::vector<double> > Mat2, int indiceAB, int indiceIJ){
    float somme = 0;
    for(int k = 0 ; k < 2 ; k++){
        somme += Mat1[indiceIJ][k]*Mat2[indiceAB][k];
    }
    return somme;
}
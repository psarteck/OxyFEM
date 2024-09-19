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
#include "Quadrature.hpp"
#include <iostream>



    Quadrature::Quadrature(std::string methodName_, std::string elementType_, int order_):
                            methodName(methodName_), elementType(elementType_), order(order_){}

    // Quadrature::Quadrature(FEMParameters parameters) : methodName(parameters.getQuadrature()){}

    void Quadrature::weightsPoints(std::string elementType){

        int q;

        if(elementType == "Q1"){
            q = 9;

            //Weight
            for(int i = 0 ; i < 4 ; i++){
                weights.push_back(1./36.);
            }
            for(int i = 0 ; i < 4 ; i++){
                weights.push_back(1./9.);
            }
            weights.push_back(4./9.);

            // Points
            points.push_back(Node(1.0,0.0));
            points.push_back(Node(1.0,1.0));
            points.push_back(Node(0.0,1.0));
            points.push_back(Node(0.0,0.0));
            points.push_back(Node(1.0,0.5));
            points.push_back(Node(0.5,1.0));
            points.push_back(Node(0.0,0.5));
            points.push_back(Node(0.5,0.0));
            points.push_back(Node(0.5,0.5));
        }
        else if(elementType == "T1"){
            q = 3;
            // Weights
            for(int i = 0 ; i < q ; i++){
                weights.push_back(1./6.);
            }
            // Points 
            points.push_back(Node(0.5,0.5));
            points.push_back(Node(0.0,0.5));
            points.push_back(Node(0.5,0.0));
        }
        else if(elementType == "S1"){
            q = 3;
            // Weights
            weights.push_back(1./6.);
            weights.push_back(1./6.);
            weights.push_back(2./3.);
            // Points
            points.push_back(Node(1.0));
            points.push_back(Node(0.0));
            points.push_back(Node(0.5));
        }
        else {
            std::cout << "Unknow Element" << std::endl;
        }		
    }


    VectorReal Quadrature::getWeights(){
        return weights;
    }

    std::vector<Node> Quadrature::getPoints(){
        return points;
    }



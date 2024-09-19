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
// Node.cpp
#include "Node.hpp"
#include <iostream>

        

    Node::Node(Real x_, Real y_, Real z_, int id_) : x(x_), y(y_), z(z_), id(id_) {}

    Node::Node(Real x_, Real y_, Real z_) : x(x_), y(y_), z(z_), id(-1) {}

    Node::Node(Real x_, Real y_) : x(x_), y(y_), z(0.0), id(-1.0) {}

    Node::Node(Real x_) : x(x_), y(0.0), z(0.0), id(-1.0) {}


    bool Node::operator==(const Node& other) const {
        return (x == other.x) && (y == other.y) && (z == other.z) ;
    }

    Real Node::operator[](int index) const {
        if (index == 0)
            return getX();
        else if (index == 1)
            return getY();
        else
            throw std::out_of_range("Index out of range");
    }

    Real Node::getX() const{
        return x;
    }

    Real Node::getY() const{
        return y;
    }

    Real Node::getZ() const{
        return z;
    }

    int Node::getId() const{
        return id;
    }

    void Node::setX(Real x_){
        x = x_;
    }

    void Node::setY(Real y_){
        y = y_;
    }

    void Node::setZ(Real z_){
        z = z_;
    }


    void Node::print(){
        std::cout << "x = " << x;
        std::cout << " y = " << y;
        std::cout << " z = " << z << std::endl;;
    }


    // // Explicit instantiation for types 
    // template class Node<Real>;
    // template class Node<float>;



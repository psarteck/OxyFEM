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

        

    Node::Node(double x_, double y_, double z_, int id_) : x(x_), y(y_), z(z_), id(id_) {}

    Node::Node(double x_, double y_, double z_) : x(x_), y(y_), z(z_), id(-1) {}

    Node::Node(double x_, double y_) : x(x_), y(y_), z(0.0), id(-1.0) {}

    Node::Node(double x_) : x(x_), y(0.0), z(0.0), id(-1.0) {}


    bool Node::operator==(const Node& other) const {
        return (x == other.x) && (y == other.y) && (z == other.z) ;
    }

    double Node::operator[](int index) const {
        if (index == 0)
            return getX();
        else if (index == 1)
            return getY();
        else
            throw std::out_of_range("Index out of range");
    }

    double Node::getX() const{
        return x;
    }

    double Node::getY() const{
        return y;
    }

    double Node::getZ() const{
        return z;
    }

    int Node::getId() const{
        return id;
    }

    void Node::setX(double x_){
        x = x_;
    }

    void Node::setY(double y_){
        y = y_;
    }

    void Node::setZ(double z_){
        z = z_;
    }


    void Node::print(){
        std::cout << "x = " << x;
        std::cout << " y = " << y;
        std::cout << " z = " << z << std::endl;;
    }


    // // Explicit instantiation for types 
    // template class Node<double>;
    // template class Node<float>;



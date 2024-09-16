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
#ifndef NODE_H
#define NODE_H

#include <vector>



// template <class T>
    class Node{
        private : 
            double x, y, z;
            const int id;
        public :
            /**
            * @brief Constructor.
            * @param x Coordonnée x du nœud.
            * @param y Coordonnée y du nœud.
            * @param z Coordonnée z du nœud.
            * @param id Identifiant unique du nœud.
            */
            Node(double x_, double y_, double z_, int id_);
            Node(double x_, double y_, double z_);
            Node(double x_, double y_);
            Node(double x_);


            bool operator==(const Node& other) const;
            double operator[](int index) const;

            double getX() const;
            double getY() const;
            double getZ() const;
            int getId() const;

        
            void setX(double x_);
            void setY(double y_);
            void setZ(double z_);

            void print();
    };

#endif

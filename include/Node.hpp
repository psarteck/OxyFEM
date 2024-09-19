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

#include "Types.hpp"


// template <class T>
    class Node{
        private : 
            Real x, y, z;
            const int id;
        public :
            /**
            * @brief Constructor.
            * @param x Coordonnée x du nœud.
            * @param y Coordonnée y du nœud.
            * @param z Coordonnée z du nœud.
            * @param id Identifiant unique du nœud.
            */
            Node(Real x_, Real y_, Real z_, int id_);
            Node(Real x_, Real y_, Real z_);
            Node(Real x_, Real y_);
            Node(Real x_);


            bool operator==(const Node& other) const;
            Real operator[](int index) const;

            Real getX() const;
            Real getY() const;
            Real getZ() const;
            int getId() const;

        
            void setX(Real x_);
            void setY(Real y_);
            void setZ(Real z_);

            void print();
    };

#endif

#pragma once

#include "GeometricSolid.hh"

#define CUBOID_TEMPLETE     "../datasets/templates/cuboid.dat"

#define BASIC_BODY_FILE     "../datasets/dat/body_"

/*!
 * \file
 * \brief Klasa opisujaca prostopadloscian
 *
 * Klasa opisujaca prostopadloscian
 */


/*!
 * \brief Klasa opisujaca prostopadloscian
 *
 *  Klasa opisuje pojecie prostopadloscianu w przestrzeni.
 *  Jest to klasa dziedziczaca po klasie Solid w trybie 
 *  publicznym. Zawiera pola opisujace polozenie bryly w
 *  ukladzie lokalnym zespolu (drona).
 */
class Cuboid: public Solid{

    private:
        /*!
        *   \brief Wektor polozenia
        */
        Vector3D Layout;
        /*!
        *   \brief Kat orientacji
        */
        double OrientAngle;
        /*!
        *   \brief Wysokosc
        */
        double Height;
        /*!
        *   \brief Rzut na plaszczyzne OXY
        */
        Vector3D Aprox_area[4];



    public:

        Cuboid();


        /*!
        *   \brief Konstruktor parametryczny klasy
        */
        Cuboid(std::string File1, std::string File2,const Vector3D &V_scale,const Vector3D &V, double angle );

        /*!
        *   \brief Metoda przechodzaca z ukladu lokalnego bryly do ukladu lokalnego zespolu (drona)
        */
        Vector3D TranformToParentialCoordinate(const Vector3D& Vertex) const;

        /*!
        *   \brief Metoda odpowiadajaca za dostep do wektora polozenia
        */
        const Vector3D& Take_Layout() const {return Layout;}; 
        /*!
        *   \brief Metoda odpowiadajaca za dostep do orientacji
        */
        double Take_OrientAngle() const {return OrientAngle;};
        /*!
        *   \brief Metoda odpowiadajaca za dostep wysokosci
        */
        double Take_Height() const {return Height;};
        /*!
        *   \brief Metoda odpowiadajaca za dostep wysokosci
        */
        double& Take_Height() {return Height;};
        /*!
        *   \brief Metoda odpowiadajaca za modyfikacje wektorow rzutu
        */
        Vector3D& Take_Aprox_Area(unsigned int Ind) {return Aprox_area[Ind];};
        /*!
        *   \brief Metoda odpowiadajaca za dostep do wektorow rzutu
        */
        const Vector3D Take_Aprox_Area(unsigned int Ind) const {return Aprox_area[Ind];}
        /*!
        *   \brief Metoda wirtualna odpowiadajaca za zwracanie typu klasy
        */
        virtual const std::string ObjectType() const override {return "Prostopadloscian";};
        /*!
        *   \brief Metoda wirtualna odpowiadajaca za zwracanie wektora polozenia
        */
        virtual const Vector3D& Take() const override {return Layout;}


};
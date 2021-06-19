#pragma once

#include <iostream>
#include "Vector3D.hh"
#include "Matrix3x3.hh"
#include "SceneObject.hh"


/*!
 * \file
 * \brief Klasa opisujaca bryle geometryczna
 *
 * Klasa opisujaca bryle geometryczna
 */


/*!
 * \brief Klasa opisujaca bryle geometryczna
 *
 *  Klasa opisuje pojecie bryly geometrycznej w przestrzeni.
 *  Sklada sie z pol przechowujacych sciezki do plikow z
 *  wzorcowymi brylami oraz docelowym miejscem skladowania
 *  bryl. Wektor jest uzywany do slkalowania bryl.
 */
class Solid: public SceneObject{

    private:
        /*!
        *   \brief Sciezka do pliku z bryla wzorcowa
        */
        std::string Filename_TemplateSolid;
        /*!
        *   \brief Sciezka do pliku przechowywania finalnych bryl
        */
        std::string Filename_FinalSolid;
        /*!
        *   \brief Wektor skalujacy
        */
        Vector3D    scale;

    public:
        
        Solid();

        /*!
        *   \brief Konstruktor parametryczny klasy Solid
        */
        Solid(std::string FirstFile,std::string SecFile,const Vector3D &V_scale);

        /*!
        *   \brief Metoda zwracajaca sciezke do pliku wzorcowego
        */
        const std::string& TakeFilename_TemplateSolid() const { return Filename_TemplateSolid; };

        /*!
        *   \brief Metoda wirtualna zwracajaca sciezke do pliku z docelowa bryla
        */
        virtual const std::string& TakeFilename_FinalSolid() const override{return Filename_FinalSolid;};

        /*!
        *   \brief Metoda skalujaca wektor
        */
        Vector3D Scale(const Vector3D& Vertex) const;
        /*!
        *   \brief Metoda wirtualna odpowiadajaca za zwracanie typu klasy
        */
        virtual const std::string ObjectType() const override {return "Bryla geometryczna";};
        /*!
        *   \brief Metoda wirtualna odpowiadajaca za zwracanie wektora skalowania
        */
        virtual const Vector3D& Take() const override {return scale;};

        virtual bool  Check_Collision(std::shared_ptr<SceneObject>&Obstacle) const override;

};


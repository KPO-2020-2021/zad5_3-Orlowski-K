// Executables must have the following defined if the library contains
// doctest definitions. For builds with this disabled, e.g. code shipped to
// users, this can be left out.
#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "../tests/doctest/doctest.h"
#endif

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <memory>

#include "exampleConfig.h"
#include "example.h"
#include "Vector3D.hh"
#include "Matrix3x3.hh"
#include "Drone.hh"
#include "Scene.hh"
#include "SceneObject.hh"
#include "Peak.hh"
#include "Slope.hh"
#include "Plateau.hh"
#include "../inc/lacze_do_gnuplota.hh"

#define SURFACE "../datasets/templates/surface.dat"
#define FILE_OBSTACLE "../datasets/templates/obstacle.dat"
#define FLIGHTHEIHGT 80


int main() {
    PzG::LaczeDoGNUPlota Link;
    unsigned int number_of_drones = 0, number_of_peaks = 0, number_of_slopes = 0, number_of_plateaus = 0;
    unsigned int type = 0;
    Vector3D Layout,Scale;
    char option[1] = {'m'}, kind[1];
    double   Angle = 0;
    double   FlightLen;
    double   x = 0,y = 0;

    std::shared_ptr<Drone> FirstDrone(new Drone()), SecondDrone(new Drone());
    std::vector<Vector3D>                   TracePoints;
    std::vector<std::shared_ptr<Drone>>     Drones;
    std::list<std::shared_ptr<SceneObject>> Objects;
    Scene Scene(Drones,Objects,SURFACE,Link);
    

    FirstDrone->MakeDrone({30,40,0},0,number_of_drones);
    FirstDrone->Count_Save_GlobalCoor();

    SecondDrone->MakeDrone({170,120,0},45,number_of_drones);
    SecondDrone->Count_Save_GlobalCoor();

    Scene.AddObject(FirstDrone);
    Scene.AddObject(SecondDrone);
    Scene.AddObject(std::shared_ptr<Peak>(new Peak(FILE_OBSTACLE,"../datasets/dat/Peak" + std::to_string(++number_of_peaks) + ".dat",{20,20,60},{150,30,0},0) ));
    Scene.AddObject(std::shared_ptr<Peak>(new Peak(FILE_OBSTACLE,"../datasets/dat/Peak" + std::to_string(++number_of_peaks) + ".dat",{40,40,50},{35,160,0},0) ));
    Scene.AddObject(std::shared_ptr<Slope>(new Slope(FILE_OBSTACLE,"../datasets/dat/Slope" + std::to_string(++number_of_slopes) + ".dat",{20,80,60},{60,90,0},0) ));
    Scene.AddObject(std::shared_ptr<Plateau>(new Plateau(FILE_OBSTACLE,"../datasets/dat/Plateau" + std::to_string(++number_of_plateaus) + ".dat",{50,60,35},{105,105,0},0) ));
    Scene.Redraw();

    while(option[0] != 'k'){
        switch(option[0]){
            case 'a':
                Scene.SwitchActiveDrone();
                std::cout << "Polozenie Drona aktywnego (x,y): " << Scene.TakeActiveDrone()->TakeLayout()[0]<< "  " << Scene.TakeActiveDrone()->TakeLayout()[1] << std::endl << std::endl;
                std::cout << "Aktualna ilosc obiektow Vector: " << Layout.show_active_vectors() << std::endl;
                std::cout << "  Laczna ilosc obiektow Vector: " << Layout.show_all_vectors() << std::endl << std::endl;
                break;
            case 'p':
                std::cout << "Podaj kierunek lotu (kat w stopniach) > ";
                std::cin >> Angle;
                std::cout << "Podaj dlugosc lotu > ";
                std::cin >> FlightLen;

                if(!Scene.Fly(Angle,FlightLen,FLIGHTHEIHGT,TracePoints)) exit(1);

                std::cout << std::endl;
                
                std::cout << "Polozenie Drona aktywnego (x,y): " << Scene.TakeActiveDrone()->TakeLayout()[0]<< "  " << Scene.TakeActiveDrone()->TakeLayout()[1] << std::endl <<std::endl;
                std::cout << "Aktualna ilosc obiektow Vector: " << Layout.show_active_vectors() << std::endl;
                std::cout << "  Laczna ilosc obiektow Vector: " << Layout.show_all_vectors() << std::endl << std::endl;

                break;
            case 'd':
                std::cout << "Wybierz rodzaj elementu powierzchni: " << std::endl << std::endl;
                std::cout << "1 - Gora z ostrym szczytem\n";
                std::cout << "2 - Gora z grania\n";
                std::cout << "3 - Plaskowyz\n\n";
                std::cout << "Wprowadz numer typu elementu > ";
                std::cin >> kind;
                std::cout << std::endl << std::endl;

                std::cout << "Podaj skale wzdluz osi OX, OY i OZ." << std::endl;
                std::cout << "Wprowadz skale OX,OY,OZ > " ;
                std::cin >> Scale;
                std::cout << std::endl << "Podaj wspolrzedne srodka podstawy x, y." << std::endl;
                std::cout << "Wprowadz dane: x y > ";
                std::cin >> x >> y;
                Layout = {x,y,0};

                switch(kind[0]){
                    case '1':
                        Scene.AddObject(std::make_shared<Peak>(FILE_OBSTACLE,"../datasets/dat/Peak" + std::to_string(++number_of_peaks) + ".dat",Scale,Layout,0) );
                        std::cout << "Element zostal dodany do sceny\n\n";
                        break;
                    case '2':
                        Scene.AddObject(std::shared_ptr<Slope>(new Slope(FILE_OBSTACLE,"../datasets/dat/Slope" + std::to_string(++number_of_slopes) + ".dat",Scale,Layout,0)) );
                        std::cout << "Element zostal dodany do sceny\n\n";
                        break;
                    case '3':
                        Scene.AddObject(std::shared_ptr<Plateau>(new Plateau(FILE_OBSTACLE,"../datasets/dat/Plateau" + std::to_string(++number_of_plateaus) + ".dat",Scale,Layout,0)) );
                        std::cout << "Element zostal dodany do sceny\n\n";
                        break;
                    default :
                        std::cerr << std::endl << "Blad: Podany typ nie istnieje. Blad dodawania !!!\n\n";
                        break;
                }
                
                std::cout << "Polozenie Drona aktywnego (x,y): " << Scene.TakeActiveDrone()->TakeLayout()[0] << "  "<<Scene.TakeActiveDrone()->TakeLayout()[1] << std::endl;
                std::cout << "Aktualna ilosc obiektow Vector: " << Layout.show_active_vectors() << std::endl;
                std::cout << "  Laczna ilosc obiektow Vector: " << Layout.show_all_vectors() << std::endl << std::endl;

                Scene.Redraw();
                //std::cin.ignore(10000,'\n');
                break;
            case 'u':
                std::cout << "Wybierz element powierzchni do usuniecia:\n";
                if(!Scene.ShowList()){
                    std::cout << "Scena jest pusta!!!\n\n";
                    break;
                }
                else{
                    std::cout << std::endl << std::endl;
                    std::cout << "Podaj numer elementu > ";
                    std::cin >> type;
                    std::cout << std::endl;
                    if(Scene.DeleteObject(type) )
                        std::cout << "Element zostal usuniety.\n\n";
                    else{
                        std::cout << "Blad przy usuwaniu.\n\n";
                    }
                }
                Scene.Redraw();


                std::cout << "Polozenie Drona aktywnego (x,y): " << Scene.TakeActiveDrone()->TakeLayout()[0] << "  "<<Scene.TakeActiveDrone()->TakeLayout()[1] << std::endl;
                std::cout << "Aktualna ilosc obiektow Vector: " << Layout.show_active_vectors() << std::endl;
                std::cout << "  Laczna ilosc obiektow Vector: " << Layout.show_all_vectors() << std::endl << std::endl;

                break;

            case 'm':
                std::cout << "Polozenie Drona aktywnego (x,y): " << Scene.TakeActiveDrone()->TakeLayout()[0] << "  "<<Scene.TakeActiveDrone()->TakeLayout()[1] << std::endl;
                std::cout << "a - wybierz aktywnego drona\n";
                std::cout << "p - zadaj parametry przelotu\n";
                std::cout << "d - dodaj element powierzchni\n";
                std::cout << "u - usun element powierzchni\n";
                std::cout << "r - obrot po oktagonie\n";
                std::cout << "t - test\n";
                std::cout << "m - wyswietl menu\n\n";
                std::cout << "k - koniec dzialania programu\n\n";
                std::cout << "Aktualna ilosc obiektow Vector: " << Layout.show_active_vectors() << std::endl;
                std::cout << "  Laczna ilosc obiektow Vector: " << Layout.show_all_vectors() << std::endl << std::endl;
                break;
            case 'r':
                
                if(!Scene.Oct()) exit(1);

                std::cout << "Polozenie Drona aktywnego (x,y): " << Scene.TakeActiveDrone()->TakeLayout()[0] << "  "<<Scene.TakeActiveDrone()->TakeLayout()[1] << std::endl;
                std::cout << "Aktualna ilosc obiektow Vector: " << Layout.show_active_vectors() << std::endl;
                std::cout << "  Laczna ilosc obiektow Vector: " << Layout.show_all_vectors() << std::endl << std::endl;

                break;
            case 't':
                // 1 Przeszkoda
                Scene.Fly(0,100,FLIGHTHEIHGT,TracePoints);
                
                // 2 Przeszkoda
                Scene.Fly(90,80,FLIGHTHEIHGT,TracePoints);
                
                // Ladowanie na plaskowyzu
                Scene.Fly(110,85,FLIGHTHEIHGT,TracePoints);
                usleep(100000);

                // 3 Przeszkoda
                Scene.Fly(0,50,80,TracePoints); 

                std::cout << "Polozenie Drona aktywnego (x,y): " << Scene.TakeActiveDrone()->TakeLayout()[0] << "  "<<Scene.TakeActiveDrone()->TakeLayout()[1] << std::endl;
                std::cout << "Aktualna ilosc obiektow Vector: " << Layout.show_active_vectors() << std::endl;
                std::cout << "  Laczna ilosc obiektow Vector: " << Layout.show_all_vectors() << std::endl << std::endl;

                break;

            default:
                exit(1);
        }
        std::cout << "Twoj wybor <m - menu> ";
        std::cin >> option;
        std::cout <<std::endl;
    }
    std::cout << "Koniec dzialania programu Dragonfly\n";



}

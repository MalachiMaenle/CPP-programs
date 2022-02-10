#include <iostream>
#include <fstream>
#include <windows.h>
#include "pokemonType.h"

void print(pokemonType pokemon);

int main() {
    bool left = false;
    bool right = false;
    std::system("cls");
    int choice = 0;

    /*while(true) {
        std::system("cls");
        switch(choice) {
            case 0:
                std::cout << "Choose your starter: <Bulbasaur>" << endl;
                break;
            case 1:
                std::cout << "Choose your starter: <Charmander>" << endl;
                break;
            case 2:
                std::cout << "Choose your starter: <Squirtle>" << endl;
                break;
            default:
                break;
        }
        if(GetAsyncKeyState(VK_LEFT)) {
            if(left == false) {
                left = true;
                choice--;
            }
        } else {
            left = false;
        }
        if(GetAsyncKeyState(VK_RIGHT)) {
            if(right == false) {
                right = true;
                choice++;
            }
        } else {
            right = false;
        }
        if(GetAsyncKeyState(VK_RETURN)) {
            break;
        }
        if(choice > 2) {
            choice = 0;
        } else if(choice < 0) {
            choice = 2;
        }
    }*/

    pokemonType pokemon1(1);
    pokemonType pokemon2(1);

    pokemon1.level = 5;
    pokemon2.level = 5;
    pokemon1.setMove(pokemon1.move1, "tackle");
    pokemon2.setMove(pokemon2.move1, "tackle");

    pokemon1.pokemonCenter();
    pokemon2.pokemonCenter();
    pokemon1.startCombat();
    pokemon2.startCombat();

    print(pokemon1);
    std::cout << endl;
    print(pokemon2);

    pokemon1.useMove(pokemon1.move1, pokemon2);

    std::cout << endl << endl;

    print(pokemon1);
    std::cout << endl;
    print(pokemon2);

    system("pause");
    
    return 0;
}

void print(pokemonType pokemon) {
    std::cout << pokemon.number << " Name: " << pokemon.name << endl;
    //std::cout << "Species: " << pokemon.species << endl;
    std::cout << "Level: " << pokemon.level << "/" << pokemon.evolveLvl << endl;
    std::cout << "Types: " << pokemon.type.primary << "/" << pokemon.type.secondary << endl;
    std::cout << "Hp: " << pokemon.currentStats.health << "/" << pokemon.baseStats.health << endl;
}


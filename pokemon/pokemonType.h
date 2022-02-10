#ifndef pokemonType_H
#define pokemonType_H

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <ctime>
#include "../libraries/json.hpp"

using namespace std;
using json = nlohmann::json;

json j;

struct Type {
    string primary;
    string secondary;
};

struct stats {
    int health;
    int attack;
    int defense;
    int speed;
};

struct attack {
    string name;
    int power;
    int accuracy;
    int powerPoints;
    int maxPowerPoints;
    string type;
    string effect;
};

struct statusEffect {
    bool poisoned;
    bool paralyzed;
    bool asleep;
    bool frozen;
    bool burned;
    bool flinch;
    bool confused;
    bool infatuation;
    bool leechSeed;
};

class pokemonType {
    public:
        pokemonType() {
            number = 0;
            name = "Undefined";
            type.primary = "Undefined";
            type.secondary = "Undefined";
            species = "Undefined";
            level = 1;
            canEvolve = false;
            evolveLvl = 0;
            baseStats.health = 0;
            baseStats.attack = 0;
            baseStats.defense = 0;
            baseStats.speed = 0;
        }
        pokemonType(int num) {
            ifstream ifs("pokemon.json");
            j = json::parse(ifs);
            ifs.close();

            num -= 1;

            number = num + 1;
            name = j["pokemon"][num]["name"];
            type.primary = j["pokemon"][num]["type"]["primary"];
            type.secondary = j["pokemon"][num]["type"]["secondary"];
            species = j["pokemon"][num]["species"];
            level = 1;
            canEvolve = j["pokemon"][num]["canEvolve"];
            evolveLvl = j["pokemon"][num]["evolveLvl"];
            baseStats.health = j["pokemon"][num]["baseStats"]["health"];
            baseStats.attack = j["pokemon"][num]["baseStats"]["attack"];
            baseStats.defense = j["pokemon"][num]["baseStats"]["defense"];
            baseStats.speed = j["pokemon"][num]["baseStats"]["speed"];
        }
        pokemonType(int iNumber, string iName, string iPrimaryType, string iSecondaryType, string iSpecies, bool iCanEvolve, int iEvolveLvl, int iHealth, int iAttack, int iDefense, int iSpeed) {
            number = iNumber;
            name = iName;
            type.primary = iPrimaryType;
            type.secondary = iSecondaryType;
            species = iSpecies;
            level = 1;
            canEvolve = iCanEvolve;
            evolveLvl = iEvolveLvl;
            baseStats.health = iHealth;
            baseStats.attack = iAttack;
            baseStats.defense = iDefense;
            baseStats.speed = iSpeed;
        }
        void operator = (const pokemonType &tempType) {
            number = tempType.number;
            name = tempType.name;
            type.primary = tempType.type.primary;
            type.secondary = tempType.type.secondary;
            species = tempType.species;
            level = tempType.level;
            canEvolve = tempType.canEvolve;
            evolveLvl = tempType.evolveLvl;
            baseStats.health = tempType.baseStats.health;
            baseStats.attack = tempType.baseStats.attack;
            baseStats.defense = tempType.baseStats.defense;
            baseStats.speed = tempType.baseStats.speed;
        }
        void evolve() {
            if(canEvolve == true && level >= evolveLvl && itemHeld != "everstone") {
                ifstream ifs("pokemon.json");
                j = json::parse(ifs);
                ifs.close();
            
                name = j["pokemon"][number]["name"];
                type.primary = j["pokemon"][number]["type"]["primary"];
                type.secondary = j["pokemon"][number]["type"]["secondary"];
                species = j["pokemon"][number]["species"];
                canEvolve = j["pokemon"][number]["canEvolve"];
                evolveLvl = j["pokemon"][number]["evolveLvl"];
                baseStats.health = j["pokemon"][number]["baseStats"]["health"];
                baseStats.attack = j["pokemon"][number]["baseStats"]["attack"];
                baseStats.defense = j["pokemon"][number]["baseStats"]["defense"];
                baseStats.speed = j["pokemon"][number]["baseStats"]["speed"];
                number = number + 1;
            }
        }
        void setMove(attack& move, string attackName) {
            ifstream ifs("pokemon.json");
            j = json::parse(ifs);
            ifs.close();

            move.name = attackName;
            move.power = j["move"][attackName]["power"];
            move.accuracy = j["move"][attackName]["accuracy"];
            move.maxPowerPoints = j["move"][attackName]["maxPowerPoints"];
            move.powerPoints = move.maxPowerPoints;
            move.type = j["move"][attackName]["type"];
            move.effect = j["move"][attackName]["effect"];
        }
        void pokemonCenter() {
            currentStats.health = baseStats.health;
            move1.powerPoints = move1.maxPowerPoints;
            move2.powerPoints = move2.maxPowerPoints;
            move3.powerPoints = move3.maxPowerPoints;
            move4.powerPoints = move4.maxPowerPoints;
            status.asleep = false;
            status.burned = false;
            status.confused = false;
            status.flinch = false;
            status.frozen = false;
            status.infatuation = false;
            status.leechSeed = false;
            status.paralyzed = false;
            status.poisoned = false;
        }
        void startCombat() {
            currentStats.attack = baseStats.attack;
            currentStats.defense = baseStats.defense;
            currentStats.speed = baseStats.speed;
        }
        double typeEffectiveness(attack move, pokemonType pokemon) {
            ifstream ifs("pokemon.json");
            j = json::parse(ifs);
            ifs.close();

            double typeEff1 = j["type"][pokemon.type.primary][move.type];
            double typeEff2 = j["type"][pokemon.type.secondary][move.type];

            return typeEff1 * typeEff2;
        }
        void useMove(attack move, pokemonType& pokemon) {
            srand(time(NULL));
            double typeEff = typeEffectiveness(move, pokemon);
            if(rand() % 100 + 1 <= move.accuracy) {
                pokemon.currentStats.health -= floor(((((2 * level / 5 + 2) * currentStats.attack * move.power / pokemon.currentStats.defense) / 50) + 2) * typeEff * (rand() % 100 + 85) / 100);
            }
        }
    
    //Pokemon variables
        int number;
        string name; //Name of the pokemon
        Type type; //Primary and secondary types: grass, fire, water, etc.
        string species; //Charmander the "Lizard pokemon"
        int level; //Level of the pokemon
        int exp; //experience to the next level
        int expToLvl;
        bool canEvolve; //Whether the pokemon can evolve or not
        int evolveLvl; //Level at which the pokemon can evolve
        string itemHeld;
        stats baseStats; //
        stats currentStats;
        attack move1;
        attack move2;
        attack move3;
        attack move4;
        statusEffect status;
};


void setPokemon(pokemonType &pokemon, int num) {
    ifstream ifs("pokemon.json");

    j = json::parse(ifs);
    num -= 1;

    ifs.close();

    string iName = j["pokemon"][num]["name"];
    string iPrimaryType = j["pokemon"][num]["type"]["primary"];
    string iSecondaryType = j["pokemon"][num]["type"]["secondary"];
    string iSpecies = j["pokemon"][num]["species"];
    bool iCanEvolve = j["pokemon"][num]["canEvolve"];
    int iEvolveLvl = j["pokemon"][num]["evolveLvl"];
    int iHealth = j["pokemon"][num]["baseStats"]["health"];
    int iAttack = j["pokemon"][num]["baseStats"]["attack"];
    int iDefense = j["pokemon"][num]["baseStats"]["defense"];
    int iSpeed = j["pokemon"][num]["baseStats"]["speed"];

    pokemonType tempType(num, iName, iPrimaryType, iSecondaryType, iSpecies, iCanEvolve, iEvolveLvl, iHealth, iAttack, iDefense, iSpeed);

    pokemon = tempType;
}

#endif
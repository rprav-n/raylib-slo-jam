#include "raylib.h"
#include <vector>

using namespace std;

// class Ability
// {
// public:
//     Ability(int i, char *t, char *d)
//     {
//         id = i;
//         title = t;
//         description = d;
//     };

// private:
//     // Texture2D texture;
//     int id;
//     char *title = "";
//     char *description = "";
// };

class AbilityScreen
{
private:
    // vector<Ability> abilities = {
    //     Ability(1, "Double Gun", "Some description about the double gun feature"),
    //     Ability(2, "Dashing", "Dashing helps you to dash and destroy enemies"),
    // };

public:
    void Update();
    void Draw();
};
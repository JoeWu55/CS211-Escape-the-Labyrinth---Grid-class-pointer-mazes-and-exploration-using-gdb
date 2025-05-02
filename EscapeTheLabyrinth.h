#include <utility>
#include <random>
#include <set>
#include "grid.h"
#include "maze.h"
using namespace std;

const string kYourNetID = "jwu248";

const string kPathOutOfRegularMaze = "SEENSWWWSEESWW";
const string kPathOutOfTwistyMaze = "EWWEWENE";

//used to move the player character, collect items, and decide if the player has collected all 3 items to win
bool isPathToFreedom(MazeCell *start, const string& moves) {
    set<string> items = {"Spellbook", "Wand", "Potion"};
    set<string> collected;

    MazeCell* cur = start;

    if (items.count(cur->whatsHere)) { //start on item
        collected.insert(cur->whatsHere);
    }
    
    for (char m: moves){
        if (m == 'N') {
            cur = cur->north;
        } else if (m == 'S') {
            cur = cur->south;
        } else if (m == 'E') {
            cur = cur->east;
        } else if (m == 'W') {
            cur = cur->west;
        } else {
            return false; //invalid direction
        }

        if (!cur) {
            return false; //move towards wall
        }

        if (items.count(cur->whatsHere)) {
            collected.insert(cur->whatsHere);
        }
    }
    
    return items == collected;
}

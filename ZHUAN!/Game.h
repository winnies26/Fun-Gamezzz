#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Well.h"
#include "UserInterface.h"
#include <string>

class Well;
class Game
{
public:
    Game();
    void play();
    
private:
    Well    m_well;
    Screen  m_screen;
    void displayPrompt(std::string s);
    bool playOneLevel();
    
};

#endif // GAME_INCLUDED

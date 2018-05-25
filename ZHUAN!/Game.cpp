#include "Game.h"
#include "Well.h"
#include "UserInterface.h"
#include <string>
#include <cmath>
using namespace std;

// Start a timer
Timer timer;
const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;

const int PROMPT_Y = 20;
const int PROMPT_X = 0;


Game::Game()
: m_screen(SCREEN_WIDTH, SCREEN_HEIGHT)
{
}

void Game::play()
{
    m_well.DisplayWell(m_screen);
    m_well.DisplayStatus(m_screen);  //  score, rows left, level
    displayPrompt("Hi ;)Press the Enter key to begin playing ZHUAN!");
    waitForEnter();
    displayPrompt("");
    for(;;m_well.levelUP())
    {
        if ( ! playOneLevel()){break;}//if piece can't be dropped
        displayPrompt("Good job!  Press the Enter key to start next level!");
        waitForEnter();
        displayPrompt("");
    }
    displayPrompt("Game Over!  Press the Enter key to exit!");
    waitForEnter();
}

void Game::displayPrompt(std::string s)
{
    m_screen.gotoXY(PROMPT_X, PROMPT_Y);
    m_screen.printStringClearLine(s);   // overwrites previous text
    m_screen.refresh();
}


bool Game::playOneLevel()
{
    Timer timer;// create and start a timer
    m_well.ClearWholeWell();//well always starts empty
    m_well.DisplayWell(m_screen);
    m_well.DisplayInitialPieces(m_screen);//display the initial current piece and next piece
    m_well.DisplayStatus(m_screen);//display initial status
    
    while ( !m_well.ifFilled())//Keep play until the current piece can’t be displayed because of overlapping
        
    {
        double x = timer.elapsed();
        char type=m_well.getPieceType();
        
        char turn;
        if(getCharIfAny(turn))
        {
            if(type=='C')//if crazy type, reverse left and right
            {
                switch (turn)
                {
                    case 'a':
                    case '4':
                        turn='6';
                        break;
                    case 'd':
                    case '6':
                        turn='4';
                        break;
                    default:
                        break;
                }
            }
            switch (turn)
            {
                case 'a':
                case '4':
                case 'd':
                case '6':
                case 's':
                case '2':
                case ' ':
                case 'w':
                case '8':
                    m_well.Move(m_screen,turn);
                    break;
                case 'q':
                case 'Q':
                    return false;
                default:
                    break;
            }
            
        }
        m_well.DisplayStatus(m_screen);
        m_screen.refresh();
        int y;
        y = int (x);    //make it an integer so I can use the % function for dropping
        int timeGive;
        if (m_well.level()<=10)//This equation apply only when level is <=10
        {
            timeGive=1000-100*(m_well.level()-1);
            
        }
        else
            timeGive=100;
        
        if (y%timeGive==0)
        {
            m_well.Move(m_screen,'2');//Every timeGive second, drop 1 if it can
            m_screen.refresh();
        }
        if (m_well.BottomHasStuff())
        {
            if (type=='F')//FoamBomb
            {m_well.foamBombUpdateWell();}//Special
            else if (type=='V')//Vaporbomb
            {m_well.vaporBombUpdateWell();}//Special
            
            else //Normal Piece
            {m_well.PlainCopyInWell('$');}
            
            m_well.FullRowCheck(m_screen);//Check if there's any completed row
            m_well.UpdateShape(m_screen);//Switch the current shape to new shape, Create new Shape
            m_well.DisplayStatus(m_screen);
            m_screen.refresh();
        }
        
        
        if(m_well.rowsLeft()==0)
        {
            return true;
        }
    }
    return false;
}



#include "Well.h"
#include "UserInterface.h"
#include "Piece.h"
#include <stack>

std::string RightAlligned (int intNumber);

Well::Well():m_score(0),m_rowsLeft(5),m_level(1)
{
    
    for (int j=0;j<=11;j++)//Build an empty well
        
    {
        for (int i=0;i<=18;i++)
        {
            if (j==0||j==11)//1st and last col is all @
                maze[i][j]='@';
            else if (i==18)//last row is all @
            {
                maze[18][j]='@';
            }
            else//the rest is empty
                maze[i][j]=' ';
        }
    }
    getCShape();//dynamically allocate new Pieces
    getNShape();
}

void Well::getCShape()
{
    switch (chooseRandomPieceType())
    {
        case PIECE_I:
            m_currPiece=new I_Piece;
            break;
        case PIECE_L:
            m_currPiece=new L_Piece;
            break;
        case PIECE_J:
            m_currPiece=new J_Piece;
            break;
        case PIECE_T:
            m_currPiece=new T_Piece;
            break;
        case PIECE_O:
            m_currPiece=new O_Piece;
            break;
        case PIECE_S:
            m_currPiece=new S_Piece;
            break;
        case PIECE_Z:
            m_currPiece=new Z_Piece;
            break;
        case PIECE_VAPOR:
            m_currPiece=new VaporBomb_Piece;
            break;
        case PIECE_FOAM:
            m_currPiece=new FoamBomb_Piece;
            break;
        case PIECE_CRAZY:
            m_currPiece=new Crazy_Piece;
            break;
        case NUM_PIECE_TYPES:
            getCShape();
            break;
        default:
            break;
    }
    
}
void Well::getNShape()
{
    switch (chooseRandomPieceType())
    {
        case PIECE_I:
            m_nextPiece=new I_Piece;
            break;
        case PIECE_L:
            m_nextPiece=new L_Piece;
            break;
        case PIECE_J:
            m_nextPiece=new J_Piece;
            break;
        case PIECE_T:
            m_nextPiece=new T_Piece;
            break;
        case PIECE_O:
            m_nextPiece=new O_Piece;
            break;
        case PIECE_S:
            m_nextPiece=new S_Piece;
            break;
        case PIECE_Z:
            m_nextPiece=new Z_Piece;
            break;
        case PIECE_VAPOR:
            m_nextPiece=new VaporBomb_Piece;
            break;
        case PIECE_FOAM:
            m_nextPiece=new FoamBomb_Piece;
            break;
        case PIECE_CRAZY:
            m_nextPiece=new Crazy_Piece;
            break;
        case NUM_PIECE_TYPES:
            getNShape();
            break;
        default:
            break;
    }
    
}
Well::~Well()
{
    delete m_currPiece;
    delete m_nextPiece;
}

void Well::ClearWholeWell()
{
    for (int j=1;j<11;j++)
    {
        for (int i=0;i<18;i++)
        {
            maze[i][j]=' ';
        }
    }
}
void Well::ClearTempPiecesOnScreen(Screen&screen)//clear every non '$' and '*'pieces on screen
{
    for(int i = 1; i <= 10; i++)
        for(int j = 0; j <= 17; j++)
        {
            if (maze[j][i]!='$'&&maze[j][i]!='*')
            {
                screen.gotoXY(i,j);
                screen.printChar(' ');
                screen.refresh();
            }
            
        }
}

void Well::DisplayInitialPieces(Screen&screen)
{
    m_currPiece->DisplayCurrentPiece(screen);
    m_nextPiece->DisplayNextPiece(screen);
    //"Next piece:"
    screen.gotoXY(16,3);
    screen.printString("Next piece:");
}



bool Well::CharExistsInMaze(int column, int row, char find) const
{
    return (maze[row][column] == find) ;
}
void Well::DisplayWell(Screen&screen)
{
    for(int R=0;R<19;R++)
    {
        for(int C=0;C<12;C++)
        {
            screen.gotoXY(C,R);
            screen.printChar(maze[R][C]);
        }
    }
}

void Well::vaporBombUpdateWell()
{
    int x,y,z;
    m_currPiece->getCoord(x, y,z);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++)
        {
            if (m_currPiece->PieceExistAt(j,i,z))
            {
                for(int test=-2;test<=2;test++)//2 rows above and below
                {
                    if (y+j+test>=0&&y+j+test<=17)//inside the well
                        maze[y+j+test][x+i]=' ';//delete
                }
                
            }
            
        }
    }
    
}


void Well::foamBombUpdateWell()
{
    int col,row,z;
    m_currPiece->getCoord(col, row,z);
    PlainCopyInWell('#');//draw # at the location
    foamDetect(++row, ++col);//The actual location of the #
    
}

void Well::foamDetect(int row,int col)//RECURSION!!!
{
    if(maze[row][col]=='#')
    {
        maze[row][col]=' ';//mark the original
        foamDetect(row, col);
    }
    
    if (maze[row][col]=='$'||OutFoamBoundary(row,col))
        return ;
    
    else if(maze[row][col]==' ')
    {
        maze[row][col]='*';
        foamDetect((row + 1), col );//4 directions
        foamDetect(row, (col + 1));
        foamDetect(row, (col - 1));
        foamDetect((row - 1), col );
    }
    
    
}
bool Well::OutFoamBoundary(int row, int col)const
{
    int x,y,z;
    m_currPiece->getCoord(x, y,z);
    ++x;
    ++y;
    if ( row < 0 || col < 1 || row >17 || col >10 ) //out of the maze
    {
        return true;
    }
    if( row<(y-2) || row>(y+2) || col<(x-2) || col>(x+2))//out of the 5*5
        return true;
    else
        return false;
}


char Well::getPieceType() const
{
    char t=m_currPiece->getType();
    return t;
}



bool Well::roll()
{
    bool rollable=true;
    int x,y,old_rotation,potential_rotation;
    m_currPiece->getCoord(x, y,old_rotation);
    if(old_rotation==3)//0-1-2-3-0....
    {
        potential_rotation=0;
    }
    else
    {
        potential_rotation=old_rotation+1;
    }
    
    for(int row = 0; row < 4; row++)//Loop through the 4*4 grid of the current piece’s potential rotation
        
    {
        for(int col = 0; col < 4; col++)
        {
            //If there is a ‘#’ at that spot of that rotation
            //If maze’s that position is not empty
            if (m_currPiece->PieceExistAt(row,col,potential_rotation) && maze[y + row][x + col] !=' ')
            {
                rollable = false;
                
            }
        }
        
    }
    
    if(rollable)
    {
        m_currPiece->UpdateRotation(potential_rotation);
    }
    return rollable;
}

void Well::PlainCopyInWell(char symbol)
{
    int x,y,z;
    m_currPiece->getCoord(x, y,z);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++)
        {
            if (m_currPiece->PieceExistAt(j,i,z))
            {
                maze[y+j][x+i]=symbol;
            }
            
        }
    }
}



void Well::UpdateShape(Screen&screen)//Gets called in Game when the current pieces touches the ground, after that current piece is stored as ‘$’
{
    DisplayWell(screen);
    Shape*temp=m_nextPiece;
    delete m_currPiece;
    m_currPiece=temp;
    m_currPiece->DisplayCurrentPiece(screen);//display the new current piece
    getNShape();//Get new Shape
    m_nextPiece->DisplayNextPiece(screen);//Display the new next piece on screen
}




bool Well::BottomHasStuff() const
{
    bool stuff = false;
    int x,y,z;
    m_currPiece->getCoord(x, y,z);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (m_currPiece->PieceExistAt(j,i,z))//If there is a 1 at that spot
            {
                //Return false if touches the bottom of the wall
                //Return false if there is a settled symbol below that spot
                if (y+j>16||CharExistsInMaze(x+i, y+j+1,'$')||CharExistsInMaze(x+i, y+j+1,'*')||CharExistsInMaze(x+i, y+j+1,'@'))
                {
                    return true;
                }
            }
        }
    }
    
    return stuff;
}

bool Well::RightHasStuff()const
{
    bool collision = false;
    int x,y,z;
    m_currPiece->getCoord(x, y,z);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (m_currPiece->PieceExistAt(j,i,z))//If there is a 1 at that spot
            {
                if (x+i+1 >= 11 ||CharExistsInMaze(x+i+1, y+j,'*')||CharExistsInMaze(x+i+1, y+j,'$')||CharExistsInMaze(x+i+1, y+j,'@'))//Right has stuff
                    return true;
                
            }
        }
    }
    
    return collision;
}

bool Well::LeftHasStuff()const
{
    bool collision = false;
    int x,y,z;
    m_currPiece->getCoord(x, y,z);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (m_currPiece->PieceExistAt(j,i,z))//If there is a 1 at that spot
            {
                if (x+i-1 < 0 ||CharExistsInMaze(x+i-1, y+j,'*')||CharExistsInMaze(x+i-1, y+j,'$')||CharExistsInMaze(x+i-1, y+j,'@'))//Left has stuff
                {
                    return true;
                }
            }
        }
    }
    return collision;
    
}

void Well::FullRowCheck(Screen&screen)
{
    bool full=true;
    int totRowDeleted=0;
    for (int i=17;i>0;i--)//Loop through each spot inside of maze, row by row
    {
        
        for (int j=1;j<10;j++)
        {
            if (maze[i][j]!='$'&&maze[i][j]!='*')//If meet a spot not ‘$’ and ‘*’
                
            {
                full=false;//Go to the next row
                
            }
        }
        if (full)//If all spot has neither ‘$’ or ‘*’
        {
            totRowDeleted++;
            dropDown(i);
            i++;
        }
        full=true;
    }
    m_rowsLeft-=totRowDeleted;//Update rows left
    if(m_rowsLeft<=0)
        m_rowsLeft=0;
    
    if(totRowDeleted==1)
        m_score+=100;
    if(totRowDeleted==2)
        m_score+=200;
    if(totRowDeleted==3)
        m_score+=400;
    if(totRowDeleted==4)
        m_score+=800;
    if(totRowDeleted==5)
        m_score+=1600;
    
    if (totRowDeleted!=0)
    {
        ClearTempPiecesOnScreen(screen);
        m_currPiece->DisplayCurrentPiece(screen);
        DisplayStatus(screen);
        return ;
    }
}

void Well::dropDown(int deleteThisRow)//Move every row above the delete row down 1 in the maze

{
    for(int r = deleteThisRow; r > 1; r--)
    {
        for(int c = 1; c < 11; c++)
        {
            maze[r][c] = maze[r - 1][c];
        }
    }
    
}

bool Well::ifFilled()const//Gets constantly called in game to check if the game should continue
{
    bool filled = false;
    int x,y,z;
    m_currPiece->getCoord(x, y,z);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (m_currPiece->PieceExistAt(j,i,z))
            {
                if (CharExistsInMaze(x+i, y+j,'$')||CharExistsInMaze(x+i, y+j,'*'))
                {
                    return true;
                }
            }
        }
    }
    
    return filled;
}


bool Well::Move(Screen&s, char move)//Game’s playOneLevel calls this if it detects any of the 9 valid input

{
    bool movable=false;
    int x,y,z;
    m_currPiece->getCoord(x, y,z);
    
    switch (move)
    {
        case '4'://the left arrow key or 'a' or '4'.
        case 'a':
            if(LeftHasStuff()==false)
            {
                movable=true;
                m_currPiece->MovePiece(move);
            }
            break;
        case '6':
        case 'd'://the right arrow key or 'd' or '6'.
            if(RightHasStuff()==false)
            {
                movable=true;
                m_currPiece->MovePiece(move);
            }
            break;
        case '2'://the down arrow or 's' or '2'.
        case 's':
            if(BottomHasStuff()==false)
            {
                movable=true;
                m_currPiece->MovePiece(move);
                
            }
            break;
        case ' ':
            while(BottomHasStuff()==false)
            {
                movable=true;
                m_currPiece->MovePiece(move);
            }
            break;
        case 'w':
        case '8':
        {
            if (roll())//checks if rollable, and rolls if rollable
                movable=true;
        }
            break;
        default:
            return false;
            
    }
    FullRowCheck(s);//checks if row if full and delete row if full, update rowsleft too
    if (movable)
    {
        
        ClearTempPiecesOnScreen(s);//put empty char at where the maze does not have ‘*’or ‘$’
        m_currPiece->DisplayCurrentPiece(s);//display the updated piece on screen
        return movable;
    }
    else
        return movable;
}


void Well::DisplayStatus(Screen&m_screen)
{
    m_screen.gotoXY(16,8);
    m_screen.printString("Score:     ");
    m_screen.printStringClearLine(RightAlligned(m_score));
    m_screen.refresh();
    /*
     The current score should be displayed at (16,8) in the form "Score:" followed by five spaces followed by the score right-justified in a field seven characters wide. 12
     */
    m_screen.gotoXY(16,9);
    m_screen.printString("Rows left: ");
    m_screen.printStringClearLine(RightAlligned(m_rowsLeft));
    m_screen.refresh();
    
    
    /*The number of rows left that must be vaporized before the current level is completed should be displayed at (16,9) in the form: "Rows left: " followed by one space, followed by the number of rows left before the level is completed, right-justified in a field 7 characers wide. 8*/
    
    m_screen.gotoXY(16,10);
    m_screen.printString("Level:     ");
    m_screen.printStringClearLine(RightAlligned(m_level));
    m_screen.refresh();
    
    m_screen.gotoXY(16,12);
    m_screen.printString("# fills in the empty slots in 5*5 bound");
    m_screen.refresh();
    
    m_screen.gotoXY(16,14);
    m_screen.printString("## removes all blocks up to 2 rows above or below");
    m_screen.refresh();
    
    m_screen.gotoXY(16,16);
    m_screen.printString("#  #");
    m_screen.refresh();
    
    m_screen.gotoXY(16,17);
    m_screen.printString(" ##  is kinda crazy~");
    m_screen.refresh();
    
    /* The current level number should be displayed at (16,10) in the form "Level:" followed by five spaces, followed by the current level number, right-justified in a field seven charcaters wide.
     */
    // [Replace this with code to display the status.]
    // [Replace this with code to display the status.]
}
int Well::level()const
{
    return m_level;
}
void Well::levelUP()
{
    ++m_level;
    m_rowsLeft=m_level*5;
}

int Well::rowsLeft()const
{
    return m_rowsLeft;
}
std::string RightAlligned (int intNumber)
{
    std::string number=std::to_string(intNumber);//convert int to string
    std::stack<char> s;
    for(unsigned long i = number.length(); i>0; i--)
    {
        s.push(number[i-1]);//push in the number from back to front
    }
    unsigned long space=7-number.length();// All 7 characters wide
    while (space>0)//fill the remain spots with space
    {
        s.push(' ');
        space--;
    }
    std::string final;
    
    while(!s.empty())
    {
        char temp=s.top();
        s.pop();
        final+=temp;//pop out the stack
    }
    return final;
}

#include "Piece.h"
#include "UserInterface.h"

Shape::Shape():xCoord(3),yCoord(0),m_rotation(0)
{
    
}

Shape::~Shape()
{}

void Shape::DisplayCurrentPiece(Screen& s)
{
    for(int i = yCoord; i < yCoord+4; i++)
        for(int j = xCoord; j < xCoord+4; j++)
        {
            if(grid[i-yCoord][j-xCoord][m_rotation] == 1)
            {
                s.gotoXY(j,i);
                s.printChar('#');
                s.refresh();
            }
        }
}
void Shape::DisplayNextPiece(Screen& s)
{
    for(int i = 4; i < 8; i++)
        for(int j = 16; j < 20; j++)
        {
            s.gotoXY(j,i);
            s.printChar(' ');
            if(grid[i-4][j-16][m_rotation] == 1)//if the position is filled
            {
                s.gotoXY(j,i);
                s.printChar('#');
                s.refresh();
            }
        }
}



int Shape::rotation()const
{
    return m_rotation;
}

void Shape::UpdateRotation(int NewRotation)
{
    m_rotation=NewRotation;
}

bool Shape::PieceExistAt(int row,int col,int rotation) const
{
    if(grid[row][col][rotation] ==1)//Loop through current piece’s grid’s each position at that rotation
        
        return true;
    else
        return false;
}

char Shape::getType() const //so the Well can decide the user's movement, and special function when landed
{
    if (type==PIECE_I)
        return 'I';
    if (type==PIECE_L)
        return 'L';
    if (type==PIECE_J)
        return 'J';
    if (type==PIECE_T)
        return 'T';
    if (type==PIECE_O)
        return 'O';
    if (type==PIECE_S)
        return 'S';
    if (type==PIECE_Z)
        return 'Z';
    if (type==PIECE_VAPOR)
        return 'V';
    if (type==PIECE_FOAM)
        return 'F';
    if (type==PIECE_CRAZY)
        return 'C';
    else
        return ' ';
}

void Shape::getCoord (int &xx,int& yy,int&zz)const
{
    zz=m_rotation;
    xx=xCoord;
    yy=yCoord;
}
void Shape::MovePiece(char move)
{
    switch (move)
    {
        case '4'://the left arrow key or 'a' or '4'.
        case 'a':
            xCoord--;
            break;
        case '6':
        case 'd'://the right arrow key or 'd' or '6'.
            xCoord++;
            break;
        case '2'://the down arrow or 's' or '2'.
        case 's':
        case ' ':
            yCoord++;
            break;
        case 'w':
        case '8':
            break;
    }
    
}
T_Piece ::T_Piece ()
{
    type=PIECE_T;
    
    grid[0][0][0] = 0;
    grid[0][1][0] = 1;
    grid[0][2][0] = 0;
    grid[0][3][0] = 0;
    grid[1][0][0] = 1;
    grid[1][1][0] = 1;
    grid[1][2][0] = 1;
    grid[1][3][0] = 0;
    grid[2][0][0] = 0;
    grid[2][1][0] = 0;
    grid[2][2][0] = 0;
    grid[2][3][0] = 0;
    grid[3][0][0] = 0;
    grid[3][1][0] = 0;
    grid[3][2][0] = 0;
    grid[3][3][0] = 0;
    //////////////////////////////////Orientation1
    grid[0][0][1] = 0;
    grid[0][1][1] = 1;
    grid[0][2][1] = 0;
    grid[0][3][1] = 0;
    grid[1][0][1] = 0;
    grid[1][1][1] = 1;
    grid[1][2][1] = 1;
    grid[1][3][1] = 0;
    grid[2][0][1] = 0;
    grid[2][1][1] = 1;
    grid[2][2][1] = 0;
    grid[2][3][1] = 0;
    grid[3][0][1] = 0;
    grid[3][1][1] = 0;
    grid[3][2][1] = 0;
    grid[3][3][1] = 0;
    //////////////////////////////////Orientation2
    grid[0][0][2] = 0;
    grid[0][1][2] = 0;
    grid[0][2][2] = 0;
    grid[0][3][2] = 0;
    grid[1][0][2] = 1;
    grid[1][1][2] = 1;
    grid[1][2][2] = 1;
    grid[1][3][2] = 0;
    grid[2][0][2] = 0;
    grid[2][1][2] = 1;
    grid[2][2][2] = 0;
    grid[2][3][2] = 0;
    grid[3][0][2] = 0;
    grid[3][1][2] = 0;
    grid[3][2][2] = 0;
    grid[3][3][2] = 0;
    //////////////////////////////////Orientation3
    grid[0][0][3] = 0;
    grid[0][1][3] = 1;
    grid[0][2][3] = 0;
    grid[0][3][3] = 0;
    grid[1][0][3] = 1;
    grid[1][1][3] = 1;
    grid[1][2][3] = 0;
    grid[1][3][3] = 0;
    grid[2][0][3] = 0;
    grid[2][1][3] = 1;
    grid[2][2][3] = 0;
    grid[2][3][3] = 0;
    grid[3][0][3] = 0;
    grid[3][1][3] = 0;
    grid[3][2][3] = 0;
    grid[3][3][3] = 0;
}
I_Piece ::I_Piece ()
{
    type=PIECE_I;
    grid[0][0][0] = 0;
    grid[0][1][0] = 0;
    grid[0][2][0] = 0;
    grid[0][3][0] = 0;
    grid[1][0][0] = 1;
    grid[1][1][0] = 1;
    grid[1][2][0] = 1;
    grid[1][3][0] = 1;
    grid[2][0][0] = 0;
    grid[2][1][0] = 0;
    grid[2][2][0] = 0;
    grid[2][3][0] = 0;
    grid[3][0][0] = 0;
    grid[3][1][0] = 0;
    grid[3][2][0] = 0;
    grid[3][3][0] = 0;
    //////////////////////////////////Orientation1
    grid[0][0][1] = 0;
    grid[0][1][1] = 1;
    grid[0][2][1] = 0;
    grid[0][3][1] = 0;
    grid[1][0][1] = 0;
    grid[1][1][1] = 1;
    grid[1][2][1] = 0;
    grid[1][3][1] = 0;
    grid[2][0][1] = 0;
    grid[2][1][1] = 1;
    grid[2][2][1] = 0;
    grid[2][3][1] = 0;
    grid[3][0][1] = 0;
    grid[3][1][1] = 1;
    grid[3][2][1] = 0;
    grid[3][3][1] = 0;
    //////////////////////////////////Orientation2
    grid[0][0][2] = 0;
    grid[0][1][2] = 0;
    grid[0][2][2] = 0;
    grid[0][3][2] = 0;
    grid[1][0][2] = 1;
    grid[1][1][2] = 1;
    grid[1][2][2] = 1;
    grid[1][3][2] = 1;
    grid[2][0][2] = 0;
    grid[2][1][2] = 0;
    grid[2][2][2] = 0;
    grid[2][3][2] = 0;
    grid[3][0][2] = 0;
    grid[3][1][2] = 0;
    grid[3][2][2] = 0;
    grid[3][3][2] = 0;
    //////////////////////////////////Orientation3
    grid[0][0][3] = 0;
    grid[0][1][3] = 1;
    grid[0][2][3] = 0;
    grid[0][3][3] = 0;
    grid[1][0][3] = 0;
    grid[1][1][3] = 1;
    grid[1][2][3] = 0;
    grid[1][3][3] = 0;
    grid[2][0][3] = 0;
    grid[2][1][3] = 1;
    grid[2][2][3] = 0;
    grid[2][3][3] = 0;
    grid[3][0][3] = 0;
    grid[3][1][3] = 1;
    grid[3][2][3] = 0;
    grid[3][3][3] = 0;
}
O_Piece ::O_Piece ()
{
    type=PIECE_O;
    grid[0][0][0] = 1;
    grid[0][1][0] = 1;
    grid[0][2][0] = 0;
    grid[0][3][0] = 0;
    grid[1][0][0] = 1;
    grid[1][1][0] = 1;
    grid[1][2][0] = 0;
    grid[1][3][0] = 0;
    grid[2][0][0] = 0;
    grid[2][1][0] = 0;
    grid[2][2][0] = 0;
    grid[2][3][0] = 0;
    grid[3][0][0] = 0;
    grid[3][1][0] = 0;
    grid[3][2][0] = 0;
    grid[3][3][0] = 0;
    
    //////////////////////////////////Orientation1
    grid[0][0][1] = 1;
    grid[0][1][1] = 1;
    grid[0][2][1] = 0;
    grid[0][3][1] = 0;
    grid[1][0][1] = 1;
    grid[1][1][1] = 1;
    grid[1][2][1] = 0;
    grid[1][3][1] = 0;
    grid[2][0][1] = 0;
    grid[2][1][1] = 0;
    grid[2][2][1] = 0;
    grid[2][3][1] = 0;
    grid[3][0][1] = 0;
    grid[3][1][1] = 0;
    grid[3][2][1] = 0;
    grid[3][3][1] = 0;
    //////////////////////////////////Orientation2
    grid[0][0][2] = 1;
    grid[0][1][2] = 1;
    grid[0][2][2] = 0;
    grid[0][3][2] = 0;
    grid[1][0][2] = 1;
    grid[1][1][2] = 1;
    grid[1][2][2] = 0;
    grid[1][3][2] = 0;
    grid[2][0][2] = 0;
    grid[2][1][2] = 0;
    grid[2][2][2] = 0;
    grid[2][3][2] = 0;
    grid[3][0][2] = 0;
    grid[3][1][2] = 0;
    grid[3][2][2] = 0;
    grid[3][3][2] = 0;
    //////////////////////////////////Orientation3
    grid[0][0][3] = 1;
    grid[0][1][3] = 1;
    grid[0][2][3] = 0;
    grid[0][3][3] = 0;
    grid[1][0][3] = 1;
    grid[1][1][3] = 1;
    grid[1][2][3] = 0;
    grid[1][3][3] = 0;
    grid[2][0][3] = 0;
    grid[2][1][3] = 0;
    grid[2][2][3] = 0;
    grid[2][3][3] = 0;
    grid[3][0][3] = 0;
    grid[3][1][3] = 0;
    grid[3][2][3] = 0;
    grid[3][3][3] = 0;
}
VaporBomb_Piece ::VaporBomb_Piece ()
{
    type=PIECE_VAPOR;
    grid[0][0][0] = 0;
    grid[0][1][0] = 1;
    grid[0][2][0] = 1;
    grid[0][3][0] = 0;
    grid[1][0][0] = 0;
    grid[1][1][0] = 0;
    grid[1][2][0] = 0;
    grid[1][3][0] = 0;
    grid[2][0][0] = 0;
    grid[2][1][0] = 0;
    grid[2][2][0] = 0;
    grid[2][3][0] = 0;
    grid[3][0][0] = 0;
    grid[3][1][0] = 0;
    grid[3][2][0] = 0;
    grid[3][3][0] = 0;
    
    //////////////////////////////////Orientation1
    grid[0][0][1] = 0;
    grid[0][1][1] = 1;
    grid[0][2][1] = 1;
    grid[0][3][1] = 0;
    grid[1][0][1] = 0;
    grid[1][1][1] = 0;
    grid[1][2][1] = 0;
    grid[1][3][1] = 0;
    grid[2][0][1] = 0;
    grid[2][1][1] = 0;
    grid[2][2][1] = 0;
    grid[2][3][1] = 0;
    grid[3][0][1] = 0;
    grid[3][1][1] = 0;
    grid[3][2][1] = 0;
    grid[3][3][1] = 0;
    //////////////////////////////////Orientation2
    grid[0][0][2] = 0;
    grid[0][1][2] = 1;
    grid[0][2][2] = 1;
    grid[0][3][2] = 0;
    grid[1][0][2] = 0;
    grid[1][1][2] = 0;
    grid[1][2][2] = 0;
    grid[1][3][2] = 0;
    grid[2][0][2] = 0;
    grid[2][1][2] = 0;
    grid[2][2][2] = 0;
    grid[2][3][2] = 0;
    grid[3][0][2] = 0;
    grid[3][1][2] = 0;
    grid[3][2][2] = 0;
    grid[3][3][2] = 0;
    //////////////////////////////////Orientation3
    grid[0][0][3] = 0;
    grid[0][1][3] = 1;
    grid[0][2][3] = 1;
    grid[0][3][3] = 0;
    grid[1][0][3] = 0;
    grid[1][1][3] = 0;
    grid[1][2][3] = 0;
    grid[1][3][3] = 0;
    grid[2][0][3] = 0;
    grid[2][1][3] = 0;
    grid[2][2][3] = 0;
    grid[2][3][3] = 0;
    grid[3][0][3] = 0;
    grid[3][1][3] = 0;
    grid[3][2][3] = 0;
    grid[3][3][3] = 0;
}
FoamBomb_Piece ::FoamBomb_Piece ()
{
    type=PIECE_FOAM;
    grid[0][0][0] = 0;
    grid[0][1][0] = 0;
    grid[0][2][0] = 0;
    grid[0][3][0] = 0;
    grid[1][0][0] = 0;
    grid[1][1][0] = 1;
    grid[1][2][0] = 0;
    grid[1][3][0] = 0;
    grid[2][0][0] = 0;
    grid[2][1][0] = 0;
    grid[2][2][0] = 0;
    grid[2][3][0] = 0;
    grid[3][0][0] = 0;
    grid[3][1][0] = 0;
    grid[3][2][0] = 0;
    grid[3][3][0] = 0;
    
    //////////////////////////////////Orientation1
    grid[0][0][1] = 0;
    grid[0][1][1] = 0;
    grid[0][2][1] = 0;
    grid[0][3][1] = 0;
    grid[1][0][1] = 0;
    grid[1][1][1] = 1;
    grid[1][2][1] = 0;
    grid[1][3][1] = 0;
    grid[2][0][1] = 0;
    grid[2][1][1] = 0;
    grid[2][2][1] = 0;
    grid[2][3][1] = 0;
    grid[3][0][1] = 0;
    grid[3][1][1] = 0;
    grid[3][2][1] = 0;
    grid[3][3][1] = 0;
    //////////////////////////////////Orientation2
    grid[0][0][2] = 0;
    grid[0][1][2] = 0;
    grid[0][2][2] = 0;
    grid[0][3][2] = 0;
    grid[1][0][2] = 0;
    grid[1][1][2] = 1;
    grid[1][2][2] = 0;
    grid[1][3][2] = 0;
    grid[2][0][2] = 0;
    grid[2][1][2] = 0;
    grid[2][2][2] = 0;
    grid[2][3][2] = 0;
    grid[3][0][2] = 0;
    grid[3][1][2] = 0;
    grid[3][2][2] = 0;
    grid[3][3][2] = 0;
    //////////////////////////////////Orientation3
    grid[0][0][3] = 0;
    grid[0][1][3] = 0;
    grid[0][2][3] = 0;
    grid[0][3][3] = 0;
    grid[1][0][3] = 0;
    grid[1][1][3] = 1;
    grid[1][2][3] = 0;
    grid[1][3][3] = 0;
    grid[2][0][3] = 0;
    grid[2][1][3] = 0;
    grid[2][2][3] = 0;
    grid[2][3][3] = 0;
    grid[3][0][3] = 0;
    grid[3][1][3] = 0;
    grid[3][2][3] = 0;
    grid[3][3][3] = 0;
}
L_Piece ::L_Piece ()
{
    type=PIECE_L;
    grid[0][0][0] = 0;
    grid[0][1][0] = 0;
    grid[0][2][0] = 0;
    grid[0][3][0] = 0;
    grid[1][0][0] = 1;
    grid[1][1][0] = 1;
    grid[1][2][0] = 1;
    grid[1][3][0] = 0;
    grid[2][0][0] = 1;
    grid[2][1][0] = 0;
    grid[2][2][0] = 0;
    grid[2][3][0] = 0;
    grid[3][0][0] = 0;
    grid[3][1][0] = 0;
    grid[3][2][0] = 0;
    grid[3][3][0] = 0;
    
    //////////////////////////////////Orientation1
    grid[0][0][1] = 0;
    grid[0][1][1] = 1;
    grid[0][2][1] = 1;
    grid[0][3][1] = 0;
    grid[1][0][1] = 0;
    grid[1][1][1] = 0;
    grid[1][2][1] = 1;
    grid[1][3][1] = 0;
    grid[2][0][1] = 0;
    grid[2][1][1] = 0;
    grid[2][2][1] = 1;
    grid[2][3][1] = 0;
    grid[3][0][1] = 0;
    grid[3][1][1] = 0;
    grid[3][2][1] = 0;
    grid[3][3][1] = 0;
    //////////////////////////////////Orientation2
    grid[0][0][2] = 0;
    grid[0][1][2] = 0;
    grid[0][2][2] = 0;
    grid[0][3][2] = 0;
    grid[1][0][2] = 0;
    grid[1][1][2] = 0;
    grid[1][2][2] = 1;
    grid[1][3][2] = 0;
    grid[2][0][2] = 1;
    grid[2][1][2] = 1;
    grid[2][2][2] = 1;
    grid[2][3][2] = 0;
    grid[3][0][2] = 0;
    grid[3][1][2] = 0;
    grid[3][2][2] = 0;
    grid[3][3][2] = 0;
    //////////////////////////////////Orientation3
    grid[0][0][3] = 0;
    grid[0][1][3] = 0;
    grid[0][2][3] = 0;
    grid[0][3][3] = 0;
    grid[1][0][3] = 0;
    grid[1][1][3] = 1;
    grid[1][2][3] = 0;
    grid[1][3][3] = 0;
    grid[2][0][3] = 0;
    grid[2][1][3] = 1;
    grid[2][2][3] = 0;
    grid[2][3][3] = 0;
    grid[3][0][3] = 0;
    grid[3][1][3] = 1;
    grid[3][2][3] = 1;
    grid[3][3][3] = 0;
}
J_Piece ::J_Piece ()
{
    type=PIECE_J;
    grid[0][0][0] = 0;
    grid[0][1][0] = 0;
    grid[0][2][0] = 0;
    grid[0][3][0] = 0;
    grid[1][0][0] = 0;
    grid[1][1][0] = 1;
    grid[1][2][0] = 1;
    grid[1][3][0] = 1;
    grid[2][0][0] = 0;
    grid[2][1][0] = 0;
    grid[2][2][0] = 0;
    grid[2][3][0] = 1;
    grid[3][0][0] = 0;
    grid[3][1][0] = 0;
    grid[3][2][0] = 0;
    grid[3][3][0] = 0;
    
    //////////////////////////////////Orientation1
    grid[0][0][1] = 0;
    grid[0][1][1] = 0;
    grid[0][2][1] = 0;
    grid[0][3][1] = 0;
    grid[1][0][1] = 0;
    grid[1][1][1] = 0;
    grid[1][2][1] = 1;
    grid[1][3][1] = 0;
    grid[2][0][1] = 0;
    grid[2][1][1] = 0;
    grid[2][2][1] = 1;
    grid[2][3][1] = 0;
    grid[3][0][1] = 0;
    grid[3][1][1] = 1;
    grid[3][2][1] = 1;
    grid[3][3][1] = 0;
    //////////////////////////////////Orientation2
    grid[0][0][2] = 0;
    grid[0][1][2] = 0;
    grid[0][2][2] = 0;
    grid[0][3][2] = 0;
    grid[1][0][2] = 0;
    grid[1][1][2] = 1;
    grid[1][2][2] = 0;
    grid[1][3][2] = 0;
    grid[2][0][2] = 0;
    grid[2][1][2] = 1;
    grid[2][2][2] = 1;
    grid[2][3][2] = 1;
    grid[3][0][2] = 0;
    grid[3][1][2] = 0;
    grid[3][2][2] = 0;
    grid[3][3][2] = 0;
    //////////////////////////////////Orientation3
    grid[0][0][3] = 0;
    grid[0][1][3] = 1;
    grid[0][2][3] = 1;
    grid[0][3][3] = 0;
    grid[1][0][3] = 0;
    grid[1][1][3] = 1;
    grid[1][2][3] = 0;
    grid[1][3][3] = 0;
    grid[2][0][3] = 0;
    grid[2][1][3] = 1;
    grid[2][2][3] = 0;
    grid[2][3][3] = 0;
    grid[3][0][3] = 0;
    grid[3][1][3] = 0;
    grid[3][2][3] = 0;
    grid[3][3][3] = 0;
}
Crazy_Piece::Crazy_Piece()
{
    type=PIECE_CRAZY;
    grid[0][0][0] = 1;
    grid[0][1][0] = 0;
    grid[0][2][0] = 0;
    grid[0][3][0] = 1;
    grid[1][0][0] = 0;
    grid[1][1][0] = 1;
    grid[1][2][0] = 1;
    grid[1][3][0] = 0;
    grid[2][0][0] = 0;
    grid[2][1][0] = 0;
    grid[2][2][0] = 0;
    grid[2][3][0] = 0;
    grid[3][0][0] = 0;
    grid[3][1][0] = 0;
    grid[3][2][0] = 0;
    grid[3][3][0] = 0;
    
    //////////////////////////////////Orientation1
    grid[0][0][1] = 0;
    grid[0][1][1] = 0;
    grid[0][2][1] = 0;
    grid[0][3][1] = 1;
    grid[1][0][1] = 0;
    grid[1][1][1] = 0;
    grid[1][2][1] = 1;
    grid[1][3][1] = 0;
    grid[2][0][1] = 0;
    grid[2][1][1] = 0;
    grid[2][2][1] = 1;
    grid[2][3][1] = 0;
    grid[3][0][1] = 0;
    grid[3][1][1] = 0;
    grid[3][2][1] = 0;
    grid[3][3][1] = 1;
    //////////////////////////////////Orientation2
    grid[0][0][2] = 0;
    grid[0][1][2] = 0;
    grid[0][2][2] = 0;
    grid[0][3][2] = 0;
    grid[1][0][2] = 0;
    grid[1][1][2] = 0;
    grid[1][2][2] = 0;
    grid[1][3][2] = 0;
    grid[2][0][2] = 0;
    grid[2][1][2] = 1;
    grid[2][2][2] = 1;
    grid[2][3][2] = 0;
    grid[3][0][2] = 1;
    grid[3][1][2] = 0;
    grid[3][2][2] = 0;
    grid[3][3][2] = 1;
    //////////////////////////////////Orientation3
    grid[0][0][3] = 1;
    grid[0][1][3] = 0;
    grid[0][2][3] = 0;
    grid[0][3][3] = 0;
    grid[1][0][3] = 0;
    grid[1][1][3] = 1;
    grid[1][2][3] = 0;
    grid[1][3][3] = 0;
    grid[2][0][3] = 0;
    grid[2][1][3] = 1;
    grid[2][2][3] = 0;
    grid[2][3][3] = 0;
    grid[3][0][3] = 1;
    grid[3][1][3] = 0;
    grid[3][2][3] = 0;
    grid[3][3][3] = 0;
}
S_Piece ::S_Piece ()
{
    type=PIECE_S;
    grid[0][0][0] = 0;
    grid[0][1][0] = 0;
    grid[0][2][0] = 0;
    grid[0][3][0] = 0;
    grid[1][0][0] = 0;
    grid[1][1][0] = 1;
    grid[1][2][0] = 1;
    grid[1][3][0] = 0;
    grid[2][0][0] = 1;
    grid[2][1][0] = 1;
    grid[2][2][0] = 0;
    grid[2][3][0] = 0;
    grid[3][0][0] = 0;
    grid[3][1][0] = 0;
    grid[3][2][0] = 0;
    grid[3][3][0] = 0;
    
    //////////////////////////////////Orientation1
    grid[0][0][1] = 0;
    grid[0][1][1] = 1;
    grid[0][2][1] = 0;
    grid[0][3][1] = 0;
    grid[1][0][1] = 0;
    grid[1][1][1] = 1;
    grid[1][2][1] = 1;
    grid[1][3][1] = 0;
    grid[2][0][1] = 0;
    grid[2][1][1] = 0;
    grid[2][2][1] = 1;
    grid[2][3][1] = 0;
    grid[3][0][1] = 0;
    grid[3][1][1] = 0;
    grid[3][2][1] = 0;
    grid[3][3][1] = 0;
    //////////////////////////////////Orientation2
    grid[0][0][2] = 0;
    grid[0][1][2] = 0;
    grid[0][2][2] = 0;
    grid[0][3][2] = 0;
    grid[1][0][2] = 0;
    grid[1][1][2] = 1;
    grid[1][2][2] = 1;
    grid[1][3][2] = 0;
    grid[2][0][2] = 1;
    grid[2][1][2] = 1;
    grid[2][2][2] = 0;
    grid[2][3][2] = 0;
    grid[3][0][2] = 0;
    grid[3][1][2] = 0;
    grid[3][2][2] = 0;
    grid[3][3][2] = 0;
    //////////////////////////////////Orientation3
    grid[0][0][3] = 0;
    grid[0][1][3] = 1;
    grid[0][2][3] = 0;
    grid[0][3][3] = 0;
    grid[1][0][3] = 0;
    grid[1][1][3] = 1;
    grid[1][2][3] = 1;
    grid[1][3][3] = 0;
    grid[2][0][3] = 0;
    grid[2][1][3] = 0;
    grid[2][2][3] = 1;
    grid[2][3][3] = 0;
    grid[3][0][3] = 0;
    grid[3][1][3] = 0;
    grid[3][2][3] = 0;
    grid[3][3][3] = 0;
}
Z_Piece ::Z_Piece ()
{
    type=PIECE_Z;
    grid[0][0][0] = 0;
    grid[0][1][0] = 0;
    grid[0][2][0] = 0;
    grid[0][3][0] = 0;
    grid[1][0][0] = 1;
    grid[1][1][0] = 1;
    grid[1][2][0] = 0;
    grid[1][3][0] = 0;
    grid[2][0][0] = 0;
    grid[2][1][0] = 1;
    grid[2][2][0] = 1;
    grid[2][3][0] = 0;
    grid[3][0][0] = 0;
    grid[3][1][0] = 0;
    grid[3][2][0] = 0;
    grid[3][3][0] = 0;
    
    //////////////////////////////////Orientation1
    grid[0][0][1] = 0;
    grid[0][1][1] = 0;
    grid[0][2][1] = 1;
    grid[0][3][1] = 0;
    grid[1][0][1] = 0;
    grid[1][1][1] = 1;
    grid[1][2][1] = 1;
    grid[1][3][1] = 0;
    grid[2][0][1] = 0;
    grid[2][1][1] = 1;
    grid[2][2][1] = 0;
    grid[2][3][1] = 0;
    grid[3][0][1] = 0;
    grid[3][1][1] = 0;
    grid[3][2][1] = 0;
    grid[3][3][1] = 0;
    //////////////////////////////////Orientation2
    grid[0][0][2] = 0;
    grid[0][1][2] = 0;
    grid[0][2][2] = 0;
    grid[0][3][2] = 0;
    grid[1][0][2] = 1;
    grid[1][1][2] = 1;
    grid[1][2][2] = 0;
    grid[1][3][2] = 0;
    grid[2][0][2] = 0;
    grid[2][1][2] = 1;
    grid[2][2][2] = 1;
    grid[2][3][2] = 0;
    grid[3][0][2] = 0;
    grid[3][1][2] = 0;
    grid[3][2][2] = 0;
    grid[3][3][2] = 0;
    //////////////////////////////////Orientation3
    grid[0][0][3] = 0;
    grid[0][1][3] = 0;
    grid[0][2][3] = 1;
    grid[0][3][3] = 0;
    grid[1][0][3] = 0;
    grid[1][1][3] = 1;
    grid[1][2][3] = 1;
    grid[1][3][3] = 0;
    grid[2][0][3] = 0;
    grid[2][1][3] = 1;
    grid[2][2][3] = 0;
    grid[2][3][3] = 0;
    grid[3][0][3] = 0;
    grid[3][1][3] = 0;
    grid[3][2][3] = 0;
    grid[3][3][3] = 0;
}

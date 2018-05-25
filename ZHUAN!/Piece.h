#ifndef PIECE_INCLUDED
#define PIECE_INCLUDED

class Screen;
enum PieceType {
    PIECE_I, PIECE_L, PIECE_J, PIECE_T, PIECE_O, PIECE_S, PIECE_Z,
    PIECE_VAPOR, PIECE_FOAM, PIECE_CRAZY, NUM_PIECE_TYPES
};

class Shape
{
private:
    int xCoord;
    int yCoord;
    int m_rotation;
public:
    Shape();
    virtual~Shape();
    
    ///////////////////////////////////////////Screen display
    void DisplayNextPiece(Screen& s);
    void DisplayCurrentPiece(Screen& s);
    
    /////////////////////////////////////////Move and Shift
    void MovePiece(char move);
    void UpdateRotation(int NewRotation);
    
    ////////////////Constant functions
    bool PieceExistAt(int row,int col,int rotation) const;
    int rotation()const;
    char getType() const;
    void getCoord(int &x,int &y,int &z) const;
    
protected:
    bool grid[4][4][4];//[row][col][rotation]
    PieceType type;
    
};

class FoamBomb_Piece : public Shape
{
public:
    FoamBomb_Piece();
    ~FoamBomb_Piece(){};
};

class VaporBomb_Piece : public Shape
{
public:
    VaporBomb_Piece();
    ~VaporBomb_Piece(){};
};
class S_Piece : public Shape
{
public:
    S_Piece();
    ~S_Piece(){};
    
};
class T_Piece : public Shape
{
public:
    T_Piece();
    ~T_Piece(){};
    
};
class I_Piece : public Shape
{
public:
    I_Piece();
    ~I_Piece(){};
    
};
class O_Piece : public Shape
{
public:
    O_Piece();
    ~O_Piece(){};
    
};
class L_Piece : public Shape
{
public:
    L_Piece();
    ~L_Piece(){};
    
};
class J_Piece : public Shape
{
public:
    J_Piece();
    ~J_Piece(){};
    
};
class Z_Piece : public Shape
{
public:
    Z_Piece();
    ~Z_Piece(){};
    
};
class Crazy_Piece : public Shape
{
public:
    Crazy_Piece();
    ~Crazy_Piece(){};
    
};



PieceType chooseRandomPieceType();

#endif // PIECE_INCLUDED

#ifndef WELL_INCLUDED
#define WELL_INCLUDED

class Screen;
class Shape;
class Well
{
public:
    Well();
    ~Well();
    void ClearWholeWell();//Clear inside of the well at each beginning of a level
    
    //////////////////////////Display to Screen
    void DisplayStatus(Screen&m_screen);//Display score
    void DisplayWell(Screen&screen);
    void DisplayInitialPieces(Screen&screen);
    
    /////////////////////////Check and Get Functions
    char getPieceType() const;
    int level() const;
    int rowsLeft() const;
    bool CharExistsInMaze(int column, int row, char find) const;
    
    /////////////////////////////////////////Move
    bool Move(Screen&screen, char move);
    void ClearTempPiecesOnScreen(Screen&screen);
    
    
    //////////////////////////////////When a piece touch the ground
    void UpdateShape(Screen&screen);
    bool ifFilled()const;
    void FullRowCheck(Screen&screen);
    
    void PlainCopyInWell(char symbol);
    
    ///////////////////////////////////SPECIAL PIECES
    void foamBombUpdateWell();
    void vaporBombUpdateWell();
    
    /////////////////////////////Check if movable
    bool BottomHasStuff() const;
    
    ///////////////////////////////////////////
    void levelUP();
    
private:
    //////////////////////Dynamically Allocate new current Shape and next Shape
    void getCShape();
    void getNShape();
    ///////////////////////////////////SPECIAL PIECES
    void foamDetect(int row,int col);
    bool OutFoamBoundary(int row, int col) const;
    
    /////////////////////////////Check if movable
    bool LeftHasStuff()const;
    bool RightHasStuff()const;
    
    //////////////////////////////////When a piece touch the ground
    void dropDown(int deleteThisRow);
    
    ////////////////////////////////////////Roll
    bool roll();
    
    
    Shape * m_currPiece;
    Shape * m_nextPiece;
    
    int m_score;
    int m_rowsLeft;
    int  m_level;
    char maze[19][12];
    
};

#endif // WELL_INCLUDED

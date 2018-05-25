#include "Game.h"


int main()
{
    Game g;
    g.play();
}

#include "Piece.h"
#include <random>

PieceType chooseRandomPieceType()
{
    static std::random_device aRandomDevice;
    static std::default_random_engine generator(aRandomDevice());
    std::uniform_int_distribution<> distro(0, NUM_PIECE_TYPES-1);
    return static_cast<PieceType>(distro(generator));
}

#include "PzBoard.h"
#include "PzPiece.h"

bool PzBoard::AddPiece(const std::vector<int>& points)
{
    int cnt = points.size();
    if (cnt % 2 != 0) {
        return false;
    }

    PzPiece pc;
    pc.SetPoints(points);
    if (!m_pieceGroup.CheckAndSetPiece(pc)) {
        return false;
    }
    m_pieces.push_back(pc);

    this->SwitchBitBoard(points);
    return true;
}


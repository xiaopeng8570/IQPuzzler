#pragma once

#include <vector>
#include "PzPoint.h"
#include "PzPieceGroup.h"

class PzBoard
{
public:
    bool AddPiece(const std::vector<int>& points);
    const std::vector<PzPiece> GetPieces() const {
        return m_pieces;
    }
    const std::vector<PzPoint> GetPoints() const {
        return m_board;
    }
    virtual bool IsCover(const PzPoint& p) {
        return false;
    }
    virtual bool Solve() {
        return false;
    }
protected:
    virtual void SwitchBitBoard(const std::vector<int>& points) = 0;
protected:
    std::vector<PzPiece>  m_pieces;
    std::vector<PzPoint>  m_board;
    PzPieceGroup    m_pieceGroup;
};


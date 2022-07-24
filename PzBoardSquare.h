#pragma once
#include <string>
#include "PzBoard.h"
#include "PzPoint.h"
#include "PzPieceGroup.h"

class PzBoardSquare :
    public PzBoard
{
public:
    PzBoardSquare() {
        InitBoard();
    }
    virtual bool IsCover(const PzPoint& p) {
        return m_bitBoard[p.x][p.y] == 1;
    }
    virtual bool Solve();
    //bool AddPiece(const std::string& name, int x, int y);
protected:
    virtual void SwitchBitBoard(const std::vector<int>& points);
private:
    void InitBoard();

    bool TestNextPiece();
    bool TestNextStyle(PzPiece& pc, uint32_t unusePos);
    bool TestPosition(PzPointGroup pg, int x, int y, uint32_t unusePos);
    bool HaveLittleSpace();
    void CalcLittleSpace(int i, int j, int& n);
    void ClearLittleSpace();
private:
    int m_bitBoard[11][5];
};


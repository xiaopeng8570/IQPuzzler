#pragma once

#include "PzBoard.h"

class PzSolveThread
{
public:
    PzBoard* GetBoard() { return m_pBoard; }
    void SetBoard(PzBoard* pBoard);
    void Solve();
    void SolveInThread();
private:
    PzBoard* m_pBoard = nullptr;

};


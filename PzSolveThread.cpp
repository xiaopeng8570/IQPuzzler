#include "PzSolveThread.h"
#include <thread>

void PzSolveThread::SetBoard(PzBoard* pBoard)
{
    m_pBoard = pBoard;
}

void ThrHandle(PzSolveThread* pThread)
{
    pThread->SolveInThread();
}

void PzSolveThread::SolveInThread()
{
    if (m_pBoard != nullptr) {
        m_pBoard->Solve();
    }
}

void PzSolveThread::Solve()
{
    std::thread thr(ThrHandle, this);
    thr.detach();

}


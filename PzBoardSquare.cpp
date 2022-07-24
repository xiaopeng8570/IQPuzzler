#include "PzBoardSquare.h"

extern PzPieceGroup gPieceGroup;

void PzBoardSquare::InitBoard()
{
    m_board.clear();
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 5; j++) {
            m_bitBoard[i][j] = 0;

            PzPoint p(i, j);
            m_board.push_back(p);
        }
    }
    m_pieceGroup = gPieceGroup;
}

void PzBoardSquare::SwitchBitBoard(const std::vector<int>& points)
{
    for (uint32_t i = 0; i < points.size(); i += 2) {
        int x = points[i];
        int y = points[i + 1];
        if (x < 0 || x > 11 || y < 0 || y > 5) {
            return;
        }
        if (m_bitBoard[x][y] == 1) {
            return;
        }
        else {
            m_bitBoard[x][y] = 1;
        }
    }
}

void PzBoardSquare::CalcLittleSpace(int i, int j, int& n) {
    int x, y;
    x = i - 1; y = j; if (x >= 0 && m_bitBoard[x][y] == 0) { m_bitBoard[x][y] = 101; n++; CalcLittleSpace(x, y, n); }
    x = i + 1; y = j; if (x < 11 && m_bitBoard[x][y] == 0) { m_bitBoard[x][y] = 101; n++; CalcLittleSpace(x, y, n); }
    x = i; y = j - 1; if (y >= 0 && m_bitBoard[x][y] == 0) { m_bitBoard[x][y] = 101; n++; CalcLittleSpace(x, y, n); }
    x = i; y = j + 1; if (y < 5 && m_bitBoard[x][y] == 0) { m_bitBoard[x][y] = 101; n++; CalcLittleSpace(x, y, n); }
}
void PzBoardSquare::ClearLittleSpace() {
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 5; j++) {
            if (m_bitBoard[i][j] == 101) {
                m_bitBoard[i][j] = 0;
            }
        }
    }
}
bool PzBoardSquare::HaveLittleSpace()
{
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 5; j++) {
            if (m_bitBoard[i][j] == 0) {
                int n = 1;
                m_bitBoard[i][j] = 101;
                CalcLittleSpace(i, j, n);
                if (n < 3) {
                    ClearLittleSpace();
                    return true;
                }
            }
        }
    }
    ClearLittleSpace();
    return false;
}

bool PzBoardSquare::TestPosition(PzPointGroup pg, int x, int y, uint32_t unusePos)
{
    std::vector<PzPoint> points = pg.GetPoints();

    std::vector<int> ps;
    for (auto p = points.begin(); p != points.end(); p++) {
        int px = p->x + x;
        int py = p->y + y;
        if (px >= 11 || py >= 5) {
            return false;
        }
        if (m_bitBoard[px][py] == 1) {
            return false;
        }
        ps.push_back(px);
        ps.push_back(py);
    }

    AddPiece(ps);
    if (!HaveLittleSpace() && TestNextPiece()) {
        return true;
    }
    m_pieceGroup.UnsetPieceMatch(unusePos);
    for (auto p = points.begin(); p != points.end(); p++) {
        int px = p->x + x;
        int py = p->y + y;
        m_bitBoard[px][py] = false;
    }
    m_pieces.pop_back();
    return false;
}

bool PzBoardSquare::TestNextStyle(PzPiece& pc, uint32_t unusePos)
{
    std::vector<PzPointGroup> styles = pc.GetStyles();
    for (auto sit = styles.begin(); sit != styles.end(); sit++) {
        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 5; j++) {
                if (TestPosition(*sit, i, j, unusePos)) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool PzBoardSquare::TestNextPiece()
{
    uint32_t unusePos = 0;
    PzPiece pc = m_pieceGroup.GetUnusePiece(unusePos);
    if (pc.IsInvalid()) {
        return true;
    }
    return TestNextStyle(pc, unusePos);
}

bool PzBoardSquare::Solve()
{
    return TestNextPiece();
}


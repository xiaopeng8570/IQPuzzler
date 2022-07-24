#pragma once

#include <vector>
#include "PzPiece.h"

class PzPieceGroup
{
public:
    void AddPiece(const PzPiece& pp) {
        PzPiece pc = pp;
        pc.InitStyle();
        m_pieces.push_back(pc);
        m_pcMatches.push_back(false);
    }
    bool CheckAndSetPiece(PzPiece& pp) {
        for (uint32_t i = 0; i < m_pieces.size(); i++) {
            if (m_pieces[i].Match(pp)) {
                pp.SetName(m_pieces[i].GetName());
                m_pcMatches[i] = true;
                return true;
            }
        }
        return false;
    }
    void SetPieceMatch(uint32_t unusePos) { m_pcMatches[unusePos] = true; }
    void UnsetPieceMatch(uint32_t unusePos) { m_pcMatches[unusePos] = false; }

    void BeginEnum() {
        m_dbgEnumIdx = 0;
        m_dbgPieceIdx = 0;
    }
    PzPointGroup EnumPointGroup() {
        m_dbgPieceIdx++;
        PzPointGroup pg = m_pieces[m_dbgEnumIdx].GetPointGroup(m_dbgPieceIdx);
        if (pg.IsError()) {
            m_dbgPieceIdx = 0;
            m_dbgEnumIdx++;
            if (m_dbgEnumIdx >= m_pieces.size()) {
                m_dbgEnumIdx = 0;
            }
            pg = m_pieces[m_dbgEnumIdx].GetPointGroup(m_dbgPieceIdx);
        }
        return pg;
    }
    PzPointGroup EnumGetPointGroup() {
        return m_pieces[m_dbgEnumIdx].GetPointGroup(m_dbgPieceIdx);
    }

    PzPiece GetUnusePiece(uint32_t &pos) {
        for (uint32_t i = 0; i < m_pcMatches.size(); i++) {
            if (!m_pcMatches[i]) {
                pos = i;
                return m_pieces[i];
            }
        }
        PzPiece p;
        return p;
    }
private:
    std::vector<PzPiece>  m_pieces;
    std::vector<bool>  m_pcMatches;

    uint32_t m_dbgEnumIdx = 0;
    uint32_t m_dbgPieceIdx = 0;
};


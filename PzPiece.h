#pragma once

#include <string>
#include <vector>
#include <stdarg.h>

#include "PzPoint.h"
#include "PzPointGroup.h"

class PzPiece
{
public:
    void Reset() {
        m_points.Reset();
        m_pointStyles.clear();
    }
    void SetName(const std::string& name) {
        m_name = name;
    }
    bool Match(const PzPiece& pc) {
        PzPointGroup pg = pc.m_points;
        if (m_points.GetPoints().size() != pg.GetPoints().size()) {
            return false;
        }
        pg.ReturnZero();
        for (auto p = m_pointStyles.begin(); p != m_pointStyles.end(); p++) {
            if (p->Overlap(pg)) {
                return true;
            }
        }
        return false;
    }
    void SetPoints(const std::vector<int>& points) {
        int cnt = points.size();
        if (cnt % 2 != 0) {
            return;
        }
        m_points.Reset();
        for (int i = 0; i < cnt; i += 2) {
            m_points.AddPoint(points[i], points[i + 1]);
        }
    }

    void InitStyle() {
        PzPointGroup pg = m_points;
        AppendStyle(pg.ReturnZero());
        AppendStyle(pg.Rotate());
        AppendStyle(pg.Rotate());
        AppendStyle(pg.Rotate());
        AppendStyle(pg.Mirror());
        AppendStyle(pg.Rotate());
        AppendStyle(pg.Rotate());
        AppendStyle(pg.Rotate());
    }
    void AppendStyle(const PzPointGroup& pg) {
        for (auto a = m_pointStyles.begin(); a != m_pointStyles.end(); a++) {
            if (a->Overlap(pg)) {
                return;
            }
        }
        m_pointStyles.push_back(pg);
    }

    PzPointGroup GetPointGroup(uint32_t idx) {
        if (idx >= m_pointStyles.size()) {
            PzPointGroup pg;
            return pg;
        }
        return m_pointStyles[idx];
    }

    std::vector<PzPoint> GetPoints() const { return m_points.GetPoints(); }
    std::string GetName() const { return m_name; }
    std::vector<PzPointGroup> GetStyles() const { return m_pointStyles; }

    bool IsInvalid() const { return m_points.IsError(); }
private:
    std::vector<PzPointGroup>  m_pointStyles;
    PzPointGroup m_points;
    std::string m_name;
};


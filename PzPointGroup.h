#pragma once

#include <vector>
#include "PzPoint.h"

class PzPointGroup
{
public:
    void Reset() {
        m_points.clear();
    }
    void AddPoint(int x, int y) {
        PzPoint p(x, y);
        m_points.push_back(p);
    }
    bool Overlap(const PzPointGroup& pg) {
        for (auto p = pg.m_points.begin(); p != pg.m_points.end(); p++) {
            bool f = false;
            for (auto tp = m_points.begin(); tp != m_points.end(); tp++) {
                if (tp->x == p->x && tp->y == p->y) {
                    f = true;
                    break;
                }
            }
            if (!f) {
                return false;
            }
        }
        return true;
    }
    const PzPointGroup& Rotate() {
        if (m_points.empty()) {
            return *this;
        }
        PzPoint pf = m_points[0];
        std::vector<PzPoint> nps;
        nps.push_back(pf);
        for (uint32_t i = 1; i < m_points.size(); i++) {
            PzPoint p(pf.x + m_points[i].y - pf.y,
                pf.y - m_points[i].x + pf.x);
            nps.push_back(p);
        }

        m_points = nps;
        return ReturnZero();
    }
    const PzPointGroup& Mirror() {
        for (auto p = m_points.begin(); p != m_points.end(); p++) {
            p->y = 0 - p->y;
        }
        return ReturnZero();
    }
    bool IsError() const {
        return m_points.empty();
    }
    std::vector<PzPoint> GetPoints() const {
        return m_points;
    }
    const PzPointGroup& ReturnZero() {
        if (m_points.empty()) {
            return *this;
        }
        PzPoint pf = m_points[0];
        int minx = pf.x;
        int miny = pf.y;
        for (auto p = m_points.begin(); p != m_points.end(); p++) {
            if (p->x < minx) {
                minx = p->x;
            }
            if (p->y < miny) {
                miny = p->y;
            }
        }
        if (minx == 0 && miny == 0) {
            return *this;
        }
        for (auto p = m_points.begin(); p != m_points.end(); p++) {
            p->x -= minx;
            p->y -= miny;
        }
        return *this;
    }
private:
    std::vector<PzPoint>  m_points;
};


#pragma once
class PzPoint
{
public:
    PzPoint(int x, int y) {
        this->x = x;
        this->y = y;
    }
    bool IsCover() {
        return cover;
    }
public:
    int x;
    int y;
    bool cover = false;
};


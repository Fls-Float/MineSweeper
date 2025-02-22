// MineSweeper.h
#pragma once
#include "FloatEngine.h"
#include <vector>

class MineSweeper : public Object {
public:
    bool firstClick;
    struct Cell {
        bool isMine = false;
        bool isRevealed = false;
        bool isFlagged = false;
        int adjacentMines = 0;
    };
    void RevealCell(int x, int y);
    void ToggleFlag(int x, int y);
    bool IsGameOver() const;
    bool IsGameWon() const;
    void onEnter() override;
    void onUpdate() override;
    void onRender() override;
    
private:
    int width, height, mineCount;
    std::vector<std::vector<Cell>> grid;
    bool gameOver = false;
    void ResetGame();
    void GenerateMines();
    void CalculateAdjacentMines();
    void RevealAdjacentCells(int x, int y);
    bool IsValidCell(int x, int y) const;
};
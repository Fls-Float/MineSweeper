#include "MineSweeper.h"
#include <algorithm>
#include <random>


void MineSweeper::GenerateMines() {
    const int maxMines = width * height - 9; // 至少保留3x3安全区
    mineCount = Clamp(mineCount, 1, maxMines);

    std::vector<std::pair<int, int>> positions;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            positions.emplace_back(x, y);
        }
    }

    std::shuffle(positions.begin(), positions.end(), std::mt19937(std::random_device()()));
    for (int i = 0; i < mineCount; ++i) {
        int x = positions[i].first;
        int y = positions[i].second;
        grid[y][x].isMine = true;
    }
}

void MineSweeper::CalculateAdjacentMines() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (grid[y][x].isMine) continue;

            int count = 0;
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    if (dx == 0 && dy == 0) continue;
                    int nx = x + dx, ny = y + dy;
                    if (IsValidCell(nx, ny) && grid[ny][nx].isMine) {
                        ++count;
                    }
                }
            }
            grid[y][x].adjacentMines = count;
        }
    }
}


void MineSweeper::RevealCell(int x, int y) {
    if (!IsValidCell(x, y) || grid[y][x].isRevealed || grid[y][x].isFlagged) return;
    if (!IsValidCell(x, y) ){
        DEBUG_LOG(LOG_DEBUG, TextFormat("(x,y) = (%d,%d)",x,y));
        return;
    }
    // 首次点击保证不是地雷
    if (firstClick) {
        firstClick = false;
        if (grid[y][x].isMine) {
            // 重新生成地雷直到当前位置安全
            do {
                GenerateMines();
            } while (grid[y][x].isMine);
            CalculateAdjacentMines();
        }
    }
    grid[y][x].isRevealed = true;
    if (grid[y][x].isMine) {
        gameOver = true;
        return;
    }

    if (grid[y][x].adjacentMines == 0) {
        RevealAdjacentCells(x, y);
    }
}

void MineSweeper::RevealAdjacentCells(int x, int y) {
    std::queue<std::pair<int, int>> cells;
    cells.emplace(x, y);

    while (!cells.empty()) {
        auto cx = cells.front().first;
        auto cy = cells.front().second;
        cells.pop();

        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                int nx = cx + dx, ny = cy + dy;
                if (IsValidCell(nx, ny) && !grid[ny][nx].isRevealed) {
                    grid[ny][nx].isRevealed = true;
                    if (grid[ny][nx].adjacentMines == 0) {
                        cells.emplace(nx, ny);
                    }
                }
            }
        }
    }
}

void MineSweeper::ToggleFlag(int x, int y) {
    if (IsValidCell(x, y) && !grid[y][x].isRevealed) {
        grid[y][x].isFlagged = !grid[y][x].isFlagged;
    }
}

bool MineSweeper::IsGameOver() const {
    return gameOver;
}

bool MineSweeper::IsGameWon() const {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (!grid[y][x].isMine && !grid[y][x].isRevealed) {
                return false;
            }
        }
    }
    return true;
}

bool MineSweeper::IsValidCell(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

void MineSweeper::onEnter()
{
    gameOver = false;
    width = height = 10;
    grid.resize(height);
    for (auto& row : grid) {
        row.resize(width);
    }
    mineCount = 10;
    firstClick = true;
    GenerateMines();
    CalculateAdjacentMines();
}

void MineSweeper::ResetGame() {
    // 重置基础状态
    gameOver = false;
    firstClick = true;

    // 重建网格
    grid = std::vector<std::vector<Cell>>(
        height,
        std::vector<Cell>(width)
    );

    // 重新初始化
    GenerateMines();
    CalculateAdjacentMines();

}
void MineSweeper::onUpdate() {
    if (gameOver || IsGameWon()) {
        if (F_Input::mb_pressed(F_Input::mouse_button_left)) {
            ResetGame();
        }
    }
    // Handle input and update game state
    if (F_Input::mb_pressed(F_Input::mouse_button_left)) {
        Vector2 mousePos = GetMousePosition();
        int x = static_cast<int>(mousePos.x) / 32;
        int y = static_cast<int>(mousePos.y) / 32;
        RevealCell(x, y);
    }

    if (F_Input::mb_pressed(F_Input::mouse_button_right)) {
        Vector2 mousePos = GetMousePosition();
        int x = static_cast<int>(mousePos.x) / 32;
        int y = static_cast<int>(mousePos.y) / 32;
        ToggleFlag(x, y);
    }
}

// 定义颜色常量
constexpr Color CELL_COLOR = { 40, 40, 40, 255 };
constexpr Color REVEALED_COLOR = { 180, 180, 180, 255 };

// 修改渲染逻辑
void MineSweeper::onRender() {
    const int cellSize = 32;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            FVec2 pos(x * cellSize, y * cellSize);

            if (grid[y][x].isRevealed) {
                if (grid[y][x].isMine) {
                    DrawRectangle(pos.x + 1, pos.y + 1, (float)cellSize - 2, (float)cellSize - 2, RED);
                }
                else {
                    DrawRectangle(pos.x + 1, pos.y + 1, (float)cellSize - 2, (float)cellSize - 2, REVEALED_COLOR);
                    // 数字颜色映射
                    const auto& count = grid[y][x].adjacentMines;
                    Color textColor = {
                        static_cast<uint8_t>(count * 28 % 255),
                        static_cast<uint8_t>(count * 57 % 255),
                        static_cast<uint8_t>(count * 86 % 255),
                        255
                    };

                    if (count > 0) {
                        std::string text(std::to_string(count).c_str());
                        F_Render::Draw_Text(text.c_str(),
                            pos.x + cellSize / 2 - 5,
                            pos.y + cellSize / 2 - 10,
                            0, 0, 0, 20, textColor);
                    }
                }
            }
            else {
                F_Render::Draw_Rectangle(pos.x + 1, pos.y + 1, cellSize - 2, cellSize - 2, CELL_COLOR);
                if (grid[y][x].isFlagged) {
                    F_Render::Draw_Text("!", pos.x+cellSize/2 - 5, pos.y+cellSize/2 - 10,0,0,0,20,RED);
                }
            }
        }
    }

    // 游戏状态提示居中显示
    if (IsGameOver() || IsGameWon()) {
        const char* msg = IsGameOver() ? "    G a m e O v e r !" : "    Y o u W i n !";
        Color color = IsGameOver() ? RED : GREEN;

        int textWidth = MeasureText(msg, 40);
        F_Render::Draw_Text(msg,
            (width * cellSize - textWidth) / 2,
            height * cellSize / 2 - 20,
            0, 0, 0, 40, color);
    }
}
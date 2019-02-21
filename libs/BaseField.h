#ifndef MINESWEEPER_BASEFIELD_H
#define MINESWEEPER_BASEFIELD_H

#include <random>
#include <ctime>
#include <cctype>
#include <string>

#include "Enums.h"


class BaseField {
private:

	int m_bombs;

	std::mt19937 m_rndgen;
	std::uniform_int_distribution<> m_randXPos;
	std::uniform_int_distribution<> m_randYPos;

protected:
	int m_height;
	int m_width;

	int **m_field;
	int **m_visibleField;
	bool **m_clicked;

	void showTile(const int x, const int y);
	void showTilesOnDeath(const int x, const int y);

	virtual void showPlayerTile(const int x, const int y) = 0;

	void shovelNums(const int x, const int y);
	Return flag(const int x, const int y);
	Return shovelWithMines(const int x, const int y);

public:
	BaseField(const int height, const int width)
			: m_height(height), m_width(width), m_randXPos(0, width - 1), m_randYPos(0, height - 1), m_rndgen(static_cast<unsigned int>(std::time(nullptr)))
	{
		m_field = new int*[m_height];
		for (int count = 0; count < m_height; ++count)
			m_field[count] = new int[m_width]; // these are our columns

		m_visibleField = new int*[m_height];
		for (int count = 0; count < m_height; ++count) {
			m_visibleField[count] = new int[m_width]; // these are our columns
		}

		m_clicked = new bool*[m_height];
		for (int count = 0; count < m_height; ++count) {
			m_clicked[count] = new bool[m_width]; // these are our columns
		}

		for(int x = 0; x < m_width; x++){
			for(int y = 0; y < m_height; y++) {
				m_visibleField[y][x] = CODE_LINE;
			}
		}
	}

	~BaseField();

	void setupField(const int bombs);

	Return click(const int x, const int y, Click type);

	int* operator[](const int row);

};

#endif
#ifndef _FIGURES_H_
#define _FIGURES_H_

#define FIGURE_COUNT 7
#define FIGURE_ROTATION 4
#define FIGURE_MATRIX_N 5
#define FIGURE_MATRIX_M 5
#define FIGURE_POSITION 2

class Figure
{
	public:
		Figure();
		~Figure();

		int GetBlockType( const int figure, const int rotation, const int x, const int y ) const;
		int GetXInitialPosition( const int figure, const int rotation ) const;
		int GetYInitialPosition( const int figure, const int rotation ) const;
};

#endif
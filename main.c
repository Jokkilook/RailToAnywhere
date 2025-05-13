#include <stdio.h>
#include "Draw.h"

int main() {

	//콘솔 인코딩 변경
	//SetConsoleOutputCP(65001);
	//SetConsoleCP(65001);

	srand(time(NULL));

	drawMainMenu();

	moveCursor(20,0);

	return 0;
}
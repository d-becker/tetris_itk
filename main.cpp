#include <iostream>

#include <graphics.hpp>

#include "BlockDrawingTool.h"
#include "ShapeDrawingTool.h"
#include "GameBoardDrawingTool.h"
#include "GameDrawingTool.h"
#include "GGameFlow.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    GGameFlow::init_game(400, 500, 8, 20);
    return 0;
}

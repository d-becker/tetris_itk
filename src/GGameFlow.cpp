#include "GGameFlow.h"
#include "graphics.hpp"

#include "BasicBlock.h"
#include "BasicBoard.h"
#include "DefaultGame.h"
#include "DefaultGameBoard.h"
#include "locking_shared_ptr.h"
#include "Shape.h"
#include "TetrominoI.h"
#include "TetrominoJ.h"
#include "TetrominoL.h"
#include "TetrominoO.h"
#include "TetrominoS.h"
#include "TetrominoT.h"
#include "TetrominoZ.h"

#include "BlockDrawingTool.h"
#include "ShapeDrawingTool.h"
#include "BoardDrawingTool.h"
#include "GameBoardDrawingTool.h"
#include "GameDrawingTool.h"
#include "OutputWrapper.h"

/* static */
std::shared_ptr<tetris::Game> GGameFlow::make_game(int height, int width)
{
  using namespace tetris;
  using namespace std;

  shared_ptr<Block> block = make_shared<BasicBlock>();

  block->setDrawingTool(make_shared<BlockDrawingTool>(RGB(255, 124, 0),
                                                      RGB(0, 0, 255)));
  shared_ptr<TetrominoO> tO = make_shared<TetrominoO>(block);
  tO->setDrawingTool(make_shared<ShapeDrawingTool>());

  block->setDrawingTool(make_shared<BlockDrawingTool>(RGB(69, 133, 154),
                                                      RGB(0, 0, 255)));
  shared_ptr<TetrominoT> tT = make_shared<TetrominoT>(block);
  tT->setDrawingTool(make_shared<ShapeDrawingTool>());

  block->setDrawingTool(make_shared<BlockDrawingTool>(RGB(255, 0, 0),
                                                      RGB(0, 0, 255)));
  shared_ptr<TetrominoL> tL = make_shared<TetrominoL>(block);
  tL->setDrawingTool(make_shared<ShapeDrawingTool>());

  block->setDrawingTool(make_shared<BlockDrawingTool>(RGB(49, 162, 49),
                                                      RGB(0, 0, 255)));
  shared_ptr<TetrominoJ> tJ = make_shared<TetrominoJ>(block);
  tJ->setDrawingTool(make_shared<ShapeDrawingTool>());

  block->setDrawingTool(make_shared<BlockDrawingTool>(RGB(124, 63, 124),
                                                      RGB(0, 0, 255)));
  shared_ptr<TetrominoI> tI = make_shared<TetrominoI>(block);
  tI->setDrawingTool(make_shared<ShapeDrawingTool>());

  block->setDrawingTool(make_shared<BlockDrawingTool>(RGB(255, 255, 255),
                                                      RGB(0, 0, 255)));
  shared_ptr<TetrominoS> tS = make_shared<TetrominoS>(block);
  tS->setDrawingTool(make_shared<ShapeDrawingTool>());

  block->setDrawingTool(make_shared<BlockDrawingTool>(RGB(255, 255, 0),
                                                      RGB(0, 0, 255)));
  shared_ptr<TetrominoZ> tZ = make_shared<TetrominoZ>(block);
  tZ->setDrawingTool(make_shared<ShapeDrawingTool>());
  vector<shared_ptr<Shape>> shapes {tO, tT, tL, tJ, tI, tS, tZ};

  shared_ptr<Board> board = make_shared<BasicBoard>(height, width);
  board->setDrawingTool(make_shared<BoardDrawingTool>(RGB(0, 0, 0)));

  shared_ptr<GameBoard> game_board = make_shared<DefaultGameBoard>(board);
  game_board->setDrawingTool(make_shared<GameBoardDrawingTool>());

  shared_ptr<Game> game = make_shared<DefaultGame>(game_board, shapes);
  game->setDrawingTool(make_shared<GameDrawingTool>());

  return game;
}

GGameFlow::GGameFlow(int window_width,
                     int window_height,
                     std::shared_ptr<tetris::Game> game,
                     unsigned int interval)
  : tetris::BasicGameFlow(game, interval),
    m_window_width(window_width),
    m_window_height(window_height),
    m_dci(OutputWrapper::instance(), calculate_block_size()),
    m_horizontal_offset(calculate_horizontal_offset())
{
  //ctor

  // Binding input.
  bindInput(genv::key_down, "move_down");
  bindInput(genv::key_left, "move_left");
  bindInput(genv::key_right, "move_right");
  bindInput('a', "rotate_left");
  bindInput('s', "rotate_right");
  bindInput(genv::key_up, "rotate_right"); //  Convenience for those that are used to Quadrapessel.
  bindInput(genv::key_space, "drop");
  bindInput('p', "toggle_paused");
  bindInput('r', "resume");
}

GGameFlow::~GGameFlow()
{
  //dtor
}


void GGameFlow::draw() {
  // TODO.
  using namespace genv;
  OutputWrapper& out_dev = m_dci.out_dev;
  out_dev.moveTo(0, 0);
  out_dev.colour(255, 255, 255);
  out_dev.box(m_window_width, m_window_height);

  out_dev.moveTo(m_horizontal_offset, 0);
  auto game = getGame();
  game->draw(m_dci);

  out_dev.refresh();
}

void GGameFlow::pause() {
  tetris::BasicGameFlow::pause();
}

int GGameFlow::calculate_block_size() const {
  auto board = getGame()->getGameBoard()->getBoard();
  int cols = board->getWidth();
  int rows = board->getHeight();

  int horizontal = m_window_width / cols; // Truncating to int.
  int vertical = m_window_height / rows; // Truncating to int.

  return horizontal < vertical ? horizontal : vertical;
}

int GGameFlow::calculate_horizontal_offset() const {
  auto board = getGame()->getGameBoard()->getBoard();
  int cols = board->getWidth();
  int block_size = m_dci.block_width;

  return (m_window_width - cols * block_size) / 2;
}

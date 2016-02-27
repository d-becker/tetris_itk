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

#include <iostream> ///////////////////////////////////////////////////////////////////////

#include "BlockDrawingTool.h"
#include "ShapeDrawingTool.h"
#include "BoardDrawingTool.h"
#include "GameBoardDrawingTool.h"
#include "GameDrawingTool.h"

/* static */
std::shared_ptr<tetris::Game> GGameFlow::make_game_flow(int height, int width)
{
  using namespace tetris;
  using namespace std;

  shared_ptr<Block> block = make_shared<BasicBlock>();
  block->setDrawingTool(make_shared<BlockDrawingTool>(RGB(0, 255, 255),
                                                      RGB(0, 0, 255)));

  if (block->getDrawingTool() == nullptr) {
    cout << "Null pointer in drawing tool.\n";
  }

  shared_ptr<TetrominoO> tO = make_shared<TetrominoO>(block);
  tO->setDrawingTool(make_shared<ShapeDrawingTool>());
  shared_ptr<TetrominoT> tT = make_shared<TetrominoT>(block);
  tT->setDrawingTool(make_shared<ShapeDrawingTool>());
  shared_ptr<TetrominoL> tL = make_shared<TetrominoL>(block);
  tL->setDrawingTool(make_shared<ShapeDrawingTool>());
  shared_ptr<TetrominoJ> tJ = make_shared<TetrominoJ>(block);
  tJ->setDrawingTool(make_shared<ShapeDrawingTool>());
  shared_ptr<TetrominoI> tI = make_shared<TetrominoI>(block);
  tI->setDrawingTool(make_shared<ShapeDrawingTool>());
  shared_ptr<TetrominoS> tS = make_shared<TetrominoS>(block);
  tS->setDrawingTool(make_shared<ShapeDrawingTool>());
  shared_ptr<TetrominoZ> tZ = make_shared<TetrominoZ>(block);
  tZ->setDrawingTool(make_shared<ShapeDrawingTool>());
  vector<shared_ptr<Shape>> shapes {tO, tT, tL, tJ, tI, tS, tZ};

  if (shapes[0]->getBlocks()[0]->getDrawingTool() == nullptr) {
    cout << "Null pointer in drawing tool.\n";
  }

  shared_ptr<Board> board = make_shared<BasicBoard>(height, width);
  board->setDrawingTool(make_shared<BoardDrawingTool>(RGB(0, 200, 0)));

  shared_ptr<GameBoard> game_board = make_shared<DefaultGameBoard>(board);
  game_board->setDrawingTool(make_shared<GameBoardDrawingTool>());

  shared_ptr<Game> game = make_shared<DefaultGame>(game_board, shapes);
  game->setDrawingTool(make_shared<GameDrawingTool>());

  return game;
}

/* static */
int GGameFlow::init_game(int window_width,
                     int window_height,
                     int cols,
                     int rows)
{
  using namespace genv;
  std::shared_ptr<tetris::Game> game = make_game_flow(rows, cols);
  GGameFlow game_flow(window_width, window_height, game);

  gout.open(window_width, window_height);
  gout << move_to(0, 0);
  game_flow.newGame();

  event ev;
  while (gin >> ev) {
    if (ev.type == ev_key) {
      if (ev.keycode == key_escape) {
        break;
      } else {
        game_flow.processInput(ev.keycode);
      }
    }
  }

  return 0;
}

GGameFlow::GGameFlow(int window_width,
                     int window_height,
                     std::shared_ptr<tetris::Game> game,
                     unsigned int interval)
  : tetris::BasicGameFlow(game, interval),
    m_window_width(window_width),
    m_window_height(window_height),
    m_dci(genv::gout, calculate_block_size())
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
  groutput& out_dev = m_dci.gout;
  out_dev << move_to(0, 0);
  out_dev << color(0, 0, 0);
  out_dev << box(m_window_width, m_window_height);

  out_dev << move_to(0, 0);
  auto game = getGame();
  game->draw(m_dci);

  out_dev << refresh;
}

int GGameFlow::calculate_block_size() const {
  auto board = getGame()->getGameBoard()->getBoard();
  int cols = board->getWidth();
  int rows = board->getHeight();

  int horizontal = m_window_width / cols; // Truncating to int.
  int vertical = m_window_height / rows; // Truncating to int.

  return horizontal < vertical ? horizontal : vertical;
}

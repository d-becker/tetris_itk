#ifndef GAMEBOARDDRAWINGTOOL_H
#define GAMEBOARDDRAWINGTOOL_H

#include <Board.h>
#include <Drawing.h>
#include <GameBoard.h>

class GameBoardDrawingTool : public tetris::DrawingTool<tetris::GameBoard>
{
  public:
    GameBoardDrawingTool()
      : tetris::DrawingTool<tetris::GameBoard>()
    {}

    virtual ~GameBoardDrawingTool() {}

    GameBoardDrawingTool(const GameBoardDrawingTool& other)
      : tetris::DrawingTool<tetris::GameBoard>(other)
    {}

    GameBoardDrawingTool(GameBoardDrawingTool&& other)
      : tetris::DrawingTool<tetris::GameBoard>(other)
    {}

    virtual void draw(const tetris::GameBoard& game_board,
                      tetris::DrawingContextInfo& dci) override
    {
      using namespace genv;
      groutput& out_dev = dci.gout;
      int orig_x = out_dev.x();
      int orig_y = out_dev.y();

      int block_size = dci.block_width;

      game_board.getBoard()->draw(dci);

      tetris::Coords c = game_board.getCurrentShapePosition();
      out_dev << move_to(orig_x + c.getHorizontal() * block_size,
                         orig_y + c.getVertical() * block_size);

      const std::shared_ptr<const tetris::Shape>& current_shape
                                        = game_board.getCurrentShape();
      if (current_shape != nullptr) {
        current_shape->draw(dci);
      }

      out_dev << move_to(orig_x, orig_y);
    }

    virtual std::shared_ptr<tetris::DrawingTool<tetris::GameBoard>> copy()
                                                 const override
    {
      return std::make_shared<GameBoardDrawingTool>(*this);
    }
  protected:
  private:
};

#endif // GAMEBOARDDRAWINGTOOL_H

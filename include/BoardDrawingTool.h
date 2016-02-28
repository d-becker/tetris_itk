#ifndef BOARDDRAWINGTOOL_H
#define BOARDDRAWINGTOOL_H

#include <Board.h>
#include <Drawing.h>

#include "RGB.h"

class BoardDrawingTool : public tetris::DrawingTool<tetris::Board>
{
  public:
    BoardDrawingTool(RGB background_colour)
      : m_background_colour(background_colour)
    {}

    virtual ~BoardDrawingTool() {}
    BoardDrawingTool(const BoardDrawingTool& other)
      : BoardDrawingTool(other.m_background_colour)
    {}

    BoardDrawingTool(BoardDrawingTool&& other)
      : BoardDrawingTool(other.m_background_colour)
    {}

    virtual void draw(const tetris::Board& board,
                      tetris::DrawingContextInfo& dci) override
    {
      using namespace genv;
      OutputWrapper& out_dev = dci.out_dev;
      int orig_x = out_dev.getX();
      int orig_y = out_dev.getY();

      int block_size = dci.block_width;

      int height = board.getHeight();
      int width = board.getWidth();

      // Painting the background.
      out_dev.setColour(m_background_colour);
      out_dev.box(width * block_size, height * block_size);

      out_dev.moveTo(orig_x, orig_y);

      // Painting the filled blocks.
      for (int vertical = 0; vertical < height; ++vertical) {
        for (int horizontal = 0; horizontal < width; ++horizontal) {
          std::shared_ptr<const tetris::Block> block = board.get(vertical,
                                                                 horizontal);
          if (block != nullptr) {
            out_dev.moveTo(orig_x + horizontal * block_size,
                           orig_y + vertical * block_size);
            block->draw(dci);
          }
        }
      }

      out_dev.moveTo(orig_x, orig_y);
    }

    virtual std::shared_ptr<tetris::DrawingTool<tetris::Board>> copy()
                                                  const override
    {
      return std::make_shared<BoardDrawingTool>(*this);
    }
  private:
    RGB m_background_colour;
};

#endif // BOARDDRAWINGTOOL_H

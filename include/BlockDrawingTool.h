#ifndef BLOCKDRAWINGTOOL_H
#define BLOCKDRAWINGTOOL_H

#include <memory>

#include <Block.h>
#include <Drawing.h>

#include "DrawingContextInfo.h"
#include "RGB.h"

class BlockDrawingTool : public tetris::DrawingTool<tetris::Block>
{
  public:
    BlockDrawingTool(RGB fill_colour, RGB line_colour)
      : m_fill_colour(fill_colour),
        m_line_colour(line_colour)
    {}

    virtual ~BlockDrawingTool() {}
    BlockDrawingTool(const BlockDrawingTool& other)
     : m_fill_colour(other.m_fill_colour),
       m_line_colour(other.m_line_colour)
    {}

    BlockDrawingTool(BlockDrawingTool&& other)
     : m_fill_colour(other.m_fill_colour),
       m_line_colour(other.m_line_colour)
    {}

    virtual void draw(const tetris::Block& block __attribute__((unused)),
                      tetris::DrawingContextInfo& dci) override
    {
      using namespace genv;
      groutput& out_dev = dci.gout;
      int orig_x = out_dev.x();
      int orig_y = out_dev.y();

      int block_size = dci.block_width;

      out_dev << m_fill_colour;
      out_dev << box(block_size, block_size);

      out_dev << move_to(orig_x, orig_y);

      out_dev << m_line_colour;
      out_dev << line(block_size, 0);
      out_dev << line(0, block_size);
      out_dev << line(-block_size, 0);
      out_dev << line(0, -block_size);

      out_dev << move_to(orig_x, orig_y); // Probably not be necessary.
    }

    virtual std::shared_ptr<tetris::DrawingTool<tetris::Block>> copy()
                                                  const override
    {
      return std::make_shared<BlockDrawingTool>(*this);
    }

  private:
    RGB m_fill_colour;
    RGB m_line_colour;
};

#endif // BLOCKDRAWINGTOOL_H

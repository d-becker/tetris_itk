#ifndef SHAPEDRAWINGTOOL_H
#define SHAPEDRAWINGTOOL_H

#include <memory>
#include <vector>

#include <Drawing.h>
#include <Shape.h>

#include <graphics.hpp>

class ShapeDrawingTool : public tetris::DrawingTool<tetris::Shape>
{
  public:
    ShapeDrawingTool() : tetris::DrawingTool<tetris::Shape>() {}
    virtual ~ShapeDrawingTool() {}
    ShapeDrawingTool(const ShapeDrawingTool& other __attribute__((unused)))
     : tetris::DrawingTool<tetris::Shape>()
    {}

    ShapeDrawingTool(ShapeDrawingTool&& other __attribute__((unused)))
     : tetris::DrawingTool<tetris::Shape>()
    {}

    virtual void draw(const tetris::Shape& shape,
                      tetris::DrawingContextInfo& dci) override
    {
      using namespace genv;
      OutputWrapper& out_dev = dci.out_dev;
      int orig_x = out_dev.getX();
      int orig_y = out_dev.getY();

      int block_size = dci.block_width;

      std::vector<tetris::Coords> block_positions = shape.getBlockPositions();

      for (const tetris::Coords& c : block_positions) {
        std::shared_ptr<tetris::Block> block = shape.get(c);
        if (block != nullptr) {
          out_dev.moveTo(orig_x + c.getHorizontal() * block_size,
                         orig_y + c.getVertical() * block_size);
          block->draw(dci);
        }
      }

      out_dev.moveTo(orig_x, orig_y);
    }

    virtual std::shared_ptr<tetris::DrawingTool<tetris::Shape>> copy()
                                                 const override
    {
      return std::make_shared<ShapeDrawingTool>(*this);
    }
};

#endif // SHAPEDRAWINGTOOL_H

#ifndef TETRIS_DRAWINGCONTEXTINFO_H
#define TETRIS_DRAWINGCONTEXTINFO_H

#include <mutex>

#include <graphics.hpp>

#include "OutputWrapper.h"

namespace tetris {

/**
 * This class is the definition and implementation of the class forward
 * declared in the tetris library. It contains the width and
 * the height of a block and a reference to \c genv::gout
 * and a mutex that protects it.
 */
struct DrawingContextInfo
{
  DrawingContextInfo(OutputWrapper& p_out_dev, int p_block_width)
   : out_dev(p_out_dev),
     block_width(p_block_width)
  {

  }

  virtual ~DrawingContextInfo() {}

  OutputWrapper& out_dev;

  const int block_width;
};

} // namespace tetris

#endif // TETRIS_DRAWINGCONTEXTINFO_H

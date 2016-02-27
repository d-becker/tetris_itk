#ifndef TETRIS_DRAWINGCONTEXTINFO_H
#define TETRIS_DRAWINGCONTEXTINFO_H

#include <mutex>

#include <graphics.hpp>

namespace tetris {

/**
 * This class is the definition and implementation of the class forward
 * declared in the tetris library. It contains the width and
 * the height of a block and a reference to \c genv::gout
 * and a mutex that protects it.
 */
struct DrawingContextInfo
{
  DrawingContextInfo(genv::groutput& p_gout, int p_block_width)
   : gout(p_gout),
     block_width(p_block_width)
  {

  }

  virtual ~DrawingContextInfo() {}

  genv::groutput& gout = genv::gout;
  std::mutex m_gout_mutex {};

  const int block_width;
};

} // namespace tetris

#endif // TETRIS_DRAWINGCONTEXTINFO_H

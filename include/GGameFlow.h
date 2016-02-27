#ifndef GGAMEFLOW_H
#define GGAMEFLOW_H

#include "BasicGameFlow.h"

#include <memory>

#include "DrawingContextInfo.h"

class GGameFlow : public tetris::BasicGameFlow
{
  public:
    static int init_game(int windiw_width,
                         int window_height,
                         int cols,
                         int rows);

    GGameFlow(int window_width,
              int window_height,
              std::shared_ptr<tetris::Game> game,
              unsigned int interval = 800u);
    virtual ~GGameFlow();

    virtual void draw() override;

    int getWindowWidth() const {
      return m_window_width;
    }

    int getWindowHeight() const {
      return m_window_height;
    }
  private:
    static std::shared_ptr<tetris::Game> make_game_flow(int height, int width);

    int calculate_block_size() const;

    const int m_window_width;
    const int m_window_height;
    tetris::DrawingContextInfo m_dci;
};

#endif // GGAMEFLOW_H

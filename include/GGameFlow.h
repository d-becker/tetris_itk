#ifndef GGAMEFLOW_H
#define GGAMEFLOW_H

#include "BasicGameFlow.h"

#include <functional>
#include <memory>

#include "DrawingContextInfo.h"

class GGameFlow : public tetris::BasicGameFlow
{
  public:
    static std::shared_ptr<tetris::Game> make_game(int height, int width);

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

    void pause();

    void setGameOverCall(std::function<void(void)> game_over_call);
  protected:
    void on_game_over() override;
  private:
    int calculate_block_size() const;
    int calculate_horizontal_offset() const;

    const int m_window_width;
    const int m_window_height;
    tetris::DrawingContextInfo m_dci;
    int m_horizontal_offset;
    std::function<void(void)> m_game_over_call;
};

#endif // GGAMEFLOW_H

#ifndef TOPFLOW_H
#define TOPFLOW_H

#include <memory>
#include <mutex>

#include <graphics.hpp>

#include "GGameFlow.h"

class TopFlow
{
  public:
    TopFlow(int windiw_width,
            int window_height,
            int cols,
            int rows);

    virtual ~TopFlow();
  private:
    void to_menu();
    void to_playing();
    void to_game_over();

    void paint_menu();
    void paint_game_over();

    void menu_event_handler(genv::event ev);
    void playing_event_handler(genv::event ev);
    void game_over_event_handler(genv::event ev);

    void increase_difficulty();
    void decrease_difficulty();
    void set_timer_difficulty();
  private:
    std::shared_ptr<GGameFlow> m_game_flow;

    enum State {
      MENU,
      PLAYING,
      GAME_OVER
    };

    State m_state = MENU;

    int m_difficulty = 0;
    mutable std::mutex m_lock {};
};

#endif // TOPFLOW_H

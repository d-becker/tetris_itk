#include "TopFlow.h"
#include "OutputWrapper.h"

TopFlow::TopFlow(int window_width,
                 int window_height,
                 int cols,
                 int rows)
{
  using namespace genv;
  std::shared_ptr<tetris::Game> game = GGameFlow::make_game(rows, cols);
  m_game_flow = std::make_shared<GGameFlow>(window_width, window_height, game);

  gout.open(window_width, window_height);
  genv::gout << genv::text("Alma") << genv::refresh; ///////////////////////////////////
  to_menu();


  event ev;
  while (gin >> ev) {
    if (ev.type == ev_key && ev.keycode == key_escape) {
      return;
    }

    switch (m_state) {
      case MENU : { menu_event_handler(ev); break; }
      case PLAYING : { playing_event_handler(ev); break; }
      case GAME_OVER : { game_over_event_handler(ev); break; }
    }
  }
}

TopFlow::~TopFlow()
{
  //dtor
}

void TopFlow::to_menu() {
  m_game_flow->pause();
  m_state = MENU;

  OutputWrapper out_dev = OutputWrapper::instance();
  out_dev.moveTo(0, 0);
  out_dev.colour(255, 255, 0);
  int window_width = m_game_flow->getWindowWidth();
  int window_height = m_game_flow->getWindowHeight();
  out_dev.box(window_width, window_height);

  out_dev.colour(230, 0, 0);
  std::string str = "Press enter to play!";
  genv::gout.load_font("LiberationMono-Bold.ttf", 16);
  int width = genv::gout.twidth(str);
  out_dev.moveTo((window_width - width) / 2, 20);
  out_dev.text(str);

  out_dev.refresh();
}

void TopFlow::to_playing() {
  m_game_flow->newGame();
  m_state = PLAYING;
}

void TopFlow::to_game_over() {
  m_game_flow->pause();
  m_state = GAME_OVER;

  OutputWrapper out_dev = OutputWrapper::instance();
  out_dev.moveTo(0, 0);
  out_dev.colour(255, 255, 0);
  int window_width = m_game_flow->getWindowWidth();
  int window_height = m_game_flow->getWindowHeight();
  out_dev.box(window_width, window_height);

  out_dev.colour(230, 0, 0);
  genv::gout.load_font("LiberationMono-Bold.ttf", 16);
  std::string str = "Game over!";
  int width = genv::gout.twidth(str);
  out_dev.moveTo((window_width - width) / 2, 20);
  out_dev.text(str);

  str = "Press enter to return to the main menu!";
  width = genv::gout.twidth(str);
  out_dev.moveTo((window_width - width) / 2, 50);
  out_dev.text(str);

  out_dev.refresh();
}

void TopFlow::menu_event_handler(genv::event ev) {
  using namespace genv;
  if (ev.type == ev_key && ev.keycode == key_enter) {
    to_playing();
  }
}

void TopFlow::playing_event_handler(genv::event ev) {
  using namespace genv;
  if (ev.type == ev_key) {
    m_game_flow->processInput(ev.keycode);
    if (m_game_flow->isGameOver()) {
       to_game_over();
    }
  }
}

void TopFlow::game_over_event_handler(genv::event ev) {
  using namespace genv;
  if (ev.type == ev_key && ev.keycode == key_enter) {
    to_menu();
  }
}

#ifndef GAMEDRAWINGTOOL_H
#define GAMEDRAWINGTOOL_H

#include <Drawing.h>
#include <Game.h>

class GameDrawingTool : public tetris::DrawingTool<tetris::Game>
{
  public:
    GameDrawingTool()
      : tetris::DrawingTool<tetris::Game>()
    {}

    virtual ~GameDrawingTool() {}

    GameDrawingTool(const GameDrawingTool& other)
      : tetris::DrawingTool<tetris::Game>(other)
    {}

    GameDrawingTool(GameDrawingTool&& other)
      : tetris::DrawingTool<tetris::Game>(other)
    {}

    virtual void draw(const tetris::Game& game,
                      tetris::DrawingContextInfo& dci) override
    {
      game.getGameBoard()->draw(dci);
    }

    virtual std::shared_ptr<tetris::DrawingTool<tetris::Game>> copy()
                                                 const override
    {
      return std::make_shared<GameDrawingTool>(*this);
    }
};

#endif // GAMEDRAWINGTOOL_H

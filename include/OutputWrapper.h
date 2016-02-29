#ifndef OUTPUTWRAPPER_H
#define OUTPUTWRAPPER_H

#include <string>

#include <graphics.hpp>

#include "RGB.h"

class OutputWrapper
{
  public:
    static OutputWrapper& instance();

    virtual ~OutputWrapper();

    int getX() const {
      return m_x;
    }

    int getY() const {
      return m_y;
    }

    void colour(int r, int g, int b);
    void setColour(RGB c);

    /**
     * Returns true if the move was successful.
     */
    bool moveTo(int x, int y);

    /**
     * Returns true if the move was successful.
     */
    bool move(int dx, int dy);

    void lineTo(int x, int y);
    void line(int dx, int dy);

    void boxTo(int x, int y);
    void box(int dx, int dy);

    void dot();

    void text(std::string str);

    void refresh();
  protected:
  private:
    OutputWrapper(genv::groutput& out_dev = genv::gout);
    void push_new_position();
    void pull_new_position();
    bool check_equal_position();

    genv::groutput& m_out_dev;
    int m_x;
    int m_y;
};

#endif // OUTPUTWRAPPER_H

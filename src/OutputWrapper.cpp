#include "OutputWrapper.h"

/* static */
OutputWrapper& OutputWrapper::instance() {
  static OutputWrapper inst;
  return inst;
}

OutputWrapper::OutputWrapper(genv::groutput& out_dev)
  : m_out_dev(out_dev),
    m_x(m_out_dev.x()),
    m_y(m_out_dev.y())
{
  //ctor
}

OutputWrapper::~OutputWrapper()
{
  //dtor
}

void OutputWrapper::colour(int r, int g, int b) {
  m_out_dev << genv::color(r, g, b);
}

void OutputWrapper::setColour(RGB c) {
  colour(c.r, c.g, c.b);
}

bool OutputWrapper::moveTo(int x, int y) {
  m_x = x;
  m_y = y;
  push_new_position();
  return check_equal_position();
}

bool OutputWrapper::move(int dx, int dy) {
  m_x += dx;
  m_y += dy;
  push_new_position();
  return check_equal_position();
}

void OutputWrapper::lineTo(int x, int y) {
  check_equal_position();
  m_out_dev << genv::line_to(x, y);
  pull_new_position();
}

void OutputWrapper::line(int dx, int dy) {
  check_equal_position();
  m_out_dev << genv::line(dx, dy);
  pull_new_position();
}

void OutputWrapper::boxTo(int x, int y) {
  check_equal_position();
  m_out_dev << genv::box_to(x, y);
  pull_new_position();
}

void OutputWrapper::box(int dx, int dy) {
  check_equal_position();
  m_out_dev << genv::box(dx, dy);
  pull_new_position();
}

void OutputWrapper::dot() {
  check_equal_position();
  m_out_dev << genv::dot;
}

void OutputWrapper::refresh() {
  m_out_dev << genv::refresh;
}

// Helper functions.
void OutputWrapper::push_new_position() {
  m_out_dev << genv::move_to(m_x, m_y);
}

void OutputWrapper::pull_new_position() {
  moveTo(m_out_dev.x(), m_out_dev.y());
  //m_x = m_out_dev.x();
  //m_y = m_out_dev.y();
}

bool OutputWrapper::check_equal_position() {
  if (m_x != m_out_dev.x()) {
    return false;
  }

  if (m_y != m_out_dev.y()) {
    return false;
  }

  return true;
}

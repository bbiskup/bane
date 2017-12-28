#include "simple_layout_mgr.h"
#include "widget.h"

#include <numeric>
#include <stdexcept>

void bane::SimpleLayoutMgr::layout() {
  if (parent_.children().size() == 0) {
    return;
  } else if (parent_.children().size() > 1) {
    throw std::runtime_error{"Expecting exactly 1 child"};
  } else {
    Widget& w = parent_.children()[0];
    w.move(parent_.relX(), parent_.relY());
  }
}

int bane::SimpleLayoutMgr::preferredWidth() const noexcept {
  return std::accumulate(parent_.children().begin(), parent_.children().end(), 0,
                         [](int s, const Widget& widget) {
                           return s + widget.preferredWidth();
                         });
}

int bane::SimpleLayoutMgr::preferredHeight() const noexcept {
  return static_cast<int>(parent_.children().size());
}

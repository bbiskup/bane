
#include "app.h"
#include "h_box_layout_mgr.h"
#include "label.h"
#include "logging.h"
#include "pane.h"

#include <boost/log/trivial.hpp>
#include <iostream>

int main() {
  bane::initLogging();
  bane::App app{"test-app"};

  bane::Pane pane{};
  pane.setLayoutMgr<bane::HBoxLayoutMgr>();
  pane.addChild<bane::Label>("my_text");
  bane::Label* label2 = pane.addChild<bane::Label>("my_other_text");
  label2->doOnClick([](int x, int y) {
    // std::cout << "Handling click: " << x << ", " << y << std::endl;
    BOOST_LOG_TRIVIAL(trace) << "Handling click: " << x << ", " << y;
  });

  // label2->click(0, 2);
  // bane::Label label{"my text"};
  // label.resize(10, 20);
  // label.render();
  pane.resize(30, 20);
  pane.render();

  app.run();

  // termWin.waitForKey();
  //  return 0;
}


#include "app.h"
#include "button/button.h"
#include "h_box_layout_mgr.h"
#include "label.h"
#include "logging.h"
#include "theme.h"
#include "v_box_layout_mgr.h"

#include <boost/log/trivial.hpp>
#include <chrono>
#include <future>
#include <iostream>
#include <memory>
#include <thread>

using namespace std::chrono_literals;

int main() {
  bane::initLogging();
  bane::App app{"test-app", std::make_unique<bane::SimpleTheme>()};

  bane::Pane* pane{app.rootPane.addChild<bane::Pane>()};
  pane->resize(20, 30);
  pane->setLayoutMgr<bane::VBoxLayoutMgr>();
  pane->addChild<bane::Label>("my_label_1");

  bane::Label* label2 = pane->addChild<bane::Label>("my_label_2");
  label2->doOnClick([](int x, int y) {
    BOOST_LOG_TRIVIAL(trace) << "Handling click: " << x << ", " << y;
  });

  // label2->click(0, 2);
  // bane::Label label{"my text"};
  // label.resize(10, 20);
  // label.render();

  std::future<void> job = std::async(std::launch::async, [&app]() {
    std::this_thread::sleep_for(1s);
    app.postEvent<bane::DummyEvent>();
  });

  pane->addChild<bane::Button>("my_button");

  bane::Pane* paneH{pane->addChild<bane::Pane>()};
  paneH->resize(50, 1);
  paneH->setLayoutMgr<bane::HBoxLayoutMgr>();
  paneH->addChild<bane::Button>("another_button");
  paneH->addChild<bane::Button>("yet_another_button");

  // termWin.waitForKey();
  //  return 0;
  app.run();
}

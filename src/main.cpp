
#include "app.h"
#include "button_group.h"
#include "checkbox.h"
#include "event/custom_event.h"
#include "event/dummy_event.h"
#include "h_box_layout_mgr.h"
#include "label.h"
#include "h_line.h"
#include "line_edit.h"
#include "logging.h"
#include "push_button.h"
#include "radio_button.h"
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
  /*
  pane->addChild<bane::Label>("my_label_1");
  bane::Label* label2 = pane->addChild<bane::Label>("my_label_2");
  label2->doOnClick([](int x, int y) {
    BOOST_LOG_TRIVIAL(trace) << "Handling click: " << x << ", " << y;
  });
  */

  // label2->click(0, 2);
  // bane::Label label{"my text"};
  // label.resize(10, 20);
  // label.render();

  bane::Label* label1{pane->addChild<bane::Label>("my_label_x")};
  label1->setText("new_label_text");
  pane->addChild<bane::HLine>();
  /*
  std::future<void> job = std::async(std::launch::async, [&label1, &app]() {
    std::this_thread::sleep_for(2s);
    // app.postEvent<bane::DummyEvent>();
    app.postEvent<bane::CustomEvent>(
        [&label1](bane::App&) { label1->setText("text_from_event"); });
  });*/

  //  pane->addChild<bane::Button>("my_button");
  /* pane->addChild<bane::Button>("my_button_x");
   bane::Pane* paneH{pane->addChild<bane::Pane>()};
   paneH->resize(50, 1);
   paneH->setLayoutMgr<bane::HBoxLayoutMgr>();
   paneH->addChild<bane::Button>("another_button");*/

  /*

  bane::Pane* paneH{pane->addChild<bane::Pane>()};
  paneH->resize(50, 1);
  paneH->setLayoutMgr<bane::HBoxLayoutMgr>();
  paneH->addChild<bane::Button>("another_button");
  paneH->addChild<bane::Button>("yet_another_button");
  */

  pane->addChild<bane::PushButton>("my_button");
  bane::ButtonGroup* bg1{pane->addChild<bane::ButtonGroup>(
      "button_group_1", bane::Orientation::vertical)};
  bg1->addChild<bane::CheckBox>("my_checkbox_1");
  bg1->addChild<bane::CheckBox>("my_checkbox_2");
  bg1->addChild<bane::RadioButton>("my_radio_button_1");
  bg1->addChild<bane::RadioButton>("my_radio_button_2");
  // bg1->addChild<bane::CheckBox>("my_checkbox_3");
  pane->addChild<bane::Label>("my_label_x2");
  bg1->children()[0].requestFocus();
  pane->addChild<bane::LineEdit>("My text", 20ul);
  bane::LineEdit* ledx = pane->addChild<bane::LineEdit>("My other text", 30ul,
                                                        "other initial text");
  ledx->requestFocus();

  pane->addChild<bane::Label>("-------------------------");
  bane::ButtonGroup* bg2{pane->addChild<bane::ButtonGroup>(
      "button_group_2", bane::Orientation::vertical)};
  bg2->addChild<bane::CheckBox>("my_checkbox_3");
  bg2->addChild<bane::CheckBox>("my_checkbox_4");

  bg1->setFocusSuccessor(ledx);
  ledx->setFocusSuccessor(bg2);

  app.run();
}

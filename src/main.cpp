
#include "app.h"
#include "button_group.h"
#include "checkbox.h"
#include "event/custom_event.h"
#include "event/dummy_event.h"
#include "h_box_layout_mgr.h"
#include "h_line.h"
#include "label.h"
#include "line_edit.h"
#include "logging.h"
#include "push_button.h"
#include "radio_button.h"
#include "theme.h"
#include "v_box_layout_mgr.h"
#include "v_line.h"
#include "tabs.h"
#include "tab.h"

#include <boost/log/trivial.hpp>
#include <chrono>
#include <future>
#include <iostream>
#include <memory>
#include <thread>


using namespace std::chrono_literals;

namespace {
[[maybe_unused]] void test_simple(bane::App& app);
[[maybe_unused]] void test_tab(bane::App& app);
[[maybe_unused]] void test_misc(bane::App& app);
}

int main() {
  bane::initLogging();
  bane::App app{L"test-Äpp", std::make_unique<bane::SimpleTheme>(), true};
  //test_tab(app);
  //test_misc(app);
  test_simple(app);

  app.run();
}

namespace {
void test_simple(bane::App& app){
    app.rootPane.setLayoutMgr<bane::VBoxLayoutMgr>();
    app.rootPane.addChild<bane::Label>(L"Label 1");
    app.rootPane.addChild<bane::Pane>();
}

void test_tab(bane::App& app){
  bane::Tabs* tabs{app.rootPane.addChild<bane::Tabs>()};

  bane::Tab* tab1{tabs->addTab(L"Tab 1")};
  bane::Pane* pane1 = tab1->addChild<bane::Pane>();
  pane1->setLayoutMgr<bane::HBoxLayoutMgr>();
  pane1->addChild<bane::Label>(L"Label 1 of pane 1");
  pane1->addChild<bane::Label>(L"Label 2 of pane 1");

  bane::Tab* tab2{tabs->addTab(L"Tab 2")};
  bane::Pane* pane2 = tab2->addChild<bane::Pane>();
  pane2->setLayoutMgr<bane::VBoxLayoutMgr>();
  pane2->addChild<bane::Label>(L"Label 1 of pane 2");
  pane2->addChild<bane::Label>(L"Label 2 of pane 2");
}

void test_misc(bane::App& app) {
  bane::Pane* pane{app.rootPane.addChild<bane::Pane>()};
  pane->resize(20, 30);
  pane->setLayoutMgr<bane::VBoxLayoutMgr>();
  /*
  pane->addChild<bane::Label>(:"my_label_1");
  bane::Label* label2 = pane->addChild<bane::Label>(L"my_label_2");
  label2->doOnClick([](int x, int y) {
    BOOST_LOG_TRIVIAL(trace) << "Handling click: " << x << ", " << y;
  });
  */

  // label2->click(0, 2);
  // bane::Label label{L"my text"};
  // label.resize(10, 20);
  // label.render();

  pane->addChild<bane::Label>(L"first_label with umlauts: äöü ÄÖÜß");
  pane->addChild<bane::Label>(L"second_label");
  pane->addChild<bane::HLine>();
  pane->addChild<bane::HLine>(L'Å');
  bane::Label* label3 = pane->addChild<bane::Label>(L"third_label");
  label3->resize(10, 3);

  /*
  std::future<void> job = std::async(std::launch::async, [&label1, &app]() {
    std::this_thread::sleep_for(2s);
    // app.postEvent<bane::DummyEvent>();
    app.postEvent<bane::CustomEvent>(
        [&label1](bane::App&) { label1->setText("text_from_event"); });
  });*/

  //  pane->addChild<bane::Button>("my_button");
  /* pane->addChild<bane::Button>("my_button_x");*/

  bane::Pane* paneH{pane->addChild<bane::Pane>()};
  // paneH->resize(50, 2);
  paneH->setLayoutMgr<bane::HBoxLayoutMgr>();
  paneH->addChild<bane::PushButton>(L"another_button");
  paneH->addChild<bane::VLine>();
  paneH->addChild<bane::VLine>(L'Ü');
  paneH->addChild<bane::Label>(L"label_in_paneH");
  BOOST_LOG_TRIVIAL(trace) << "######## " << paneH->height();

  // pane->addChild<bane::PushButton>("my_button");
  pane->addChild<bane::Label>(L"my_label");

  bane::ButtonGroup* bg1{pane->addChild<bane::ButtonGroup>(
      L"button_group_1", bane::Orientation::vertical)};
  bg1->addChild<bane::CheckBox>(L"my_checkbox_1");
  bg1->addChild<bane::CheckBox>(L"my_checkbox_2");
  bg1->addChild<bane::RadioButton>(L"my_radio_button_1");
  bg1->addChild<bane::RadioButton>(L"my_radio_button_2");
  // bg1->addChild<bane::CheckBox>(L"my_checkbox_3");

  pane->addChild<bane::Label>(L"fourth_label");

  pane->addChild<bane::Label>(L"my_label_x2");
  // bg1->children()[0].requestFocus();
  pane->addChild<bane::LineEdit>(L"My text", 20ul);
  bane::LineEdit* ledx =
      pane->addChild<bane::LineEdit>(L"My other text", 30ul, L"initial äöüºª¡");
  ledx->requestFocus();

  bane::ButtonGroup* bg2{pane->addChild<bane::ButtonGroup>(
      L"button_group_2", bane::Orientation::horizontal)};
  bg2->addChild<bane::CheckBox>(L"my_checkbox_3 i¹²ëý");
  bg2->addChild<bane::CheckBox>(L"my_checkbox_4");

  bg1->setFocusSuccessor(ledx);
  ledx->setFocusSuccessor(bg2);
}
} // namespace

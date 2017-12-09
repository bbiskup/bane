#include "button.h"
#include <boost/log/trivial.hpp>

bane::Button::Button() {
  std::shared_ptr<ButtonModel> model = std::make_shared<ButtonModel>();
  std::shared_ptr<View<ButtonModel>> view = std::make_shared<ButtonView>(model);
  controller_ = std::make_shared<ButtonController>(model, view);
}

void bane::Button::ButtonView::render() {
  BOOST_LOG_TRIVIAL(trace) << "Button::ButtonView::render";
}

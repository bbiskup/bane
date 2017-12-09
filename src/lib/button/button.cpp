#include "button.h"
#include <boost/log/trivial.hpp>

bane::Button::Button(Widget* root, std::string label) : Widget{root} {
  std::shared_ptr<ButtonModel> model = std::make_shared<ButtonModel>(label);
  std::shared_ptr<View<ButtonModel>> view = std::make_shared<ButtonView>(model);
  controller_ = std::make_shared<ButtonController>(model, view);
}

int bane::Button::preferredWidth() const noexcept {
  return static_cast<int>(controller_->model().label().size());
}
int bane::Button::preferredHeight() const noexcept { return 1; }

void bane::Button::doRender() {
  BOOST_LOG_TRIVIAL(trace) << "Button::doRender" << y() << " " << x();
  CharPoint orig{origin()};
  mvaddstr(orig.y, orig.x, controller_->model().label().c_str());
}

bane::Button::ButtonModel::ButtonModel(std::string label)
    : label_{std::move(label)} {}

void bane::Button::ButtonView::render() {
  BOOST_LOG_TRIVIAL(trace) << "Button::ButtonView::render";
}

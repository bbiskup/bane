#ifndef BUTTON_H
#define BUTTON_H

#include "mvc/controller.h"
#include "mvc/model.h"
#include "mvc/view.h"
#include "widget.h"

#include <memory>
#include <string>

namespace bane {
class Button : public Widget {
public:
  Button();

private:
  class ButtonModel : public Model {
    std::string label_;
  };

  class ButtonView : public View<ButtonModel> {
  public:
    using View::View;
    ~ButtonView() override {}
    void render() override;
  };

  class ButtonController : public Controller<ButtonModel> {
    using Controller<ButtonModel>::Controller;
  };

  std::shared_ptr<ButtonController> controller_;
};
} // namespace bane

#endif /* BUTTON_H */

#ifndef H_LINE_H
#define H_LINE_H

#include "widget.h"

#include <string>

namespace bane {

// Horizontal line
class HLine : public Widget {
public:
  HLine(Widget* root, char lineChar='-');

  int preferredWidth() const noexcept override;
  int preferredHeight() const noexcept override;

  void doRender() override;

private:
  const char lineChar_;
};
} // namespace bane



#endif /* H_LINE_H */

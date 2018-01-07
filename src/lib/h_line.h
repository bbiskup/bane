#ifndef H_LINE_H
#define H_LINE_H

#include "widget.h"

#include <string>

namespace bane {

// Horizontal line (separator)
class HLine : public Widget {
public:
  HLine(Widget* root, wchar_t lineChar='-');

  int preferredWidth() const noexcept override;
  int preferredHeight() const noexcept override;

  void doRender() override;

private:
  const wchar_t lineChar_;
};
} // namespace bane



#endif /* H_LINE_H */

#ifndef V_LINE_H
#define V_LINE_H

#include "widget.h"

#include <string>

namespace bane {

// Vertical line (separator)
class VLine : public Widget {
public:
  VLine(Widget* root, wchar_t lineChar=L'|');

  int preferredWidth() const noexcept override;
  int preferredHeight() const noexcept override;

  void doRender() override;

private:
  const wchar_t lineChar_;
};
} // namespace bane



#endif /* H_LINE_H */

#ifndef PANE_H
#define PANE_H

#include "widget.h"

namespace bane {

/// A Simple empty pane.
/// Its sole purpose is to host one or more chilren.
class Pane : public Widget {
  int preferredWidth() const noexcept override;
  int preferredHeight() const noexcept override;
};

} // namespace bane

#endif /* PANE_H */

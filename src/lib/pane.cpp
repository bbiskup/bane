#include "pane.h"

int bane::Pane::preferredWidth() const noexcept { return layoutMgr_->preferredWidth(); }

int bane::Pane::preferredHeight() const noexcept { return layoutMgr_->preferredHeight(); }

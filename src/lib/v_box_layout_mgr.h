#ifndef V_BOX_LAYOUT_MGR_H
#define V_BOX_LAYOUT_MGR_H

#include "layout_mgr.h"

namespace bane {

/// Lay out widgets in a vertical row
class VBoxLayoutMgr : public LayoutMgr {
public:
  using LayoutMgr::LayoutMgr;
  ~VBoxLayoutMgr() override = default;
  void layout() override;
  int preferredWidth() const noexcept override;
  int preferredHeight() const noexcept override;
};

} // namespace bane
#endif /* V_BOX_LAYOUT_MGR_H */

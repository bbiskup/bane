#ifndef H_BOX_LAYOUT_MGR_H
#define H_BOX_LAYOUT_MGR_H

#include "layout_mgr.h"

namespace bane {

/// Lay out widgets in a horizontal row
class HBoxLayoutMgr : public LayoutMgr {
public:
  using LayoutMgr::LayoutMgr;
  ~HBoxLayoutMgr() override = default;
  void layout() override;
  int preferredWidth() const noexcept override;
  int preferredHeight() const noexcept override;
};

} // namespace bane
#endif /* H_BOX_LAYOUT_MGR_H */

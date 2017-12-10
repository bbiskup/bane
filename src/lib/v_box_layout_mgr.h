#ifndef V_BOX_LAYOUT_MGR_H
#define V_BOX_LAYOUT_MGR_H

#include "layout_mgr.h"

namespace bane {

/// Lay out widgets in a vertical row
class VBoxLayoutMgr : public LayoutMgr {
public:
  ~VBoxLayoutMgr() override = default;
  void layout(const Widget& parent,
              boost::ptr_vector<Widget>& widgets) override;
};

} // namespace bane
#endif /* V_BOX_LAYOUT_MGR_H */

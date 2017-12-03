#ifndef H_BOX_LAYOUT_MGR_H
#define H_BOX_LAYOUT_MGR_H

#include "layout_mgr.h"

namespace bane {

/// Lay out widgets in a horizontal row
class HBoxLayoutMgr : public LayoutMgr {
public:
  ~HBoxLayoutMgr() override = default;
  void layout(const Widget& parent,
              boost::ptr_vector<Widget>& widgets) override;
};

} // namespace bane
#endif /* H_BOX_LAYOUT_MGR_H */

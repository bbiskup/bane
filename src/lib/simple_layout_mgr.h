#ifndef SIMPLE_LAYOUT_MGR_H
#define SIMPLE_LAYOUT_MGR_H

#include "layout_mgr.h"
#include <boost/ptr_container/ptr_vector.hpp>

namespace bane {

/// Simple layout:
/// - expect max 1 child
/// - move child to top left of parent
class SimpleLayoutMgr : public LayoutMgr {
public:
  using LayoutMgr::LayoutMgr;
  ~SimpleLayoutMgr() override = default;
  void layout() override;
  int preferredWidth() const noexcept override;
  int preferredHeight() const noexcept override;
};

} // namespace bane

#endif /* SIMPLE_LAYOUT_MGR_H */

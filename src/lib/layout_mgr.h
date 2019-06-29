#ifndef LAYOUT_MGR_H
#define LAYOUT_MGR_H

#include <boost/ptr_container/ptr_vector.hpp>

namespace bane {
class Widget;

enum class Orientation { horizontal, vertical };

class LayoutMgr {
public:
  LayoutMgr(Widget& parent) : parent_{parent} {}
  virtual ~LayoutMgr() = default;
  virtual void layout() = 0;
  virtual int preferredWidth() const noexcept = 0;
  virtual int preferredHeight() const noexcept = 0;

protected:
  Widget& parent_;
};

} // namespace bane

#endif /* LAYOUT_MGR_H */

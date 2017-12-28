#ifndef LAYOUT_MGR_H
#define LAYOUT_MGR_H

#include <boost/ptr_container/ptr_vector.hpp>

namespace bane {
class Widget;

enum class Orientation{ horizontal, vertical};

class LayoutMgr {
public:
  virtual ~LayoutMgr() = default;
  virtual void layout(const Widget& parent,
                      boost::ptr_vector<Widget>& widgets) = 0;
};

} // namespace bane

#endif /* LAYOUT_MGR_H */

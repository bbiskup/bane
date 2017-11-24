#ifndef LABEL_H
#define LABEL_H

#include "widget.h"

namespace bane {

class Label : public Widget {
public:
  Label(std::string label);
  void doRender() override;

private:
  std::string label_;
};

} // namespace bane

#endif /* LABEL_H */

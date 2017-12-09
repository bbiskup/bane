#include "model.h"

/// Handle change event
boost::signals2::connection
bane::Model::doOnChange(const OnChangeSlotType& slot) {
  return onChange_.connect(slot);
}

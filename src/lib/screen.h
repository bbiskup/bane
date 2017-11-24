#ifndef SCREEN_H
#define SCREEN_H

namespace bane {
class Screen {
public:
  Screen();
  ~Screen();

  void waitForKey() const;
};
} // namespace bane

#endif

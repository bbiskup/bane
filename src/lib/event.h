#ifndef EVENT_H
#define EVENT_H

namespace bane {

/// base class for application events
class Event {
public:
  virtual ~Event() {}
  virtual void handle() = 0;
};

/// Placeholder event for testing
class DummyEvent : public Event {
public:
  DummyEvent() {}
  ~DummyEvent() override {}
  void handle() override;
};

//
class ResizeEvent : public Event {
public:
  ResizeEvent() {}
  ~ResizeEvent() override {}
  void handle() override;
};

} // namespace bane

#endif /* EVENT_H */

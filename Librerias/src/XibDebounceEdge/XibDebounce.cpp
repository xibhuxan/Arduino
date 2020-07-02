#include <XibDebounceEdge.h>

XibDebounceEdge::XibDebounceEdge(uint32_t debounceDuration)
{
  this->debounceDuration = debounceDuration;
}

XibDebounceEdge::~XibDebounceEdge() {}

void XibDebounceEdge::whenRisingEdge(bool inputData, void (*f)())
{
  if (inputData != lastInputDataState)
  {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDuration)
  {

    if (inputData != inputDataState)
    {
      inputDataState = inputData;

      if (inputDataState == HIGH)
      {
        f();
      }
    }
  }
  lastInputDataState = inputData;
}

void XibDebounceEdge::whenFallingEdge(bool inputData, void (*f)())
{
  if (inputData != lastInputDataState)
  {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDuration)
  {

    if (inputData != inputDataState)
    {
      inputDataState = inputData;

      if (inputDataState == LOW)
      {
        f();
      }
    }
  }
  lastInputDataState = inputData;
}

void XibDebounceEdge::whenActive(bool inputData, void (*f)())
{
  if (inputData != lastInputDataState)
  {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDuration)
  {

    if (inputData)
    {
      f();
    }
  }
  lastInputDataState = inputData;
}

void XibDebounceEdge::whenDeactive(bool inputData, void (*f)())
{
  if (inputData != lastInputDataState)
  {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDuration)
  {

    if (!inputData)
    {
      f();
    }
  }
  lastInputDataState = inputData;
}

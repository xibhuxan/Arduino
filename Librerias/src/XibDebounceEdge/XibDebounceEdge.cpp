#include <XibDebounceEdge.h>

XibDebounceEdge::XibDebounceEdge(uint16_t debounceDuration)
{
  this->debounceDuration = debounceDuration;
}

XibDebounceEdge::~XibDebounceEdge() {}

//void functions

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

//Bool functions

bool XibDebounceEdge::whenRisingEdge(bool inputData)
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
        lastInputDataState = inputData;
        return true;
      }
    }
    else
    {
      lastInputDataState = inputData;
      return false;
    }
  }
  
}

bool XibDebounceEdge::whenFallingEdge(bool inputData)
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
        lastInputDataState = inputData;
        return true;
      }
    }
    else
    {
      lastInputDataState = inputData;
      return false;
    }
  }
  
}

bool XibDebounceEdge::whenActive(bool inputData)
{
  if (inputData != lastInputDataState)
  {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDuration)
  {
    lastInputDataState = inputData;
    if (inputData)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  
}

bool XibDebounceEdge::whenDeactive(bool inputData)
{
  if (inputData != lastInputDataState)
  {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDuration)
  {
    lastInputDataState = inputData;
    if (!inputData)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  
}
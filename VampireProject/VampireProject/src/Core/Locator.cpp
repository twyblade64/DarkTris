#include "Locator.hpp"

std::unique_ptr<Window> Locator::mWindowService = nullptr;
std::unique_ptr<Time> Locator::mTimeService = nullptr;
std::unique_ptr<Input> Locator::mInputService = nullptr;
std::unique_ptr<ResourceLoader> Locator::mResourceLoaderService = nullptr;
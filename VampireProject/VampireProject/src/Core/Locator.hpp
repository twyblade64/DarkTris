#ifndef HEX_LOCATOR_H_
#define HEX_LOCATOR_H_

#include <memory>
#include "../Services/Window.hpp"
#include "../Services/Time.hpp"
#include "../Services/Input.hpp"
#include "../Services/ResourceLoader.hpp"

class Locator {
public:
    static void InitWindowService(std::unique_ptr<Window> windowService) { mWindowService = std::move(windowService); }
    static Window& GetWindow() { return *mWindowService; }
    static void InitTimeService(std::unique_ptr<Time> timeService) { mTimeService = std::move(timeService); }
    static Time& GetTime() { return *mTimeService; }
    static void InitInputService(std::unique_ptr<Input> inputService) { mInputService = std::move(inputService); }
    static Input& GetInput() { return *mInputService; }
    static void InitResourceLoaderService(std::unique_ptr<ResourceLoader> resourceLoaderService) { mResourceLoaderService = std::move(resourceLoaderService); }
    static ResourceLoader& GetResourceLoader() { return *mResourceLoaderService; }
private:
    static std::unique_ptr<Window> mWindowService;
    static std::unique_ptr<Time> mTimeService;
    static std::unique_ptr<Input> mInputService;
    static std::unique_ptr<ResourceLoader> mResourceLoaderService;
};

#endif // HEX_LOCATOR_H_

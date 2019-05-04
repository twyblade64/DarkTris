#ifndef HEX_TIME_H_
#define HEX_TIME_H_

class Time {
public:
    Time(float fixedUpdateRate, float fixedRenderRate, float currentTime = 0.f):
        mFixedUpdateRate(fixedUpdateRate), mFixedUpdateDeltaTime(1.f/fixedUpdateRate),
        mFixedRenderRate(fixedRenderRate), mFixedRenderDeltaTime(1.f/fixedRenderRate),
        mTotalTime(currentTime), mDeltaTime(0) {}
public:
    void SetFixedUpdateRate(float fixedUpdateRate) { mFixedUpdateRate = fixedUpdateRate; mFixedUpdateDeltaTime = 1.f/fixedUpdateRate; }
    void SetFixedRenderRate(float fixedRenderRate) { mFixedRenderRate = fixedRenderRate; mFixedRenderDeltaTime = 1.f/fixedRenderRate; }
    void UpdateTime(float deltaTime) { mTotalTime += mDeltaTime = deltaTime; }
    void SetTotalTime(float totalTime) { mTotalTime = 0; }
    float GetFixedUpdateRate() { return mFixedUpdateRate; }
    float GetFixedRenderRate() { return mFixedRenderRate; }
    float GetFixedUpdateDeltaTime() { return mFixedUpdateDeltaTime; }
    float GetFixedRenderDeltaTime() { return mFixedRenderDeltaTime; }
    float GetDeltaTime() { return mDeltaTime; }
    float GetTotalTime() { return mTotalTime; }
private:
    float mFixedUpdateRate;
    float mFixedUpdateDeltaTime;
    float mFixedRenderRate;
    float mFixedRenderDeltaTime;
    float mDeltaTime;
    float mTotalTime;
};

#endif // HEX_TIME_H_

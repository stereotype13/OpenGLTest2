#include "clock.h"

namespace VR {
	namespace utils {

		void Clock::addListener(ClockListener* listener) {
			mClockListeners.push_back(listener);
		}

		void Clock::tick() {
			mDeltaTime = std::chrono::duration_cast<milliseconds_type>(HighResolutionClock::now() - mStartTimePoint).count() / 1000.0f;
			mStartTimePoint = HighResolutionClock::now();

			for (const auto& clockListener : mClockListeners)
				clockListener->onTick(mDeltaTime);
		}
	}
}